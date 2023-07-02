#include <iostream>
#include <fstream>
#include <string>
#include <list>


#include "Rental.h"
#include "Customer.h"
#include "Tool.h"

//reads through all the customers(using read function), and adds to the customerlist, 
//checking that the id is not empty. The customers are placed in id order
void readcustomers(std::ifstream& customerin, std::list<Tool>& toollist, 
std::list<Customer>& customerlist){
    Customer acustomer;
    while(acustomer.read(customerin,toollist,customerlist)){
        if(acustomer.get_id() != ""){
            bool isadded = false;
            std::list<Customer>::iterator itr1;
            for(itr1 = customerlist.begin();itr1!=customerlist.end();itr1++){
                if(acustomer.get_id()<(*itr1).get_id()){
                    customerlist.insert(itr1,acustomer);
                    isadded = true;
                    break;
                }
            }
            if(!isadded){
                //if the id is not less than any objects id, it is added to end
                customerlist.push_back(acustomer);
            }
        }
    }
}

//reads through all the tools(using read function), and adds to the toollist, 
//checking that the id is not empty. The tools are placed in id order
void readtools(std::ifstream& inventoryin, std::list<Tool>& toollist){
    Tool atool;
    while(atool.read(inventoryin)){
        if(atool.get_id() != ""){
            bool isadded = false;
            std::list<Tool>::iterator itr1;
            for(itr1 = toollist.begin();itr1!=toollist.end();itr1++){
                if(atool.get_id()<(*itr1).get_id()){
                    toollist.insert(itr1,atool);
                    isadded = true;
                    break;
                }
            }
            if(!isadded){
                //if the id is not less than any objects id, it is added to end
                toollist.push_back(atool);
            }
        }
    }
}

//prints tool information one by one to output file
void printtools(std::ostream& toolout, std::list<Tool>& toollist){
    std::list<Tool>::iterator itr;
    for(itr = toollist.begin();itr!=toollist.end();itr++){
        (*itr).output_tool(toolout);
    }
}

//deletes empty customers from customerlist
void clean_customers(std::list<Customer>& customerlist){
    std::list<Customer>::iterator itr2;
    for(itr2 = customerlist.begin();itr2!=customerlist.end();itr2++){
        if((*itr2).isEmpty()){
            itr2 = customerlist.erase(itr2);
            itr2--;
        }
    }
}

//prints customer information to output file
void printcustomers(std::ostream& customerout, std::list<Customer>& customerlist){
    std::list<Customer>::iterator itr2;
    for(itr2 = customerlist.begin();itr2!=customerlist.end();itr2++){
        (*itr2).output_customer(customerout);
    }
}

int main(int argc, char *argv[]){
    std::ifstream inventoryin(argv[1]);//defines input file stream as toolin
    if (!inventoryin)//checks whether input file can be read, if not gives error
    {
        std::cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }

    std::ifstream customerin(argv[2]);//defines input file stream as customerin
    if (!customerin)//checks whether input file can be read, if not gives error
    {
        std::cerr << "Could not open " << argv[2] << " to read\n";
        return 1;
    }

    std::ofstream toolout(argv[3]);//defines output file as toolout
    if (!toolout)//checks whether output file can be written to, if not gives error
    {
        std::cerr << "Could not open " << argv[3] << " to write\n";
        return 1;
    }

    std::ofstream customerout(argv[4]);//defines output file as customerout
    if (!customerout)//checks whether output file can be written to, if not gives error
    {
        std::cerr << "Could not open " << argv[4] << " to write\n";
        return 1;
    }

    std::list<Tool> toollist;
    std::list<Customer> customerlist;
    readtools(inventoryin, toollist);
    readcustomers(customerin, toollist, customerlist);
    printtools(toolout, toollist);
    clean_customers(customerlist);
    printcustomers(customerout,customerlist);

    return 0;
}