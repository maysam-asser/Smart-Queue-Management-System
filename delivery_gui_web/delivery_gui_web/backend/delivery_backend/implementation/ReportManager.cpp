#include "ReportManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

void ReportManager::generateReport(const std::string& filterType, const std::string& sortCriteria) const
{
    std::cout << "\n=== Detailed Delivery Report ===" << std::endl;

    const std::vector<Delivery>& deliveries = deliveryManager.getProcessedDeliveries();
    std::vector<Delivery> filtered;

    // Filter by type if specified
    if (!filterType.empty()) {
        for (const Delivery& d : deliveries) {
            std::string typeStr;
            switch (d.getType()) {
                case URGENT: typeStr = "urgent"; break;
                case STANDARD: typeStr = "standard"; break;
                case FRAGILE: typeStr = "fragile"; break;
            }
            if (typeStr == filterType) {
                filtered.push_back(d);
            }
        }
    } else {
        filtered = deliveries;
    }

    // Sort by criteria
    if (sortCriteria == "waiting_time") {
        std::sort(filtered.begin(), filtered.end(), [](const Delivery &a, const Delivery &b) {
            double waitTimeA = std::difftime(a.getServiceStartTime(), a.getEntryTime());
            double waitTimeB = std::difftime(b.getServiceStartTime(), b.getEntryTime());
            return waitTimeA > waitTimeB; // Descending order
        });
    } else {
        // Default sort by priority score
        std::sort(filtered.begin(), filtered.end(), [](const Delivery &a, const Delivery &b) {
            return a.getPriorityScore() > b.getPriorityScore();
        });
    }

    std::ofstream outFile("delivery_report.csv");
    outFile << "ID,Type,Priority,Wait Time,Service Time\n";

    for (const Delivery &d : filtered) {
        double waitTime = std::difftime(d.getServiceStartTime(), d.getEntryTime()) / 60.0; // Convert to minutes
        double serviceTime = std::difftime(d.getServiceEndTime(), d.getServiceStartTime()) / 60.0; // Convert to minutes

        std::string typeStr;
        switch (d.getType()) {
            case URGENT: typeStr = "urgent"; break;
            case STANDARD: typeStr = "standard"; break;
            case FRAGILE: typeStr = "fragile"; break;
        }

        outFile << d.getId() << ","
                << typeStr << ","
                << std::fixed << std::setprecision(2) << d.getPriorityScore() << ","
                << waitTime << ","
                << serviceTime << "\n";

        std::cout << "ID=" << d.getId() << " | " << typeStr << " | " 
                  << waitTime << " min wait | " << serviceTime << " min service" << std::endl;
    }

    outFile.close();
    std::cout << "Report has been saved to delivery_report.csv" << std::endl;
}

