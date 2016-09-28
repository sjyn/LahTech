#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle();
    virtual ~Vehicle(void);
    virtual std::string getInfo() = 0;
protected:
    std::string color;
};

#endif
