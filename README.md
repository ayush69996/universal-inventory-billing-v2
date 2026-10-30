
# Universal Inventory & Billing System

## About the Project

The Universal Inventory & Billing System is a console-based application developed using C++.

It helps businesses manage their products, maintain inventory records, generate customer bills, calculate discounts and taxes, and track sales revenue.

The project uses Object-Oriented Programming concepts and CSV files for data storage.

## Features

- Add new products
- Display all products
- Search products using Product ID
- Update product information
- Delete products
- Restock products
- Identify low-stock products
- Generate customer bills
- Calculate discounts and taxes
- Automatically update inventory after billing
- Maintain sales history
- View individual sale details
- Calculate total sales revenue
- Display inventory summary
- Save and load data using CSV files

## Technologies Used

- C++
- C++ Standard Library
- File Handling
- CSV Data Storage
- Object-Oriented Programming

## Project Structure

```text
UniversalInventoryBillingV2/
│
├── main.cpp
├── Product.h
├── Product.cpp
├── Inventory.h
├── Inventory.cpp
├── Billing.h
├── Billing.cpp
├── Sales.h
├── Sales.cpp
├── Storage.h
├── Storage.cpp
│
├── products.csv
├── sales.csv
│
├── README.md
└── .gitignore
```

## How to Run

### Requirements

- C++ compiler (G++)
- C++17 support

### Compilation

Run this command in the project directory:

```bash
g++ -std=c++17 main.cpp Product.cpp Inventory.cpp Billing.cpp Sales.cpp Storage.cpp -o inventory
```

### Execution

On Windows:

```powershell
.\inventory.exe
```

On Linux:

```bash
./inventory
```

## Data Storage

The application uses two CSV files:

- `products.csv` stores product and inventory information.
- `sales.csv` stores completed sales and their item details.

The application automatically loads saved data when it starts and saves changes to the CSV files.

## Author

Ayush Kumar
