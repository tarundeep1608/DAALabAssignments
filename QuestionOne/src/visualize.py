"""
@file visualize.py
@brief Plot insertion sort results with best-fit curves
"""

import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Change to script directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

def quadratic(x, a, b, c):
    """Quadratic function: ax² + bx + c"""
    return a * x**2 + b * x + c

# Read data
df = pd.read_csv('../results/summary.csv')
n = df['n'].values
avg_age_comp = df['avg_age_comp'].values
avg_name_comp = df['avg_name_comp'].values
avg_combined_comp = df['avg_combined_comp'].values
avg_age_assign = df['avg_age_assign'].values
avg_name_assign = df['avg_name_assign'].values
avg_combined_assign = df['avg_combined_assign'].values

# Fit curves for comparisons
x_fit = np.linspace(10, 100, 100)
p_age_comp, _ = curve_fit(quadratic, n, avg_age_comp)
p_name_comp, _ = curve_fit(quadratic, n, avg_name_comp)
p_comb_comp, _ = curve_fit(quadratic, n, avg_combined_comp)

# Fit curves for assignments
p_age_assign, _ = curve_fit(quadratic, n, avg_age_assign)
p_name_assign, _ = curve_fit(quadratic, n, avg_name_assign)
p_comb_assign, _ = curve_fit(quadratic, n, avg_combined_assign)

# Create plots for comparisons
fig, axes = plt.subplots(2, 2, figsize=(12, 9))
fig.suptitle('Insertion Sort: Average Comparisons vs n', fontsize=14, fontweight='bold')

# Plot 1: Sort by Age
ax = axes[0, 0]
ax.scatter(n, avg_age_comp, c='blue', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_age_comp), 'r-', lw=2, 
        label=f'{p_age_comp[0]:.4f}n² + {p_age_comp[1]:.2f}n + {p_age_comp[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(a) Sort by Age')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 2: Sort by Name
ax = axes[0, 1]
ax.scatter(n, avg_name_comp, c='green', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_name_comp), 'r-', lw=2,
        label=f'{p_name_comp[0]:.4f}n² + {p_name_comp[1]:.2f}n + {p_name_comp[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(b) Sort by Name')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 3: Combined Sort
ax = axes[1, 0]
ax.scatter(n, avg_combined_comp, c='purple', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_comb_comp), 'r-', lw=2,
        label=f'{p_comb_comp[0]:.4f}n² + {p_comb_comp[1]:.2f}n + {p_comb_comp[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('(c) Combined Sort')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 4: All together
ax = axes[1, 1]
ax.scatter(n, avg_age_comp, c='blue', s=60, label='By Age')
ax.scatter(n, avg_name_comp, c='green', s=60, label='By Name')
ax.scatter(n, avg_combined_comp, c='purple', s=60, label='Combined')
ax.plot(x_fit, quadratic(x_fit, *p_age_comp), 'b--', alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_name_comp), 'g--', alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_comb_comp), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Comparisons')
ax.set_title('All Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/insertion_sort_analysis.png', dpi=150)
plt.close()

# Create plots for assignments
fig, axes = plt.subplots(2, 2, figsize=(12, 9))
fig.suptitle('Insertion Sort: Average Assignments vs n', fontsize=14, fontweight='bold')

# Plot 1: Sort by Age
ax = axes[0, 0]
ax.scatter(n, avg_age_assign, c='blue', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_age_assign), 'r-', lw=2, 
        label=f'{p_age_assign[0]:.4f}n² + {p_age_assign[1]:.2f}n + {p_age_assign[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(a) Sort by Age')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 2: Sort by Name
ax = axes[0, 1]
ax.scatter(n, avg_name_assign, c='green', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_name_assign), 'r-', lw=2,
        label=f'{p_name_assign[0]:.4f}n² + {p_name_assign[1]:.2f}n + {p_name_assign[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(b) Sort by Name')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 3: Combined Sort
