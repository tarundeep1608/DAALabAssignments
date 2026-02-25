/**
 * @file main.cpp
 * @brief Menu-driven program for quick sort implementations
 * @details Combines two sorting programs:
 *          1. Name-Age records with performance analysis
 *          2. Bank customer data sorting by salary
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <ctime>

using namespace std;

// ============================================================================
// OPTION 1: Name-Age Records Sorting with Performance Analysis
// ============================================================================

/**
 * @struct Record
 * @brief Represents a record with a name and an age.
 */
struct Record {
    string name;
    float age;
};

long long comparisons = 0; ///< Global counter for comparisons.
long long assignments = 0; ///< Global counter for assignments.

///< Sample names for data generation.
const vector<string> NAMES = {
    "Amit", "Priya", "Rahul", "Sneha", "Vikram", "Anita", "Ravi", "Meera",
    "Arjun", "Kavita", "Suresh", "Reeta", "Geet", "Mohan", "Neha", "Kiran"
};
///< Sample ages for data generation.
const vector<float> AGES = {
    17.5f, 18.0f, 18.3f, 18.5f, 19.0f, 19.5f, 20.0f, 20.5f,
    21.0f, 21.5f, 22.0f, 22.5f, 23.0f, 23.5f, 17.8f, 19.8f
};

/**
 * @brief Generates a vector of random Record data.
 * @param n The number of records to generate.
 * @param rng The random number generator.
 * @return A vector of generated records.
 */
vector<Record> generateData(int n, mt19937& rng) {
    vector<Record> data(n);
    for (int i = 0; i < n; i++) {
        data[i].name = NAMES[rng() % NAMES.size()];
        data[i].age = AGES[rng() % AGES.size()];
    }
    return data;
}

// Custom swap function to count assignments
void swapRecords(Record& a, Record& b) {
    Record temp = a;
    a = b;
    b = temp;
    assignments += 3;
}

/**
 * @brief Partitions the array for Quick Sort by Age.
 */
int partitionByAge(vector<Record>& data, int low, int high) {
    float pivot = data[high].age; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (data[j].age <= pivot) {
            i++;
            swapRecords(data[i], data[j]);
        }
    }
    swapRecords(data[i + 1], data[high]);
    return (i + 1);
}

/**
 * @brief Sorts a vector of Records by age using Quick Sort.
 */
void quickSortByAge(vector<Record>& data, int low, int high) {
    if (low < high) {
        int pi = partitionByAge(data, low, high);
        quickSortByAge(data, low, pi - 1);
        quickSortByAge(data, pi + 1, high);
    }
}

/**
 * @brief Partitions the array for Quick Sort by Name.
 */
int partitionByName(vector<Record>& data, int low, int high) {
    string pivot = data[high].name;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (data[j].name <= pivot) {
            i++;
            swapRecords(data[i], data[j]);
        }
    }
    swapRecords(data[i + 1], data[high]);
    return (i + 1);
}

/**
 * @brief Sorts a vector of Records by name using Quick Sort.
 */
void quickSortByName(vector<Record>& data, int low, int high) {
    if (low < high) {
        int pi = partitionByName(data, low, high);
        quickSortByName(data, low, pi - 1);
        quickSortByName(data, pi + 1, high);
    }
}

/**
 * @brief Partitions the array for Quick Sort by Name then Age.
 */
int partitionByNameThenAge(vector<Record>& data, int low, int high) {
    Record pivot = data[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Compare logic: Name first, then Age
        bool smaller = false;
        comparisons++;
        if (data[j].name < pivot.name) {
            smaller = true;
        } else if (data[j].name > pivot.name) {
            smaller = false;
        } else {
            comparisons++; 
            if (data[j].age <= pivot.age) {
                smaller = true;
            }
        }

        if (smaller) {
            i++;
            swapRecords(data[i], data[j]);
        }
    }
    swapRecords(data[i + 1], data[high]);
    return (i + 1);
}

/**
 * @brief Sorts a vector of Records by name then age using Quick Sort.
 */
void quickSortByNameThenAge(vector<Record>& data, int low, int high) {
    if (low < high) {
        int pi = partitionByNameThenAge(data, low, high);
        quickSortByNameThenAge(data, low, pi - 1);
        quickSortByNameThenAge(data, pi + 1, high);
    }
}

/**
 * @brief Runs performance analysis for Quick Sort on Name-Age records.
 */
