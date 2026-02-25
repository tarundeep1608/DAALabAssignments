"""
@file visualize.py
@brief Plot quick sort, merge sort and insertion sort results with best-fit curves
"""

import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Change to script directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

def nlogn(x, a, b):
    """Linear function of n*log(n): a*n*log(n) + b"""
    # Ensure x is positive to avoid log of non-positive numbers
    x_safe = np.maximum(x, 1e-9)
    return a * x_safe * np.log(x_safe) + b

def n_squared(x, a, b, c):
    """Quadratic function: a*n^2 + b*n + c"""
    return a * x**2 + b * x + c

# --- Read Quick Sort Data ---
df_quick = pd.read_csv('../results/summary.csv')
n_quick = df_quick['n'].values
avg_age_comp_quick = df_quick['avg_age_comp'].values
avg_name_comp_quick = df_quick['avg_name_comp'].values
avg_combined_comp_quick = df_quick['avg_combined_comp'].values
avg_age_assign_quick = df_quick['avg_age_assign'].values
avg_name_assign_quick = df_quick['avg_name_assign'].values
avg_combined_assign_quick = df_quick['avg_combined_assign'].values

# --- Read Merge Sort Data ---
merge_sort_summary_path = '../comparison_data/merge_sort/results/summary.csv'
if os.path.exists(merge_sort_summary_path):
    df_merge = pd.read_csv(merge_sort_summary_path)
    n_merge = df_merge['n'].values
    avg_age_comp_merge = df_merge['avg_age_comp'].values
    avg_name_comp_merge = df_merge['avg_name_comp'].values
    avg_combined_comp_merge = df_merge['avg_combined_comp'].values
    avg_age_assign_merge = df_merge['avg_age_assign'].values
    avg_name_assign_merge = df_merge['avg_name_assign'].values
    avg_combined_assign_merge = df_merge['avg_combined_assign'].values
else:
    df_merge = None
    print(f"Warning: Merge sort summary file not found at {merge_sort_summary_path}")

# --- Read Insertion Sort Data ---
insertion_sort_summary_path = '../comparison_data/insertion_sort/results/summary.csv'
if os.path.exists(insertion_sort_summary_path):
    df_insertion = pd.read_csv(insertion_sort_summary_path)
    n_insertion = df_insertion['n'].values
    avg_age_comp_insertion = df_insertion['avg_age_comp'].values
    avg_name_comp_insertion = df_insertion['avg_name_comp'].values
    avg_combined_comp_insertion = df_insertion['avg_combined_comp'].values
    avg_age_assign_insertion = df_insertion['avg_age_assign'].values
    avg_name_assign_insertion = df_insertion['avg_name_assign'].values
    avg_combined_assign_insertion = df_insertion['avg_combined_assign'].values
else:
    df_insertion = None
    print(f"Warning: Insertion sort summary file not found at {insertion_sort_summary_path}")

# Fit curves
x_fit = np.linspace(10, 100, 400)

# Quick Sort (n log n)
p_age_comp_quick, _ = curve_fit(nlogn, n_quick, avg_age_comp_quick)
p_name_comp_quick, _ = curve_fit(nlogn, n_quick, avg_name_comp_quick)
p_comb_comp_quick, _ = curve_fit(nlogn, n_quick, avg_combined_comp_quick)
p_age_assign_quick, _ = curve_fit(nlogn, n_quick, avg_age_assign_quick)
p_name_assign_quick, _ = curve_fit(nlogn, n_quick, avg_name_assign_quick)
p_comb_assign_quick, _ = curve_fit(nlogn, n_quick, avg_combined_assign_quick)

# Merge Sort (n log n)
if df_merge is not None:
    p_age_comp_merge, _ = curve_fit(nlogn, n_merge, avg_age_comp_merge)
    p_name_comp_merge, _ = curve_fit(nlogn, n_merge, avg_name_comp_merge)
    p_comb_comp_merge, _ = curve_fit(nlogn, n_merge, avg_combined_comp_merge)
    p_age_assign_merge, _ = curve_fit(nlogn, n_merge, avg_age_assign_merge)
    p_name_assign_merge, _ = curve_fit(nlogn, n_merge, avg_name_assign_merge)
    p_comb_assign_merge, _ = curve_fit(nlogn, n_merge, avg_combined_assign_merge)

# Insertion Sort (n^2)
if df_insertion is not None:
    p_age_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_age_comp_insertion)
    p_name_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_name_comp_insertion)
    p_comb_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_combined_comp_insertion)
    p_age_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_age_assign_insertion)
    p_name_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_name_assign_insertion)
    p_comb_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_combined_assign_insertion)


# --- Create Comparison Plots (Comparisons) ---
fig, axes = plt.subplots(2, 2, figsize=(14, 11))
fig.suptitle('Quick Sort vs Merge Sort vs Insertion Sort: Average Comparisons', fontsize=16, fontweight='bold')

