
#include "Product.h"

Product::Product() {
    id = 0;
    name = "";
    sku = "";
    category = "";
    costPrice = 0.0;
    sellingPrice = 0.0;
    quantity = 0;
    lowStockLevel = 5;
}

Product::Product(int id, string name, string sku, string category,
                 double costPrice, double sellingPrice,
                 int quantity, int lowStockLevel) {
    this->id = id;
    this->name = name;
    this->sku = sku;
    this->category = category;
    this->costPrice = costPrice;
    this->sellingPrice = sellingPrice;
    this->quantity = quantity;
    this->lowStockLevel = lowStockLevel;
}

int Product::getId() const {
    return id;
}

string Product::getName() const {
    return name;
}

string Product::getSku() const {
    return sku;
}

string Product::getCategory() const {
    return category;
}

double Product::getCostPrice() const {
    return costPrice;
}

double Product::getSellingPrice() const {
    return sellingPrice;
}

int Product::getQuantity() const {
    return quantity;
}

int Product::getLowStockLevel() const {
    return lowStockLevel;
}

void Product::setName(string name) {
    this->name = name;
}

void Product::setSku(string sku) {
    this->sku = sku;
}

void Product::setCategory(string category) {
    this->category = category;
}

void Product::setCostPrice(double costPrice) {
    this->costPrice = costPrice;
}

void Product::setSellingPrice(double sellingPrice) {
    this->sellingPrice = sellingPrice;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Product::setLowStockLevel(int level) {
    lowStockLevel = level;
}

bool Product::isLowStock() const {
    return quantity <= lowStockLevel;
}

void Product::display() const {
    cout << "\nProduct ID: " << id;
    cout << "\nName: " << name;
    cout << "\nSKU: " << sku;
    cout << "\nCategory: " << category;
    cout << "\nCost Price: Rs. " << costPrice;
    cout << "\nSelling Price: Rs. " << sellingPrice;
    cout << "\nQuantity: " << quantity;
    cout << "\nLow Stock Level: " << lowStockLevel;
    cout << "\nStock Status: "
         << (isLowStock() ? "Low Stock" : "Available");
    cout << "\n";
}
