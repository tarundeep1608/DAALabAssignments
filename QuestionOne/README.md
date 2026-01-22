# Question 1: Insertion Sort

Insertion Sort implementation for (Name, Age) records with **comparison and assignment counting**.

## Structure
```
QuestionOne/
├── src/
│   ├── insertion_sort.cpp   # C++ implementation
│   └── visualize.py         # Python visualization
├── data/                    # Generated datasets
├── results/                 # CSV results
├── plots/                   # Output graphs
└── README.md
```

## How to Run

### 1. Compile and Run C++ Program
```bash
cd src
g++ -o insertion_sort insertion_sort.cpp -std=c++11
./insertion_sort
```

The program will:
- Generate 10 random datasets for each size n (10, 20, ..., 100)
- Count **comparisons** and **assignments** for each sort operation
- Save results to CSV files in `results/` directory
- Save sample datasets to `data/` directory

### 2. Run Python Visualization
```bash
cd src
pip install pandas matplotlib scipy
python visualize.py
```

The visualization script will:
- Read comparison and assignment data from CSV files
- Generate plots with quadratic best-fit curves
- Save three graph files to `plots/` directory

## What is Counted

### Comparisons
- In insertion sort, a comparison occurs when we check if `data[j] > key`
- This happens in the while loop condition for each sorting function

### Assignments
The implementation counts three types of assignments in insertion sort:
1. **Key extraction**: `Record key = data[i]` - Storing the current element to insert
2. **Shifting elements**: `data[j + 1] = data[j]` - Moving elements to make space (inside while loop)
3. **Inserting key**: `data[j + 1] = key` - Placing the key in its correct position

## Output Files

### CSV Results (in `results/` directory)
- `sort_by_age.csv` - Comparison counts for sorting by age
- `sort_by_name.csv` - Comparison counts for sorting by name  
- `sort_combined.csv` - Comparison counts for combined sort
- `sort_by_age_assignments.csv` - Assignment counts for sorting by age
- `sort_by_name_assignments.csv` - Assignment counts for sorting by name
- `sort_combined_assignments.csv` - Assignment counts for combined sort
- `summary.csv` - Average comparisons and assignments for all methods

Format of individual sort CSV files (e.g., `sort_by_age.csv`):
```
n,dataset,comparisons
10,1,26
10,2,21
...
```

Format of summary CSV file:
```
n,avg_age_comp,avg_name_comp,avg_combined_comp,avg_age_assign,avg_name_assign,avg_combined_assign
10,26.70,27.10,54.50,39.00,38.40,78.20
...
```

### Graphs (in `plots/` directory)
- `insertion_sort_analysis.png` - Four subplots showing comparison analysis:
  - (a) Sort by Age with quadratic fit
  - (b) Sort by Name with quadratic fit
  - (c) Combined Sort with quadratic fit
  - (d) All methods comparison
- `insertion_sort_assignments.png` - Four subplots showing assignment analysis:
  - (a) Sort by Age with quadratic fit
  - (b) Sort by Name with quadratic fit
  - (c) Combined Sort with quadratic fit
  - (d) All methods comparison
- `insertion_sort_combined_comparison.png` - Three subplots comparing comparisons vs assignments:
  - (a) Sort by Age: Comparisons vs Assignments
  - (b) Sort by Name: Comparisons vs Assignments
  - (c) Combined Sort: Comparisons vs Assignments

## Algorithm Analysis

Both comparisons and assignments follow a **quadratic growth pattern** (O(n²)), which is characteristic of Insertion Sort in the average and worst cases. The best-fit curves show the relationship:

**Comparisons**: `an² + bn + c` where `a ≈ 0.23-0.45`  
**Assignments**: `an² + bn + c` where `a ≈ 0.23-0.45`

The similarity in growth rates indicates that both operations contribute similarly to the overall time complexity of the algorithm.