def plot_comparison(ax, title, y_label, quick_data, quick_fit, merge_data, merge_fit, insert_data, insert_fit):
    # Quick Sort
    ax.scatter(n_quick, quick_data, c='blue', s=60, label='Quick Sort', zorder=5)
    ax.plot(x_fit, nlogn(x_fit, *quick_fit), 'b-', lw=2, alpha=0.7, label='Quick Sort Fit (n log n)')
    
    # Merge Sort
    if df_merge is not None:
        ax.scatter(n_merge, merge_data, c='green', s=60, marker='s', label='Merge Sort', zorder=5)
        ax.plot(x_fit, nlogn(x_fit, *merge_fit), 'g--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
        
    # Insertion Sort
    if df_insertion is not None:
        ax.scatter(n_insertion, insert_data, c='red', s=60, marker='x', label='Insertion Sort', zorder=5)
        ax.plot(x_fit, n_squared(x_fit, *insert_fit), 'r:', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
        
    ax.set_xlabel('n')
    ax.set_ylabel(y_label)
    ax.set_title(title)
    ax.legend()
    ax.grid(True, alpha=0.3)

# Plot 1: Sort by Age
plot_comparison(axes[0, 0], '(a) Sort by Age', 'Comparisons', 
               avg_age_comp_quick, p_age_comp_quick,
               avg_age_comp_merge if df_merge is not None else None, p_age_comp_merge if df_merge is not None else None,
               avg_age_comp_insertion if df_insertion is not None else None, p_age_comp_insertion if df_insertion is not None else None)

# Plot 2: Sort by Name
plot_comparison(axes[0, 1], '(b) Sort by Name', 'Comparisons',
               avg_name_comp_quick, p_name_comp_quick,
               avg_name_comp_merge if df_merge is not None else None, p_name_comp_merge if df_merge is not None else None,
               avg_name_comp_insertion if df_insertion is not None else None, p_name_comp_insertion if df_insertion is not None else None)

# Plot 3: Combined Sort
plot_comparison(axes[1, 0], '(c) Combined Sort', 'Comparisons',
               avg_combined_comp_quick, p_comb_comp_quick,
               avg_combined_comp_merge if df_merge is not None else None, p_comb_comp_merge if df_merge is not None else None,
               avg_combined_comp_insertion if df_insertion is not None else None, p_comb_comp_insertion if df_insertion is not None else None)

# Plot 4: Quick Sort Summary
ax = axes[1, 1]
ax.scatter(n_quick, avg_age_comp_quick, c='blue', s=60, label='Age (Quick)')
ax.scatter(n_quick, avg_name_comp_quick, c='cyan', s=60, label='Name (Quick)')
ax.scatter(n_quick, avg_combined_comp_quick, c='purple', s=60, label='Combined (Quick)')
ax.plot(x_fit, nlogn(x_fit, *p_age_comp_quick), 'b--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_name_comp_quick), 'c--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_comb_comp_quick), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('Quick Sort Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('../plots/comparison_plots_comparisons.png', dpi=150)
plt.close()


# --- Create Comparison Plots (Assignments) ---
fig, axes = plt.subplots(2, 2, figsize=(14, 11))
fig.suptitle('Quick Sort vs Merge Sort vs Insertion Sort: Average Assignments', fontsize=16, fontweight='bold')

# Plot 1: Sort by Age
plot_comparison(axes[0, 0], '(a) Sort by Age', 'Assignments', 
               avg_age_assign_quick, p_age_assign_quick,
               avg_age_assign_merge if df_merge is not None else None, p_age_assign_merge if df_merge is not None else None,
               avg_age_assign_insertion if df_insertion is not None else None, p_age_assign_insertion if df_insertion is not None else None)

# Plot 2: Sort by Name
plot_comparison(axes[0, 1], '(b) Sort by Name', 'Assignments',
               avg_name_assign_quick, p_name_assign_quick,
               avg_name_assign_merge if df_merge is not None else None, p_name_assign_merge if df_merge is not None else None,
               avg_name_assign_insertion if df_insertion is not None else None, p_name_assign_insertion if df_insertion is not None else None)

# Plot 3: Combined Sort
plot_comparison(axes[1, 0], '(c) Combined Sort', 'Assignments',
               avg_combined_assign_quick, p_comb_assign_quick,
               avg_combined_assign_merge if df_merge is not None else None, p_comb_assign_merge if df_merge is not None else None,
               avg_combined_assign_insertion if df_insertion is not None else None, p_comb_assign_insertion if df_insertion is not None else None)

# Plot 4: Quick Sort Summary
ax = axes[1, 1]
ax.scatter(n_quick, avg_age_assign_quick, c='blue', s=60, label='Age (Quick)')
ax.scatter(n_quick, avg_name_assign_quick, c='cyan', s=60, label='Name (Quick)')
ax.scatter(n_quick, avg_combined_assign_quick, c='purple', s=60, label='Combined (Quick)')
ax.plot(x_fit, nlogn(x_fit, *p_age_assign_quick), 'b--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_name_assign_quick), 'c--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_comb_assign_quick), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('Quick Sort Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('../plots/comparison_plots_assignments.png', dpi=150)
plt.close()
