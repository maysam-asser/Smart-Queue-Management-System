#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <iostream> // For std::cout and std::endl
#include <ostream> // For std::endl (though usually covered by iostream)

enum DeliveryType {
    URGENT,
    STANDARD,
    FRAGILE
};

class Delivery {
public:
    std::string deliveryId;
    std::string destination;
    int priorityScore; // Higher score means higher priority
    DeliveryType deliveryType;
    int estimatedDeliveryTime; // in minutes

    Delivery(std::string id, std::string dest, DeliveryType type, int estTime) :
        deliveryId(id),
        destination(dest),
        deliveryType(type),
        estimatedDeliveryTime(estTime),
        priorityScore(0) // Initialize to 0, will be calculated later
    {
        // Calculate initial priority score based on delivery type
        switch (deliveryType) {
            case URGENT:
                priorityScore += 100;
                break;
            case STANDARD:
                priorityScore += 50;
                break;
            case FRAGILE:
                priorityScore += 75; // Fragile might also be urgent
                break;
        }
        // A lower estimated delivery time could also increase priority
        // This is a simple example, a more complex formula can be used
        priorityScore += (200 - estimatedDeliveryTime); // Max 200, min 0 for time
    }

    // Overload < operator for MinHeap (e.g., for sorting by estimatedDeliveryTime)
    // For MinHeap, we want the 'smallest' delivery to be the one with the lowest estimated delivery time
    bool operator<(const Delivery& other) const {
        return estimatedDeliveryTime < other.estimatedDeliveryTime;
    }

    // Overload > operator for MaxHeap (e.g., for sorting by priorityScore)
    // For MaxHeap, we want the 'largest' delivery to be the one with the highest priorityScore
    bool operator>(const Delivery& other) const {
        return priorityScore > other.priorityScore;
    }

    // For printing delivery information
    void print() const {
        std::cout << "Delivery ID: " << deliveryId
                  << ", Destination: " << destination
                  << ", Type: ";
        switch (deliveryType) {
            case URGENT: std::cout << "URGENT"; break;
            case STANDARD: std::cout << "STANDARD"; break;
            case FRAGILE: std::cout << "FRAGILE"; break;
        }
        std::cout << ", Est. Time: " << estimatedDeliveryTime << " min"
                  << ", Priority Score: " << priorityScore << std::endl;
    }
};

#endif // DELIVERY_H


