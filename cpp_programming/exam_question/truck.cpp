#include "truck.h"

Truck::Truck(std::string color): Vehicle(){
    this->color = color;
}

Truck::~Truck(){}

std::string Truck::getInfo(){
    return "A " + this->color + " Truck";
}
