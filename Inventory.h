
#pragma once

#include "Product.h"
#include <vector>
#include <string>
using namespace std;

class Inventory {
private:
    vector<Product> products;
    int nextProductId;

public:
    Inventory();

    void addProduct();
    void displayProducts() const;
    void searchProduct() const;
    void updateProduct();
    void deleteProduct();
    void restockProduct();
    void displayLowStockProducts() const;

    Product* findProductById(int id);
    const Product* findProductById(int id) const;

    bool reduceStock(int id, int quantity);
    void displayInventorySummary() const;

    vector<Product>& getProducts();
    const vector<Product>& getProducts() const;

    int generateProductId();
};
