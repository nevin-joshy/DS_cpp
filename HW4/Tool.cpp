#include <iostream>
#include <list>
#include <string>

#include "Tool.h"
#include "Rental.h"

//This is the implementation of the Tool class

//The default constructor sets all values to empty
Tool::Tool(){
    m_id = "";
    m_name = "";
    m_quantity = 0;
    
}

//This function adds a Rental object to the rentlist, in order of id
void Tool::add_to_rental(Rental r){
    bool isadded = false;
    std::list<Rental>::iterator itr1;
    for(itr1 = rentlist.begin();itr1!=rentlist.end();itr1++){
        //compares the ids until the id is smaller than the next element
        if(r.get_id()<(*itr1).get_id()){
            rentlist.insert(itr1,r);
            isadded = true;
            break;
        }
    }
    //adds rental object to end of the list if its id is not smaller than any
    //object already in the list
    if(!isadded){
        rentlist.push_back(r);
    }
}

//This function adds a Rental object to the waitlist, in order of id
void Tool::add_to_wait(Rental r){
    bool isadded = false;
    std::list<Rental>::iterator itr1;
    for(itr1 = waitlist.begin();itr1!=waitlist.end();itr1++){
        //compares the ids until the id is smaller than the next element
        if(r.get_id()<(*itr1).get_id()){
            waitlist.insert(itr1,r);
            isadded = true;
            break;
        }
    }
    //adds rental object to end of the list if its id is not smaller than any
    //object already in the list
    if(!isadded){
        waitlist.push_back(r);
    }
}

//This function removes a Rental object from the renting list, for example if it
//is returned
void Tool::remove_from_rental(const std::string& id){
    std::list<Rental>::iterator itr;
    for(itr = rentlist.begin(); itr != rentlist.end();itr++){
        //looks for id in renting list and erases
        if((*itr).get_id()==id){
            rentlist.erase(itr);
            return;
        }
    }
}

//This function removes a Rental object from the waiting list, for example if 
//there was a return and it can be moved to the renting list
void Tool::remove_from_wait(const std::string& id){
    std::list<Rental>::iterator itr;
    for(itr = waitlist.begin(); itr != waitlist.end();itr++){
        //looks for id in waiting list and erases
        if((*itr).get_id()==id){
            waitlist.erase(itr);
            return;
        }
    }
}

//This function checks whether a customer is renting an item, so that they cannot
//return an item they are not renting
bool Tool::isRenting(const std::string& id){
    std::list<Rental>::iterator itr;
    for(itr = rentlist.begin(); itr != rentlist.end();itr++){
        //looks for id in the renting list
        if((*itr).get_id()==id){
            return true;
        }
    }
    return false;
}

//This function returns true if a Rental object can be removed from the waitlist
//based on the quantity requested and its timestamp
bool Tool::check_waitlist(){
    if(waitlist.size() == 0){
        return false;
    }
    std::list<Rental>::iterator lowest;
    //initializes the lowest time at a high time so that the lowest will be found
    std::string lowtime="99999";
    std::string cid;
    for(lowest = waitlist.begin();lowest!= waitlist.end();lowest++){
        if((*lowest).get_time()<lowtime){
            //if a lower time is found, it is assigned to lowtime, and its id is kept
            lowtime = (*lowest).get_time();
            cid = (*lowest).get_id();
        }
    }
    //sets iterator to the point of the rental with the lowest time and id found before
    for(lowest = waitlist.begin();lowest!= waitlist.end();lowest++){
        if((*lowest).get_time()==lowtime && (*lowest).get_id()==cid){
            break;
        }
    }
    //checks whether the quantity requested at the lowest time is less than or equal to
    //what is ava/ible
    if((*lowest).get_quantity()<=m_quantity){
        return true;
    }
    return false;
}

//This function removes the Rental object with the lowest time from the waitlist
//and adds it to the rental list
void Tool::edit_waitlist(std::string& cid){
    std::list<Rental>::iterator lowest;
    //initializes the lowest time at a high time so that the lowest will be found
    std::string lowtime="99999";
    for(lowest = waitlist.begin();lowest!= waitlist.end();lowest++){
        if((*lowest).get_time()<lowtime){
            //if a lower time is found, it is assigned to lowtime, and its id is kept
            lowtime = (*lowest).get_time();
            cid = (*lowest).get_id();
        }
    }
    //sets iterator to the point of the rental with the lowest time and id found before
    for(lowest = waitlist.begin();lowest!= waitlist.end();lowest++){
        if((*lowest).get_time()==lowtime && (*lowest).get_id()==cid){
            break;
        }
    }
    //checks whether the amount can possibly be rented, then removes that amount,
    // and then adds the Rental object 
    //to rental list, then removes it from the waiting list
    if((*lowest).get_quantity()<=m_quantity){
        add_to_rental(*lowest);
        sub_quantity((*lowest).get_quantity());
        remove_from_wait((*lowest).get_id());
    }
}

//This function outputs the Tool object information directly into the output file in the
//proper order
std::ostream& Tool::output_tool(std::ostream& out_str) const{
    out_str<<m_id<<" "<<m_quantity<<" available "<<m_name<<"\n";
    std::list<Rental>::const_iterator itr;
    //only prints if there are rental cusotmers
    if(rentlist.size()!=0){
        out_str<<"Rental Customers: ";
        for(itr = rentlist.begin(); itr != rentlist.end(); itr++){
            out_str<<(*itr).get_id()<<" "<<(*itr).get_name()<<" ("<<(*itr).get_quantity()<<") ";
        }
        out_str<<"\n";
    }
    //only prints if there are waiting customers
    if(waitlist.size()!=0){
        out_str<<"Pending Customers: ";
        for(itr = waitlist.begin(); itr != waitlist.end(); itr++){
            out_str<<(*itr).get_id()<<" "<<(*itr).get_name()<<" ("<<(*itr).get_quantity()<<") ";
        }
        out_str<<"\n";
    }
    out_str<<"\n";

    return out_str;
}

//This function acts as a constructor for the tool class in that it uses the input file
//to assign a Tool object's member variables, returns true while it can read words
bool Tool::read(std::istream& in_str){
    if (!(in_str >> m_id)) return false;

    //saves the first letter of the id and the 4 numbers
    std::string tletter = m_id.substr(0,1);
    std::string tnumber = m_id.substr(1,4);
    
    in_str>>m_quantity;

    in_str>>m_name;

    //if the id does not begin with T and is not greater than zero, the id is set to
    //empty, which acts as a flag so it will not be added to the main toollist
    if((tletter!="T")||(tnumber<"0001")||(m_quantity<1)){
        std::cerr<<"Invalid inventory ID "<<m_id<<" found in the inventory file.\n";
        m_id = "";
    }

    return true;

}