void nameAgePerformanceAnalysis() {
    mt19937 rng(time(nullptr));
    
    const int DATASETS = 10;
    
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
    
    cout << "\nQuick Sort Performance Analysis (Name-Age Records)\n";
    cout << "===================================================\n\n";
    
    for (int n = 10; n <= 100; n += 10) {
        long long totalAge = 0, totalName = 0, totalCombined = 0;
        long long totalAgeAssign = 0, totalNameAssign = 0, totalCombinedAssign = 0;
        
        cout << "n = " << setw(3) << n << ": ";
        
        for (int d = 0; d < DATASETS; d++) {
            vector<Record> original = generateData(n, rng);
            
            ofstream fData("../data/dataset_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            for (auto& r : original)
                fData << r.name << "," << fixed << setprecision(1) << r.age << "\n";
            
            // Sort by age
            vector<Record> data = original;
            comparisons = 0;
            assignments = 0;
            if (data.size() > 0)
                quickSortByAge(data, 0, data.size() - 1);
            fAge << n << "," << d+1 << "," << comparisons << "\n";
            fAgeAssign << n << "," << d+1 << "," << assignments << "\n";
            totalAge += comparisons;
            totalAgeAssign += assignments;
            
            ofstream fSortedAge("../results/sorted_by_age_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fSortedAge << "name,age\n";
            for (auto& r : data)
                fSortedAge << r.name << "," << fixed << setprecision(1) << r.age << "\n";

            // Sort by name
            data = original;
            comparisons = 0;
            assignments = 0;
            if (data.size() > 0)
                quickSortByName(data, 0, data.size() - 1);
            fName << n << "," << d+1 << "," << comparisons << "\n";
            fNameAssign << n << "," << d+1 << "," << assignments << "\n";
            totalName += comparisons;
            totalNameAssign += assignments;
            
            ofstream fSortedName("../results/sorted_by_name_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fSortedName << "name,age\n";
            for (auto& r : data)
                fSortedName << r.name << "," << fixed << setprecision(1) << r.age << "\n";

            // Combined sort
            data = original;
            comparisons = 0;
            assignments = 0;
            if (data.size() > 0)
                quickSortByNameThenAge(data, 0, data.size() - 1);
            fCombined << n << "," << d+1 << "," << comparisons << "\n";
            fCombinedAssign << n << "," << d+1 << "," << assignments << "\n";
            totalCombined += comparisons;
            totalCombinedAssign += assignments;
            
            ofstream fSortedCombined("../results/sorted_combined_n" + to_string(n) + "_d" + to_string(d+1) + ".csv");
            fSortedCombined << "name,age\n";
            for (auto& r : data)
                fSortedCombined << r.name << "," << fixed << setprecision(1) << r.age << "\n";

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
}

// ============================================================================
// OPTION 2: Bank Customer Data Sorting by Salary
// ============================================================================

/**
 * @struct Customer
 * @brief Represents a bank customer with various attributes.
 */
struct Customer {
    string id, score, country, gender, age, tenure, balance, products, card, active, churn;
    double salary;
};

// Custom swap for Customer
void swapCustomers(Customer& a, Customer& b) {
    Customer temp = a;
    a = b;
    b = temp;
}

/**
 * @brief Loads bank customer data from a CSV file.
 */
vector<Customer> loadBankData(string filename) {
    vector<Customer> data;
    ifstream file(filename);
    string line, item;

    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return data;
    }

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, item, ',')) row.push_back(item);

        if (row.size() >= 12) {
            Customer c;
            c.id = row[0]; c.score = row[1]; c.country = row[2];
            c.gender = row[3]; c.age = row[4]; c.tenure = row[5];
            c.balance = row[6]; c.products = row[7]; c.card = row[8];
            c.active = row[9];
            try { c.salary = stod(row[10]); } catch (...) { c.salary = 0.0; }
            c.churn = row[11];
            data.push_back(c);
        }
    }
    return data;
}

/**
 * @brief Partition for Bank Customer Data by Salary.
 */
int partitionBySalary(vector<Customer>& data, int low, int high) {
    double pivot = data[high].salary;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (data[j].salary <= pivot) {
            i++;
            swapCustomers(data[i], data[j]);
        }
    }
    swapCustomers(data[i + 1], data[high]);
    return (i + 1);
}

/**
 * @brief Sorts a vector of Customers by salary using Quick Sort.
 */
void quickSortBySalary(vector<Customer>& data, int low, int high) {
    if (low < high) {
        int pi = partitionBySalary(data, low, high);
        quickSortBySalary(data, low, pi - 1);
        quickSortBySalary(data, pi + 1, high);
    }
}

/**
 * @brief Loads bank customer data, sorts it by salary, and saves the result.
 */
void bankCustomerSorting() {
    string input = "../bank_dataset.csv";
    vector<Customer> customers = loadBankData(input);

    if (customers.empty()) {
        cout << "\nError: Could not load bank customer data from " << input << endl;
        return;
    }

    cout << "\nBank Customer Data Sorting\n";
    cout << "===========================\n";
    cout << "Sorting " << customers.size() << " records by Estimated Salary...\n";
    
    quickSortBySalary(customers, 0, customers.size() - 1);

    ofstream fout("../results/sorted_bank_dataset.csv");
    fout << "customer_id,credit_score,country,gender,age,tenure,balance,products_number,credit_card,active_member,estimated_salary,churn\n";
    
    for (const auto& c : customers) {
        fout << c.id << "," << c.score << "," << c.country << "," << c.gender << ","
             << c.age << "," << c.tenure << "," << c.balance << "," << c.products << ","
             << c.card << "," << c.active << "," << fixed << setprecision(2) << c.salary << ","
             << c.churn << "\n";
    }

    cout << "Success! Sorted data saved to ../results/sorted_bank_dataset.csv\n";
}

