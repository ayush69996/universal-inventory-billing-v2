
#include <iostream>
#include <limits>
#include "Inventory.h"
#include "Billing.h"
#include "Sales.h"
#include "Storage.h"
#include "InventoryReport.h"
#include "SalesReport.h"
using namespace std;

int main() {
    Inventory inventory;
    Sales sales;
    Billing billing(inventory, sales);

    Storage::loadProducts(inventory);
    Storage::loadSales(sales);

    int choice;

    cout << "\n============================================\n";
    cout << "       UNIVERSAL INVENTORY & BILLING       \n";
    cout << "============================================\n";
    cout << "Inventory and sales data loaded successfully.\n";

    do {
        cout << "\n\n============== MAIN MENU ==============\n";
        cout << "1. Add Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Restock Product\n";
        cout << "7. Display Low Stock Products\n";
        cout << "8. Create Customer Bill\n";
        cout << "9. Sales History\n";
        cout << "10. Sales Revenue Summary\n";
        cout << "11. View Sale Details\n";
        cout << "12. Inventory Summary\n";
        cout << "13. Save Data\n";
        cout << "14. Generate Inventory Report\n";
        cout << "15. Generate Sales Report\n";
        cout << "0. Exit\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                inventory.addProduct();
                Storage::saveProducts(inventory);
                break;

            case 2:
                inventory.displayProducts();
                break;

            case 3:
                inventory.searchProduct();
                break;

            case 4:
                inventory.updateProduct();
                Storage::saveProducts(inventory);
                break;

            case 5:
                inventory.deleteProduct();
                Storage::saveProducts(inventory);
                break;

            case 6:
                inventory.restockProduct();
                Storage::saveProducts(inventory);
                break;

            case 7:
                inventory.displayLowStockProducts();
                break;

            case 8:
                billing.createBill();
                Storage::saveProducts(inventory);
                Storage::saveSales(sales);
                break;

            case 9:
                sales.displaySalesHistory();
                break;

            case 10:
                sales.displayTotalRevenue();
                break;

            case 11: {
                int saleId;

                cout << "\nEnter Sale ID: ";
                cin >> saleId;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid Sale ID.\n";
                    break;
                }

                sales.displaySaleDetails(saleId);
                break;
            }

            case 12:
                inventory.displayInventorySummary();
                break;

            case 13:
                Storage::saveProducts(inventory);
                Storage::saveSales(sales);
                cout << "\nAll data saved successfully!\n";
                break;

            case 14: {
                InventoryReport inventoryReport(inventory);
                Report* report = &inventoryReport;
                report->generateReport();
                break;
            }

            case 15: {
                SalesReport salesReport(sales);
                Report* report = &salesReport;
                report->generateReport();
                break;
            }

            case 0:
                Storage::saveProducts(inventory);
                Storage::saveSales(sales);

                cout << "\nAll data saved successfully.\n";
                cout << "Thank you for using the system!\n";
                cout << "Exiting program...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
