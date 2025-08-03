#include "AdminConsole.h"
#include "ConfigurationManager.h"
#include <iostream>

AdminConsole::AdminConsole(DeliveryManager &dm, SimulationManager &sm, ReportManager &rm)
    : deliveryManager(dm), simulationManager(sm), reportManager(rm) {}

void AdminConsole::start()
{
    std::cout << "[DEBUG] AdminConsole::start() loaded\n"; //  Debug confirmation

    int choice;
    do
    {
        std::cout << "\n--- Smart Queue Management System ---\n";
        std::cout << "1. Configure System Parameters\n";
        std::cout << "2. Run Simulation\n";
        std::cout << "3. View Stats\n";
        std::cout << "4. Modify Queue Policies\n";
        std::cout << "5. Generate Report\n";
        std::cout << "6. Add Delivery\n";
        std::cout << "7. Cancel Delivery\n";               // New menu option
        std::cout << "8. View Cancelled Deliveries Log\n"; //  New menu option
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            ConfigurationManager::configure();
            break;
        case 2:
            simulationManager.runSimulation();
            break;
        case 3:
            viewStats();
            break;
        case 4:
            modifyQueuePolicies();
            break;
        case 5:
            generateReport();
            break;
        case 6:
            addDelivery();
            break;
        case 7:
            cancelDelivery(); // Cancel delivery
            break;
        case 8:
            deliveryManager.viewCancelledDeliveries(); //  View cancelled log
            break;
        case 9:
            std::cout << "Exiting Admin Console.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 9);
}

void AdminConsole::viewStats()
{
    std::cout << "\n=== Current System Stats ===\n";
    std::cout << "Total Deliveries Processed: " << simulationManager.getProcessedDeliveriesCount() << "\n";
    std::cout << "Number of Deliveries in Queue: " << simulationManager.getQueueSize() << "\n";
    std::cout << "Urgent Queue Size: " << deliveryManager.getUrgentQueueSize() << "\n";
    std::cout << "Standard Queue Size: " << deliveryManager.getStandardQueueSize() << "\n";
    std::cout << "Fragile Queue Size: " << deliveryManager.getFragileQueueSize() << "\n";
}

void AdminConsole::modifyQueuePolicies()
{
    std::cout << "\nEnter new max wait time for fairness boost: ";
    int newMaxWaitTime;
    std::cin >> newMaxWaitTime;
    ConfigurationManager::setMaxWaitTime(newMaxWaitTime);

    std::cout << "Enter new number of service counters: ";
    int newServiceCounters;
    std::cin >> newServiceCounters;
    ConfigurationManager::setServiceCounters(newServiceCounters);

    std::cout << "Queue policies updated.\n";
}

void AdminConsole::generateReport()
{
    std::string filterType, sortCriteria;
    std::cout << "\nEnter filter type (urgent/standard/fragile or leave empty): ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, filterType);

    std::cout << "Enter sort criteria (waiting_time or leave empty for priority): ";
    std::getline(std::cin, sortCriteria);

    reportManager.generateReport(filterType, sortCriteria);
}

void AdminConsole::addDelivery()
{
    std::string id, dest;
    int type_int, est_time;
    std::cout << "Enter Delivery ID: ";
    std::cin >> id;
    std::cout << "Enter Destination: ";
    std::cin >> dest;
    std::cout << "Enter Delivery Type (0=URGENT, 1=STANDARD, 2=FRAGILE): ";
    std::cin >> type_int;
    std::cout << "Enter Estimated Time (minutes): ";
    std::cin >> est_time;

    DeliveryType type = static_cast<DeliveryType>(type_int);
    Delivery new_delivery(id, dest, type, est_time);
    deliveryManager.addDelivery(new_delivery);

    deliveryManager.printQueuedDeliveriesWithScores();
    std::cout << "Delivery added successfully.\n";
}

void AdminConsole::cancelDelivery()
{
    std::string id;
    std::cout << "Enter Delivery ID to cancel: ";
    std::cin >> id;

    if (deliveryManager.cancelDeliveryById(id))
    {
        std::cout << "Delivery " << id << " cancelled and logged.\n";
    }
    else
    {
        std::cout << "Delivery ID not found in any active queue.\n";
    }
}
