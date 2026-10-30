
#include "Storage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

string escapeCSV(const string& value) {
    string result = "\"";

    for (char ch : value) {
        if (ch == '"') {
            result += "\"\"";
        } else {
            result += ch;
        }
    }

    result += "\"";
    return result;
}

vector<string> parseCSV(const string& line) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char ch = line[i];

        if (ch == '"') {
            if (insideQuotes && i + 1 < line.size() &&
                line[i + 1] == '"') {
                field += '"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (ch == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += ch;
        }
    }

    fields.push_back(field);
    return fields;
}

void Storage::saveProducts(const Inventory& inventory,
                           const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "\nUnable to save products.\n";
        return;
    }

    file << "ID,Name,SKU,Category,CostPrice,SellingPrice,Quantity,LowStockLevel\n";

    for (const auto& product : inventory.getProducts()) {
        file << product.getId() << ","
             << escapeCSV(product.getName()) << ","
             << escapeCSV(product.getSku()) << ","
             << escapeCSV(product.getCategory()) << ","
             << product.getCostPrice() << ","
             << product.getSellingPrice() << ","
             << product.getQuantity() << ","
             << product.getLowStockLevel() << "\n";
    }

    file.close();
}

void Storage::loadProducts(Inventory& inventory,
                           const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    inventory.getProducts().clear();

    string line;
    getline(file, line);

    int maxProductId = 0;

    while (getline(file, line)) {
        try {
            vector<string> fields = parseCSV(line);

            if (fields.size() != 8) {
                continue;
            }

            int id = stoi(fields[0]);

            Product product(
                id,
                fields[1],
                fields[2],
                fields[3],
                stod(fields[4]),
                stod(fields[5]),
                stoi(fields[6]),
                stoi(fields[7])
            );

            inventory.getProducts().push_back(product);

            maxProductId = max(maxProductId, id);
        } catch (...) {
            cout << "\nSkipping invalid product record.\n";
        }
    }

    while (inventory.generateProductId() <= maxProductId) {
    }

    file.close();
}

void Storage::saveSales(const Sales& sales,
                        const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "\nUnable to save sales records.\n";
        return;
    }

    file << "SaleID,Date,Subtotal,Discount,Tax,Total,"
         << "ProductID,ProductName,Quantity,UnitPrice,ItemTotal\n";

    for (const auto& sale : sales.getSales()) {
        if (sale.items.empty()) {
            file << sale.saleId << ","
                 << escapeCSV(sale.date) << ","
                 << sale.subtotal << ","
                 << sale.discount << ","
                 << sale.tax << ","
                 << sale.total
                 << ",,,,,\n";
        }

        for (const auto& item : sale.items) {
            file << sale.saleId << ","
                 << escapeCSV(sale.date) << ","
                 << sale.subtotal << ","
                 << sale.discount << ","
                 << sale.tax << ","
                 << sale.total << ","
                 << item.productId << ","
                 << escapeCSV(item.productName) << ","
                 << item.quantity << ","
                 << item.unitPrice << ","
                 << item.total << "\n";
        }
    }

    file.close();
}

void Storage::loadSales(Sales& sales,
                        const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    map<int, Sale> loadedSales;

    while (getline(file, line)) {
        try {
            vector<string> fields = parseCSV(line);

            if (fields.size() != 11) {
                continue;
            }

            int saleId = stoi(fields[0]);

            if (loadedSales.find(saleId) == loadedSales.end()) {
                Sale sale;

                sale.saleId = saleId;
                sale.date = fields[1];
                sale.subtotal = stod(fields[2]);
                sale.discount = stod(fields[3]);
                sale.tax = stod(fields[4]);
                sale.total = stod(fields[5]);

                loadedSales[saleId] = sale;
            }

            if (!fields[6].empty()) {
                SaleItem item;

                item.productId = stoi(fields[6]);
                item.productName = fields[7];
                item.quantity = stoi(fields[8]);
                item.unitPrice = stod(fields[9]);
                item.total = stod(fields[10]);

                loadedSales[saleId].items.push_back(item);
            }
        } catch (...) {
            cout << "\nSkipping invalid sales record.\n";
        }
    }

    for (const auto& entry : loadedSales) {
        sales.addSale(entry.second);
    }

    file.close();
}
