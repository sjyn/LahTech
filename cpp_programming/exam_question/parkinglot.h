#ifndef PL_H
#define PL_H

#include <vector>
#include <mutex>

#include "car.h"
#include "truck.h"
#include "vehicle.h"

class ParkingLot {
private:
    std::vector<Vehicle*> autos;
    std::vector<Vehicle*>::iterator it;
    std::mutex myTex;
public:
    ParkingLot();
    ~ParkingLot();

    void addVehicle(Vehicle* a);
    void listVehicles();
};

#endif
