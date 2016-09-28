#ifndef TRUCK_H
#define TRUCK_H

#include "vehicle.h"
#include <string>

class Truck: public Vehicle
{
public:
    Truck(std::string color);
    ~Truck();

    std::string getInfo();
};

#endif
