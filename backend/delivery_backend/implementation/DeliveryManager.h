#ifndef DELIVERY_MANAGER_H
#define DELIVERY_MANAGER_H

#include "Delivery.h"
#include "PriorityQueue.h"
#include "ConfigurationManager.h"
#include <string>
#include <vector>
#include <map>
#include <stack> //  For Cancelled Deliveries Log

class DeliveryManager
{
private:
    PriorityQueue<Delivery> urgentDeliveries;
    PriorityQueue<Delivery> standardDeliveries;
    PriorityQueue<Delivery> fragileDeliveries;
    std::vector<Delivery> processedDeliveries; // To store processed deliveries for reporting

    std::stack<Delivery> cancelledStack; //  Stack to store cancelled deliveries in LIFO order

public:
    void printQueuedDeliveriesWithScores() const;
    DeliveryManager();

    // === Core Delivery Operations ===
    void addDelivery(Delivery &delivery);
    Delivery processNextDelivery();
    bool hasDeliveries() const;

    // === Queue Management ===
    void updatePriorities();   // Recalculates and repositions based on score
    void mergeQueues();        // Handles fallback merging when queues are empty
    void applyFairnessBoost(); // Boosts long-waiting deliveries

    // === Cancelled Delivery Feature ===
    bool cancelDeliveryById(const std::string &id); //  Cancels and logs
    void viewCancelledDeliveries() const;           //  Displays from stack

    // === Metrics Access ===
    int getUrgentQueueSize() const { return urgentDeliveries.size(); }
    int getStandardQueueSize() const { return standardDeliveries.size(); }
    int getFragileQueueSize() const { return fragileDeliveries.size(); }
    int getTotalQueueSize() const { return urgentDeliveries.size() + standardDeliveries.size() + fragileDeliveries.size(); }
    const std::vector<Delivery> &getProcessedDeliveries() const { return processedDeliveries; }
};

#endif // DELIVERY_MANAGER_H