ax = axes[1, 0]
ax.scatter(n, avg_combined_assign, c='purple', s=60, zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_comb_assign), 'r-', lw=2,
        label=f'{p_comb_assign[0]:.4f}n² + {p_comb_assign[1]:.2f}n + {p_comb_assign[2]:.2f}')
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('(c) Combined Sort')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 4: All together
ax = axes[1, 1]
ax.scatter(n, avg_age_assign, c='blue', s=60, label='By Age')
ax.scatter(n, avg_name_assign, c='green', s=60, label='By Name')
ax.scatter(n, avg_combined_assign, c='purple', s=60, label='Combined')
ax.plot(x_fit, quadratic(x_fit, *p_age_assign), 'b--', alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_name_assign), 'g--', alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_comb_assign), 'purple', linestyle='--', alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Assignments')
ax.set_title('All Methods Comparison')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/insertion_sort_assignments.png', dpi=150)
plt.close()

# Create combined comparison chart
fig, axes = plt.subplots(3, 1, figsize=(12, 12))
fig.suptitle('Insertion Sort: Comparisons vs Assignments', fontsize=14, fontweight='bold')

# Plot 1: Sort by Age - Comparisons vs Assignments
ax = axes[0]
ax.scatter(n, avg_age_comp, c='blue', s=60, label='Comparisons', zorder=5)
ax.scatter(n, avg_age_assign, c='red', s=60, label='Assignments', zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_age_comp), 'b--', lw=2, alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_age_assign), 'r--', lw=2, alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Count')
ax.set_title('(a) Sort by Age: Comparisons vs Assignments')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 2: Sort by Name - Comparisons vs Assignments
ax = axes[1]
ax.scatter(n, avg_name_comp, c='green', s=60, label='Comparisons', zorder=5)
ax.scatter(n, avg_name_assign, c='orange', s=60, label='Assignments', zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_name_comp), 'g--', lw=2, alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_name_assign), 'orange', linestyle='--', lw=2, alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Count')
ax.set_title('(b) Sort by Name: Comparisons vs Assignments')
ax.legend()
ax.grid(True, alpha=0.3)

# Plot 3: Combined Sort - Comparisons vs Assignments
ax = axes[2]
ax.scatter(n, avg_combined_comp, c='purple', s=60, label='Comparisons', zorder=5)
ax.scatter(n, avg_combined_assign, c='brown', s=60, label='Assignments', zorder=5)
ax.plot(x_fit, quadratic(x_fit, *p_comb_comp), 'purple', linestyle='--', lw=2, alpha=0.7)
ax.plot(x_fit, quadratic(x_fit, *p_comb_assign), 'brown', linestyle='--', lw=2, alpha=0.7)
ax.set_xlabel('n')
ax.set_ylabel('Count')
ax.set_title('(c) Combined Sort: Comparisons vs Assignments')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/insertion_sort_combined_comparison.png', dpi=150)
plt.close()

# Print results
print("\n" + "="*60)
print("BEST-FIT CURVES FOR COMPARISONS (an² + bn + c)")
print("="*60)
print(f"Sort by Age:    {p_age_comp[0]:.4f}n² + {p_age_comp[1]:.2f}n + {p_age_comp[2]:.2f}")
print(f"Sort by Name:   {p_name_comp[0]:.4f}n² + {p_name_comp[1]:.2f}n + {p_name_comp[2]:.2f}")
print(f"Combined:       {p_comb_comp[0]:.4f}n² + {p_comb_comp[1]:.2f}n + {p_comb_comp[2]:.2f}")
print("="*60)

print("\n" + "="*60)
print("BEST-FIT CURVES FOR ASSIGNMENTS (an² + bn + c)")
print("="*60)
print(f"Sort by Age:    {p_age_assign[0]:.4f}n² + {p_age_assign[1]:.2f}n + {p_age_assign[2]:.2f}")
print(f"Sort by Name:   {p_name_assign[0]:.4f}n² + {p_name_assign[1]:.2f}n + {p_name_assign[2]:.2f}")
print(f"Combined:       {p_comb_assign[0]:.4f}n² + {p_comb_assign[1]:.2f}n + {p_comb_assign[2]:.2f}")
print("="*60)

print("\nPlots saved:")
print("  - ../plots/insertion_sort_analysis.png (comparisons)")
print("  - ../plots/insertion_sort_assignments.png (assignments)")
print("  - ../plots/insertion_sort_combined_comparison.png (combined)")

