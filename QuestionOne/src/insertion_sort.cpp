/**
 * @file insertion_sort.cpp
 * @brief Insertion Sort on (Name, Age) records with comparison counting
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <ctime>

using namespace std;

struct Record {
    string name;
    float age;
};

long long comparisons = 0;
long long assignments = 0;

// Pools for generating data with duplicates
const vector<string> NAMES = {
    "Amit", "Priya", "Rahul", "Sneha", "Vikram", "Anita", "Ravi", "Meera",
    "Arjun", "Kavita", "Suresh", "Reeta", "Geet", "Mohan", "Neha", "Kiran"
};
const vector<float> AGES = {
    17.5f, 18.0f, 18.3f, 18.5f, 19.0f, 19.5f, 20.0f, 20.5f,
    21.0f, 21.5f, 22.0f, 22.5f, 23.0f, 23.5f, 17.8f, 19.8f
};

/// @brief Generate random dataset from pools
vector<Record> generateData(int n, mt19937& rng) {
    vector<Record> data(n);
    for (int i = 0; i < n; i++) {
        data[i].name = NAMES[rng() % NAMES.size()];
        data[i].age = AGES[rng() % AGES.size()];
    }
    return data;
}

/// @brief Sort by age (ascending)
void sortByAge(vector<Record>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        Record key = data[i];
        assignments++;
        int j = i - 1;
        while (j >= 0 && (comparisons++, data[j].age > key.age)) {
            data[j + 1] = data[j];
            assignments++;
            j--;
        }
        data[j + 1] = key;
        assignments++;
    }
}

/// @brief Sort by name (ascending)
void sortByName(vector<Record>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        Record key = data[i];
        assignments++;
        int j = i - 1;
        while (j >= 0 && (comparisons++, data[j].name > key.name)) {
            data[j + 1] = data[j];
            assignments++;
            j--;
        }
        data[j + 1] = key;
        assignments++;
    }
}

/// @brief Stable Sort by name then age : maintains age order within same names)
void sortByNameThenAge(vector<Record>& data) {
    // First sort by age
    for (size_t i = 1; i < data.size(); i++) {
        Record key = data[i];
        assignments++;
        int j = i - 1;
        while (j >= 0 && (comparisons++, data[j].age > key.age)) {
            data[j + 1] = data[j];
            assignments++;
            j--;
        }
        data[j + 1] = key;
        assignments++;
    }
    // Stable sort by name
    for (size_t i = 1; i < data.size(); i++) {
        Record key = data[i];
        assignments++;
        int j = i - 1;
        while (j >= 0 && (comparisons++, data[j].name > key.name)) {
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
    ofstream fAge("../results/sort_by_age.csv");
    ofstream fName("../results/sort_by_name.csv");
    ofstream fCombined("../results/sort_combined.csv");
    ofstream fAgeAssign("../results/sort_by_age_assignments.csv");
    ofstream fNameAssign("../results/sort_by_name_assignments.csv");
    ofstream fCombinedAssign("../results/sort_combined_assignments.csv");
    ofstream fSummary("../results/summary.csv");
    
    fAge << "n,dataset,comparisons\n";
    fName << "n,dataset,comparisons\n";
    fCombined << "n,dataset,comparisons\n";
    fAgeAssign << "n,dataset,assignments\n";
    fNameAssign << "n,dataset,assignments\n";
    fCombinedAssign << "n,dataset,assignments\n";
    fSummary << "n,avg_age_comp,avg_name_comp,avg_combined_comp,avg_age_assign,avg_name_assign,avg_combined_assign\n";
    
    cout << "Insertion Sort \n";
    cout << "=========================\n\n";
    
    for (int n = 10; n <= 100; n += 10) {
        long long totalAge = 0, totalName = 0, totalCombined = 0;
        long long totalAgeAssign = 0, totalNameAssign = 0, totalCombinedAssign = 0;
        
        cout << "n = " << setw(3) << n << ": ";
        
        for (int d = 0; d < DATASETS; d++) {
            vector<Record> original = generateData(n, rng);
            
            // Save first dataset of each n
            if (d == 0) {
                ofstream fData("../data/dataset_n" + to_string(n) + ".csv");
                for (auto& r : original)
                    fData << r.name << "," << fixed << setprecision(1) << r.age << "\n";
            }
            
            // Sort by age
            vector<Record> data = original;
            comparisons = 0;
            assignments = 0;
            sortByAge(data);
            fAge << n << "," << d+1 << "," << comparisons << "\n";
            fAgeAssign << n << "," << d+1 << "," << assignments << "\n";
            totalAge += comparisons;
            totalAgeAssign += assignments;
            
            // Save sorted by age data for first dataset
            if (d == 0) {
                ofstream fSortedAge("../results/sorted_by_age_n" + to_string(n) + ".csv");
                fSortedAge << "name,age\n";
                for (auto& r : data)
                    fSortedAge << r.name << "," << fixed << setprecision(1) << r.age << "\n";
            }
            
            // Sort by name
            data = original;
            comparisons = 0;
            assignments = 0;
            sortByName(data);
            fName << n << "," << d+1 << "," << comparisons << "\n";
            fNameAssign << n << "," << d+1 << "," << assignments << "\n";
            totalName += comparisons;
            totalNameAssign += assignments;
            
            // Save sorted by name data for first dataset
            if (d == 0) {
                ofstream fSortedName("../results/sorted_by_name_n" + to_string(n) + ".csv");
                fSortedName << "name,age\n";
                for (auto& r : data)
                    fSortedName << r.name << "," << fixed << setprecision(1) << r.age << "\n";
            }
            
            // Combined sort
            data = original;
            comparisons = 0;
            assignments = 0;
            sortByNameThenAge(data);
            fCombined << n << "," << d+1 << "," << comparisons << "\n";
            fCombinedAssign << n << "," << d+1 << "," << assignments << "\n";
            totalCombined += comparisons;
            totalCombinedAssign += assignments;
            
            // Save combined sorted data for first dataset
            if (d == 0) {
                ofstream fSortedCombined("../results/sorted_combined_n" + to_string(n) + ".csv");
                fSortedCombined << "name,age\n";
                for (auto& r : data)
                    fSortedCombined << r.name << "," << fixed << setprecision(1) << r.age << "\n";
            }
            
            cout << ".";
        }
        
        double avgAge = (double)totalAge / DATASETS;
        double avgName = (double)totalName / DATASETS;
        double avgCombined = (double)totalCombined / DATASETS;
        double avgAgeAssign = (double)totalAgeAssign / DATASETS;
        double avgNameAssign = (double)totalNameAssign / DATASETS;
        double avgCombinedAssign = (double)totalCombinedAssign / DATASETS;
        
        fSummary << n << "," << fixed << setprecision(2) 
                 << avgAge << "," << avgName << "," << avgCombined << ","
                 << avgAgeAssign << "," << avgNameAssign << "," << avgCombinedAssign << "\n";
        
        cout << " Avg: Age=" << avgAge << ", Name=" << avgName 
             << ", Combined=" << avgCombined << "\n";
    }
    
    cout << "\nResults saved to ../results/\n";
    cout << "Sorted data saved to ../results/sorted_*.csv\n";
    cout << "Datasets saved to ../data/\n";
    
    return 0;
}
