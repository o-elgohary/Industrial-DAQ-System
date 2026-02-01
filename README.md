# Real-Time Industrial DAQ System ⚡

A C++ simulation of an embedded data acquisition system designed for industrial monitoring. This project demonstrates Object-Oriented Programming (OOP) principles and Digital Signal Processing (DSP) techniques to process noisy sensor data in real-time.

## Key Features
* **Object-Oriented Architecture:** Utilizes abstract base classes and polymorphism to manage diverse sensor types (Temperature, Pressure).
* **Signal Processing:** Implements a **Moving Average Filter** to smooth raw sensor noise and improve data reliability.
* **Automated Fault Detection:** Continuously monitors filtered data against safety thresholds, triggering alerts for critical events.
* **Data Logging:** Persists error logs to a local file system for root-cause analysis and maintenance tracking.

## Technical Stack
* **Language:** C++
* **Concepts:** Polymorphism, Vectors, File I/O, Algorithms.
