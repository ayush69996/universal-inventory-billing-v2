
#pragma once

#include "Report.h"
#include "Sales.h"

class SalesReport : public Report {
private:
    const Sales& sales;

public:
    SalesReport(const Sales& sales);

    void generateReport() const override;
};
