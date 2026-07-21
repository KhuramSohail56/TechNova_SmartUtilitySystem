# Smart Utility & Billing Management System (C++)

A robust, console-based utility and multi-item billing application built in C++ for the **TechNova C++ Programming Internship (Task 5 - Mini Project)**.

---

## 📌 Project Overview
This project simulates a real-world Point of Sale (POS) and inventory management system. It allows users to manage inventory stock and process customer orders dynamically using an interactive shopping cart system before generating a detailed final receipt.

---

## ✨ Key Features
* **Dynamic Inventory Management:** View and add items with auto-validation for duplicate IDs.
* **Interactive Multi-Item Cart System:** Continuously add multiple items to the cart until typing `done`.
* **Stock & Validation Control:** Prevents ordering items exceeding available stock and handles invalid inputs gracefully.
* **Automated Final Billing:** Generates an itemized receipt with calculated totals upon completing the purchase.
* **Data Persistence (File Handling):** Saves all inventory updates to `inventory_data.txt` and automatically reloads data upon startup.

---

## 🛠️ Concepts & Technologies Used
* **Programming Language:** C++
* **Object-Oriented Programming (OOP):** Encapsulation (Classes & Access Specifiers), Objects, Constructors, and Destructors.
* **Data Structures:** C++ STL (`std::vector`) for dynamic memory and cart management.
* **File Handling:** `std::ifstream` and `std::ofstream` for persistent storage.

---

## 📂 Project Structure
```text
TechNova_SmartUtilitySystem/
├── main.cpp                 # Source code
├── inventory_data.txt       # Auto-generated database file
└── README.md                # Project documentation
🚀 How to Run
1. Prerequisites
Ensure you have a C++ compiler installed (e.g., GCC/MinGW or Clang).

2. Compilation
Open your terminal/command prompt and run:

Bash
g++ main.cpp -o utility_system
3. Execution
Run the compiled executable:

Windows:

DOS
utility_system.exe
Linux / macOS:

Bash
./utility_system
📝 Usage Guide
Display Inventory: Check available items, prices, and stock quantities.

Add New Item: Add new products into the store inventory.

Generate Order: Enter item IDs and quantities one by one. Once finished, type done to print the final itemized bill receipt.

Exit: Saves current inventory state to file and closes the application.

👤 Author
Name: Khuram Sohail

Role: C++ Programming Intern at TechNova
