#include "car.h"

Car::Car(std::string color) : Vehicle(){
    this->color = color;
}

Car::~Car(){

}

std::string Car::getInfo(){
    return "A " + this->color + " Car";
}
