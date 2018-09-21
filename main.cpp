/**
 * @author: walther
 * @date: Sept 2018
 */

#include <string>
#include <iostream>

#include "Car.hpp"
#include "CarDealer.hpp"
#include "PrinterIterator.hpp"

// Main entry point to the program.
int main()
{
    // Instantiate the classes.
	Car car1 = {250, 3.5, 3.3};
	Car car2 = {260, 3.6, 3.3};
	Car car3 = {275, 3.75, 3.3};
    // Chevy chevy = { 315, 4.2, "Tahoe", 2005, Platform::CAR };	
	CarDealer dealer = { 3.3, {car1, car2, car3} };
	
	// Print their fields.
	printJson(car1);
	printJson(dealer);
    // PrintMembers(car);
    // PrintMembers(chevy);
    // PrintMembers(dealer);
	
    std::cout << std::endl << "Successful completion!" << std::endl;
	return EXIT_SUCCESS;
}






