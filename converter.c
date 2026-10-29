
#include "converter.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void displayMenu(void) 
{
    printf("%s============================================================%s\n", COLOR_TITLE, COLOR_RESET);
    printf("%s     ADVANCED NUMBER SYSTEM CONVERTER (WITH DERIVATION) %s\n", COLOR_PROMPT, COLOR_RESET);
    printf("%s============================================================%s\n", COLOR_TITLE, COLOR_RESET);

    printf("%s 1. Decimal to Binary       2. Decimal to Octal\n", COLOR_MENU);
    printf(" 3. Decimal to Hexadecimal  4. Binary to Decimal\n");
    printf(" 5. Binary to Octal         6. Binary to Hexadecimal\n");
    printf(" 7. Octal to Decimal        8. Octal to Binary\n");
    printf(" 9. Octal to Hexadecimal   10. Hexadecimal to Decimal\n");
    printf("11. Hexadecimal to Binary  12. Hexadecimal to Octal\n");
    printf("13. Exit Program%s\n", COLOR_RESET);
    printf("%s===================================================%s\n", COLOR_TITLE, COLOR_RESET);
}

int validateInput(const char toCheck[], int base) 
{
    int len = strlen(toCheck);

    if (len == 0) return 0;
    int dotCount = 0;

    for (int i = 0; i < len; i++) 
    {
        if (toCheck[i] == '.') 
        {
            dotCount++;
        
            if (dotCount > 1) return 0;
            continue;
        }
        
        char c = toupper((unsigned char)toCheck[i]);
        
        if (base == 2 && (c != '0' && c != '1')) return 0;
        
        if (base == 8 && (c < '0' || c > '7')) return 0;
        
        if (base == 10 && (c < '0' || c > '9')) return 0;
        
        if (base == 16 && !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) return 0;
    }
    return 1;
}

double toDecimal(const char value[], int base) 
{
    char temp[MAX_STR_LEN];
    strncpy(temp, value, MAX_STR_LEN);
    char *dot = strchr(temp, '.');
    char *intPart = temp;
    char *fracPart = NULL;

    if (dot != NULL) 
    {
        *dot = '\0';
        fracPart = dot + 1;
    }
    
    double decimalValue = 0.0;
    
    int intLen = strlen(intPart);
    
    for (int i = 0; i < intLen; i++) 
    {
        char c = toupper((unsigned char)intPart[intLen - 1 - i]);
    
        int digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
    
        decimalValue += digit * pow(base, i);
    }
    
    if (fracPart != NULL && strlen(fracPart) > 0) 
    {
        int fracLen = strlen(fracPart);
    
        for (int i = 0; i < fracLen; i++) 
        {
            char c = toupper((unsigned char)fracPart[i]);
        
            int digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
        
            decimalValue += digit * pow(base, -(i + 1));
        }
    }
    return decimalValue;
}

