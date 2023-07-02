#ifndef __Customer_h_
#define __Customer_h_
#include <iostream>
#include <list>
#include <string>

#include "Tool.h"
#include "Rental.h"

/*The customer class will create a customer object for each customer in the customer file
and maintain their id and name as well as 2 lists of Rental objects, one for current 
rentals and one for pending ones. As customers rent tools, the renting list and waiting 
list will be changed. The customer object is created through the read fucntion which 
assigns its member variables and populates the lists, as well as for the tools depending
on whether there is a rent or return action
*/

class Customer{
public:
    Customer();
    const std::string& get_id() const{return m_cid;}
    const std::string& get_name() const{return m_cname;}
    const std::list<Rental>& get_rentinglist(){return renting;}
    const std::list<Rental>& get_pendinglist(){return pending;}
    
    void add_to_rental(Rental r);
    void add_to_wait(Rental r);
    void remove_from_rental(const std::string& id);
    void remove_from_wait(const std::string& id);
    bool isEmpty();
    bool read(std::istream& in_str, std::list<Tool> &toollist, std::list<Customer> &customerlist);
    std::ostream& output_customer(std::ostream& out_str) const;

private:
    std::string m_cid;
    std::string m_cname;
    std::list<Rental> renting;
    std::list<Rental> pending;
};

#endif