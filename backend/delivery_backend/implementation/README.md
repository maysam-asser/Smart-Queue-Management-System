# Smart Queue Management System

A dynamic delivery queue management system with real-time simulation, configurable parameters, intelligent priority scoring, and delivery reporting.

## Overview

The Smart Queue Management System is designed to simulate and manage the flow of deliveries based on priority queues. Each delivery is assigned a dynamic priority score influenced by urgency, waiting time, and service type. The system allows administrators to configure simulation parameters, modify queue policies at runtime, generate detailed reports, and manage delivery life cycles—including cancellations and fairness-based priority boosting.

## Features

- **Real-Time Simulation**: Run timed simulations with adjustable arrival rates and counters.
- **Priority Queueing**: Deliveries are categorized and queued into Urgent, Standard, or Fragile, each managed via a `MaxHeap`-based priority queue.
- **Dynamic Priority Scoring**: Priority scores are calculated and updated based on urgency, wait time, and service type weights.
- **Fairness Boosting**: Deliveries waiting beyond a configured threshold are boosted for fairness.
- **Delivery Cancellation & Logging**: Cancel any active delivery by ID, with a log of all cancellations.
- **Custom Configuration**: Change weights, counters, scores, and simulation settings via the Admin Console.
- **Detailed Reporting**: Generate CSV reports with filtering (by type) and sorting (by priority or waiting time).
- **Interactive Admin Console**: Text-based interface for managing operations and monitoring system state.

## Components

- **`AdminConsole`**: CLI-based interface for managing the system.
- **`DeliveryManager`**: Handles delivery queues, cancellations, and fairness policies.
- **`SimulationManager`**: Runs timed simulations and manages delivery generation and processing.
- **`ReportManager`**: Generates CSV reports with delivery statistics.
- **`ConfigurationManager`**: Manages global configuration and scoring weights.
- **`PriorityQueue` / `MaxHeap` / `MinHeap`**: Custom implementations used for managing delivery ordering efficiently.

## Delivery Types

- `URGENT`: Highest base urgency score.
- `STANDARD`: Default delivery type.
- `FRAGILE`: Requires careful handling, gets special scoring.

## Simulation Parameters

You can configure the following before or during simulation:

- Urgency, Waiting Time, and Service Type Weights
- Fairness Boost Thresholds (`maxWaitTime`, `boostMultiplier`)
- Number of Service Counters
- Simulation Duration and Arrival Rate

## Reports

Reports are generated at the end of simulations or via the Admin Console. Each report includes:

- Delivery ID, Type, Priority Score
- Waiting Time (in minutes)
- Service Time (in minutes)
- Output to both console and `delivery_report.csv`


## How to Run 
-Open PowerShell and navigate to the project folder:
cd path\to\Final_Destenation_CSAI_201_Project_FILES_ONLY

-Compile the source files: 
g++ *.cpp -o delivery.exe

-Run the executable:     
./delivery.exe

# Note: If g++ is not recognized, install MinGW and add it to your system PATH.