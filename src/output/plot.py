import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# 1️⃣ Load the CSV file
df = pd.read_csv('results.csv')

# 2️⃣ Remove beta = 0
df = df[df['beta'] != 0]
df = df[df['beta'] != 1]
df = df[df['alpha'] != 0]

# 3️⃣ Use absolute error
df['abs_error'] = df['error'].abs()

# 4️⃣ Pivot the data for the heatmap: rows = alpha, columns = beta, values = abs_error
heatmap_data = df.pivot(index='alpha', columns='beta', values='abs_error')

# 5️⃣ Find the best parameters (minimum absolute error)
best_row = df.loc[df['abs_error'].idxmin()]
best_alpha = best_row['alpha']
best_beta = best_row['beta']
best_error = best_row['abs_error']

print(f"Best parameters: alpha = {best_alpha}, beta = {best_beta}, absolute error = {best_error}")

# 6️⃣ Plot the heatmap
plt.figure(figsize=(12, 8))
sns.heatmap(
    heatmap_data,
    annot=True,
    fmt=".1f",
    cmap="coolwarm",
    linewidths=0.5,
    cbar_kws={'label': 'Absolute Error'}
)

plt.title("Heatmap of Absolute Error (α vs β, beta != 0)")
plt.xlabel("Beta (β)")
plt.ylabel("Alpha (α)")

# Highlight the best parameter combination
# plt.scatter(x=best_beta + 0.5, y=best_alpha + 0.5, s=200, c='yellow', edgecolors='black', label='Best')
# plt.legend(loc='upper right')

plt.tight_layout()
plt.show()
