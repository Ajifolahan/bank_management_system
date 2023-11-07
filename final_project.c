/**
 * Implementation Expectations:
●	Make use of functions to modularize the code. Each feature can be implemented as a function(s).
●	For sorting and statistics, consider creating arrays or lists in-memory and performing operations on them.
●	Make sure to handle invalid inputs gracefully. For example, if a user enters a string when a number was expected, prompt them to enter the correct data type.
●	Add proper error handling, especially during file operations.
●	The interface should be clear and easy to use. All roles should have clear submenus for their respective operations.
●	The code should be well-organized and well-commented.
●	Ensure the system provides informative prompts and instructions.
●	You can optionally use a version control system such as github to organize all your code.

Topic 2: Bank Management System
Objective: Develop a console-based Bank Management System in C that facilitates users to log in and manage their accounts (withdrawal/deposit) and provides an admin interface to oversee and manage customer details.
Specifications:

●	Roles:
○	User (Customer): Log in using a unique ID and password to access personal bank account for transactions like withdrawal and deposit.
○	Admin: Log in using a separate admin ID/password to manage customer information, add or remove customers.
●	File I/O:
○	Two or more files for storage Viz. one to store user IDs and passwords and other to store account information (customer name, customer ID, balance, etc.).
○	Read and update data in these files as needed.
●	Bank Admin Features:
○	Login, View Customer Info, Add Customers, Remove Customers, Sort.
●	User / Customer Features:
○	Login, Withdraw, Deposit, Transactions.

Design a clear and concise main menu to navigate between Users and Admin.

*/

#include <stdio.h>

int main(void){
    int choice;
    puts("Welcome to the Bank Management System. Please select from the following options:\n");
    puts("Please enter an integer value to represent your choice:\n");
    puts("1. User\n");
    puts("2. Admin\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            puts("User");
            break;
        case 2:
            puts("Admin");
            break;
        default:
            puts("Invalid choice");
            break;
    }
}