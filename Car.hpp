#ifndef CAR_HPP
#define CAR_HPP

/**
 * @author: walther
 * @date: Sept 2018
 */

#include <boost/fusion/adapted/struct.hpp>

//typedef Car[] CarArrayType;

// Define a set of Platform types.
enum Platform {
    UNKNOWN,
    SHIP,
    CAR,
    AIRCRAFT
};

// Define a Car base class.
struct Car
{
    unsigned int horsePower;
    double engineSize;
    char name[10];
};

// Define an Chevy child class.
struct Chevy : public Car
{
    Chevy(unsigned int horsePower, double engineSize, char name[], unsigned int year, Platform plat) :
            Car{horsePower, engineSize, {'c', 'a', 'r', '1', '\0'} },
            year(year),
            plat(plat)
    {
        return;
    }
	
    unsigned int year;
    Platform plat;
};

// Apply Boost.Fusion to these classes.
BOOST_FUSION_ADAPT_STRUCT(Car, horsePower, engineSize, name)
BOOST_FUSION_ADAPT_STRUCT(Chevy, horsePower, engineSize, name, year, plat)



#endif /* CAR_HPP */