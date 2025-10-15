import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("sorting_results.csv")

# Extract values
sizes = df["InputSize"]
serial = df["Serial"]
openmp = df["OpenMP"]
mpi = df["MPI"]
pthreads = df["Pthreads"]

# ------------------ Plot 1: Execution Time ------------------
plt.figure(figsize=(10, 6))
plt.plot(sizes, serial, marker='o', label="Serial")
plt.plot(sizes, openmp, marker='o', label="OpenMP (4 threads)")
plt.plot(sizes, mpi, marker='o', label="MPI (4 processes)")
plt.plot(sizes, pthreads, marker='o', label="Pthreads (4 threads)")

plt.xscale('log')
plt.yscale('log')
plt.xlabel("Input Size (log scale)")
plt.ylabel("Execution Time (seconds, log scale)")
plt.title("Execution Time Comparison of Sorting Algorithms")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("sorting_execution_time.png")
print("Saved: sorting_execution_time.png")

# ------------------ Plot 2: Speedup ------------------
def calc_speedup(serial, parallel):
    return [s/p if p > 0 else 0 for s, p in zip(serial, parallel)]

omp_speedup = calc_speedup(serial, openmp)
mpi_speedup = calc_speedup(serial, mpi)
pthreads_speedup = calc_speedup(serial, pthreads)

plt.figure(figsize=(10, 6))
plt.plot(sizes, omp_speedup, marker='o', label="OpenMP Speedup")
plt.plot(sizes, mpi_speedup, marker='o', label="MPI Speedup")
plt.plot(sizes, pthreads_speedup, marker='o', label="Pthreads Speedup")

plt.xscale('log')
plt.xlabel("Input Size (log scale)")
plt.ylabel("Speedup (Serial Time / Parallel Time)")
plt.title("Speedup Comparison of Parallel Sorting Algorithms")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("sorting_speedup.png")
print("Saved: sorting_speedup.png")
