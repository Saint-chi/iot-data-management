# IoT Data Management System

A C++ data pipeline for loading, partitioning, and analyzing CSV-based IoT datasets.

---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Classes & Methods](#classes--methods)
- [Known Issues & Notes](#known-issues--notes)

---

## Overview

This project implements a lightweight data management system in C++ designed to ingest CSV files (such as IoT sensor logs), partition them into smaller shards, extract specific column data, and analyze flow metrics with performance timing.

---

## Features

- Load CSV files into memory with header parsing
- Partition large datasets into multiple shard files
- Extract specific columns by name into typed key-value containers
- Analyze total flow values with execution time measurement (`<chrono>`)
- Template-based `PairContainer<K, V>` for flexible data storage

---

## Project Structure

```
untitled/
├── main.cpp              # Entry point
├── Header.h              # Declarations for Tensor and management classes
├── Header.cpp            # Implementations of Tensor and management methods
├── paircontainer.h       # Template class PairContainer<K, V>
├── iot-shard.txt         # Sample input CSV data file
└── CMakeLists.txt        # CMake build configuration
```

---

## Requirements

- C++20 or later
- CMake 4.1+
- CLion (recommended) or any CMake-compatible IDE
- MinGW (Windows) or GCC/Clang (Linux/macOS)

---

## Building the Project

1. Clone or download the repository
2. Open the project in CLion
3. Select **File → Reload CMake Project** to ensure `iot-shard.txt` is copied to the build directory
4. Build using **Run → Build** or `Ctrl+F9`

> **Note:** The CMakeLists.txt uses `configure_file` to copy `iot-shard.txt` into the build directory. You must reload CMake after any changes to CMakeLists.txt for this to take effect.

```cmake
configure_file(iot-shard.txt ${CMAKE_BINARY_DIR}/iot-shard.txt COPYONLY)
```

---

## Usage

```cpp
management m;
m.load("iot-shard.txt");

// Partition the dataset into shards
m.partition(); // prompts user for number of partitions

// Extract two columns by name and analyze
PairContainer<int, double> result = m.extractColValues("id", "flow");
m.analyzeflows(result);
```

### Example Output

```
Enter number of partitions: 3
Total flow: 142.75 sec
Time taken to analyze: 0.000021 seconds
```

---

## Classes & Methods

### `Tensor`
Represents a single row of CSV data as a vector of strings.

| Method | Description |
|---|---|
| `operator>>` | Parses a comma-delimited line into the tensor |
| `operator<<` | Outputs tensor data as comma-separated values |
| `operator[]` | Access individual fields by index |

### `management`
Manages the full dataset including header and all tensor rows.

| Method | Description |
|---|---|
| `load(filename)` | Loads a CSV file into memory |
| `extract(begin, end, path)` | Writes a range of rows to a new file |
| `partition()` | Splits the dataset into N shard files |
| `extractColValues(col1, col2)` | Returns a `PairContainer` of two columns |
| `analyzeflows(container)` | Sums flow values and prints total + time taken |

### `PairContainer<K, V>`
A template container holding `std::vector<std::pair<K, V>>`.

| Method              | Description |
|---------------------|---|
| `insert(key, value)` | Adds a key-value
| `operator<<`        | Stream output of all pairs |
| 'operator>>'        |Streams input data directly into the management object|

---

## Known Issues & Notes

- `rows` in the `management` class must be initialized to `0` in the header to avoid undefined behavior
- `#include <chrono>` must be placed at the top of `Header.cpp` with other includes, not inside or after any function
- The `configure_file` CMake directive only runs on CMake reconfigure — reload CMake if the input file is not found at runtime