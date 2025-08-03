# 🚚 Smart Queue Management System (SQMS)

A **priority-based intelligent delivery management system** powered by **C++**, **Python (Flask)**, and a **real-time web GUI**.  
This system simulates how deliveries are handled smartly based on urgency, waiting time, service type, and fairness—all visualized with a modern dashboard.

---

## 📌 Table of Contents

1. [📝 Project Description](#-project-description)  
2. [🎯 Objectives](#-objectives)  
3. [🧠 Features & Functionality](#-features--functionality)  
4. [📊 Feature-File Mapping](#-feature-file-mapping)  
5. [🧰 Technologies Used](#-technologies-used)  
6. [📁 Directory Structure](#-directory-structure)  
7. [⚙️ Installation Guide](#-installation-guide)  
8. [🚀 Usage](#-usage)  
9. [🧪 Testing](#-testing)  
10. [📡 API Reference](#-api-reference)  
11. [🖥️ GUI Overview](#-gui-overview)  
12. [📚 Technical Architecture](#-technical-architecture)  
13. [📌 Core Algorithms](#-core-algorithms)

---

## 📝 Project Description

**Smart Queue Management System (SQMS)** is designed to:
- Manage **multiple delivery queues** with **priority-based processing**.
- Adapt dynamically using **fairness monitors**, **time-based scoring**, and **simulation logic**.
- Provide both a **CLI admin interface** and a **web GUI dashboard** for management.

---

## 🎯 Objectives

- ✅ Ensure fair delivery processing based on dynamic priority scoring.
- ✅ Support urgent and special-case deliveries using multi-queue strategies.
- ✅ Deliver a responsive and interactive web interface.
- ✅ Provide extensible and testable architecture.
- ✅ Offer real-world simulation tools for stress testing.

---

## 🧠 Features & Functionality

| # | Feature                              | Description                                                                                   | Output / Result                                                                 |
|---|--------------------------------------|-----------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|
| 1 | **Priority Score Calculation**       | Calculates delivery priority dynamically using weighted formula.                              | Deliveries with highest score are processed first.                              |
| 2 | **Dynamic Priority Update**          | Periodic recalculation of priorities to avoid starvation.                                     | Older deliveries rise in rank over time.                                        |
| 3 | **Multiple Queues + Merging**        | Queues for Urgent, Fragile, Standard; merges when urgent is empty.                           | Ensures service continuity and fairness.                                        |
| 4 | **Fairness Monitor**                 | Boosts priority for long-waiting deliveries.                                                  | Prevents starvation and improves equity.                                        |
| 5 | **Simulation Mode**                  | Generates random deliveries with arrival rates, urgency, destinations.                        | Loads system under pressure, validates merging & scoring logic.                |
| 6 | **Advanced Reporting & Sorting**     | Reports processed deliveries sorted by waiting time.                                          | Stats on wait time, service time, per-type average.                             |
| 7 | **Admin Console (CLI)**              | C++ console for adding, cancelling, viewing deliveries.                                       | Fast CLI interaction with real-time data.                                       |
| 8 | **GUI Web Dashboard**                | HTML/CSS/JS + Flask GUI to visualize queue, processing, simulation.                           | Intuitive user interface.                                                       |
| 9 | **Cancelled Deliveries Log (Stack)** | Keeps cancelled deliveries in stack (LIFO).                                                   | Logs actions and provides audit trail.                                          |
|10 | **User Management**                  | Simple Flask-based user model for future extension.                                           | Allows CRUD operations on users.                                                |

---

## 📊 Feature-File Mapping

| **Feature**                         | **Primary Files (C++)**                    | **Primary Files (Python/GUI)**                 |
|------------------------------------|--------------------------------------------|-----------------------------------------------|
| Priority Score Calculation         | `Delivery.h/.cpp`                          | `delivery.py`                                 |
| Dynamic Priority Updates           | `DeliveryManager.cpp`                      | `queue_manager.py`                            |
| Multiple Queues + Merging          | `DeliveryManager.cpp`, `MaxHeap.h`         | `queue_manager.py`                            |
| Fairness Monitor                   | `Delivery.cpp`                             | `queue_manager.py`                            |
| Simulation Mode                    | `AdminConsole.cpp`                         | `delivery_routes.py`                          |
| Admin Console                      | `AdminConsole.cpp`, `main.cpp`             | N/A                                           |
| GUI Interface                      | N/A                                        | `index.html`, `styles.css`, `script.js`, `main.py` |
| Cancelled Delivery Log             | `CancelledDeliveryStack.h/.cpp`            | `queue_manager.py`                            |
| Reporting                          | `DeliveryManager.cpp`                      | `delivery_routes.py`                          |

---

## 🧰 Technologies Used

| **Component**       | **Technology / Tool**                             | **Purpose**                                  |
|---------------------|---------------------------------------------------|----------------------------------------------|
| 🧠 Core Engine       | `C++17`, OOP, STL                                 | Implements delivery logic, priority scoring  |
| 📦 Data Structures   | `MaxHeap`, `Custom Stack`, `PriorityQueue`       | Manages queues and cancellation log          |
| 🛠 Build System      | `g++`, `Makefile` (optional)                      | Compiles and builds the C++ system           |
| 🌐 Backend API       | `Python 3.10`, `Flask`, `SQLAlchemy`, `CORS`     | Serves REST APIs to GUI                      |
| 🗄 Database          | `SQLite`                                         | Stores deliveries and logs persistently      |
| 🎨 Frontend GUI      | `HTML5`, `CSS3`, `Vanilla JavaScript`            | Web interface for monitoring and interaction |
| 📱 Responsive Design | `Flexbox`, `CSS Grid`, `Media Queries`           | Mobile & desktop compatibility               |
| 🔁 API Integration   | `Fetch API (JS)`                                  | Communicates with Flask API                  |
| 🧪 Testing           | `pytest`, `curl`, Manual CLI & GUI simulations   | Tests functionality and robustness           |
| 🧰 Dev Tools         | `VS Code`, `Flask CLI`, `Browser Dev Tools`      | Development and debugging                    |

---

## 📁 Directory Structure

```
.
├── cpp_core/
│   ├── Delivery.cpp/.h
│   ├── DeliveryManager.cpp/.h
│   ├── AdminConsole.cpp/.h
│   └── ...
│
├── gui/
│   ├── static/
│   │   ├── styles.css
│   │   ├── script.js
│   │   └── index.html
│   ├── src/
│   │   ├── models/
│   │   │   ├── delivery.py
│   │   │   ├── queue_manager.py
│   │   │   └── user.py
│   │   └── routes/
│   │       ├── delivery_routes.py
│   │       └── user.py
│   ├── main.py
│   └── requirements.txt
│
└── README.md
```

---

## ⚙️ Installation Guide

### 🔧 C++ Engine

```bash
cd cpp_core
g++ -std=c++17 -o delivery_system main.cpp DeliveryManager.cpp AdminConsole.cpp
./delivery_system
```

### 🐍 Python Web GUI

```bash
cd gui
pip install -r requirements.txt
python main.py
```

Access the dashboard at:  
👉 `http://localhost:5000`

---

## 🚀 Usage

### 👨‍💻 CLI (Admin Console)

Run:
```bash
./delivery_system
```

Operations:
- `Add Delivery`
- `Cancel Delivery`
- `Process Next`
- `Show Report`
- `Show Cancelled Log`

---

### 🌐 GUI Instructions

1. Go to `http://localhost:5000`
2. Add deliveries using left form.
3. View queues in center panel.
4. See stats and activity on right.
5. Use buttons to **simulate** or **process** deliveries.

---

## 🧪 Testing

To run backend unit tests:

```bash
cd gui
pytest tests/
```

You can also test APIs manually using:

```bash
curl -X POST http://localhost:5000/api/delivery/add -H "Content-Type: application/json" \
     -d '{"destination": "Office", "delivery_type": "urgent"}'
```

---

## 📡 API Reference

| Method | Endpoint                    | Description                            |
|--------|-----------------------------|----------------------------------------|
| POST   | `/api/delivery/add`         | Add a new delivery                     |
| POST   | `/api/delivery/process`     | Process next delivery                  |
| POST   | `/api/delivery/clear`       | Clear all deliveries                   |
| GET    | `/api/delivery/status`      | Get all queues and stats               |
| GET    | `/api/delivery/report`      | Report of processed deliveries         |
| POST   | `/api/delivery/simulate`    | Start simulation mode                  |
| GET    | `/users`                    | Get all users                          |
| POST   | `/users`                    | Create user                            |

---

## 🖥️ GUI Overview

- 🟥 **Left Panel** → Add new deliveries  
- 🟦 **Center Panel** → Urgent, Fragile, Standard queues  
- 🟩 **Right Panel** →  
  - Processing state  
  - Statistics  
  - Recent activity  
- 🟨 **Footer** → Status and real-time messages

---

## 📚 Technical Architecture

```
+---------------------+
|     C++ Core        |  Handles logic, CLI, scores
+---------------------+
        ⬇️ via APIs
+---------------------+
|   Flask (Python)    |  REST APIs, manages delivery objects
+---------------------+
        ⬇️ JSON/Fetch
+---------------------+
| Web GUI (HTML/CSS)  | User interface, statistics, interaction
+---------------------+
```

---

## 📌 Core Algorithms

### 🧮 Priority Score Formula

\[
\text{Priority} = (U \times W_u) + (W_t \times W_w) + (S \times W_s)
\]

Where:
- \( U \) = Urgency level (1-5)
- \( W_t \) = Waiting time in minutes
- \( S \) = Service score
- \( W_u, W_w, W_s \) = Configurable weights

### 🧠 Fairness Boost

If waiting time > max threshold:
```cpp
priority += (waiting_time - threshold) * fairness_multiplier;
```

---

## 🔮 Future Work & Enhancements

While the **Smart Queue Management System** achieves a comprehensive simulation of real-world delivery processing using priority-based queues, there are several areas where the system can evolve further:

### 🚀 Planned Improvements

- **🔄 Real-Time WebSocket Updates**  
  Replace periodic polling with WebSocket-based live updates to improve performance and responsiveness.

- **📱 Mobile-Friendly Interface**  
  Extend and optimize the GUI for mobile and tablet devices using responsive frameworks like Bootstrap or TailwindCSS.

- **🧠 AI-Based Priority Optimization**  
  Introduce ML algorithms to predict delivery importance based on past behavior, distance, and delivery type.

- **📡 Distributed System Support**  
  Allow multiple processing nodes or API servers to handle queues in parallel (e.g., via microservices or load balancers).

- **💾 Persistent Queues with Redis/Kafka**  
  Replace in-memory queues with message queues (e.g., Redis streams, Apache Kafka) to enable scalable, durable message delivery.

- **🛡️ User Roles and Authentication**  
  Add user authentication, admin vs.

