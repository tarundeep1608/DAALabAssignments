# Question 4: Quick Sort and Comparison

Quick Sort implementation for (Name, Age) records and Bank Customer data, with comparison against Insertion Sort and Merge Sort results.

## Structure
```
QuestionFour/
├── src/
│   ├── main.cpp             # C++ implementation (Quick Sort)
│   └── visualize.py         # Python visualization
├── data/                    # Generated datasets
├── results/                 # CSV results (Quick Sort)
├── comparison_data/         # Results from previous questions
│   ├── merge_sort/          # Merge Sort summary
│   └── insertion_sort/      # Insertion Sort summary
├── plots/                   # Output graphs
└── README.md
```

## How to Run

### 1. Compile and Run C++ Program
```bash
cd src
g++ -o main main.cpp -std=c++11
./main
```

The program will present a menu:
1.  **Name-Age Records Performance Analysis**: Run this to generate Quick Sort performance data.
    - Generates 10 random datasets for each size n (10 to 100).
    - Sorts by Age, Name, and Combined (Name then Age).
    - Saves results to `results/`.
2.  **Bank Customer Data Sorting**: Sorts the full bank dataset by salary.
3.  **Bank Customer Data Sorting with Sampling**: Sorts sampled subsets of the bank data.

### 2. Run Python Visualization
```bash
cd src
pip install pandas matplotlib scipy
python visualize.py
```

The visualization script will:
- Read Quick Sort results from `../results/summary.csv`.
- Read Merge Sort results from `../comparison_data/merge_sort/results/summary.csv`.
- Read Insertion Sort results from `../comparison_data/insertion_sort/results/summary.csv`.
- Generate comparison plots fitting $O(n \log n)$ for Quick/Merge and $O(n^2)$ for Insertion.
- Save graphs to `plots/` directory.

## Algorithm Details

### Quick Sort
- **Time Complexity**: Average $O(n \log n)$, Worst Case $O(n^2)$.
- **Space Complexity**: $O(\log n)$ (recursion stack).
- **Partitioning**: Uses the last element as pivot.

### Comparisons vs Assignments
- **Comparisons**: Counted inside partitioning logic.
- **Assignments**: Counted during swaps.
