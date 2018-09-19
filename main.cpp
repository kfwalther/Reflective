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
    Car car = { 280, 3.8, "Racer" };
    Chevy chevy = { 315, 4.2, "Tahoe", 2005, Platform::CAR };

	// Print their fields.
    PrintMembers(car);
    PrintMembers(chevy);
    
    std::cout << std::endl << "Successful completion!" << std::endl;
	return EXIT_SUCCESS;
}






