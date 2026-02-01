#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <numeric> // Required for accumulate

// PROJECT: Real-Time Industrial Data Acquisition System (DAQ)
// Author: Omar El-Gohary
// Keywords: C++, OOP, DSP (Moving Average), Data Logging, Fault Detection

using namespace std;

// --- Abstract Base Class (Polymorphism) ---
class Sensor {
protected:
    int id;
    string type;
    vector<double> dataBuffer; // Buffer for DSP

public:
    Sensor(int sensorID, string sensorType) : id(sensorID), type(sensorType) {}
    
    // Virtual function for simulation
    virtual double readRawValue() = 0; 
    
    // DIGITAL SIGNAL PROCESSING: Moving Average Filter
    double getFilteredValue() {
        double raw = readRawValue();
        dataBuffer.push_back(raw);
        if (dataBuffer.size() > 5) { // Keep last 5 readings
            dataBuffer.erase(dataBuffer.begin());
        }
        
        // Calculate Average
        double sum = accumulate(dataBuffer.begin(), dataBuffer.end(), 0.0);
        return sum / dataBuffer.size();
    }

    string getType() { return type; }
    int getID() { return id; }
};

// --- Derived Class: Temp Sensor ---
class TempSensor : public Sensor {
public:
    TempSensor(int id) : Sensor(id, "Temperature") {}
    double readRawValue() override {
        return 80.0 + (rand() % 200) / 10.0; // Simulates 80-100 deg C + Noise
    }
};

// --- Derived Class: Pressure Sensor ---
class PressureSensor : public Sensor {
public:
    PressureSensor(int id) : Sensor(id, "Pressure") {}
    double readRawValue() override {
        return 50.0 + (rand() % 100) / 10.0; // Simulates 50-60 PSI + Noise
    }
};

// --- Logger Module ---
void logEvent(string message) {
    ofstream logFile;
    logFile.open("daq_log.txt", ios_base::app);
    logFile << "[LOG] " << message << endl;
    logFile.close();
}

int main() {
    srand(time(0));
    vector<Sensor*> sensors;

    // Dynamic Resource Allocation
    sensors.push_back(new TempSensor(101));
    sensors.push_back(new PressureSensor(102));

    cout << "--- INDUSTRIAL DAQ SYSTEM STARTED ---\n";
    cout << "--- APPLYING MOVING AVERAGE FILTER ---\n\n";

    for (int i = 0; i < 5; i++) { // Simulate 5 cycles
        cout << "Cycle " << i + 1 << ":\n";
        for (Sensor* s : sensors) {
            double val = s->getFilteredValue(); // Calls DSP function
            cout << "Sensor " << s->getID() << " [" << s->getType() << "] Filtered Output: " << val << endl;

            // Fault Detection Logic
            if (val > 95.0 && s->getType() == "Temperature") {
                string alert = "OVERHEAT DETECTED: Sensor " + to_string(s->getID());
                cout << " >> ALERT: " << alert << endl;
                logEvent(alert);
            }
        }
        cout << "-----------------------------------\n";
    }
    
    return 0;
}
