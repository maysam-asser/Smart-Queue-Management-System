#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <map>
#include <string>
#include "DeliveryTypes.h" // For DeliveryType enum

class ConfigurationManager
{
public:
    static std::map<std::string, float> weights;
    static std::map<DeliveryType, int> serviceTypeScores;
    static int maxWaitTime;
    static float boostMultiplier;
    static int simulationDuration;
    static float simulationArrivalRate;
    static int simulationCounters;

    static void initialize();

    // Getters for weights
    static float getWeight(const std::string &key);
    // Setters for weights
    static void setWeight(const std::string &key, float value);

    // Getters for service type scores
    static int getServiceTypeScore(DeliveryType type);
    // Setters for service type scores
    static void setServiceTypeScore(DeliveryType type, int score);

    // Getters and Setters for Fairness Thresholds
    static int getMaxWaitTime() { return maxWaitTime; }
    static void setMaxWaitTime(int value) { maxWaitTime = value; }
    static float getBoostMultiplier() { return boostMultiplier; }
    static void setBoostMultiplier(float value) { boostMultiplier = value; }

    // Getters and Setters for Simulation Parameters
    static int getSimulationDuration() { return simulationDuration; }
    static void setSimulationDuration(int value) { simulationDuration = value; }
    static float getSimulationArrivalRate() { return simulationArrivalRate; }
    static void setSimulationArrivalRate(float value) { simulationArrivalRate = value; }
    static int getSimulationCounters() { return simulationCounters; }
    static void setServiceCounters(int value) { simulationCounters = value; }

    static void configure(); // New method for admin console configuration
};

#endif // CONFIGURATION_MANAGER_H
