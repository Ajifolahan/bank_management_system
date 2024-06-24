// git pull origin master
// git add .
// git commit -m "Added main menu"
// git push origin master

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <uuid/uuid.h>
#include <microhttpd.h>
#include <openssl/rand.h>

void generateAccountNumber(char *account_number);

typedef struct Customer { //  Customer Structure
    char  username[8], password[12], firstName[20], lastName[20], account[13], dateOfBirth[8];
} Customer;

Customer add_customer()
{

    Customer* newUser = (Customer*)malloc(sizeof(Customer));  //Initialize a new user and check if allocation was successful
    if(newUser == NULL)
    {
        fprintf(stderr,"Memory allocation failed\n");
        exit(1);
    }
    
    generateAccountNumber(newUser->account);  // Generate unique account number
    return *newUser;

}

int calculate_check_digit(const char *number) {
    
    // Luhn's Algorithm, copied from chatgpt
    int sum = 0;
    int nDigits = strlen(number);
    int parity = (nDigits - 1) % 2;

    for (int i = 0; i < nDigits; i++) {
        int digit = number[i] - '0';
        if (i % 2 == parity) {
            digit *= 2;
        }
        if (digit > 9) {
            digit -= 9;
        }
        sum += digit;
    }
    return (10 - (sum % 10)) % 10;
}

void generateAccountNumber(char *account_number)
{
    // UUID - UNIVERSAL UNIQUE IDENTIFIER
    unsigned char rand_bytes[16];
    char uuid_str[37];  // Array to store act num string
    
    if (RAND_bytes(rand_bytes, sizeof(rand_bytes)) != 1) {  // Generate random bytes
        fprintf(stderr, "RAND_bytes failed\n");
        exit(1);
    }
    for (int i = 0; i < 16; i++) {
        snprintf(&uuid_str[i * 2], 3, "%02x", rand_bytes[i]);   // Converting to hexidecimal
    }

    char digits[13] = {0};  // + 1 for null terminator
    int i = 0, j = 0;

    for (i = 0; i<36 && j<12; i++)
    {
        if (uuid_str[i] >= '0' && uuid_str[i] <= '9')
        {
            digits[j++] = uuid_str[i];
        }
    }
    int check_digit = calculate_check_digit(digits);
    snprintf(account_number, sizeof(account_number), "%s%d", digits, check_digit);

}

int main(void) { // Main
    
    char account_number[14];  // 12 digits + 1 check digit + 1 for null terminator
    generateAccountNumber(account_number);
    printf("Generated Account Number: %s\n", account_number);
    return 0;
}