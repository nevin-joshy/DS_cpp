#include <iostream>
#include <string>
#include <list>

#include "Customer.h"

//This is the implementation of the Customer class

//the default constructor sets the member variables to empty
Customer::Customer(){
    m_cid = "";
    m_cname = "";
}

//This function adds a Rental object to the renting list, in order of id
void Customer::add_to_rental(Rental r){
    bool isadded = false;
    std::list<Rental>::iterator itr1;
    for(itr1 = renting.begin();itr1!=renting.end();itr1++){
        //compares the ids until the id is smaller than the next element
        if(r.get_id()<(*itr1).get_id()){
            renting.insert(itr1,r);
            isadded = true;
            break;
        }
    }
    //adds rental object to end of the list if its id is not smaller than any
    //object already in the list
    if(!isadded){
        renting.push_back(r);
    }
}

//This function adds a Rental object to the renting list, in order of id
void Customer::add_to_wait(Rental r){
    bool isadded = false;
    std::list<Rental>::iterator itr1;
    for(itr1 = pending.begin();itr1!=pending.end();itr1++){
        //compares the ids until the id is smaller than the next element
        if(r.get_id()<(*itr1).get_id()){
            pending.insert(itr1,r);
            isadded = true;
            break;
        }
    }
    //adds rental object to end of the list if its id is not smaller than any
    //object already in the list
    if(!isadded){
        pending.push_back(r);
    }
}

//This function removes a Rental object from the renting list, for example if it
//is returned
void Customer::remove_from_rental(const std::string& id){
    std::list<Rental>::iterator itr;
    for(itr = renting.begin(); itr != renting.end();itr++){
        //looks for id in renting list and erases
        if((*itr).get_id()==id){
            renting.erase(itr);
            return;
        }
    }
}

//This function removes a Rental object from the waiting list, for example if 
//there was a return and it can be moved to the renting list
void Customer::remove_from_wait(const std::string& id){
    std::list<Rental>::iterator itr;
    for(itr = pending.begin(); itr != pending.end();itr++){
        //looks for id in waiting list and erases
        if((*itr).get_id()==id){
            pending.erase(itr);
            return;
        }
    }
}

//This function outputs the Customer object information directly into the output file in 
//the proper order
std::ostream& Customer::output_customer(std::ostream& out_str) const{
    std::list<Rental>::const_iterator itr;
    out_str<<m_cid<<" "<<m_cname<<"\n";
    //Only prints out rentals if the renting list has Rentals in it
    if(renting.size()!=0){
        out_str<<"Rentals: ";
        for(itr = renting.begin(); itr != renting.end(); itr++){
            out_str<<(*itr).get_id()<<" ("<<(*itr).get_quantity()<<") ";
        }
        out_str<<"\n";
    }
    //Only prints out pending rentals if the waiting list has Rentals in it
    if(pending.size()!=0){
        out_str<<"Pending: ";
        for(itr = pending.begin(); itr != pending.end(); itr++){
            out_str<<(*itr).get_id()<<" ("<<(*itr).get_quantity()<<") ";
        }
        out_str<<"\n";
    }
    out_str<<"\n";
    return out_str;
}

//This function checks whether a customer is empty, meaning its
//renting and waiting list are both empty. If this fucntion is true,
//the customer need to be deleted from the customer list
bool Customer::isEmpty(){
    if(m_cid ==""||(renting.size()==0&&pending.size()==0)){
        return true;
    }
    return false;
}

