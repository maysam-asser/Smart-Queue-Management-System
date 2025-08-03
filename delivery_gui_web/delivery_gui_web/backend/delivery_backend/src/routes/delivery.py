from flask import Blueprint, request, jsonify
from flask_cors import cross_origin
import json
import subprocess
import tempfile
import os

delivery_bp = Blueprint('delivery', __name__)

# In-memory storage for deliveries (in a real app, this would be a database)
deliveries = {
    'urgent': [],
    'fragile': [],
    'standard': []
}
processed_deliveries = []

@delivery_bp.route('/deliveries', methods=['GET'])
@cross_origin()
def get_deliveries():
    """Get all deliveries in queues"""
    return jsonify({
        'deliveries': deliveries,
        'processed': processed_deliveries
    })

@delivery_bp.route('/deliveries', methods=['POST'])
@cross_origin()
def add_delivery():
    """Add a new delivery"""
    try:
        data = request.get_json()
        
        # Validate required fields
        required_fields = ['id', 'destination', 'type', 'estimatedTime']
        for field in required_fields:
            if field not in data:
                return jsonify({'error': f'Missing required field: {field}'}), 400
        
        # Calculate priority score
        priority_score = calculate_priority_score(data['type'], data['estimatedTime'])
        
        delivery = {
            'id': data['id'],
            'destination': data['destination'],
            'type': data['type'],
            'estimatedTime': data['estimatedTime'],
            'priorityScore': priority_score,
            'timestamp': data.get('timestamp')
        }
        
        # Add to appropriate queue
        queue_type = data['type'].lower()
        if queue_type in deliveries:
            deliveries[queue_type].append(delivery)
            # Sort by priority score (highest first)
            deliveries[queue_type].sort(key=lambda x: x['priorityScore'], reverse=True)
            
            return jsonify({
                'message': f'Delivery {delivery["id"]} added successfully',
                'delivery': delivery
            }), 201
        else:
            return jsonify({'error': 'Invalid delivery type'}), 400
            
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@delivery_bp.route('/deliveries/process', methods=['POST'])
@cross_origin()
def process_delivery():
    """Process the next highest priority delivery"""
    try:
        # Priority: Urgent > Fragile > Standard
        next_delivery = None
        source_queue = None
        
        if deliveries['urgent']:
            next_delivery = deliveries['urgent'].pop(0)
            source_queue = 'urgent'
        elif deliveries['fragile']:
            next_delivery = deliveries['fragile'].pop(0)
            source_queue = 'fragile'
        elif deliveries['standard']:
            next_delivery = deliveries['standard'].pop(0)
            source_queue = 'standard'
        
        if next_delivery:
            # Add to processed deliveries
            processed_deliveries.insert(0, next_delivery)
            
            # Keep only last 10 processed deliveries
            if len(processed_deliveries) > 10:
                processed_deliveries.pop()
            
            return jsonify({
                'message': f'Processing delivery {next_delivery["id"]}',
                'delivery': next_delivery,
                'source_queue': source_queue
            }), 200
        else:
            return jsonify({'error': 'No deliveries to process'}), 404
            
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@delivery_bp.route('/deliveries/stats', methods=['GET'])
@cross_origin()
def get_stats():
    """Get delivery statistics"""
    try:
        total_pending = sum(len(queue) for queue in deliveries.values())
        total_processed = len(processed_deliveries)
        
        stats = {
            'pending': {
                'urgent': len(deliveries['urgent']),
                'fragile': len(deliveries['fragile']),
                'standard': len(deliveries['standard']),
                'total': total_pending
            },
            'processed': total_processed,
            'total': total_pending + total_processed
        }
        
        return jsonify(stats), 200
        
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@delivery_bp.route('/deliveries/cpp-process', methods=['POST'])
@cross_origin()
def cpp_process_delivery():
    """Process delivery using the C++ backend (demonstration)"""
    try:
        # This would compile and run the C++ code with current deliveries
        # For now, we'll simulate it by calling the regular process function
        return process_delivery()
        
    except Exception as e:
        return jsonify({'error': str(e)}), 500

def calculate_priority_score(delivery_type, estimated_time):
    """Calculate priority score based on delivery type and estimated time"""
    base_score = 0
    
    if delivery_type == 'URGENT':
        base_score = 100
    elif delivery_type == 'FRAGILE':
        base_score = 75
    elif delivery_type == 'STANDARD':
        base_score = 50
    
    # Lower estimated time increases priority
    time_score = max(0, 200 - estimated_time)
    return base_score + time_score

