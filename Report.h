
#pragma once

#include <string>
using namespace std;

class Report {
public:
    virtual void generateReport() const = 0;

    virtual ~Report() {
    }
};
