
#include <stdio.h>
#include <string.h>
#include "converter.h"

int main(void) 
{
    int choice;
    char input[MAX_STR_LEN];
    char output[MAX_STR_LEN];
    double decimalValue;

    do
    {
        displayMenu();
        
        printf("%sEnter your choice (1-13): %s", COLOR_PROMPT, COLOR_RESET);
        
        if (scanf("%d", &choice) != 1) 
        {
            printf("\n%s[Error] Invalid selection input. Exiting.%s\n", COLOR_ERROR, COLOR_RESET);
            break;
        }
        getchar(); 

        if (choice >= 1 && choice <= 12) 
        {
            printf("%sEnter the number to convert: %s", COLOR_PROMPT, COLOR_RESET);
        
            if (fgets(input, sizeof(input), stdin) != NULL) 
            {
                input[strcspn(input, "\n")] = '\0';
            }

            int fromBase = 10, toBase = 10;
            
            switch (choice) 
            {
                case 1:  fromBase = 10; toBase = 2;  break;
                case 2:  fromBase = 10; toBase = 8;  break;
                case 3:  fromBase = 10; toBase = 16; break;
                case 4:  fromBase = 2;  toBase = 10; break;
                case 5:  fromBase = 2;  toBase = 8;  break;
                case 6:  fromBase = 2;  toBase = 16; break;
                case 7:  fromBase = 8;  toBase = 10; break;
                case 8:  fromBase = 8;  toBase = 2;  break;
                case 9:  fromBase = 8;  toBase = 16; break;
                case 10: fromBase = 16; toBase = 10; break;
                case 11: fromBase = 16; toBase = 2;  break;
                case 12: fromBase = 16; toBase = 8;  break;
                default: break;
            }

            if (!validateInput(input, fromBase)) 
            {
                printf("\n%s>>> [Error] Invalid characters for Base-%d! Try again.%s\n\n", COLOR_ERROR, fromBase, COLOR_RESET);
                continue;
            }

            decimalValue = toDecimal(input, fromBase);
            
            fromDecimal(decimalValue, toBase, output);
            
            explainSteps(input, fromBase, toBase, decimalValue, output);
            
        }
        else if(choice != 13) 
        {
            printf("\n%s[Error] Invalid choice! Please select between 1 and 13.%s\n\n", COLOR_ERROR, COLOR_RESET);
        }
    } while (choice != 13);

    printf("\n%sThank you for using the Advanced Number System Converter. Goodbye!%s\n\n", COLOR_TITLE, COLOR_RESET);
    return 0;
}


