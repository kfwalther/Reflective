#ifndef CARDEALER_HPP
#define CARDEALER_HPP

/**
 * @author: walther
 * @date: Sept 2018
 */

#include <boost/fusion/adapted/struct.hpp>
#include "Car.hpp"
 
int const MAX_VEHICLES = 10;

// Define a CarDealer class.
struct CarDealer
{
    float name;
	Car inventory[MAX_VEHICLES];
};

// Apply Boost.Fusion to this class.
BOOST_FUSION_ADAPT_STRUCT(CarDealer, name, inventory)


#endif /* CARDEALER_HPP */