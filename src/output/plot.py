import pandas as pd
import matplotlib.pyplot as plt

# === Pas deze twee bestandsnamen aan ===
FILE_SERIAL = "src/output/resultsSerial.csv"
FILE_PARALLEL = "src/output/resultsParallel.csv"

# CSV’s inladen
serial = pd.read_csv(FILE_SERIAL)
parallel = pd.read_csv(FILE_PARALLEL)

plt.figure(figsize=(10, 6))

# Seriële curve
plt.plot(
    serial["graphSize"],
    serial["duration(s)"],
    marker="o",
    label="Serial"
)

# Parallelle curve
plt.plot(
    parallel["graphSize"],
    parallel["duration(s)"],
    marker="o",
    label="Parallel"
)

plt.xlabel("Graph Size")
plt.ylabel("Duration (s)")
plt.title("Serial vs Parallel Duration")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
