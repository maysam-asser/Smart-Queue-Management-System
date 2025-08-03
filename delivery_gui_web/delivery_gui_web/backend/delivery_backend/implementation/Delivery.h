#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <iostream>
#include <ostream>
#include <ctime>
#include "ConfigurationManager.h"
#include "DeliveryTypes.h" // Include the common enum definition

class Delivery
{
public:
    std::string deliveryId;
    std::string destination;
    double priorityScore; // Changed to double for more precise calculations
    DeliveryType deliveryType;
    int estimatedDeliveryTime; // in minutes
    time_t entryTime;          // Time when the delivery was created/entered the system
    time_t serviceStartTime;   // Added for tracking service start time
    time_t serviceEndTime;     // Added for tracking service end time

    Delivery(std::string id, std::string dest, DeliveryType type, int estTime) : deliveryId(id),
                                                                                 destination(dest),
                                                                                 deliveryType(type),
                                                                                 estimatedDeliveryTime(estTime),
                                                                                 priorityScore(0.0),
                                                                                 entryTime(time(0)),
                                                                                 serviceStartTime(0),
                                                                                 serviceEndTime(0)
    {
        // Initial priority score calculation will be done via calculatePriorityScore method
    }

    // Getters
    std::string getId() const { return deliveryId; }
    DeliveryType getType() const { return deliveryType; }
    double getPriorityScore() const { return priorityScore; }
    time_t getEntryTime() const { return entryTime; }
    time_t getServiceStartTime() const { return serviceStartTime; }
    time_t getServiceEndTime() const { return serviceEndTime; }

    // Setters
    void setServiceStartTime(time_t t) { serviceStartTime = t; }
    void setServiceEndTime(time_t t) { serviceEndTime = t; }

    // New methods for priority calculation and boosting
    void calculatePriorityScore()
    {
        float urgency_weight = ConfigurationManager::getWeight("urgency");
        float waiting_time_weight = ConfigurationManager::getWeight("waiting_time");
        float service_type_weight = ConfigurationManager::getWeight("service_type");

        int service_type_score = ConfigurationManager::getServiceTypeScore(this->deliveryType);

        time_t current_time = time(0);
        double seconds_waited = difftime(current_time, this->entryTime);
        int current_waiting_time = static_cast<int>(seconds_waited / 60.0);

        int urgency_level = 0;
        switch (this->deliveryType)
        {
        case URGENT:
            urgency_level = 5;
            break;
        case FRAGILE:
            urgency_level = 4;
            break;
        case STANDARD:
            urgency_level = 3;
            break;
        }

        this->priorityScore =
            (urgency_level * urgency_weight) +
            (current_waiting_time * waiting_time_weight) +
            (service_type_score * service_type_weight);
    }

    void boostPriority()
    {
        time_t current_time = time(0);
        double seconds_waited = difftime(current_time, this->entryTime);
        int current_waiting_time = static_cast<int>(seconds_waited / 60.0);

        int max_wait_time = ConfigurationManager::getMaxWaitTime();
        double boost_multiplier = ConfigurationManager::getBoostMultiplier();

        if (current_waiting_time > max_wait_time)
        {
            double extra_waiting_time = current_waiting_time - max_wait_time;
            double fairness_boost = extra_waiting_time * boost_multiplier;
            this->priorityScore += fairness_boost;
        }
    }

    double getWaitingTime(time_t now) const
    {
        return difftime(now, entryTime) / 60.0;
    }

    // Operator overloads for comparison (MaxHeap uses >)
    bool operator<(const Delivery &other) const
    {
        return priorityScore < other.priorityScore;
    }

    bool operator>(const Delivery &other) const
    {
        return priorityScore > other.priorityScore;
    }

    void print() const
    {
        std::cout << "Delivery ID: " << deliveryId
                  << ", Destination: " << destination
                  << ", Type: ";
        switch (deliveryType)
        {
        case URGENT:
            std::cout << "URGENT";
            break;
        case STANDARD:
            std::cout << "STANDARD";
            break;
        case FRAGILE:
            std::cout << "FRAGILE";
            break;
        }
        std::cout << ", Est. Time: " << estimatedDeliveryTime << " min"
                  << ", Priority Score: " << priorityScore << std::endl;
    }
};

#endif // DELIVERY_H
