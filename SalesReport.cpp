
#include "SalesReport.h"
#include <iostream>
#include <iomanip>
using namespace std;

SalesReport::SalesReport(const Sales& sales)
    : sales(sales) {
}

void SalesReport::generateReport() const {
    cout << "\n========== SALES REPORT ==========\n";

    cout << "Total Sales: " << sales.getTotalSales() << "\n";

    cout << fixed << setprecision(2);

    cout << "Total Revenue: Rs. "
         << sales.calculateTotalRevenue() << "\n";

    cout << "\n========== SALES DETAILS ==========\n";

    sales.displaySalesHistory();

    cout << "\n===================================\n";
}
