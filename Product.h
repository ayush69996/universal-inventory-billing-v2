
#pragma once

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    string sku;
    string category;
    double costPrice;
    double sellingPrice;
    int quantity;
    int lowStockLevel;

public:
    Product();

    Product(int id, string name, string sku, string category,
            double costPrice, double sellingPrice,
            int quantity, int lowStockLevel = 5);

    int getId() const;
    string getName() const;
    string getSku() const;
    string getCategory() const;
    double getCostPrice() const;
    double getSellingPrice() const;
    int getQuantity() const;
    int getLowStockLevel() const;

    void setName(string name);
    void setSku(string sku);
    void setCategory(string category);
    void setCostPrice(double costPrice);
    void setSellingPrice(double sellingPrice);
    void setQuantity(int quantity);
    void setLowStockLevel(int level);

    bool isLowStock() const;

    void display() const;
};