// ============================================================================
// OPTION 3: Bank Customer Data Sorting with Sampling
// ============================================================================

/**
 * @brief Samples data from the main bank dataset.
 */
vector<Customer> sampleBankData(const vector<Customer>& allCustomers, int n, mt19937& rng) {
    vector<Customer> sampledData;
    if (allCustomers.empty() || n == 0) {
        return sampledData;
    }
    
    uniform_int_distribution<size_t> dist(0, allCustomers.size() - 1);
    
    for (int i = 0; i < n; ++i) {
        sampledData.push_back(allCustomers[dist(rng)]);
    }
    
    return sampledData;
}

/**
 * @brief Runs sorting on sampled bank customer data.
 */
void bankCustomerSamplingSorting() {
    string main_dataset_path = "../bank_dataset.csv";
    vector<Customer> allCustomers = loadBankData(main_dataset_path);

    if (allCustomers.empty()) {
        cout << "\nError: Could not load main bank customer data from " << main_dataset_path << endl;
        return;
    }

    mt19937 rng(time(nullptr));
    const int DATASETS = 10;

    cout << "\nBank Customer Data Sorting (with Sampling)\n";
    cout << "===========================================\n\n";

    for (int n = 10; n <= 100; n += 10) {
        cout << "n = " << setw(3) << n << ": ";
        for (int d = 0; d < DATASETS; d++) {
            // Sample data
            vector<Customer> sampledData = sampleBankData(allCustomers, n, rng);

            // Save unsorted sample
            string unsorted_filename = "../data/bank_sampled_n" + to_string(n) + "_d" + to_string(d+1) + ".csv";
            ofstream funsorted(unsorted_filename);
            funsorted << "customer_id,credit_score,country,gender,age,tenure,balance,products_number,credit_card,active_member,estimated_salary,churn\n";
            for (const auto& c : sampledData) {
                funsorted << c.id << "," << c.score << "," << c.country << "," << c.gender << ","
                         << c.age << "," << c.tenure << "," << c.balance << "," << c.products << ","
                         << c.card << "," << c.active << "," << fixed << setprecision(2) << c.salary << ","
                         << c.churn << "\n";
            }
            funsorted.close();

            // Sort the sampled data
            quickSortBySalary(sampledData, 0, sampledData.size() - 1);

            // Save sorted sample
            string sorted_filename = "../results/sorted_bank_sampled_n" + to_string(n) + "_d" + to_string(d+1) + ".csv";
            ofstream fsorted(sorted_filename);
            fsorted << "customer_id,credit_score,country,gender,age,tenure,balance,products_number,credit_card,active_member,estimated_salary,churn\n";
            for (const auto& c : sampledData) {
                fsorted << c.id << "," << c.score << "," << c.country << "," << c.gender << ","
                       << c.age << "," << c.tenure << "," << c.balance << "," << c.products << ","
                       << c.card << "," << c.active << "," << fixed << setprecision(2) << c.salary << ","
                       << c.churn << "\n";
            }
            fsorted.close();

            cout << ".";
        }
        cout << " Done.\n";
    }

    cout << "\nSuccess! Sampled, sorted data saved to ../results/ and ../data/ directories.\n";
}

// ============================================================================
// MAIN MENU
// ============================================================================

void displayMenu() {
    cout << "\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "|          QUICK SORT - MENU DRIVEN PROGRAM              |\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "\n";
    cout << "  1. Name-Age Records Performance Analysis(Generates datasets, sorts by age/name/combined)\n";
    cout << "\n";
    cout << "  2. Bank Customer Data Sorting(Sorts customer records by estimated salary)\n";  
    cout << "\n";
    cout << "  3. Bank Customer Data Sorting with Sampling\n";
    cout << "\n";
    cout << "  4. Exit\n";
    cout << "\n";
    cout << "----------------------------------------------------------\n";
    cout << "Enter your choice (1-4): ";
}

int main() {
    int choice;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                nameAgePerformanceAnalysis();
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
                
            case 2:
                bankCustomerSorting();
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
                
            case 3:
                bankCustomerSamplingSorting();
                cout << "\nPress Enter to continue...";
                cin.get();
                break;

            case 4:
                cout << "\nExited!\n";
                return 0;
                
            default:
                cout << "\nInvalid choice! Please select 1-4.\n";
        }
    }
    
    return 0;
}
