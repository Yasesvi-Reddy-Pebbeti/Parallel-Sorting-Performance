# Parallel Sorting Algorithms: Performance Profiling with OpenMP, MPI, and Pthreads

This project demonstrates how **parallel computing** improves the performance of classic sorting algorithms using three major paradigms — **OpenMP**, **MPI**, and **Pthreads**.  
It compares performance, scalability, and efficiency across implementations of **Merge Sort** and **QuickSort**, backed by detailed profiling and visual analytics.

---

## 📘 Overview

Sorting is one of the most fundamental operations in computer science, often acting as a benchmark for computational performance.  
This project implements and analyzes **serial and parallel versions** of Merge Sort and QuickSort to explore how different parallelization models impact execution time and scalability.

---

## ⚙️ Technologies Used

| Category               | Tools / Libraries                                                         |
| ---------------------- | ------------------------------------------------------------------------- |
| **Languages**          | C, C++                                                                    |
| **Parallel Models**    | OpenMP (shared memory), MPI (distributed memory), Pthreads (thread-based) |
| **Profiling Tools**    | gprof, htop, valgrind                                                     |
| **Data Visualization** | Python (Pandas, Matplotlib)                                               |
| **Compiler**           | GCC / mpicc                                                               |
| **Platform**           | Ubuntu (via WSL or native Linux)                                          |

---

## 🗂️ Folder Structure

```
Parallel-Sorting-Performance/
│
├── src/                # All source code files (.c)
│   ├── serial_mergesort.c
│   ├── omp_mergesort.c
│   ├── mpi_mergesort.c
│   ├── pthread_mergesort.c
│   ├── omp_quicksort.c
│   └── pthread_quicksort.c
│
├── analysis/           # Python scripts and CSV data
│   ├── sorting_results.csv
│   └── plot_from_csv.py
│
├── profiling/          # Profiling and benchmarking reports
│   ├── gprof_report.txt
│   ├── valgrind_report.txt
│
├── docs/               # Documentation, proposal, and presentation
│   ├── Project_Proposal.txt
│   ├── Project_Breakdown.txt
│
└── README.md
```

---

## 🧩 Implementation Summary

| Algorithm      | Paradigm          | Description                                                         |
| -------------- | ----------------- | ------------------------------------------------------------------- |
| **Merge Sort** | Serial            | Baseline recursive merge sort implementation                        |
| **Merge Sort** | OpenMP            | Uses parallel sections to handle recursive divisions                |
| **Merge Sort** | MPI               | Distributes subarrays across processes, sorts, and merges results   |
| **Merge Sort** | Pthreads          | Manages thread creation and joins manually for each partition       |
| **QuickSort**  | OpenMP / Pthreads | Parallel partitioning around pivots with controlled recursion depth |

---

## 💻 Compilation & Execution

### 🔹 Serial

```bash
gcc src/serial_mergesort.c -o serial
./serial
```

### 🔹 OpenMP

```bash
gcc -fopenmp src/omp_mergesort.c -o omp_sort
./omp_sort
```

### 🔹 MPI

```bash
mpicc src/mpi_mergesort.c -o mpi_sort
mpirun -np 4 ./mpi_sort
```

### 🔹 Pthreads

```bash
gcc -pthread src/pthread_mergesort.c -o pthread_sort
./pthread_sort
```

---

## 📊 Visualization of Results

Python was used to automate performance graph generation from CSV files.

### 🔸 Run the plotting script:

```bash
cd analysis
python3 plot_from_csv.py
```

This generates:

- `sorting_execution_time.png` → Comparison of execution time (log-log scale)
- `sorting_speedup.png` → Speedup graph of parallel vs. serial sorting

---

## 🧮 Profiling & Performance Analysis

### 🔸 Using `gprof`:

```bash
gcc -pg src/omp_mergesort.c -o omp_prof
./omp_prof
gprof omp_prof gmon.out > profiling/gprof_report.txt
```

### 🔸 Using `valgrind`:

```bash
valgrind ./omp_prof
```

### 🔸 Using `htop` (to monitor CPU/thread utilization):

```bash
htop
```

---

## 🚀 Sample Results

| Input Size | Serial (s) | OpenMP (s) | MPI (s) | Pthreads (s) |
| ---------- | ---------- | ---------- | ------- | ------------ |
| 10,000     | 0.017      | 0.021      | 0.030   | 0.001        |
| 100,000    | 0.150      | 0.120      | 0.110   | 0.090        |
| 1,000,000  | 1.200      | 0.880      | 0.700   | 0.650        |

**Speedup (vs Serial):**

- OpenMP → ~1.36×
- MPI → ~1.71×
- Pthreads → ~1.84×

---

## 🧠 Key Learnings

- Parallelization significantly reduces execution time for large datasets.
- OpenMP provides the easiest scalability for shared-memory systems.
- MPI excels in distributed workloads but introduces communication overhead.
- Manual thread management with Pthreads offers fine-grained control.
- Profiling (`gprof`, `valgrind`) helps locate performance bottlenecks and optimize function-level behavior.

---

## 🧾 Author

**Yasesvi Reddy Pebbeti**  
💻 [GitHub: Yasesvi-Reddy-Pebbeti](https://github.com/Yasesvi-Reddy-Pebbeti)  
🌐 [Portfolio: yasesvireddy.dev](https://yasesvireddy.dev)

---

## 📜 License

This project is open-sourced for educational and research purposes under the **MIT License**.

---

⭐ **If you found this project useful, don’t forget to star the repo!**