void fromDecimal(double decimal, int base, char result[]) 
{
    double intPart;

    double fracPart = modf(decimal, &intPart);

    long long integerVal = (long long)intPart;

    char intStr[MAX_STR_LEN] = "";

    int idx = 0;
    if (integerVal == 0) 
    {
        strcpy(intStr, "0");
    }
    else 
    {
        char temp[MAX_STR_LEN];
    
        while (integerVal > 0) 
        {
            int rem = integerVal % base;
            temp[idx++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
            integerVal /= base;
        }
        
        temp[idx] = '\0';
        int tLen = strlen(temp);
        
        for (int i = 0; i < tLen; i++) 
        {
            intStr[i] = temp[tLen - 1 - i];
        }
        intStr[tLen] = '\0';
    }

    char fracStr[MAX_STR_LEN] = "";
    
    if (fracPart > 0.0) 
    {
        int fIdx = 0;
        fracStr[fIdx++] = '.';
        int maxPrecision = 6; 
    
        while (fracPart > 0.0 && maxPrecision-- > 0) 
        {
            fracPart *= base;
            double digitInt;
            fracPart = modf(fracPart, &digitInt);
            int d = (int)digitInt;
            fracStr[fIdx++] = (d < 10) ? (d + '0') : (d - 10 + 'A');
        }
        fracStr[fIdx] = '\0';
    }
    sprintf(result, "%s%s", intStr, fracStr);
}

void getBaseName(int base, char name[]) 
{
    switch(base) 
    {
        case 2:  strcpy(name, "BINARY");      break;
    
        case 8:  strcpy(name, "OCTAL");       break;
    
        case 10: strcpy(name, "DECIMAL");     break;
    
        case 16: strcpy(name, "HEXADECIMAL"); break;
    
        default: strcpy(name, "UNKNOWN");     break;
    }
}

void explainSteps(const char input[], int fromBase, int toBase, double interDecimal, const char output[]) 
{
    char fromName[30], toName[30];
    getBaseName(fromBase, fromName);
    getBaseName(toBase, toName);

    printf("\n\033[1;42;30m >>> CURRENT ACTIVE OPERATION: %s TO %s <<< %s\n", fromName, toName, COLOR_RESET);
    printf("%s--- MATH DERIVATION BREAKDOWN ---%s\n", COLOR_TITLE, COLOR_RESET);
    
    if (fromBase != 10) 
    {
        printf("%s[Step 1] Processing Input via %s Expansion Rule (Base %d -> Base 10):%s\n", COLOR_STEP, fromName, fromBase, COLOR_RESET);
    
        printf("%s", COLOR_MATH);
    
        char temp[MAX_STR_LEN];
        strncpy(temp, input, MAX_STR_LEN);
    
        char *dot = strchr(temp, '.');
        int intLen = dot ? (int)(dot - temp) : (int)strlen(temp);
        
        for (int i = 0; i < intLen; i++) 
        {
            char c = toupper((unsigned char)temp[i]);
            printf("  ('%c' * %d^%d)", c, fromBase, intLen - 1 - i);
            if (i < intLen - 1 || dot != NULL) printf(" + ");
        }
        
        if (dot != NULL) 
        {
            char *frac = dot + 1;
            int fracLen = strlen(frac);
        
            for (int i = 0; i < fracLen; i++) 
            {
                printf("  ('%c' * %d^-%d)", frac[i], fromBase, i + 1);
                if (i < fracLen - 1) printf(" + ");
            }
        }

        printf("\n  = %f in Base 10\n\n%s", interDecimal, COLOR_RESET);
    } 
    else
    {
        printf("%s[Step 1] Input is already starting in Baseline Base 10: %f%s\n\n", COLOR_STEP, interDecimal, COLOR_RESET);
    }
    
    if (toBase != 10) 
    {
        printf("%s[Step 2] Processing Intermediate Value via %s Radix Rules (Base 10 -> Base %d):%s\n", COLOR_STEP, toName, toBase, COLOR_RESET);
        printf("%s", COLOR_MATH);
    
        double intPart;
        double fracPart = modf(interDecimal, &intPart);
        long long integerVal = (long long)intPart;
        
        printf("  - Successive Division of Integer space (%lld):\n", integerVal);
    
        while (integerVal > 0) 
        {
            printf("    %lld / %d = %lld with Remainder: %d\n", integerVal, toBase, integerVal / toBase, (int)(integerVal % toBase));
            integerVal /= toBase;
        }
        
        if (fracPart > 0.0) 
        {
            printf("  - Successive Multiplication of Fractional space (%f):\n", fracPart);
            int maxP = 4;
        
            while (fracPart > 0.0 && maxP-- > 0) 
            {
                double nextVal = fracPart * toBase;
                double outInt;
                modf(nextVal, &outInt);
            
                printf("    %f * %d = %f (Extracted Integer: %d)\n", fracPart, toBase, nextVal, (int)outInt);
                fracPart = modf(nextVal, &outInt);
            }
        }
        printf("%s", COLOR_RESET);
    }

    printf("\n%s>>> Final Output: (%s) in %s Base = (%s) in %s Base%s\n", COLOR_RESULT, input, fromName, output, toName, COLOR_RESET);
    printf("%s---------------------------------%s\n\n", COLOR_TITLE, COLOR_RESET);
}

