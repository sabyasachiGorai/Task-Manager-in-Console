# Command-Line Task Manager (C++)

A feature-rich command-line To-Do List Task Manager built using **C++**, designed to help users add, update, delete, sort, and save tasks with file persistence. The project showcases concepts from **Data Structures**, **File Handling**, and **Modular Programming**.

---

## Features

- **Add Task** – Input task name and priority.
- **Print Tasks** – Display tasks in tabular format, sorted by priority.
- **Delete Task** – Mark a task as done and remove it by ID.
- **Sort by Creation Time** – Optional sorting of tasks based on the time they were added.
- **File Persistence** – Tasks are saved to and fetched from a file (`tasks.txt`) using CSV-style formatting.
- **CLI Menu** – Easy-to-use menu-driven interface.

---

## Technologies & Concepts Used

- **C++**
- **Linked Lists**
- **File Handling**
- **Modular Functions**
- **Standard Libraries**: `<iostream>`, `<fstream>`, `<iomanip>`, `<ctime>`, `<string>`, `<sstream>`

---
## Project Structure
- main.cpp – Main program logic and menu system.
- tasks.txt – CSV-style file where tasks are saved and loaded.


## How to Run

1. **Clone or Download** this repository.
2. Open the project in any C++ IDE or terminal.
3. Compile and run using a C++ compiler like `g++`:
```
   g++ main.cpp -o taskmanager
   ./taskmanager
```

## Sample Output On First Run:
```code
----------------------------------------
          Task Manager
----------------------------------------
1. Create Task
2. Print Task
3. Done By ID
4. Sort By Cr Time
5. Save and Exit
6. Fetch From CSV
(-1) Exit
Enter -->
```


## After Adding Some Tasks and Printing:
```
============================================================
| Task ID   | Task Name  | Priority  | Creation Time       |
============================================================
| 1         | Eat        | 1         | 2025-04-12 11:36:14 |
| 2         | Code       | 2         | 2025-04-12 11:36:19 |
| 3         | Repeat     | 3         | 2025-04-12 11:36:27 |
============================================================
```