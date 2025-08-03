


#include "DeliveryManager.h"
#include <iostream>

void DeliveryManager::addDelivery(const Delivery& delivery) {
    switch (delivery.deliveryType) {
        case URGENT:
            urgentDeliveries.enqueue(delivery);
            std::cout << "Added urgent delivery: " << delivery.deliveryId << std::endl;
            break;
        case STANDARD:
            standardDeliveries.enqueue(delivery);
            std::cout << "Added standard delivery: " << delivery.deliveryId << std::endl;
            break;
        case FRAGILE:
            fragileDeliveries.enqueue(delivery);
            std::cout << "Added fragile delivery: " << delivery.deliveryId << std::endl;
            break;
    }
}

Delivery DeliveryManager::processNextDelivery() {
    // Simple logic: prioritize urgent, then fragile, then standard
    if (!urgentDeliveries.isEmpty()) {
        return urgentDeliveries.dequeue();
    } else if (!fragileDeliveries.isEmpty()) {
        return fragileDeliveries.dequeue();
    } else if (!standardDeliveries.isEmpty()) {
        return standardDeliveries.dequeue();
    } else {
        throw std::out_of_range("No deliveries to process.");
    }
}

bool DeliveryManager::hasDeliveries() const {
    return !urgentDeliveries.isEmpty() || !standardDeliveries.isEmpty() || !fragileDeliveries.isEmpty();
}


