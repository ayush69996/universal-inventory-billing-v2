
#pragma once

#include "Inventory.h"
#include "Sales.h"
#include <vector>
#include <string>
using namespace std;

struct BillItem {
    int productId;
    string productName;
    int quantity;
    double unitPrice;
    double total;
};

class Billing {
private:
    Inventory& inventory;
    Sales& sales;

public:
    Billing(Inventory& inventory, Sales& sales);

    void createBill();

private:
    double calculateSubtotal(const vector<BillItem>& items) const;

    double calculateDiscount(double subtotal, double discountRate) const;

    double calculateTax(double amount, double taxRate) const;

    void displayBill(const vector<BillItem>& items,
                     double subtotal,
                     double discount,
                     double tax,
                     double total) const;
};
