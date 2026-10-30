
#pragma once

#include "Report.h"
#include "Inventory.h"

class InventoryReport : public Report {
private:
    const Inventory& inventory;

public:
    InventoryReport(const Inventory& inventory);

    void generateReport() const override;
};
