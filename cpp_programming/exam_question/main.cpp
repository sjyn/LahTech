#include "parkinglot.h"
#include <iostream>
#include <thread>

using namespace std;

ParkingLot lot;

void addCar(string color){
    lot.addVehicle(new Car(color));
}

void addTruck(string color){
    lot.addVehicle(new Truck(color));
}

int main(){
    for (int i = 0; i < 20; i++) {
        if(i % 2 == 0){
            thread addc(addCar, "Red");
            addc.join();
        } else {
            thread addt(addTruck, "Purple");
            addt.join();
        }
    }
    lot.listVehicles();
}
