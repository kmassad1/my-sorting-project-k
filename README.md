# my-sorting-project-k
# Empirical Analysis of Sorting Algorithms

This project presents an empirical performance comparison between three sorting algorithms:
- Bubble Sort
- Merge Sort
- Quick Sort

## 📌 Objective
To measure and compare the execution time of each algorithm on different input sizes using C++.

## 🛠 Implementation Details

- Implemented in C++.
- Execution times measured using std::chrono.
- Input sizes tested: 10, 1000, 10000.
- Results saved to a CSV file: results.csv.

## 📁 Files Included

- main.cpp – Full C++ implementation.
- results.csv – Measured execution times.
- Sorting_Report_Kinda.pdf – Detailed report including graphs and conclusion.
- Sorting_Presentation_Kinda.pptx – PowerPoint summary (optional).
- README.md – This documentation.

## 📊 Sample Results (average times in seconds)

| Algorithm   | Input Size | Avg Time (s) |
|-------------|------------|---------------|
| Bubble Sort | 10         | ~8.65e-07     |
| Merge Sort  | 10         | ~3.35e-06     |
| Quick Sort  | 10         | ~7.83e-07     |
| Bubble Sort | 1000       | ~0.00555      |
| Merge Sort  | 1000       | ~0.000368     |
| Quick Sort  | 1000       | ~0.00358      |
| Bubble Sort | 10000      | ~0.55779      |
| Merge Sort  | 10000      | ~0.004465     |
| Quick Sort  | 10000      | ~0.235542     |

## ✅ Conclusion

- *Bubble Sort* is inefficient for large datasets.
- *Merge Sort* is the most stable and fastest.
- *Quick Sort* is fast, but its performance depends on the data distribution.

---

Project by Kinda Massad – 2025
