"""
@file visualize.py
@brief Plot merge sort and insertion sort results with best-fit curves
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

# --- Read Merge Sort Data ---
df_merge = pd.read_csv('../results/summary.csv')
n_merge = df_merge['n'].values
avg_age_comp_merge = df_merge['avg_age_comp'].values
avg_name_comp_merge = df_merge['avg_name_comp'].values
avg_combined_comp_merge = df_merge['avg_combined_comp'].values
avg_age_assign_merge = df_merge['avg_age_assign'].values
avg_name_assign_merge = df_merge['avg_name_assign'].values
avg_combined_assign_merge = df_merge['avg_combined_assign'].values

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
    
    # Fit curves for insertion sort (O(n^2))
    p_age_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_age_comp_insertion)
    p_name_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_name_comp_insertion)
    p_comb_comp_insertion, _ = curve_fit(n_squared, n_insertion, avg_combined_comp_insertion)
    p_age_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_age_assign_insertion)
    p_name_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_name_assign_insertion)
    p_comb_assign_insertion, _ = curve_fit(n_squared, n_insertion, avg_combined_assign_insertion)
else:
    df_insertion = None
    print(f"Warning: Insertion sort summary file not found at {insertion_sort_summary_path}")

# Fit curves for merge sort comparisons (O(n*log(n)))
x_fit = np.linspace(10, 100, 400)
p_age_comp_merge, _ = curve_fit(nlogn, n_merge, avg_age_comp_merge)
p_name_comp_merge, _ = curve_fit(nlogn, n_merge, avg_name_comp_merge)
p_comb_comp_merge, _ = curve_fit(nlogn, n_merge, avg_combined_comp_merge)

# Fit curves for merge sort assignments (O(n*log(n)))
p_age_assign_merge, _ = curve_fit(nlogn, n_merge, avg_age_assign_merge)
p_name_assign_merge, _ = curve_fit(nlogn, n_merge, avg_name_assign_merge)
p_comb_assign_merge, _ = curve_fit(nlogn, n_merge, avg_combined_assign_merge)

# --- Create Comparison Plots ---
fig, axes = plt.subplots(2, 2, figsize=(14, 11))
fig.suptitle('Merge Sort vs Insertion Sort: Average Comparisons', fontsize=16, fontweight='bold')

# Plot 1: Sort by Age
ax = axes[0, 0]
ax.scatter(n_merge, avg_age_comp_merge, c='blue', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_age_comp_merge), 'b--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_age_comp_insertion, c='red', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_age_comp_insertion), 'r:', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(a) Sort by Age')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 2: Sort by Name
ax = axes[0, 1]
ax.scatter(n_merge, avg_name_comp_merge, c='green', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_name_comp_merge), 'g--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_name_comp_insertion, c='orange', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_name_comp_insertion), 'orange', linestyle=':', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(b) Sort by Name')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 3: Combined Sort
ax = axes[1, 0]
ax.scatter(n_merge, avg_combined_comp_merge, c='purple', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_comb_comp_merge), 'purple', linestyle='--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_combined_comp_insertion, c='brown', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_comb_comp_insertion), 'brown', linestyle=':', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(c) Combined Sort')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 4: All Merge Sort Methods
ax = axes[1, 1]
ax.scatter(n_merge, avg_age_comp_merge, c='blue', s=60, label='Age (Merge)')
ax.scatter(n_merge, avg_name_comp_merge, c='green', s=60, label='Name (Merge)')
ax.scatter(n_merge, avg_combined_comp_merge, c='purple', s=60, label='Combined (Merge)')
ax.plot(x_fit, nlogn(x_fit, *p_age_comp_merge), 'b--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_name_comp_merge), 'g--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_comb_comp_merge), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('Merge Sort Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('../plots/merge_vs_insertion_comparisons.png', dpi=150)
plt.close()

# --- Create Assignment Comparison Plots ---
fig, axes = plt.subplots(2, 2, figsize=(14, 11))
fig.suptitle('Merge Sort vs Insertion Sort: Average Assignments', fontsize=16, fontweight='bold')

# Plot 1: Sort by Age
ax = axes[0, 0]
ax.scatter(n_merge, avg_age_assign_merge, c='blue', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_age_assign_merge), 'b--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_age_assign_insertion, c='red', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_age_assign_insertion), 'r:', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(a) Sort by Age')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 2: Sort by Name
ax = axes[0, 1]
ax.scatter(n_merge, avg_name_assign_merge, c='green', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_name_assign_merge), 'g--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_name_assign_insertion, c='orange', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_name_assign_insertion), 'orange', linestyle=':', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(b) Sort by Name')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 3: Combined Sort
ax = axes[1, 0]
ax.scatter(n_merge, avg_combined_assign_merge, c='purple', s=60, label='Merge Sort', zorder=5)
ax.plot(x_fit, nlogn(x_fit, *p_comb_assign_merge), 'purple', linestyle='--', lw=2, alpha=0.7, label='Merge Sort Fit (n log n)')
if df_insertion is not None:
    ax.scatter(n_insertion, avg_combined_assign_insertion, c='brown', s=60, marker='x', label='Insertion Sort', zorder=5)
    ax.plot(x_fit, n_squared(x_fit, *p_comb_assign_insertion), 'brown', linestyle=':', lw=2, alpha=0.7, label='Insertion Sort Fit (n^2)')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(c) Combined Sort')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 4: All Merge Sort Methods
ax = axes[1, 1]
ax.scatter(n_merge, avg_age_assign_merge, c='blue', s=60, label='Age (Merge)')
ax.scatter(n_merge, avg_name_assign_merge, c='green', s=60, label='Name (Merge)')
ax.scatter(n_merge, avg_combined_assign_merge, c='purple', s=60, label='Combined (Merge)')
ax.plot(x_fit, nlogn(x_fit, *p_age_assign_merge), 'b--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_name_assign_merge), 'g--', alpha=0.7)
ax.plot(x_fit, nlogn(x_fit, *p_comb_assign_merge), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('Merge Sort Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('../plots/merge_vs_insertion_assignments.png', dpi=150)
plt.close()

# Print results
print("\n" + "="*60)
print("BEST-FIT CURVES FOR MERGE SORT (a*n*log(n) + b)")
print("="*60)
print("--- Comparisons ---")
print(f"Sort by Age:    {p_age_comp_merge[0]:.4f}n*log(n) + {p_age_comp_merge[1]:.2f}")
print(f"Sort by Name:   {p_name_comp_merge[0]:.4f}n*log(n) + {p_name_comp_merge[1]:.2f}")
print(f"Combined:       {p_comb_comp_merge[0]:.4f}n*log(n) + {p_comb_comp_merge[1]:.2f}")
print("\n--- Assignments ---")
print(f"Sort by Age:    {p_age_assign_merge[0]:.4f}n*log(n) + {p_age_assign_merge[1]:.2f}")
print(f"Sort by Name:   {p_name_assign_merge[0]:.4f}n*log(n) + {p_name_assign_merge[1]:.2f}")
print(f"Combined:       {p_comb_assign_merge[0]:.4f}n*log(n) + {p_comb_assign_merge[1]:.2f}")
print("="*60)

if df_insertion is not None:
    print("\n" + "="*60)
    print("BEST-FIT CURVES FOR INSERTION SORT (a*n^2 + b*n + c)")
    print("="*60)
    print("--- Comparisons ---")
    print(f"Sort by Age:    {p_age_comp_insertion[0]:.4f}n^2 + {p_age_comp_insertion[1]:.2f}n + {p_age_comp_insertion[2]:.2f}")
    print(f"Sort by Name:   {p_name_comp_insertion[0]:.4f}n^2 + {p_name_comp_insertion[1]:.2f}n + {p_name_comp_insertion[2]:.2f}")
    print(f"Combined:       {p_comb_comp_insertion[0]:.4f}n^2 + {p_comb_comp_insertion[1]:.2f}n + {p_comb_comp_insertion[2]:.2f}")
    print("\n--- Assignments ---")
    print(f"Sort by Age:    {p_age_assign_insertion[0]:.4f}n^2 + {p_age_assign_insertion[1]:.2f}n + {p_age_assign_insertion[2]:.2f}")
    print(f"Sort by Name:   {p_name_assign_insertion[0]:.4f}n^2 + {p_name_assign_insertion[1]:.2f}n + {p_name_assign_insertion[2]:.2f}")
    print(f"Combined:       {p_comb_assign_insertion[0]:.4f}n^2 + {p_comb_assign_insertion[1]:.2f}n + {p_comb_assign_insertion[2]:.2f}")
    print("="*60)

print("\nPlots saved:")
print("  - ../plots/merge_vs_insertion_comparisons.png")
print("  - ../plots/merge_vs_insertion_assignments.png")


