// Delivery Management System - Frontend JavaScript

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
        this.updateDisplay();
        
        // Update time every second
        setInterval(() => this.updateTime(), 1000);
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

    updateTime() {
        const now = new Date();
        const timeString = now.toLocaleTimeString();
        document.getElementById('current-time').textContent = timeString;
    }

    addDelivery() {
        const form = document.getElementById('delivery-form');
        const formData = new FormData(form);
        
        const delivery = {
            id: formData.get('deliveryId'),
            destination: formData.get('destination'),
            type: formData.get('deliveryType'),
            estimatedTime: parseInt(formData.get('estimatedTime')),
            timestamp: new Date(),
            priorityScore: this.calculatePriorityScore(formData.get('deliveryType'), parseInt(formData.get('estimatedTime')))
        };

        // Add to appropriate queue
        const queueType = delivery.type.toLowerCase();
        this.deliveries[queueType].push(delivery);
        
        // Sort by priority score (highest first)
        this.deliveries[queueType].sort((a, b) => b.priorityScore - a.priorityScore);

        this.updateDisplay();
        this.clearForm();
        this.showMessage(`Delivery ${delivery.id} added successfully!`, 'success');
        this.updateStatus(`Added ${delivery.type.toLowerCase()} delivery: ${delivery.id}`);
    }

    calculatePriorityScore(type, estimatedTime) {
        let baseScore = 0;
        
        switch (type) {
            case 'URGENT':
                baseScore = 100;
                break;
            case 'FRAGILE':
                baseScore = 75;
                break;
            case 'STANDARD':
                baseScore = 50;
                break;
        }
        
        // Lower estimated time increases priority
        const timeScore = Math.max(0, 200 - estimatedTime);
        return baseScore + timeScore;
    }

    processNextDelivery() {
        let nextDelivery = null;
        let sourceQueue = null;

        // Priority: Urgent > Fragile > Standard
        if (this.deliveries.urgent.length > 0) {
            nextDelivery = this.deliveries.urgent.shift();
            sourceQueue = 'urgent';
        } else if (this.deliveries.fragile.length > 0) {
            nextDelivery = this.deliveries.fragile.shift();
            sourceQueue = 'fragile';
        } else if (this.deliveries.standard.length > 0) {
            nextDelivery = this.deliveries.standard.shift();
            sourceQueue = 'standard';
        }

        if (nextDelivery) {
            this.currentDelivery = nextDelivery;
            this.processedDeliveries.unshift(nextDelivery);
            
            // Keep only last 5 processed deliveries
            if (this.processedDeliveries.length > 5) {
                this.processedDeliveries.pop();
            }

            this.updateDisplay();
            this.updateStatus(`Processing ${nextDelivery.type.toLowerCase()} delivery: ${nextDelivery.id}`);
            
            // Simulate processing time
            setTimeout(() => {
                this.currentDelivery = null;
                this.updateDisplay();
                this.updateStatus(`Completed delivery: ${nextDelivery.id}`);
            }, 2000);
        } else {
            this.showMessage('No deliveries to process!', 'error');
            this.updateStatus('No deliveries available for processing');
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
        
        this.processedDeliveries.forEach(delivery => {
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
    new DeliveryGUI();
});

// Add some sample data for demonstration
document.addEventListener('DOMContentLoaded', () => {
    setTimeout(() => {
        const gui = window.deliveryGUI = new DeliveryGUI();
        
        // Add some sample deliveries for demonstration
        const sampleDeliveries = [
            { deliveryId: 'D001', destination: '123 Main St', deliveryType: 'STANDARD', estimatedTime: 60 },
            { deliveryId: 'D002', destination: '456 Oak Ave', deliveryType: 'URGENT', estimatedTime: 30 },
            { deliveryId: 'D003', destination: '789 Pine Ln', deliveryType: 'FRAGILE', estimatedTime: 90 }
        ];
        
        // Uncomment the following lines to add sample data automatically
        /*
        sampleDeliveries.forEach((delivery, index) => {
            setTimeout(() => {
                Object.keys(delivery).forEach(key => {
                    const element = document.getElementById(key.replace(/([A-Z])/g, '-$1').toLowerCase());
                    if (element) element.value = delivery[key];
                });
                gui.addDelivery();
            }, (index + 1) * 500);
        });
        */
    }, 100);
});

