
#include "InventoryReport.h"
#include <iostream>
#include <iomanip>
using namespace std;

InventoryReport::InventoryReport(const Inventory& inventory)
    : inventory(inventory) {
}

void InventoryReport::generateReport() const {
    cout << "\n========== INVENTORY REPORT ==========\n";

    cout << left
         << setw(8) << "ID"
         << setw(20) << "Product"
         << setw(15) << "Category"
         << setw(12) << "Quantity"
         << setw(15) << "Stock Value"
         << "\n";

    cout << string(70, '-') << "\n";

    double totalValue = 0.0;

    for (const auto& product : inventory.getProducts()) {
        double value = product.getCostPrice() * product.getQuantity();
        totalValue += value;

        cout << left
             << setw(8) << product.getId()
             << setw(20) << product.getName()
             << setw(15) << product.getCategory()
             << setw(12) << product.getQuantity()
             << setw(15) << fixed << setprecision(2) << value
             << "\n";
    }

    cout << string(70, '-') << "\n";
    cout << "Total Inventory Cost Value: Rs. "
         << fixed << setprecision(2) << totalValue << "\n";
    cout << "======================================\n";
}
