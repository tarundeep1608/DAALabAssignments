/**
 * @file insertion_sort.cpp
 * @brief Insertion Sort on F1 Qualifying (Driver, LapTime) records with comparison counting
 * 
 * @dataset Source: Kaggle - F1 Qualifying Times (2014-2024)
 *          URL: https://www.kaggle.com/datasets/kartikag234/f1-qualifying-times2014-2024
 *          - 500 rows extracted from the original dataset
 *          - Only 2 columns used: Driver (name) and Q1 (qualifying lap time in seconds)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Driver {
    string name;
    double lapTime;
};

long long comparisons = 0;
long long assignments = 0;

/// @brief Load all data from CSV file
vector<Driver> loadAllData(const string& filename) {
    vector<Driver> allData;
    ifstream file(filename);
    string line;
    
    // Skip header
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        double lapTime;
        
        getline(ss, name, ',');
        ss >> lapTime;
        
        allData.push_back({name, lapTime});
    }
    
    return allData;
}

/// @brief Get a subset of data for a specific n and dataset number
vector<Driver> getData(const vector<Driver>& allData, int n, int datasetNum) {
    vector<Driver> data;
    int startIdx = ((datasetNum - 1) * n) % allData.size();
    
    for (int i = 0; i < n; i++) {
        int idx = (startIdx + i) % allData.size();
        data.push_back(allData[idx]);
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
    const int DATASETS = 10;
    
    // Load all data from CSV
    vector<Driver> allData = loadAllData("../q1_data.csv");
    
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
            vector<Driver> original = getData(allData, n, d + 1);
            
            // Save dataset
            ofstream fData("../data/qualifying_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fData << "driver,q1\n";
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
            fSorted << "Position,driver,q1\n";
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
