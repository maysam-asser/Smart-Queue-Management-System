#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "DeliveryManager.h"
#include "ReportManager.h"
#include "ConfigurationManager.h"

class SimulationManager
{
private:
    DeliveryManager &deliveryManager;
    ReportManager &reportManager;
    int currentSimTime;

public:
    SimulationManager(DeliveryManager &dm, ReportManager &rm) : deliveryManager(dm),
                                                                reportManager(rm),
                                                                currentSimTime(0) {}

    void runSimulation();
    Delivery generateRandomDelivery();

    int getProcessedDeliveriesCount() const { return deliveryManager.getProcessedDeliveries().size(); }
    int getQueueSize() const { return deliveryManager.getTotalQueueSize(); }
};

#endif // SIMULATION_MANAGER_H
