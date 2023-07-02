#ifndef __Tool_h_
#define __Tool_h_
#include <iostream>
#include <list>
#include <string>

#include "Rental.h"

/*The tool class will create a tool object for each tool in the inventory and maintain
its id, name, and quantity available at the current time. As customers rent the tool,
the avaiable quantity can be changed. Each tool object also maintains 2 lists of
Rental objects, a rentlist and waitlist, which contain information about people
who are renting and waiting to rent the tool.
*/

class Tool{
public:
    Tool();
    const std::string& get_id() const{return m_id;}
    const std::string& get_name() const{return m_name;}
    int get_quantity() const{return m_quantity;}
    int get_wait_size() const{return waitlist.size();}
    const std::list<Rental>& get_rentlist() {return rentlist;}
    const std::list<Rental>& get_waitlist() {return waitlist;}

    //These 2 functions can change the quantity of the tool available depending on
    //the quantity each cusotmer rents/returns
    void sub_quantity(int num){m_quantity-=num;}
    void add_quantity(int num){m_quantity+=num;}

    bool read(std::istream& in_str);
    void add_to_rental(Rental r);
    void add_to_wait(Rental r);
    void remove_from_rental(const std::string& id);
    void remove_from_wait(const std::string& id);
    void edit_waitlist(std::string& cid);
    bool check_waitlist();
    bool isRenting(const std::string &id);
    std::ostream& output_tool(std::ostream& out_str) const;



private:
    std::string m_id;
    std::string m_name;
    int m_quantity;
    std::list<Rental> rentlist;
    std::list<Rental> waitlist;
};



#endif