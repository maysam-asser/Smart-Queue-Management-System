#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include "Delivery.h"
#include "DeliveryManager.h"
#include <vector>
#include <string>
#include <algorithm>

class ReportManager
{
private:
    const DeliveryManager& deliveryManager;

public:
    ReportManager(const DeliveryManager& dm) : deliveryManager(dm) {}
    void generateReport(const std::string& filterType = "", const std::string& sortCriteria = "") const;
};

#endif


