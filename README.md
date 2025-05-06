# 📦 Inventory Management System - C++

A simple yet powerful Inventory Management System developed in C++ using Object-Oriented Programming (OOP), File Handling, and Standard Template Library (STL).

## 🧰 Features

✅ Admin Login System (with basic password hashing)  
✅ Add, Update, Delete Items  
✅ Search by Name or ID  
✅ Sort Items (Name, Price, Quantity)  
✅ Display All Items  
✅ View Items by Supplier  
✅ Show Low Stock Items  
✅ Update Low Stock Threshold  
✅ Calculate Total Inventory Value  
✅ File Persistence (`inventory.txt`)

## 📁 File Structure

```
inventory/
├── inventory.txt         # Saved data (auto-generated)
├── main.cpp              # Source code
├── README.md             # Project documentation
```

## 🧪 How to Run

1. **Clone this repository:**
```bash
git clone https://github.com/your-username/inventory-management-cpp.git
cd inventory-management-cpp
```

2. **Compile the code:**
```bash
g++ -o inventory main.cpp
```

3. **Run the program:**
```bash
./inventory
```

4. **Login Credentials:**
```
Username: admin
Password: admin123
```

## 🖥 Sample Output

```
==== Inventory Management System ====
Enter username: admin
Enter password: admin123
Login successful.

1. Add Item
2. Update Item
3. Delete Item
...
```

## 📌 Concepts Used

- Classes & Objects (OOP)
- File Handling with fstream
- STL (vector, string, algorithm)
- Basic Hashing for Passwords
- Input Validation
- Formatting with iomanip

## 🔐 Security Note

This system uses a **simple hash function** for learning purposes. **Do not** use this method in production.

## 👨‍💻 Author

**[Github](https://github.com/TechieRS)**

## 📜 License

This project is open source and available under the [MIT License](LICENSE).
