# 📦 DataLite — A Lightweight DBMS Engine

**DataLite** is a command-line database management system that simulates the behavior of a real DBMS. Designed as a lightweight SQL engine, it allows users to perform standard SQL operations such as `CREATE`, `INSERT`, `SELECT`, `UPDATE`, and `DELETE`—right from the terminal.

This project was developed to deeply understand how real DBMS systems parse, validate, and execute SQL commands, and how data and schema are stored and manipulated under the hood.

---

## 🔧 Features

- Fully functional **Command Line Interface** (CLI)
- Supports major SQL operations:
  - `CREATE TABLE`
  - `INSERT INTO`
  - `SELECT`
  - `UPDATE`
  - `DELETE FROM`
  - `DROP TABLE`
  - `DESCRIBE TABLE`
  - `HELP`
- Case-insensitive command recognition (only for SQL keywords)
- In-built error detection and validation
- Maintains schema in a separate **Schema File**
- Data of each table is stored in individual text files
- Supports **WHERE clause** in `SELECT`, `UPDATE`, and `DELETE`
- Enforces **Primary Key constraint** during table creation

---

## 🧠 How It Works

1. **Query Input**: User enters a SQL query as a string into the CLI.
2. **Parsing**: The query string is tokenized into a vector of strings.
3. **Normalization**: SQL keywords are converted to a common case for case-insensitive handling.
4. **Validation**: Tokens are checked for syntactic and semantic correctness.
5. **Execution**: Upon validation, the corresponding operation function is invoked.
6. **Persistence**:
   - Schema info is updated in the schema file.
   - Row data is stored or modified in table-specific text files.

---

## 📸 Screenshots

### ✅ Create Table & Insert Into
![Create & Insert](https://github.com/ParthAher07/Mini-DB-Engine/blob/main/Images/1.png)

### 🔍 Select Command
![Select](https://github.com/ParthAher07/Mini-DB-Engine/blob/main/Images/2.png)

### ✏️ Update with Where Clause
![Update](https://github.com/ParthAher07/Mini-DB-Engine/blob/main/Images/3.png)

### ❌ Delete with Where Clause
![Delete](https://github.com/ParthAher07/Mini-DB-Engine/blob/main/Images/4.png)

### ℹ️ Help & Describe
![Help & Describe](https://github.com/ParthAher07/Mini-DB-Engine/blob/main/Images/5.png)

---

## 📌 Design Assumptions

- **Primary key definition is mandatory** during table creation; omitting it raises an error.
- No support for advanced data types, joins, or transactions (as this is a lightweight simulation).
- Text-based storage is used for both schema and data, to maintain simplicity.

---

## 🛠 Tech Stack

- **C++**: Core language used to implement parsing, query execution, and file operations.
- **File I/O**: For schema and data persistence using `.txt` files.
- No external libraries — the project is built using standard C++ libraries only.

---

## ▶️ How to Run

### Prerequisites
- C++17 or above
- g++ compiler

### Steps

### Step 1: Compile
```bash
g++ main.cpp -o datalite
```

### Step 2: Run
```bash
./datalite
```



---

## 🎯 Motivation

This project was created as a learning tool to explore:
- The internal architecture of relational databases.
- How SQL parsing and command execution works under the hood.
- File-based data modeling for persistent storage.
  
It also serves as a strong foundation for anyone wanting to dive into systems programming, compilers, or database internals.

---
