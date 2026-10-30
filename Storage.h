
#pragma once

#include "Inventory.h"
#include "Sales.h"
#include <string>
using namespace std;

class Storage {
public:
    static void saveProducts(const Inventory& inventory,
                             const string& filename = "products.csv");

    static void loadProducts(Inventory& inventory,
                             const string& filename = "products.csv");

    static void saveSales(const Sales& sales,
                          const string& filename = "sales.csv");

    static void loadSales(Sales& sales,
                          const string& filename = "sales.csv");
};
