
#include "Sales.h"
#include <iomanip>
using namespace std;

Sales::Sales() {
    nextSaleId = 1;
}

int Sales::generateSaleId() {
    return nextSaleId++;
}

void Sales::addSale(const Sale& sale) {
    Sale newSale = sale;

    if (newSale.saleId <= 0) {
        newSale.saleId = generateSaleId();
    } else if (newSale.saleId >= nextSaleId) {
        nextSaleId = newSale.saleId + 1;
    }

    sales.push_back(newSale);

    cout << "\nSale recorded successfully!\n";
    cout << "Sale ID: " << newSale.saleId << "\n";
}

void Sales::displaySalesHistory() const {
    if (sales.empty()) {
        cout << "\nNo sales records available.\n";
        return;
    }

    cout << "\n========== SALES HISTORY ==========\n";

    cout << left
         << setw(12) << "Sale ID"
         << setw(20) << "Date"
         << setw(15) << "Subtotal"
         << setw(15) << "Discount"
         << setw(15) << "Tax"
         << setw(15) << "Total"
         << "\n";

    cout << string(92, '-') << "\n";

    for (const auto& sale : sales) {
        cout << left
             << setw(12) << sale.saleId
             << setw(20) << sale.date
             << setw(15) << fixed << setprecision(2) << sale.subtotal
             << setw(15) << sale.discount
             << setw(15) << sale.tax
             << setw(15) << sale.total
             << "\n";
    }
}

double Sales::calculateTotalRevenue() const {
    double revenue = 0.0;

    for (const auto& sale : sales) {
        revenue += sale.total;
    }

    return revenue;
}

void Sales::displayTotalRevenue() const {
    cout << "\n========== SALES REVENUE ==========\n";

    cout << fixed << setprecision(2);
    cout << "Total Sales: " << sales.size() << "\n";
    cout << "Total Revenue: Rs. "
         << calculateTotalRevenue() << "\n";
}

void Sales::displaySaleDetails(int saleId) const {
    for (const auto& sale : sales) {
        if (sale.saleId == saleId) {
            cout << "\n========== SALE DETAILS ==========\n";

            cout << "Sale ID: " << sale.saleId << "\n";
            cout << "Date: " << sale.date << "\n";

            cout << "\nProduct Details:\n";

            cout << left
                 << setw(20) << "Product"
                 << setw(10) << "Quantity"
                 << setw(12) << "Price"
                 << setw(12) << "Total"
                 << "\n";

            cout << string(54, '-') << "\n";

            for (const auto& item : sale.items) {
                cout << left
                     << setw(20) << item.productName
                     << setw(10) << item.quantity
                     << setw(12) << fixed << setprecision(2)
                     << item.unitPrice
                     << setw(12) << item.total
                     << "\n";
            }

            cout << "\nSubtotal: Rs. " << sale.subtotal << "\n";
            cout << "Discount: Rs. " << sale.discount << "\n";
            cout << "Tax: Rs. " << sale.tax << "\n";
            cout << "Final Total: Rs. " << sale.total << "\n";

            return;
        }
    }

    cout << "\nSale record not found.\n";
}

int Sales::getTotalSales() const {
    return static_cast<int>(sales.size());
}

const vector<Sale>& Sales::getSales() const {
    return sales;
}
