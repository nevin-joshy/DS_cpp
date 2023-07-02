// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//


//adds car to end of specified train
void PushBack(TrainCar*& train, TrainCar* car){
    TrainCar* temp = train;
    //if there is nothing in the train, the train becoems the car
    if(temp == NULL){
        train = car;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = car;
        car->prev = temp;
        car->next = NULL;
    }
}

//adds car to the front of specified train
void PushFront(TrainCar*& train, TrainCar* car){
    //if there is nothing in the train, the train becoems the car
    if(train == NULL){
        train = car;
    }
    else{
        train -> prev = car;
        car->next = train;
        car->prev = NULL;
        train = car;
    }

}

//counts the number of engines in the specified train
int NumEngines(TrainCar*& train){
    TrainCar* counter = train;
    int numeng = 0;
    while(counter!=NULL){
        if(counter->isEngine()){
            numeng++;
        }
        counter = counter->next;
    }
    return numeng;
}

//erases a specified car fron the given train, and return a
//pointer to the car
TrainCar* Erase(TrainCar*& train, TrainCar*& car){
    //if the car is at the begninning, the next car becomes the head
    if(car->prev ==NULL){
        car->next->prev = NULL; 
        train = car->next;
    }
    //if car at end, sets previous car to be the end
    else if(car->next ==NULL){
        car->prev->next = NULL;  
    }
    else{
        car->prev->next = car->next;
        car->next->prev = car->prev;
    }
    car->next = NULL;
    car->prev = NULL;
    return car;
}

//counts the number of cars in the train
int NumCars(TrainCar*& train){
    TrainCar* counter = train;
    int numcar = 0;
    while(counter!=NULL){
        numcar++;
        counter = counter->next;
    }
    return numcar;
}

//deletes each car in the train starting at beginning
void DeleteAllCars(TrainCar*& train){
    TrainCar* temp = train;
    while(train!=NULL){
        temp = train;
        train = train -> next;
        delete temp;
    }
}

//takes in references to the train, int values for weight, engines, freight,
//passengercars, dining crs, and sleeping cars
void TotalWeightAndCountCars(TrainCar*& train, int& t_weight, int& num_engines, 
int& num_freight, int& num_pass_cars, int& num_dining_cars,int& num_sleep_cars){
    t_weight = 0;
    num_engines = 0;
    num_freight = 0;
    num_pass_cars = 0;
    num_dining_cars = 0;
    num_sleep_cars = 0;
    if(train ==NULL){
        return;
    }
    TrainCar* temp = train;
    for(temp = train; temp !=NULL; temp = temp->next){
        if(temp->isEngine()){
            num_engines++;
        }else if(temp->isFreightCar()){
            num_freight++;
        }else if(temp->isPassengerCar()){
            num_pass_cars++;
        }else if(temp->isDiningCar()){
            num_dining_cars++;
        }else if(temp->isSleepingCar()){
            num_sleep_cars++;
        }
        t_weight += temp->getWeight();
    }
}

//takes in the reference to a train and calculates the speed using the speed
//formula given in homework pdf
float CalculateSpeed(TrainCar*& train){
    TrainCar* temp = train;
    if (train==NULL){
        return 0;
    }
    float numengines = 0;
    float totalweight = 0;
    //adds to numengines each time there is an engine, and adds the weight of each
    //car to total weight
    for(temp = train; temp !=NULL; temp = temp->next){
        if(temp->isEngine()){
            numengines++;
        }
        totalweight+=temp->getWeight();
    }
    return (float(3000*numengines*550*3600))/(float(40*5280*totalweight));
}

//given a train, calculates the closest distance to a dining car
float AverageDistanceToDiningCar(TrainCar*& train){
    TrainCar* lead = train;
    TrainCar* forward = NULL;
    TrainCar* backward= NULL;
    int total = 0;
    int numpass = 0;

    //loops through each car in the train
    while(lead!=NULL){
        //if the car is a passenger, the the forward pointer goes forward through
        //the train and stops when an engine or dining car is reached or the end
        if(lead->isPassengerCar()){
            int forval=0;
            int backval=0;
            numpass++;
            forward = lead->next;
            while(forward!=NULL && !(forward->isEngine())){
                forval++;
                if(forward->isDiningCar()){
                    break;
                }
                forward = forward->next;
            }
            //now goes backward starting at the car and stops when dining, engine,
            //or end is reached
            backward = lead->prev;
            while(backward!=NULL && !(backward->isEngine())){
                backval++;
                if(backward->isDiningCar()){
                    break;
                }
                backward = backward->prev;
            }
            //checks whether the pointers got to a dining car, if not the values
            //are replaced by -1
            if(forward ==NULL || !(forward->isDiningCar())){
                forval = -1;
            }
            if(backward==NULL || !(backward->isDiningCar())){
                backval = -1;
            }
            // if both values are -1, then the car cannot reach a dining so we return -1
            if(forval ==-1 && backval ==-1){
                return -1;
            } else if(forval ==-1){
                total+=backval;
            } else if(backval ==-1){
                total+=forval;
            } else if(forval<backval){
                total+=forval;
            } else{
                total+=backval;
            }
        }
        lead = lead->next;
    }
    return (float(total))/(float(numpass));
}

