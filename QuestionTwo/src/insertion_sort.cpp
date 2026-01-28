/**
 * @file insertion_sort.cpp
 * @brief Insertion Sort on F1 Qualifying (Driver, LapTime) records with comparison counting
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

struct Driver {
    string name;
    double lapTime;
};

long long comparisons = 0;
long long assignments = 0;

// Pool for generating driver data
const vector<string> DRIVERS = {
    "VER", "HAD", "RUS", "ANT", "LEC", "HAM", "HUL", "BOR",
    "PER", "BOT", "GAS", "COL", "OCO", "BEA", "SAI", "ALB",
    "ALO", "STR", "NOR", "PIA", "LAW", "LIN"
};

/// @brief Generate random dataset from pool with attempt numbers
vector<Driver> generateData(int n, mt19937& rng) {
    vector<Driver> data(n);
    uniform_real_distribution<double> dist(77.0, 93.0);
    map<string, int> attemptCount;  // Track attempts per driver
    
    for (int i = 0; i < n; i++) {
        string driverCode = DRIVERS[rng() % DRIVERS.size()];
        attemptCount[driverCode]++;  // Increment attempt count
        data[i].name = driverCode + " (Lap " + to_string(attemptCount[driverCode]) + ")";
        data[i].lapTime = dist(rng);
    }
    return data;
}

/// @brief Sort by lap time (ascending)
void sortByLapTime(vector<Driver>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        Driver key = data[i];
        assignments++;
        int j = i - 1;
        while (j >= 0 && (comparisons++, data[j].lapTime > key.lapTime)) {
            data[j + 1] = data[j];
            assignments++;
            j--;
        }
        data[j + 1] = key;
        assignments++;
    }
}

int main() {
    mt19937 rng(time(nullptr));
    
    const int DATASETS = 10;
    
    // Open output files
    ofstream fLapTime("../results/sort_by_laptime.csv");
    ofstream fLapTimeAssign("../results/sort_by_laptime_assignments.csv");
    ofstream fSummary("../results/summary.csv");
    
    fLapTime << "n,dataset,comparisons\n";
    fLapTimeAssign << "n,dataset,assignments\n";
    fSummary << "n,avg_comparisons,avg_assignments\n";
    
    cout << "Insertion Sort on F1 Qualifying Data\n";
    cout << "===============================\n\n";
    
    for (int n = 10; n <= 100; n += 10) {
        long long totalComp = 0, totalAssign = 0;
        
        cout << "n = " << setw(3) << n << ": ";
        
        for (int d = 0; d < DATASETS; d++) {
            vector<Driver> original = generateData(n, rng);
            
            // Save dataset
            ofstream fData("../data/qualifying_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fData << "Name,LapTime\n";
            for (auto& r : original)
                fData << r.name << "," << fixed << setprecision(3) << r.lapTime << "\n";
            
            // Sort by lap time
            vector<Driver> data = original;
            comparisons = 0;
            assignments = 0;
            sortByLapTime(data);
            fLapTime << n << "," << d+1 << "," << comparisons << "\n";
            fLapTimeAssign << n << "," << d+1 << "," << assignments << "\n";
            totalComp += comparisons;
            totalAssign += assignments;
            
            // Save sorted data
            ofstream fSorted("../results/sorted_by_laptime_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fSorted << "Position,Name,LapTime\n";
            for (size_t i = 0; i < data.size(); i++)
                fSorted << (i + 1) << "," << data[i].name << "," << fixed << setprecision(3) << data[i].lapTime << "\n";
            
            cout << ".";
        }
        
        double avgComp = (double)totalComp / DATASETS;
        double avgAssign = (double)totalAssign / DATASETS;
        
        fSummary << n << "," << fixed << setprecision(2) << avgComp << "," << avgAssign << "\n";
        
        cout << " Avg: Comparisons=" << avgComp << ", Assignments=" << avgAssign << "\n";
    }
    
    cout << "\nResults saved to ../results/\n";
    cout << "Sorted data saved to ../results/sorted_*.csv\n";
    cout << "Datasets saved to ../data/\n";
    
    return 0;
}
