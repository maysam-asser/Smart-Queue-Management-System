// Delivery Management System - Frontend JavaScript with Backend Integration

class DeliveryGUI {
    constructor() {
        this.deliveries = {
            urgent: [],
            fragile: [],
            standard: []
        };
        this.processedDeliveries = [];
        this.currentDelivery = null;
        
        this.initializeEventListeners();
        this.updateTime();
        this.loadDeliveries();
        
        // Update time every second
        setInterval(() => this.updateTime(), 1000);
        
        // Refresh data every 5 seconds
        setInterval(() => this.loadDeliveries(), 5000);
    }

    initializeEventListeners() {
        // Form submission
        document.getElementById('delivery-form').addEventListener('submit', (e) => {
            e.preventDefault();
            this.addDelivery();
        });

        // Clear form button
        document.getElementById('clear-form').addEventListener('click', () => {
            this.clearForm();
        });

        // Process delivery button
        document.getElementById('process-delivery').addEventListener('click', () => {
            this.processNextDelivery();
        });
    }

    async loadDeliveries() {
        try {
            const response = await fetch('/api/deliveries');
            if (response.ok) {
                const data = await response.json();
                this.deliveries = data.deliveries;
                this.processedDeliveries = data.processed;
                this.updateDisplay();
            }
        } catch (error) {
            console.error('Error loading deliveries:', error);
        }
    }

    updateTime() {
        const now = new Date();
        const timeString = now.toLocaleTimeString();
        document.getElementById('current-time').textContent = timeString;
    }

    async addDelivery() {
        const form = document.getElementById('delivery-form');
        const formData = new FormData(form);
        
        const delivery = {
            id: formData.get('deliveryId'),
            destination: formData.get('destination'),
            type: formData.get('deliveryType'),
            estimatedTime: parseInt(formData.get('estimatedTime')),
            timestamp: new Date().toISOString()
        };

        try {
            const response = await fetch('/api/deliveries', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(delivery)
            });

            if (response.ok) {
                const result = await response.json();
                this.showMessage(result.message, 'success');
                this.updateStatus(`Added ${delivery.type.toLowerCase()} delivery: ${delivery.id}`);
                this.clearForm();
                this.loadDeliveries(); // Refresh data
            } else {
                const error = await response.json();
                this.showMessage(error.error || 'Failed to add delivery', 'error');
            }
        } catch (error) {
            console.error('Error adding delivery:', error);
            this.showMessage('Network error: Failed to add delivery', 'error');
        }
    }

    async processNextDelivery() {
        try {
            const response = await fetch('/api/deliveries/process', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                }
            });

            if (response.ok) {
                const result = await response.json();
                this.currentDelivery = result.delivery;
                this.updateStatus(`Processing ${result.delivery.type.toLowerCase()} delivery: ${result.delivery.id}`);
                this.updateDisplay();
                
                // Simulate processing time
                setTimeout(() => {
                    this.currentDelivery = null;
                    this.updateDisplay();
                    this.updateStatus(`Completed delivery: ${result.delivery.id}`);
                    this.loadDeliveries(); // Refresh data
                }, 2000);
            } else {
                const error = await response.json();
                this.showMessage(error.error || 'Failed to process delivery', 'error');
                this.updateStatus('No deliveries available for processing');
            }
        } catch (error) {
            console.error('Error processing delivery:', error);
            this.showMessage('Network error: Failed to process delivery', 'error');
        }
    }

    updateDisplay() {
        this.updateQueueDisplays();
        this.updateProcessingArea();
        this.updateStatistics();
    }

    updateQueueDisplays() {
        const queueTypes = ['urgent', 'fragile', 'standard'];
        
        queueTypes.forEach(type => {
            const container = document.getElementById(`${type}-deliveries`);
            const sizeElement = document.getElementById(`${type}-size`);
            
            container.innerHTML = '';
            sizeElement.textContent = this.deliveries[type].length;
            
            this.deliveries[type].forEach(delivery => {
                const card = this.createDeliveryCard(delivery);
                container.appendChild(card);
            });
        });
    }

    createDeliveryCard(delivery) {
        const card = document.createElement('div');
        card.className = `delivery-card ${delivery.type.toLowerCase()} new`;
        
        card.innerHTML = `
            <div class="delivery-id">${delivery.id}</div>
            <div class="delivery-destination">${delivery.destination}</div>
            <div class="delivery-details">
                <span>${delivery.estimatedTime} min</span>
                <span class="priority-score">Score: ${delivery.priorityScore}</span>
            </div>
        `;
        
        // Remove animation class after animation completes
        setTimeout(() => card.classList.remove('new'), 300);
        
        return card;
    }

    updateProcessingArea() {
        const currentDeliveryElement = document.getElementById('current-delivery');
        const processButton = document.getElementById('process-delivery');
        
        if (this.currentDelivery) {
            currentDeliveryElement.innerHTML = `
                <div class="delivery-id">${this.currentDelivery.id}</div>
                <div class="delivery-destination">${this.currentDelivery.destination}</div>
                <div class="delivery-details">
                    <span>Type: ${this.currentDelivery.type}</span>
                    <span>Est. Time: ${this.currentDelivery.estimatedTime} min</span>
                </div>
                <div style="margin-top: 0.5rem; color: #059669; font-weight: bold;">Processing...</div>
            `;
            processButton.disabled = true;
        } else {
            currentDeliveryElement.innerHTML = '<p>No delivery being processed</p>';
            processButton.disabled = false;
        }

        // Update recent activity
        const recentContainer = document.getElementById('recent-deliveries');
        recentContainer.innerHTML = '';
        
        this.processedDeliveries.slice(0, 5).forEach(delivery => {
            const item = document.createElement('div');
            item.className = 'activity-item';
            item.textContent = `${delivery.id} - ${delivery.destination} (${delivery.type})`;
            recentContainer.appendChild(item);
        });
    }

    updateStatistics() {
        const totalPending = this.deliveries.urgent.length + 
                           this.deliveries.fragile.length + 
                           this.deliveries.standard.length;
        
        document.getElementById('processed-count').textContent = this.processedDeliveries.length;
        document.getElementById('pending-count').textContent = totalPending;
        document.getElementById('total-deliveries').textContent = `Total Deliveries: ${totalPending + this.processedDeliveries.length}`;
    }

    clearForm() {
        document.getElementById('delivery-form').reset();
    }

    showMessage(text, type) {
        // Remove existing messages
        const existingMessages = document.querySelectorAll('.message');
        existingMessages.forEach(msg => msg.remove());
        
        const message = document.createElement('div');
        message.className = `message ${type}`;
        message.textContent = text;
        
        const form = document.getElementById('delivery-form');
        form.insertBefore(message, form.firstChild);
        
        // Remove message after 3 seconds
        setTimeout(() => message.remove(), 3000);
    }

    updateStatus(text) {
        document.getElementById('status-message').textContent = 'Ready';
        document.getElementById('last-action').textContent = text;
    }
}

// Initialize the application when the page loads
document.addEventListener('DOMContentLoaded', () => {
    window.deliveryGUI = new DeliveryGUI();
});

