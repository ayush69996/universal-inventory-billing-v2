
#include "Billing.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
using namespace std;

Billing::Billing(Inventory& inventory, Sales& sales)
    : inventory(inventory), sales(sales) {
}

double Billing::calculateSubtotal(const vector<BillItem>& items) const {
    double subtotal = 0.0;

    for (const auto& item : items) {
        subtotal += item.total;
    }

    return subtotal;
}

double Billing::calculateDiscount(double subtotal, double discountRate) const {
    return subtotal * discountRate / 100.0;
}

double Billing::calculateTax(double amount, double taxRate) const {
    return amount * taxRate / 100.0;
}

void Billing::displayBill(const vector<BillItem>& items,
                          double subtotal,
                          double discount,
                          double tax,
                          double total) const {

    cout << "\n\n";
    cout << "============================================\n";
    cout << "             CUSTOMER BILL                 \n";
    cout << "============================================\n";

    cout << left
         << setw(20) << "Product"
         << setw(10) << "Qty"
         << setw(12) << "Price"
         << setw(12) << "Total"
         << "\n";

    cout << string(54, '-') << "\n";

    for (const auto& item : items) {
        cout << left
             << setw(20) << item.productName
             << setw(10) << item.quantity
             << setw(12) << fixed << setprecision(2) << item.unitPrice
             << setw(12) << item.total
             << "\n";
    }

    cout << string(54, '-') << "\n";

    cout << fixed << setprecision(2);
    cout << "Subtotal:          Rs. " << subtotal << "\n";
    cout << "Discount:          Rs. " << discount << "\n";
    cout << "Tax:               Rs. " << tax << "\n";

    cout << "--------------------------------------------\n";
    cout << "FINAL TOTAL:       Rs. " << total << "\n";
    cout << "============================================\n";
    cout << "          THANK YOU FOR SHOPPING!           \n";
    cout << "============================================\n";
}

void Billing::createBill() {
    vector<BillItem> items;
    int productId, quantity;

    cout << "\n========== CREATE NEW BILL ==========\n";
    cout << "Enter Product ID (0 to finish):\n";

    while (true) {
        cout << "\nProduct ID: ";
        cin >> productId;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (productId == 0) {
            break;
        }

        const Product* product = inventory.findProductById(productId);

        if (product == nullptr) {
            cout << "Product not found. Try again.\n";
            continue;
        }

        cout << "Product: " << product->getName() << "\n";
        cout << "Available Stock: " << product->getQuantity() << "\n";
        cout << "Selling Price: Rs. "
             << fixed << setprecision(2)
             << product->getSellingPrice() << "\n";

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid quantity.\n";
            continue;
        }

        int alreadyAdded = 0;

        for (const auto& item : items) {
            if (item.productId == productId) {
                alreadyAdded += item.quantity;
            }
        }

        if (quantity <= 0 ||
            quantity > product->getQuantity() - alreadyAdded) {
            cout << "Invalid quantity or insufficient stock.\n";
            continue;
        }

        BillItem item;

        item.productId = productId;
        item.productName = product->getName();
        item.quantity = quantity;
        item.unitPrice = product->getSellingPrice();
        item.total = item.unitPrice * quantity;

        items.push_back(item);

        cout << "Product added to bill successfully!\n";
    }

    if (items.empty()) {
        cout << "\nNo products added. Bill cancelled.\n";
        return;
    }

    double subtotal = calculateSubtotal(items);
    double discountRate, taxRate;

    cout << "\nEnter Discount Percentage (0-100): ";
    cin >> discountRate;

    if (cin.fail() || discountRate < 0 || discountRate > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid discount. Bill cancelled.\n";
        return;
    }

    cout << "Enter Tax Percentage (0-100): ";
    cin >> taxRate;

    if (cin.fail() || taxRate < 0 || taxRate > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid tax rate. Bill cancelled.\n";
        return;
    }

    double discount = calculateDiscount(subtotal, discountRate);
    double taxableAmount = subtotal - discount;
    double tax = calculateTax(taxableAmount, taxRate);
    double total = taxableAmount + tax;

    for (const auto& item : items) {
        if (!inventory.reduceStock(item.productId, item.quantity)) {
            cout << "\nStock update failed. Bill cancelled.\n";
            return;
        }
    }

    Sale sale;

    sale.saleId = sales.generateSaleId();

    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char dateBuffer[20];
    strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", localTime);

    sale.date = dateBuffer;
    sale.subtotal = subtotal;
    sale.discount = discount;
    sale.tax = tax;
    sale.total = total;

    for (const auto& item : items) {
        SaleItem saleItem;

        saleItem.productId = item.productId;
        saleItem.productName = item.productName;
        saleItem.quantity = item.quantity;
        saleItem.unitPrice = item.unitPrice;
        saleItem.total = item.total;

        sale.items.push_back(saleItem);
    }

    sales.addSale(sale);

    displayBill(items, subtotal, discount, tax, total);

    cout << "\nStock updated successfully!\n";
    cout << "Sale recorded in sales history.\n";
}
