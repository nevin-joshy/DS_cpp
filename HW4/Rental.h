#ifndef __Rental_h_
#define __Rental_h_
#include <iostream>
#include <list>
#include <string>

/*The Rental class stores the information of every rent that is made in the file.
It holds a id, quantity, and timestamp, and can have a name too.
*/
class Rental{
public:
    Rental(const std::string& id, int quantity, const std::string& time);
    Rental(const std::string& id, int quantity, const std::string& time, const std::string& name);
    const std::string& get_name() const{return m_name;}
    const std::string& get_time() const{return timestamp;}
    const std::string& get_id() const{return m_id;}
    int get_quantity() const{return m_quantity;}
    void add(int num){m_quantity+=num;}
    void sub(int num){m_quantity-=num;}

private:
    std::string m_name;
    std::string m_id;
    std::string timestamp;
    unsigned int m_quantity;

};

#endif