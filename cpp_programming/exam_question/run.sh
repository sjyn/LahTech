#Compile the cpp files
g++ -c vehicle.cpp
g++ -c car.cpp
g++ -c truck.cpp
g++ -c parkinglot.cpp

#compile the main file
#enable threading
#specify the cpp11 stdlib
#link the resulting object files
g++ main.cpp -pthread -std=c++11 parkinglot.o car.o vehicle.o truck.o

#clean the directory
rm car.o
rm truck.o
rm vehicle.o
rm parkinglot.o

#remove some of the auxillary files
if [ -e "parkinglot.h.gch" ]
then
    rm parkinglot.h.gch
fi
if [ -e "truck.h.gch" ]
then
    rm truck.h.gch
fi
if [ -e "car.h.gch" ]
then
    rm car.h.gch
fi
if [ -e "vehicle.h.gch" ]
then
    rm vehicle.h.gch
fi

#run the executable
./a.out
