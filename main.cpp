/**
 * @author: walther
 * @date: Sept 2018
 */

#include <string>
#include <iostream>

#include "Car.hpp"
#include "PrinterIterator.hpp"

// Main entry point to the program.
int main()
{
    // Instantiate the classes.
    Car car = { 280, 38, "Racer" };
    Chevy chevy = { 315, 42, "Tahoe", 2005, Platform::CAR };

	// Print their fields.
    PrintMembers(car);
    PrintMembers(chevy);
    
    std::cout << "Successful completion!" << std::endl;
	return EXIT_SUCCESS;
}






