
#include "Inventory.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

Inventory::Inventory() {
    nextProductId = 1;
}

int Inventory::generateProductId() {
    return nextProductId++;
}

Product* Inventory::findProductById(int id) {
    for (auto& product : products) {
        if (product.getId() == id) {
            return &product;
        }
    }
    return nullptr;
}

const Product* Inventory::findProductById(int id) const {
    for (const auto& product : products) {
        if (product.getId() == id) {
            return &product;
        }
    }
    return nullptr;
}

void Inventory::addProduct() {
    string name, sku, category;
    double costPrice, sellingPrice;
    int quantity, lowStockLevel;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter Product Name: ";
    getline(cin, name);

    cout << "Enter SKU: ";
    getline(cin, sku);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Cost Price: ";
    cin >> costPrice;

    cout << "Enter Selling Price: ";
    cin >> sellingPrice;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Low Stock Level (default 5): ";
    cin >> lowStockLevel;

    if (cin.fail() || costPrice < 0 || sellingPrice < 0 ||
        quantity < 0 || lowStockLevel < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input. Product was not added.\n";
        return;
    }

    for (const auto& product : products) {
        if (product.getSku() == sku) {
            cout << "\nSKU already exists. Product was not added.\n";
            return;
        }
    }

    Product product(generateProductId(), name, sku, category,
                    costPrice, sellingPrice, quantity, lowStockLevel);

    products.push_back(product);

    cout << "\nProduct added successfully!\n";
    cout << "Generated Product ID: " << product.getId() << "\n";
}

void Inventory::displayProducts() const {
    if (products.empty()) {
        cout << "\nInventory is empty.\n";
        return;
    }

    cout << "\n========== PRODUCT INVENTORY ==========\n";

    cout << left
         << setw(6) << "ID"
         << setw(20) << "Name"
         << setw(15) << "SKU"
         << setw(15) << "Category"
         << setw(12) << "Cost"
         << setw(12) << "Selling"
         << setw(10) << "Quantity"
         << "\n";

    cout << string(90, '-') << "\n";

    for (const auto& product : products) {
        cout << left
             << setw(6) << product.getId()
             << setw(20) << product.getName()
             << setw(15) << product.getSku()
             << setw(15) << product.getCategory()
             << setw(12) << fixed << setprecision(2) << product.getCostPrice()
             << setw(12) << product.getSellingPrice()
             << setw(10) << product.getQuantity()
             << "\n";
    }
}

void Inventory::searchProduct() const {
    int id;

    cout << "\nEnter Product ID to search: ";
    cin >> id;

    const Product* product = findProductById(id);

    if (product == nullptr) {
        cout << "\nProduct not found.\n";
        return;
    }

    product->display();
}

void Inventory::updateProduct() {
    int id;

    cout << "\nEnter Product ID to update: ";
    cin >> id;

    Product* product = findProductById(id);

    if (product == nullptr) {
        cout << "\nProduct not found.\n";
        return;
    }

    int choice;

    cout << "\n1. Update Name";
    cout << "\n2. Update SKU";
    cout << "\n3. Update Category";
    cout << "\n4. Update Cost Price";
    cout << "\n5. Update Selling Price";
    cout << "\n6. Update Quantity";
    cout << "\n7. Update Low Stock Level";
    cout << "\nEnter choice: ";
    cin >> choice;

    string text;
    double price;
    int number;

    switch (choice) {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new name: ";
            getline(cin, text);
            product->setName(text);
            break;

        case 2:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new SKU: ";
            getline(cin, text);

            for (const auto& item : products) {
                if (item.getId() != id && item.getSku() == text) {
                    cout << "\nSKU already exists.\n";
                    return;
                }
            }

            product->setSku(text);
            break;

        case 3:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new category: ";
            getline(cin, text);
            product->setCategory(text);
            break;

        case 4:
            cout << "Enter new cost price: ";
            cin >> price;

            if (cin.fail() || price < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid price.\n";
                return;
            }

            product->setCostPrice(price);
            break;

        case 5:
            cout << "Enter new selling price: ";
            cin >> price;

            if (cin.fail() || price < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid price.\n";
                return;
            }

            product->setSellingPrice(price);
            break;

        case 6:
            cout << "Enter new quantity: ";
            cin >> number;

            if (cin.fail() || number < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid quantity.\n";
                return;
            }

            product->setQuantity(number);
            break;

        case 7:
            cout << "Enter new low stock level: ";
            cin >> number;

            if (cin.fail() || number < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid stock level.\n";
                return;
            }

            product->setLowStockLevel(number);
            break;

        default:
            cout << "\nInvalid choice.\n";
            return;
    }

    cout << "\nProduct updated successfully!\n";
}

void Inventory::deleteProduct() {
    int id;

    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    auto it = find_if(products.begin(), products.end(),
        [id](const Product& product) {
            return product.getId() == id;
        });

    if (it == products.end()) {
        cout << "\nProduct not found.\n";
        return;
    }

    products.erase(it);

    cout << "\nProduct deleted successfully!\n";
}

void Inventory::restockProduct() {
    int id, quantity;

    cout << "\nEnter Product ID: ";
    cin >> id;

    Product* product = findProductById(id);

    if (product == nullptr) {
        cout << "\nProduct not found.\n";
        return;
    }

    cout << "Enter quantity to add: ";
    cin >> quantity;

    if (cin.fail() || quantity <= 0 ||
        product->getQuantity() > numeric_limits<int>::max() - quantity) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid quantity.\n";
        return;
    }

    product->setQuantity(product->getQuantity() + quantity);

    cout << "\nStock updated successfully!\n";
    cout << "New Quantity: " << product->getQuantity() << "\n";
}

void Inventory::displayLowStockProducts() const {
    bool found = false;

    cout << "\n========== LOW STOCK PRODUCTS ==========\n";

    for (const auto& product : products) {
        if (product.isLowStock()) {
            product.display();
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo low-stock products found.\n";
    }
}

bool Inventory::reduceStock(int id, int quantity) {
    Product* product = findProductById(id);

    if (product == nullptr || quantity <= 0 ||
        product->getQuantity() < quantity) {
        return false;
    }

    product->setQuantity(product->getQuantity() - quantity);
    return true;
}

void Inventory::displayInventorySummary() const {
    int totalProducts = static_cast<int>(products.size());
    int totalUnits = 0;
    double inventoryValue = 0.0;
    int lowStockCount = 0;

    for (const auto& product : products) {
        totalUnits += product.getQuantity();
        inventoryValue += product.getCostPrice() * product.getQuantity();

        if (product.isLowStock()) {
            lowStockCount++;
        }
    }

    cout << "\n========== INVENTORY SUMMARY ==========\n";
    cout << "Total Products: " << totalProducts << "\n";
    cout << "Total Units: " << totalUnits << "\n";
    cout << "Inventory Cost Value: Rs. "
         << fixed << setprecision(2) << inventoryValue << "\n";
    cout << "Low Stock Products: " << lowStockCount << "\n";
}

vector<Product>& Inventory::getProducts() {
    return products;
}

const vector<Product>& Inventory::getProducts() const {
    return products;
}