//returns an int of the closest distance between an engine and sleeper car
int ClosestEngineToSleeperCar(TrainCar*& train){
    TrainCar* lead = train;
    TrainCar* forward = NULL;
    TrainCar* backward= NULL;
    //closest starts at high number to compare
    int closest = 1000;
    //loops through each car
    while(lead!=NULL){
        //if car is an engine, first goes forward until end or sleeper is reached
        if(lead->isEngine()){
            int forval=0;
            int backval=0;
            forward = lead->next;
            while(forward!=NULL){
                forval++;
                if(forward->isSleepingCar()){
                    break;
                }
                if(forward->isEngine()){
                    forward = NULL;
                    break;
                }
                forward = forward->next;
            }
            //goes backward from engine to find sleeper
            backward = lead->prev;
            while(backward!=NULL){
                backval++;
                if(backward->isSleepingCar()){
                    break;
                }
                if(backward->isEngine()){
                    backward = NULL;
                    break;
                }
                backward = backward->prev;
            }
            //only compares values if they were in bounds or hit a sleeper
            if(backward ==NULL && forward != NULL){
                if(forval<closest){
                    closest = forval;
                }
            }else if(backward != NULL && forward ==NULL){
                if(backval<closest){
                    closest = backval;
                }
            }else if(forward!= NULL && backward!= NULL){
                if(backval<closest){
                    closest = backval;
                }
                if(forval<closest){
                    closest = forval;
                }
            }
        }
        lead = lead->next;
    }
    return closest;
}

//This function takes in a linked stucture of engines, freightcars, and a minimum speed
//and maximum cars as restraints, in effort to carry as much of the freight as possible 
//in as little trains as possible that are above the minimum speed and below the maximum
// cars.
std::vector<TrainCar*> ShipFreight(TrainCar*& allEngines, TrainCar *& freightCars,
 int minSpeed, int maxCars){
    std::vector<TrainCar*> trainlist;
    TrainCar* newtrain = NULL;
    TrainCar* current = NULL;
    TrainCar* previous = NULL;
    int numcars = 0;
    int numengines = 0;
    double maxweight = 0;
    double currentweight = 0;
    //each loop is a new train, and keeps making trains while both lists are not null
    while(freightCars!=NULL && allEngines!=NULL){
        //train starts with engine
        newtrain = allEngines;
        newtrain->prev = NULL;
        allEngines = allEngines->next;
        if(allEngines != NULL)
            allEngines->prev = NULL;
        newtrain->next = NULL;
        //current tracks the car we are on, and previous will track the car before for
        //linking purposes
        current = newtrain;
        previous = newtrain;
        numcars++;
        currentweight+=150;
        numengines++;
        //calculates the maximum weight a train can have per engine given the
        // minimum speed
        maxweight = 59400000/(minSpeed*2112);
        //a car is added to the train with each loop. a freight train is added if the
        //weight does not go over, and if it does, then a new engine is considered by
        //seeing how many cars a new engine could fit, and if that fits in the current
        //train it is added, but if not the train will end so the potential of the engine
        //is not wasted
        while(numcars<maxCars && freightCars!=NULL){
            if((currentweight + freightCars->getWeight())<maxweight){
                current->next = freightCars;
                freightCars = freightCars->next;
                previous = current;
                current = current->next;
                current->next = NULL;
                current->prev = previous;
                if (freightCars != NULL)
                    freightCars->prev = NULL;
                currentweight+=current->getWeight();
                numcars++;
            }
            else{
                if(allEngines==NULL){
                    break;
                }
                TrainCar* temp = freightCars;
                double tempweight = 150;
                int possnum = 1;
                //checks possible number of cars engine can hold
                while(temp!=NULL && tempweight+temp->getWeight()<maxweight){
                    tempweight+=temp->getWeight();
                    temp = temp->next;
                    possnum++;
                }
                if(numcars+possnum<=maxCars){
                    current->next = allEngines;
                    allEngines = allEngines->next;
                    if (allEngines != NULL)
                        allEngines->prev = NULL;
                    previous = current;
                    current = current->next;
                    current->next = NULL;
                    current->prev = previous;
                    currentweight+=150;
                    numcars++;
                    numengines++;
                    //if engine is added, maxweight is adjusted accordingly
                    maxweight = float(numengines*59400000)/(minSpeed*2112);
                }
                else if(numcars+possnum>maxCars){
                    break;
                }
            }
        }
        //train is added to vector, and all variables are emptied
        trainlist.push_back(newtrain);
        newtrain = NULL;
        current = NULL;
        previous = NULL;
        numcars = 0;
        maxweight = 0;
        currentweight = 0;
        numengines = 0;
    }
    return trainlist;
}

