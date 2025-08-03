#include "ConfigurationManager.h"
#include <iostream>

// Initialize static members
std::map<std::string, float> ConfigurationManager::weights;
std::map<DeliveryType, int> ConfigurationManager::serviceTypeScores;
int ConfigurationManager::maxWaitTime = 25;
float ConfigurationManager::boostMultiplier = 0.5f;
int ConfigurationManager::simulationDuration = 60;
float ConfigurationManager::simulationArrivalRate = 0.5f;
int ConfigurationManager::simulationCounters = 3;

void ConfigurationManager::initialize()
{
    // Initialize with default values
    weights["urgency"] = 0.5f;
    weights["waiting_time"] = 0.3f;
    weights["service_type"] = 0.2f;

    serviceTypeScores[URGENT] = 10;
    serviceTypeScores[FRAGILE] = 8;
    serviceTypeScores[STANDARD] = 5;

    maxWaitTime = 25;
    boostMultiplier = 0.5f;

    simulationDuration = 60;
    simulationArrivalRate = 0.5f;
    simulationCounters = 3;
}

float ConfigurationManager::getWeight(const std::string &key)
{
    auto it = weights.find(key);
    if (it != weights.end())
    {
        return it->second;
    }
    return 0.0f; // Default or error value
}

void ConfigurationManager::setWeight(const std::string &key, float value)
{
    weights[key] = value;
}

int ConfigurationManager::getServiceTypeScore(DeliveryType type)
{
    auto it = serviceTypeScores.find(type);
    if (it != serviceTypeScores.end())
    {
        return it->second;
    }
    return 0; // Default or error value
}

void ConfigurationManager::setServiceTypeScore(DeliveryType type, int score)
{
    serviceTypeScores[type] = score;
}

void ConfigurationManager::configure()
{
    std::cout << "==== Configure System Parameters ====\n";

    std::cout << "Enter urgency weight (current: " << weights["urgency"] << "): ";
    std::cin >> weights["urgency"];

    std::cout << "Enter waiting time weight (current: " << weights["waiting_time"] << "): ";
    std::cin >> weights["waiting_time"];

    std::cout << "Enter service type weight (current: " << weights["service_type"] << "): ";
    std::cin >> weights["service_type"];

    std::cout << "Enter max wait time for fairness boost (current: " << maxWaitTime << "): ";
    std::cin >> maxWaitTime;

    std::cout << "Enter fairness boost multiplier (current: " << boostMultiplier << "): ";
    std::cin >> boostMultiplier;

    std::cout << "Enter simulation duration (minutes) (current: " << simulationDuration << "): ";
    std::cin >> simulationDuration;

    std::cout << "Enter simulation arrival rate (individuals/minute) (current: " << simulationArrivalRate << "): ";
    std::cin >> simulationArrivalRate;

    std::cout << "Enter number of service counters (current: " << simulationCounters << "): ";
    std::cin >> simulationCounters;

    std::cout << "Enter URGENT service type score (current: " << serviceTypeScores[URGENT] << "): ";
    std::cin >> serviceTypeScores[URGENT];
    std::cout << "Enter STANDARD service type score (current: " << serviceTypeScores[STANDARD] << "): ";
    std::cin >> serviceTypeScores[STANDARD];
    std::cout << "Enter FRAGILE service type score (current: " << serviceTypeScores[FRAGILE] << "): ";
    std::cin >> serviceTypeScores[FRAGILE];

    std::cout << "Configuration updated successfully.\n";
}
