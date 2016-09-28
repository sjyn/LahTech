#ifndef CAR_H
#define CAR_H

#include "vehicle.h"
#include <string>

class Car : public Vehicle
{
public:
    Car(std::string color);
    ~Car();
    std::string getInfo();
};

#endif
