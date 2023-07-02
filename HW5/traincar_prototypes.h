// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"


//this prototypes header file is an extension of traincar.h, and defines non-member
//functions to operate on trains

#include <vector>

void PushBack(TrainCar*& train, TrainCar* car);

void PushFront(TrainCar*& train, TrainCar* car);

int NumEngines(TrainCar*& train);

TrainCar* Erase(TrainCar*& train, TrainCar*& car);

int NumCars(TrainCar*& train);

void DeleteAllCars(TrainCar*& train);

float CalculateSpeed(TrainCar*& train);

void TotalWeightAndCountCars(TrainCar*& train, int& t_weight, int& num_engines, 
    int& num_freight, int& num_pass_cars, int& num_dining_cars,int& num_sleep_cars);

float AverageDistanceToDiningCar(TrainCar*& train);

int ClosestEngineToSleeperCar(TrainCar*& train);

std::vector<TrainCar*> ShipFreight(TrainCar*& allEngines, TrainCar *& freightCars,
int minSpeed, int maxCars);

void Separate(TrainCar*& train1,TrainCar*& train2,TrainCar*& train3);