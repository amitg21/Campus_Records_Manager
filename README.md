# Campus Record Manager

A C++ command-line application designed to manage academic records, including students, courses, enrollments, grades, and transcripts.

The project demonstrates practical implementation of **Object-Oriented Programming, CRUD operations, file handling, and modular application design** in C++.

## Features

- Student record management
- Course management
- Student enrollment management
- Academic record and transcript management
- Create, read, update, and delete (CRUD) operations
- Persistent data storage using file handling
- Data import/export
- Backup functionality
- Command-line interface

## Technologies Used

- **Language:** C++
- **Programming Concepts:** Object-Oriented Programming, CRUD Operations, File Handling
- **Storage:** Local files
- **Interface:** Command-Line Interface (CLI)

## Project Structure

```text
CCRM/
│
├── src/                 # Source files
├── include/             # Header files
├── data/                # Application data files
├── backup/              # Backup files
├── README.md
└── ...
```

> The exact structure may vary depending on the current implementation of the project.

## Core Concepts

### Object-Oriented Programming

The application uses classes and objects to organize different entities such as students, courses, enrollments, and grades. This helps separate responsibilities and keeps the code modular.

### CRUD Operations

The system provides basic operations for managing academic records:

- **Create** new records
- **Read** existing records
- **Update** existing information
- **Delete** records

### File Handling

The application uses C++ file handling to maintain data between program executions and support importing, exporting, and backing up records.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later
- Command-line/terminal environment
- Git (optional, for cloning the repository)

### Clone the Repository

```bash
git clone https://github.com/amitg21/CCRM.git
cd CCRM
```

### Compile

Using `g++`:

```bash
g++ -std=c++11 -o ccrm main.cpp
```

If the project contains multiple source files:

```bash
g++ -std=c++11 src/*.cpp -Iinclude -o ccrm
```

### Run

On Windows:

```bash
ccrm.exe
```

On Linux/macOS:

```bash
./ccrm
```

## How It Works

1. The application starts through a command-line interface.
2. Users can select operations related to students, courses, enrollments.
3. The application performs the requested CRUD operation.
4. Academic records are stored using file handling.
5. Users can export or back up their records when required.

## Learning Outcomes

Through this project, I gained practical experience with:

- C++ programming
- Object-Oriented Programming
- Classes and objects
- File input/output
- CRUD operations
- Modular application design
- Data persistence
- Command-line application development
- Git and GitHub

## Future Improvements

Possible future improvements include:

- Adding a graphical user interface
- Migrating from file-based storage to a relational database
- Adding user authentication and role-based access
- Improving input validation and error handling
- Adding automated testing
- Adding search and filtering functionality

## Author

**Amit Kumar Gupta**

GitHub: https://github.com/amitg21  
LinkedIn: https://www.linkedin.com/in/amit-gupta21/
