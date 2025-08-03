


#ifndef DELIVERY_MANAGER_H
#define DELIVERY_MANAGER_H

#include "Delivery.h"
#include "PriorityQueue.h"
#include <string>
#include <map>

class DeliveryManager {
private:
    // Using a map to hold different priority queues for different delivery types
    // For simplicity, we'll use a MaxHeap for all deliveries, prioritizing by priorityScore
    // In a more complex system, you might have different queues for different criteria.
    PriorityQueue<Delivery> urgentDeliveries; // MaxHeap based on priorityScore
    PriorityQueue<Delivery> standardDeliveries; // MaxHeap based on priorityScore
    PriorityQueue<Delivery> fragileDeliveries; // MaxHeap based on priorityScore

public:
    DeliveryManager() :
        urgentDeliveries(MAX_HEAP),
        standardDeliveries(MAX_HEAP),
        fragileDeliveries(MAX_HEAP) {}

    // Add a new delivery to the appropriate queue
    void addDelivery(const Delivery& delivery);

    // Process the next highest priority delivery across all queues
    // This is a simplified approach; a real system would have more complex logic
    // to decide which queue to pull from next.
    Delivery processNextDelivery();

    // Check if there are any pending deliveries
    bool hasDeliveries() const;

    // Get the number of deliveries in each queue
    int getUrgentQueueSize() const { return urgentDeliveries.size(); }
    int getStandardQueueSize() const { return standardDeliveries.size(); }
    int getFragileQueueSize() const { return fragileDeliveries.size(); }
};

#endif // DELIVERY_MANAGER_H


