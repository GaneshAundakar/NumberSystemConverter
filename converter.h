
#ifndef CONVERTER_H
#define CONVERTER_H

#define MAX_STR_LEN 256

#define COLOR_RESET   "\033[0m"
#define COLOR_TITLE   "\033[1;36m" 
#define COLOR_MENU    "\033[36m"   
#define COLOR_ERROR   "\033[1;31m" 
#define COLOR_RESULT  "\033[1;32m" 
#define COLOR_MATH    "\033[33m"   
#define COLOR_STEP    "\033[1;33m" 
#define COLOR_PROMPT  "\033[1;35m" 

void displayMenu(void); // Displays the structural selection menu to the standard output.

int validateInput(const char toCheck[], int base); // Validates if the given string represents a valid entry for the target base.

double toDecimal(const char value[], int base); // Converts a validated string value (integer + fractional) from any base to a base-10 baseline value.

void fromDecimal(double decimal, int base, char result[]); // Generates the target base representation string from a decimal baseline value.

void explainSteps(const char input[], int fromBase, int toBase, double interDecimal, const char output[]); // Prints out the step-by-step mathematical breakdown of how the conversion occurred.

#endif
 
