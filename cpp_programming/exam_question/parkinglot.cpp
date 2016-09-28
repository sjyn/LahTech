#include "parkinglot.h"
#include <iostream>

ParkingLot::ParkingLot(){

}

ParkingLot::~ParkingLot(){
    it = autos.begin();
    while(it != autos.end()){
        delete *it;
        it++;
    }
    autos.clear();
}

void ParkingLot::addVehicle(Vehicle* a){
    if(a){
        std::lock_guard<std::mutex> lock(myTex);
        autos.push_back(a);
    }
}

void ParkingLot::listVehicles(){
    std::lock_guard<std::mutex> lock(myTex);
    it = autos.begin();
    while(it != autos.end()){
        std::cout << (*it)->getInfo() << std::endl;
        it++;
    }
}
