#include <iostream>
#include <string>
#include <list>

#include "Rental.h"

//This is the implementation of the Rental class

//This constructor is for customers which do not need to hold their name, just the id,
//quantity, and timestamp
Rental::Rental(const std::string& id, int quantity, const std::string& time){
    m_id = id;
    m_quantity = quantity;
    timestamp = time;
}

//This constructor is for tools, which need to hold the id, name, quantity and timestamp
Rental::Rental(const std::string& id, int quantity, const std::string& time, const std::string& name){
    m_id = id;
    m_quantity = quantity;
    m_name = name;
    timestamp = time;
}