
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct SaleItem {
    int productId;
    string productName;
    int quantity;
    double unitPrice;
    double total;
};

struct Sale {
    int saleId;
    string date;
    vector<SaleItem> items;
    double subtotal;
    double discount;
    double tax;
    double total;
};

class Sales {
private:
    vector<Sale> sales;
    int nextSaleId;

public:
    Sales();

    int generateSaleId();

    void addSale(const Sale& sale);

    void displaySalesHistory() const;

    void displayTotalRevenue() const;

    void displaySaleDetails(int saleId) const;

    double calculateTotalRevenue() const;

    int getTotalSales() const;

    const vector<Sale>& getSales() const;
};
