/**
 * @author: walther
 * @date: Sept 2018
 */

#include <string>
#include <iostream>

#include "Car.hpp"
#include "CarDealer.hpp"
#include "PrinterIterator.hpp"

// Define a specialized version of printJson for characters.
void printJson(char & charObj) {
	// Check to ensure character is printable.
	if ((static_cast<uint8_t>(charObj) >= 32) && (static_cast<uint8_t>(charObj) <= 126)) {
		std::cout << charObj;
	} else {
		std::cout << " ";		
	}
}

// Main entry point to the program.
int main()
{
    // Instantiate the classes.
	Car car1 = {250, 3.5, "car1"};
	Car car2 = {260, 3.6, "car1"};
	Car car3 = {275, 3.75, "car1"};
    Chevy chevy = { 315, 4.2, "Tahoe", 2005, Platform::CAR };	
	CarDealer dealer = { 3.3, {car1, car2, car3} };
	
	// Print their fields.
	printJson(car1);
	std::cout << std::endl;
	printJson(chevy);
	std::cout << std::endl;
	printJson(dealer);
	
    std::cout << std::endl << "Successful completion!" << std::endl;
	return EXIT_SUCCESS;
}