//This function takes in a reference to 3 trains, the first is the train to be separated
//and the other 2 are the separated trains. The cfunction will split the trains into
//2 trains of similar speed while also minimizing the linking and unlinking and shifting
//so the price can also be minimized.
void Separate(TrainCar*& train1,TrainCar*& train2,TrainCar*& train3){
    train2 = NULL;
    train3 = NULL;
    int numcars = NumCars(train1);
    int normalcars = numcars - NumEngines(train1);
    int mid = 0;
    int frontengines = 0;
    int backengines = 0;
    TrainCar* counter = train1;
    TrainCar* lastengine;
    mid = numcars/2;
    TrainCar* middle = train1;

    int midcount = 0;
    while(midcount!=mid){
        middle = middle->next;
        midcount++;
    }

    //splits train1 in half, first half is train2 and second is train3
    train3 = middle;
    middle->prev->next = NULL;
    train3->prev = NULL;
    train2 = train1;
    train1= NULL;

    frontengines = NumEngines(train2);
    backengines = NumEngines(train3);
    int totalengines = frontengines + backengines;
    //keeps track of normal, or non engine cars is each of the 2 trains
    int t2norm = NumCars(train2) - frontengines;
    int t3norm = NumCars(train3) - backengines;

    //evens out the engines in each train while they are unbalanced. To optimize
    //shifting, takes last engine from train 2 and adds to front of train3, and
    //takes first engine from train3 and adds to back of train2.
    while(frontengines!=totalengines/2 && backengines!= totalengines/2){
        //more engines in train2
        if(backengines<frontengines){
            counter = train2;
            while(counter!=NULL){
                if(counter->isEngine()){
                    lastengine = counter;
                }
                counter=counter->next;
            }
            lastengine = Erase(train2, lastengine);
            PushFront(train3, lastengine);
            frontengines-=1;
            backengines+=1;
        }
        //more engines in train3
        else{
            counter = train3;
            while(counter!=NULL){
                if(counter->isEngine()){
                    lastengine = counter;
                    break;
                }
                counter=counter->next;
            }
            lastengine = Erase(train3, lastengine);
            PushBack(train2,lastengine);
            backengines-=1;
            frontengines+=1;
        }
    }
    TrainCar* lastnorm =NULL;

    //evens out the non engine cars while they are uneven, using the same
    //method as the engines
    while(t2norm!=normalcars/2 && t3norm!= normalcars/2){
        lastnorm = NULL;
        if(t2norm>t3norm){
            counter = train2;
            while(counter!=NULL){
                if(!(counter->isEngine())){
                    lastnorm = counter;
                }
                counter=counter->next;
            }
            lastnorm = Erase(train2, lastnorm);
            PushFront(train3,lastnorm);
            t2norm--;
            t3norm++;
        }
        if(t3norm>t2norm){
            counter = train3;
            while(counter!=NULL){
                if(!(counter->isEngine())){
                    lastnorm = counter;
                    break;
                }
                counter=counter->next;
            }
            lastnorm = Erase(train3, lastnorm);
            PushBack(train2,lastnorm);
            t3norm--;
            t2norm++;
        }
    }

    //if one train has more engines, (because number of engines is odd),
    //then that train should have 1 more normal car
    if(NumEngines(train2)>NumEngines(train3)){
        //train 2 has more engines and less normal cars
        if(t2norm<=t3norm){
            counter = train3;
            while(counter!=NULL){
                if(!(counter->isEngine())){
                    lastnorm = counter;
                }
                counter=counter->next;
            }
            lastnorm = Erase(train3, lastnorm);
            PushBack(train2,lastnorm);
            t2norm--;
            t3norm++;
        }
    }
    else if(NumEngines(train3)>NumEngines(train2)){
        //train 3 has more engines and less normal cars
        if(t3norm<=t2norm){
            counter = train2;
            while(counter!=NULL){
                if(!(counter->isEngine())){
                    lastnorm = counter;
                    break;
                }
                counter=counter->next;
            }
            lastnorm = Erase(train2, lastnorm);
            PushFront(train3,lastnorm);
            t2norm++;
            t3norm--;
        }
    }
}

