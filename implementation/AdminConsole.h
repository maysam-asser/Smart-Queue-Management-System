#ifndef ADMINCONSOLE_H
#define ADMINCONSOLE_H

#include <vector>
#include <string>
#include "DeliveryManager.h"
#include "SimulationManager.h"
#include "ReportManager.h"

class AdminConsole
{
private:
    DeliveryManager &deliveryManager;
    SimulationManager &simulationManager;
    ReportManager &reportManager;

public:
    AdminConsole(DeliveryManager &dm, SimulationManager &sm, ReportManager &rm);
    void start();               // Start the admin console
    void viewStats();           // View live simulation stats
    void modifyQueuePolicies(); // Modify queue policies at runtime
    void generateReport();      // Generate a report
    void addDelivery();         // Add a new delivery

    //  New features
    void cancelDelivery(); // Cancel a delivery by ID
    // (No need to declare viewCancelledDeliveries here, it is directly called via deliveryManager)
};

#endif
