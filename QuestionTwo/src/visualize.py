"""
@file visualize.py
@brief Plot insertion sort results for F1 Qualifying
"""

import os
import pandas as pd
import matplotlib.pyplot as plt

# Change to script directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))
# Create plots directory if it doesn't exist
os.makedirs('../plots', exist_ok=True)

# Read data
df = pd.read_csv('../results/summary.csv')
n = df['n'].values
avg_comp = df['avg_comparisons'].values
avg_assign = df['avg_assignments'].values


# ============================================================
# Plot 1: Comparisons vs n
# ============================================================
fig, ax = plt.subplots(figsize=(10, 6))

ax.scatter(n, avg_comp, c='#E10600', s=80, zorder=5, edgecolors='black', linewidths=1)
ax.plot(n, avg_comp, '#E10600', lw=2, alpha=0.7)
ax.set_xlabel('Number of Lap Times (n)', fontsize=12)
ax.set_ylabel('Average Comparisons', fontsize=12)
ax.set_title('F1 Qualifying: Comparisons vs n', fontsize=14, fontweight='bold')
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/comparisons_vs_n.png', dpi=150)
plt.close()

# ============================================================
# Plot 2: Assignments vs n
# ============================================================
fig, ax = plt.subplots(figsize=(10, 6))

ax.scatter(n, avg_assign, c='#1E41FF', s=80, zorder=5, edgecolors='black', linewidths=1)
ax.plot(n, avg_assign, '#1E41FF', lw=2, alpha=0.7)
ax.set_xlabel('Number of Lap Times (n)', fontsize=12)
ax.set_ylabel('Average Assignments', fontsize=12)
ax.set_title('F1 Qualifying: Assignments vs n', fontsize=14, fontweight='bold')
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/assignments_vs_n.png', dpi=150)
plt.close()

# ============================================================
# Plot 3: Comparisons vs Assignments 
# ============================================================
fig, ax = plt.subplots(figsize=(10, 6))

ax.scatter(n, avg_comp, c='#E10600', s=80, zorder=5, edgecolors='black', linewidths=1, label='Comparisons')
ax.plot(n, avg_comp, '#E10600', lw=2, alpha=0.7)
ax.scatter(n, avg_assign, c='#1E41FF', s=80, zorder=5, edgecolors='black', linewidths=1, label='Assignments')
ax.plot(n, avg_assign, '#1E41FF', lw=2, alpha=0.7)
ax.set_xlabel('Number of Lap Times (n)', fontsize=12)
ax.set_ylabel('Count', fontsize=12)
ax.set_title('F1 Qualifying: Comparisons vs Assignments', fontsize=14, fontweight='bold')
ax.legend(loc='upper left')
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('../plots/comparisons_vs_assignments.png', dpi=150)
plt.close()

print("\nPlots saved to ../plots/:")
print("  - comparisons_vs_n.png")
print("  - assignments_vs_n.png")
print("  - comparisons_vs_assignments.png")
