# LocalBigtable: A Bigtable Simulation in C++

## Overview

LocalBigtable is a local, in-memory simulation of Google Cloud Bigtable, built in C++. It provides basic functionalities such as inserting, updating, retrieving, and deleting cells and rows, as well as scanning the entire table. Additionally, the project supports persistence by saving to and loading from files and includes a simple text-based UI for user interaction.

## Why C++?

C++ is chosen for this project for several reasons:
- **Performance:** C++ allows fine-grained control over memory and resources, which is critical for building high-performance systems that scale.
- **System-Level Programming:** Many distributed systems and storage solutions (like Google Cloud Bigtable) are implemented in C++ to meet performance and concurrency requirements.
- **Concurrency:** C++ provides robust support for multi-threading and concurrency (using `std::mutex`), essential for simulating thread-safe operations similar to those in a distributed environment.
- **Industry Standard:** C++ is widely used in systems programming, making it a natural choice for a project that simulates a distributed storage system.

## Correlation to Google Cloud Bigtable

While LocalBigtable is a simplified, local simulation, it mirrors several core concepts of Bigtable:
- **Data Model:** Data is stored in rows and columns. In our simulation, a row is a map from column names to cells.
- **Cells and Timestamps:** Each cell holds a value and a timestamp, reflecting Bigtable's versioning system.
- **Scalable Operations:** Basic operations like insert, update, retrieve, and delete are implemented. The design can be extended to support sharding, distributed storage, and network communication.
- **Persistence:** The project includes file-based persistence for saving and restoring table data.
