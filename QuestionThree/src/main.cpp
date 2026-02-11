/**
 * @file main.cpp
 * @brief Menu-driven program for merge sort implementations
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

/**
 * @brief Merges two subarrays of Records, sorted by age.
 * @param data The vector of Records.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 */
void mergeByAge(vector<Record>& data, int left, int mid, int right) {
    vector<Record> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        comparisons++;
        if (data[i].age <= data[j].age) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
        assignments++;
    }

    while (i <= mid) {
        temp[k++] = data[i++];
        assignments++;
    }
    while (j <= right) {
        temp[k++] = data[j++];
        assignments++;
    }

    for (int l = 0; l < temp.size(); l++) {
        data[left + l] = temp[l];
        assignments++;
    }
}

/**
 * @brief Sorts a vector of Records by age using merge sort.
 * @param data The vector of Records to sort.
 * @param left The starting index of the array to be sorted.
 * @param right The ending index of the array to be sorted.
 */
void mergeSortByAge(vector<Record>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByAge(data, left, mid);
        mergeSortByAge(data, mid + 1, right);
        mergeByAge(data, left, mid, right);
    }
}

/**
 * @brief Merges two subarrays of Records, sorted by name.
 * @param data The vector of Records.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 */
void mergeByName(vector<Record>& data, int left, int mid, int right) {
    vector<Record> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        comparisons++;
        if (data[i].name <= data[j].name) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
        assignments++;
    }

    while (i <= mid) {
        temp[k++] = data[i++];
        assignments++;
    }
    while (j <= right) {
        temp[k++] = data[j++];
        assignments++;
    }

    for (int l = 0; l < temp.size(); l++) {
        data[left + l] = temp[l];
        assignments++;
    }
}

/**
 * @brief Sorts a vector of Records by name using merge sort.
 * @param data The vector of Records to sort.
 * @param left The starting index of the array to be sorted.
 * @param right The ending index of the array to be sorted.
 */
void mergeSortByName(vector<Record>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByName(data, left, mid);
        mergeSortByName(data, mid + 1, right);
        mergeByName(data, left, mid, right);
    }
}

/**
 * @brief Merges two subarrays of Records, sorted first by name, then by age.
 * @param data The vector of Records.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 */
void mergeByNameThenAge(vector<Record>& data, int left, int mid, int right) {
    vector<Record> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        comparisons++;
        if (data[i].name < data[j].name) {
            temp[k++] = data[i++];
            assignments++;
        } else if (data[i].name > data[j].name) {
            temp[k++] = data[j++];
            assignments++;
        } else {
            comparisons++;
            if (data[i].age <= data[j].age) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
            }
            assignments++;
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
        assignments++;
    }
    while (j <= right) {
        temp[k++] = data[j++];
        assignments++;
    }

    for (int l = 0; l < temp.size(); l++) {
        data[left + l] = temp[l];
        assignments++;
    }
}

/**
 * @brief Sorts a vector of Records by name then age using merge sort.
 * @param data The vector of Records to sort.
 * @param left The starting index of the array to be sorted.
 * @param right The ending index of the array to be sorted.
 */
void mergeSortByNameThenAge(vector<Record>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByNameThenAge(data, left, mid);
        mergeSortByNameThenAge(data, mid + 1, right);
        mergeByNameThenAge(data, left, mid, right);
    }
}

/**
 * @brief Runs performance analysis for merge sort on Name-Age records.
 * @details Generates datasets, sorts them by age, name, and a combination of name and age.
 * It records the number of comparisons and assignments for each sort and saves the results to CSV files.
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
    
    cout << "\nMerge Sort Performance Analysis (Name-Age Records)\n";
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
                mergeSortByAge(data, 0, data.size() - 1);
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
                mergeSortByName(data, 0, data.size() - 1);
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
                mergeSortByNameThenAge(data, 0, data.size() - 1);
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

/**
 * @brief Loads bank customer data from a CSV file.
 * @param filename The path to the CSV file.
 * @return A vector of Customer objects.
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
 * @brief Merges two subarrays of Customers, sorted by salary.
 * @param data The vector of Customers.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 */
void mergeBySalary(vector<Customer>& data, int left, int mid, int right) {
    vector<Customer> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (data[i].salary <= data[j].salary) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) temp[k++] = data[i++];
    while (j <= right) temp[k++] = data[j++];

    for (int l = 0; l < temp.size(); l++) {
        data[left + l] = temp[l];
    }
}

/**
 * @brief Sorts a vector of Customers by salary using merge sort.
 * @param data The vector of Customers to sort.
 * @param left The starting index of the array to be sorted.
 * @param right The ending index of the array to be sorted.
 */
void mergeSortBySalary(vector<Customer>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortBySalary(data, left, mid);
        mergeSortBySalary(data, mid + 1, right);
        mergeBySalary(data, left, mid, right);
    }
}

/**
 * @brief Loads bank customer data, sorts it by salary, and saves the result.
 * @details Reads data from `../bank_dataset.csv`, sorts it, and writes the sorted data
 * to `../results/sorted_bank_dataset.csv`.
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
    
    mergeSortBySalary(customers, 0, customers.size() - 1);

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
// MAIN MENU
// ============================================================================

/**
 * @brief Displays the main menu of the program.
 */
void displayMenu() {
    cout << "\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "|          MERGE SORT - MENU DRIVEN PROGRAM              |\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "\n";
    cout << "  1. Name-Age Records Performance Analysis(Generates datasets, sorts by age/name/combined)\n";
    cout << "\n";
    cout << "  2. Bank Customer Data Sorting(Sorts customer records by estimated salary)\n";  
    cout << "\n";
    cout << "  3. Exit\n";
    cout << "\n";
    cout << "----------------------------------------------------------\n";
    cout << "Enter your choice (1-3): ";
}

/**
 * @brief The main function of the program.
 * @return 0 on successful execution.
 */
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
                cout << "\nExited!\n";
                return 0;
                
            default:
                cout << "\nInvalid choice! Please select 1-3.\n";
        }
    }
    
    return 0;
}