//This function does most of the work of all the code. It reads each line of the
//customer input file and assigns member variables to a Customer object which can
//then be added to the customerlist. It takes in all of the arguments and determines
//what to do if it is a rental or a return, and if the customer already exists to 
//add the rental to that list, not this new object. It also edits the tool objects
//based on whether there is a rental or return
bool Customer::read(std::istream& in_str, std::list<Tool> &toollist, 
std::list<Customer> &customerlist){
    if (!(in_str >> m_cid)) return false;

    //checks whether the id is in the customerlist already, and if it is inlist
    //becomes true, reference to the object in list can be accessed through currentcustomer
    bool inlist = false;
    std::list<Customer>::iterator currentcustomer;
    for(currentcustomer = customerlist.begin(); currentcustomer!= customerlist.end()
    ;currentcustomer++){
        if((*currentcustomer).get_id() == m_cid){
            inlist = true;
            break;
        }
    }
    
    //clears renting and pending list of objects from previous Customer object
    renting.clear();
    pending.clear();

    //Saves first letter of customer id as letter and the numbers as number
    std::string letter = m_cid.substr(0,1);
    std::string number = m_cid.substr(1,4);

    std::string action;
    std::string time;
    int quantity;
    std::string toolid;

    //reads all remaining values in the line and assigns them to variables
    in_str>>action>>time>>quantity>>toolid>>m_cname;

    //Saves first letter of tool id as letter and the numbers as number
    std::string tletter = toolid.substr(0,1);
    std::string tnumber = toolid.substr(1,4);

    //Checks whether the tool being requested is in the toollist, and if not,
    //intoollist is false, stores the tool given at currenttool
    std::list<Tool>::iterator currenttool;
    bool intoollist = false;
    for(currenttool = toollist.begin(); currenttool!= toollist.end();currenttool++){
        if((*currenttool).get_id() == toolid){
            intoollist = true;
            break;
        }
    }

    //error checking to make sure the tool requested by the customer is valid
    if((tletter!="T")||(tnumber<"0001")){
        std::cerr<<"Invalid inventory ID "<<toolid<<" found in the inventory file.";
    }
    //checks whether the requested item is in the inventory list
    else if((!intoollist)&&action=="rent"){
        std::cerr<<"Customer "<<m_cid<<" requested item "<<toolid
        <<" which is not in the inventory.\n";
    }
    //if the item is not in the toollist and they are returning, outputs separate
    //error message
    else if((!intoollist)&&action=="return"){
        std::cerr<<"Customer "<<m_cid<<" attempted to return item "<<toolid
        <<" which is not in the inventory.\n";
    }
    //checks whether the given customer id is valid, starts with C and is greater than 1
    else if((letter!="C")||(number<"0001")){
        std::cerr<<"Invalid customer information found for ID "<<m_cid
        <<" in the customer file.\n";
        m_cid = "";
    }
    else{
        if(action =="rent" && !(inlist)){
            //if the customer is not in the list, and the quantity remaining in the tool
            //is big enough for the requested rental and there is no one in the waitlist,
            //the suantity is take from the tools quantity and the Rental is added to the
            //tool and customer's renting list
            if((*currenttool).get_quantity()>=quantity&&(*currenttool)
            .get_wait_size()==0){
                (*currenttool).sub_quantity(quantity);
                (*currenttool).add_to_rental(Rental(m_cid,quantity,time,m_cname));
                (*this).add_to_rental(Rental(toolid, quantity,time));
            }
            //if there is not enough quantity in the tool or there is a waiting list,
            //the customer is added to the waiting list as a Rental object and to the
            //tools waiting list
            else{
                (*currenttool).add_to_wait(Rental(m_cid,quantity,time,m_cname));
                (*this).add_to_wait(Rental(toolid, quantity,time));
            }
        }
        else if(action=="rent"){
            //if the customer is already in list, and the quantity remaining in the tool
            //is big enough for the requested rental and there is no one in the waitlist,
            //the quantity is take from the tools quantity and the Rental is added to the
            //tool and the customer's that is already in the lists renting list(currentcustomer),
            //rather than the current customer object
            if((*currenttool).get_quantity()>=quantity&&(*currenttool)
            .get_wait_size()==0){
                (*currenttool).sub_quantity(quantity);
                (*currenttool).add_to_rental(Rental(m_cid,quantity,time,m_cname));
                (*currentcustomer).add_to_rental(Rental(toolid, quantity,time));
            }
            //if there is not enough quantity in the tool or there is a waiting list,
            //the customer is added to the waiting list as a Rental object and to the
            //tools waiting list
            else{
                (*currenttool).add_to_wait(Rental(m_cid,quantity,time,m_cname));
                (*currentcustomer).add_to_wait(Rental(toolid, quantity,time));
            }
        }
        //if the customer is renting, cheacks whether the customer is in the tools
        //returning list because it could be an error, returning something they never
        //rented
        else if(action=="return" && (*currenttool).isRenting(m_cid)){
            (*currenttool).add_quantity(quantity);
            //removes customer from the tool and customer rental lists
            (*currenttool).remove_from_rental(m_cid);
            (*currentcustomer).remove_from_rental(toolid);

            //checks whether the earliest waitlist Rental request can be fulfilled
            while((*currenttool).check_waitlist()){
                std::string cid;
                (*currenttool).edit_waitlist(cid);
                std::list<Customer>::iterator newcustomer;
                //finds customer that was removed from the waitlist
                for(newcustomer = customerlist.begin(); newcustomer!= customerlist.end()
                ;newcustomer++){
                    if((*newcustomer).get_id() == cid){
                        break;
                    }
                }
                std::list<Rental> templist = (*newcustomer).get_pendinglist();
                std::list<Rental>::iterator newrental;
                int newquantity;
                std::string newtime;
                //looks through the pendinglist of the customer and finds the
                //Rental information and stores it
                for(newrental = templist.begin();newrental != templist.end()
                ; newrental++){
                    if((*newrental).get_id() == toolid){
                        newquantity = (*newrental).get_quantity();
                        newtime = (*newrental).get_time();
                    }
                }
                //adds the Rental object to the customers renting list, removes from
                //the waiting list
                (*newcustomer).add_to_rental(Rental(toolid, newquantity,newtime));
                (*newcustomer).remove_from_wait(toolid);
                (*currenttool).remove_from_wait(cid);
            }

        }else{
            std::cerr<<"Customer "<<m_cid<<" attempted to return item "<<toolid
            <<" which she/he did not rent.\n";
        }
    }

    //if the customer is already in the customerlist, the id is set to empty as a flag 
    //so it is not added to the customerlist again
    if(inlist){
        m_cid = "";
    }

    return true;
}