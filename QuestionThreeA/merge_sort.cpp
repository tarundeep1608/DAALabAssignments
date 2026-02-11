/**
 * @file merge_sort.cpp
 * @brief Merge Sort implementation on bank customer data.
 * @details Processes 10,000 rows and 12 columns, sorting by estimated salary.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure representing all 12 columns of the bank dataset
struct Customer {
    string id, score, country, gender, age, tenure, balance, products, card, active, churn;
    double salary; // Key used for sorting
};

// Loads all rows from the CSV file into a vector of Customer objects
vector<Customer> loadData(string filename) {
    vector<Customer> data;
    ifstream file(filename);
    string line, item;

    if (!file.is_open()) return data;

    getline(file, line); // Skip the header row
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, item, ',')) row.push_back(item); // Split by comma

        if (row.size() >= 12) {
            Customer c;
            c.id = row[0]; c.score = row[1]; c.country = row[2];
            c.gender = row[3]; c.age = row[4]; c.tenure = row[5];
            c.balance = row[6]; c.products = row[7]; c.card = row[8];
            c.active = row[9];
            try { c.salary = stod(row[10]); } catch (...) { c.salary = 0.0; } // Convert salary to double
            c.churn = row[11];
            data.push_back(c);
        }
    }
    return data;
}

// Merge helper function for merge sort
void merge(vector<Customer>& data, int left, int mid, int right) {
    vector<Customer> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (data[i].salary <= data[j].salary) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
    }
    while (j <= right) {
        temp[k++] = data[j++];
    }

    for (int i = 0; i < temp.size(); i++) {
        data[left + i] = temp[i];
    }
}

// Recursive merge sort function
void mergeSort(vector<Customer>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

int main() {
    string input = "dataset.csv";
    vector<Customer> customers = loadData(input);

    if (customers.empty()) {
        cout << "Error loading data." << endl;
        return 1;
    }

    cout << "Sorting " << customers.size() << " records by Estimated Salary..." << endl;
    mergeSort(customers, 0, customers.size() - 1);

    ofstream fout("sorted_dataset.csv");
    // Write original header back to the file
    fout << "customer_id,credit_score,country,gender,age,tenure,balance,products_number,credit_card,active_member,estimated_salary,churn\n";
    
    for (const auto& c : customers) {
        fout << c.id << "," << c.score << "," << c.country << "," << c.gender << ","
             << c.age << "," << c.tenure << "," << c.balance << "," << c.products << ","
             << c.card << "," << c.active << "," << fixed << setprecision(2) << c.salary << ","
             << c.churn << "\n";
    }

    cout << "Success! Sorted data saved to sorted_dataset.csv" << endl;
    return 0;
}
