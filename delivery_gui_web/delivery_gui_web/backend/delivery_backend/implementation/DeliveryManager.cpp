#include "DeliveryManager.h"
#include <iostream>
#include <algorithm>

DeliveryManager::DeliveryManager() :
    urgentDeliveries(MAX_HEAP),
    standardDeliveries(MAX_HEAP),
    fragileDeliveries(MAX_HEAP) {
    ConfigurationManager::initialize(); // Ensure ConfigurationManager is initialized
}

void DeliveryManager::addDelivery(Delivery& delivery) {
    delivery.calculatePriorityScore(); // Calculate initial priority score
    switch (delivery.getType()) {
    case URGENT:
        urgentDeliveries.enqueue(delivery);
        std::cout << "Added urgent delivery: " << delivery.getId() << std::endl;
        break;
    case STANDARD:
        standardDeliveries.enqueue(delivery);
        std::cout << "Added standard delivery: " << delivery.getId() << std::endl;
        break;
    case FRAGILE:
        fragileDeliveries.enqueue(delivery);
        std::cout << "Added fragile delivery: " << delivery.getId() << std::endl;
        break;
    }
}

Delivery DeliveryManager::processNextDelivery() {
    if (!urgentDeliveries.isEmpty()) {
        Delivery processed = urgentDeliveries.dequeue();
        processed.setServiceStartTime(time(0));
        time_t serviceEndTime = time(0) + (rand() % 10 + 5);
        processed.setServiceEndTime(serviceEndTime);
        processedDeliveries.push_back(processed);
        return processed;
    }
    else if (!fragileDeliveries.isEmpty()) {
        Delivery processed = fragileDeliveries.dequeue();
        processed.setServiceStartTime(time(0));
        time_t serviceEndTime = time(0) + (rand() % 10 + 5);
        processed.setServiceEndTime(serviceEndTime);
        processedDeliveries.push_back(processed);
        return processed;
    }
    else if (!standardDeliveries.isEmpty()) {
        Delivery processed = standardDeliveries.dequeue();
        processed.setServiceStartTime(time(0));
        time_t serviceEndTime = time(0) + (rand() % 10 + 5);
        processed.setServiceEndTime(serviceEndTime);
        processedDeliveries.push_back(processed);
        return processed;
    }
    else {
        throw std::out_of_range("No deliveries to process.");
    }
}

bool DeliveryManager::hasDeliveries() const {
    return !urgentDeliveries.isEmpty() || !standardDeliveries.isEmpty() || !fragileDeliveries.isEmpty();
}

void DeliveryManager::updatePriorities() {
    std::vector<Delivery> tempDeliveries;

    while (!urgentDeliveries.isEmpty()) {
        tempDeliveries.push_back(urgentDeliveries.dequeue());
    }
    while (!standardDeliveries.isEmpty()) {
        tempDeliveries.push_back(standardDeliveries.dequeue());
    }
    while (!fragileDeliveries.isEmpty()) {
        tempDeliveries.push_back(fragileDeliveries.dequeue());
    }

    for (auto& delivery : tempDeliveries) {
        delivery.calculatePriorityScore();
        delivery.boostPriority();

        switch (delivery.getType()) {
        case URGENT:
            urgentDeliveries.enqueue(delivery);
            break;
        case STANDARD:
            standardDeliveries.enqueue(delivery);
            break;
        case FRAGILE:
            fragileDeliveries.enqueue(delivery);
            break;
        }
    }
}

void DeliveryManager::mergeQueues() {
    if (urgentDeliveries.isEmpty() && !standardDeliveries.isEmpty()) {
        std::cout << "VIP queue is now empty. Redirecting individuals from regular queue to VIP service counter." << std::endl;
        while (!standardDeliveries.isEmpty()) {
            urgentDeliveries.enqueue(standardDeliveries.dequeue());
        }
    }
    if (urgentDeliveries.isEmpty() && !fragileDeliveries.isEmpty()) {
        std::cout << "Fragile queue is now empty. Redirecting individuals from fragile queue to urgent service counter." << std::endl;
        while (!fragileDeliveries.isEmpty()) {
            urgentDeliveries.enqueue(fragileDeliveries.dequeue());
        }
    }
}

void DeliveryManager::applyFairnessBoost() {
    updatePriorities();
}

//  Cancel delivery by ID
bool DeliveryManager::cancelDeliveryById(const std::string& id) {
    std::vector<Delivery> tempUrgent, tempStandard, tempFragile;
    bool found = false;

    auto searchQueue = [&](PriorityQueue<Delivery>& queue, std::vector<Delivery>& temp) {
        while (!queue.isEmpty()) {
            Delivery d = queue.dequeue();
            if (!found && d.getId() == id) {
                cancelledStack.push(d);
                found = true;
            }
            else {
                temp.push_back(d);
            }
        }
        };

    searchQueue(urgentDeliveries, tempUrgent);
    searchQueue(standardDeliveries, tempStandard);
    searchQueue(fragileDeliveries, tempFragile);

    for (const auto& d : tempUrgent) urgentDeliveries.enqueue(d);
    for (const auto& d : tempStandard) standardDeliveries.enqueue(d);
    for (const auto& d : tempFragile) fragileDeliveries.enqueue(d);

    return found;
}

//  View cancelled deliveries log
void DeliveryManager::viewCancelledDeliveries() const {
    if (cancelledStack.empty()) {
        std::cout << "No cancelled deliveries.\n";
        return;
    }

    std::cout << "\n--- Cancelled Deliveries Log (Most recent first) ---\n";
    std::stack<Delivery> temp = cancelledStack;
    while (!temp.empty()) {
        temp.top().print();
        temp.pop();
    }
}

void DeliveryManager::printQueuedDeliveriesWithScores() const {
    std::cout << "--- Queued Deliveries with Scores ---" << std::endl;
    auto printQueue = [](const PriorityQueue<Delivery>& queue, const std::string& label) {
        std::vector<Delivery> items = queue.getInternalData();
        std::cout << label << " (" << items.size() << " deliveries):" << std::endl;
        for (const auto& d : items) {
            std::cout << "ID: " << d.getId() << ", Score: " << d.getPriorityScore() << std::endl;
        }
    };
    printQueue(urgentDeliveries, "Urgent");
    printQueue(standardDeliveries, "Standard");
    printQueue(fragileDeliveries, "Fragile");
}
