#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "DeliveryManager.h"
#include "Delivery.h"
#include "ConfigurationManager.h"
#include "AdminConsole.h"
#include "SimulationManager.h"
#include "ReportManager.h"

// Explicit template instantiations
template class MinHeap<Delivery>;
template class MaxHeap<Delivery>;
template class PriorityQueue<Delivery>;

int main() {
    srand(time(0)); // Seed for random number generation

    ConfigurationManager::initialize(); // Initialize static members of ConfigurationManager

    DeliveryManager deliveryManager;
    ReportManager reportManager(deliveryManager);
    SimulationManager simulationManager(deliveryManager, reportManager);
    AdminConsole adminConsole(deliveryManager, simulationManager, reportManager);

    adminConsole.start();

    return 0;
}


