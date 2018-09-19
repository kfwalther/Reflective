/**
 * @author: walther
 * @date: Sept 2018
 */

#include <boost/fusion/adapted/struct.hpp>

 
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
    int engineSize;
    std::string name;
};

// Define an Chevy child class.
struct Chevy : public Car
{
    Chevy(unsigned int horsePower, int engineSize, std::string name, unsigned int year, Platform plat) :
            Car{horsePower, engineSize, name},
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