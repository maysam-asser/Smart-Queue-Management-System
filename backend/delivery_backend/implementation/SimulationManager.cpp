#include "SimulationManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

void SimulationManager::runSimulation()
{
    int duration = ConfigurationManager::getSimulationDuration();
    float arrivalRate = ConfigurationManager::getSimulationArrivalRate();
    int serviceCounters = ConfigurationManager::getSimulationCounters();

    std::cout << "Starting simulation for " << duration << " minutes with arrival rate " << arrivalRate << " and " << serviceCounters << " counters." << std::endl;

    for (currentSimTime = 0; currentSimTime < duration; ++currentSimTime)
    {
        std::cout << "\n--- Time: " << currentSimTime << " minutes ---\n";

        // 1. Generate new arrivals
        if ((static_cast<float>(rand()) / RAND_MAX) < arrivalRate)
        {
            Delivery new_delivery = generateRandomDelivery();
            deliveryManager.addDelivery(new_delivery);
            std::cout << "New Arrival: ID=" << new_delivery.deliveryId << " (P=" << new_delivery.priorityScore << ")" << std::endl;
        }

        // 2. Process deliveries
        for (int i = 0; i < serviceCounters; ++i)
        {
            if (deliveryManager.hasDeliveries())
            {
                Delivery processed_delivery = deliveryManager.processNextDelivery();
                processed_delivery.setServiceEndTime(time(0)); // Set service end time
                std::cout << "Processed: ID=" << processed_delivery.deliveryId << " (P=" << processed_delivery.priorityScore << ")" << std::endl;
            }
            else
            {
                break;
            }
        }

        // 3. Update priorities and apply fairness boost
        deliveryManager.updatePriorities();

        // 4. Merge queues if necessary
        deliveryManager.mergeQueues();

        // 5. Display queue states
        std::cout << "Urgent Queue Size: " << deliveryManager.getUrgentQueueSize() << std::endl;
        std::cout << "Standard Queue Size: " << deliveryManager.getStandardQueueSize() << std::endl;
        std::cout << "Fragile Queue Size: " << deliveryManager.getFragileQueueSize() << std::endl;

        // Optional: slow down simulation for readability
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Simulation finished." << std::endl;
    reportManager.generateReport();
}

Delivery SimulationManager::generateRandomDelivery()
{
    std::string id = "D" + std::to_string(rand() % 10000);
    std::string dest = "Random Destination";
    DeliveryType type = static_cast<DeliveryType>(rand() % 3);
    int estTime = rand() % 120 + 10; // 10 to 129 minutes
    return Delivery(id, dest, type, estTime);
}
