// git pull origin master
// git add .
// git commit -m "Added main menu"
// git push origin master

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>

void user_login();
void admin_login();
void user_banking();
void view_previous_transactions();
void sorting();


int generateAccountNumber()
{
    static int counter = 100000; // Start with 100000 as the initial account number
    return counter++;
}



bool exit_option(const char* input) {
    return strcmp(input, "exit") == 0;
}



void archive_customer(const char *filename)
{
    // search name of file
    // snprintf to concatinate any username to the file path so long as it exists
     if (remove(filename) == 0)
        printf("Client Successfully Archived\n");
    else
        printf("Unable to archive customer");
}



int add_customer()
{
    char first[20], last[20], usern[20], pass[20], dob[20]; // shortened to initialize on one line
    float deposit, limit;
    int temp = generateAccountNumber(), acctnum = temp + first[0] + last[0];

    printf("Welcome to Customer Registration\n(Type 'exit' at anytime to cancel) Customer First Name: "); // merged successive print statements
    scanf("%s", first);
        if(exit_option(first)){puts("Cancelled. Now exiting...\n"); return 0;}

    printf("Customer Last Name: ");
    scanf("%s", last);
        if(exit_option(last)){puts("Cancelled. Now exiting...\n"); return 0;}

    printf("Date of Birth (MM/DD/YY): ");
    scanf("%s", dob);
        if(exit_option(dob)){puts("Cancelled. Now exiting...\n"); return 0;}

    printf("Customer Username: ");
    scanf("%s", usern);
        if(exit_option(usern)){puts("Cancelled. Now exiting...\n"); return 0;}

    printf("Customer Password: ");
    scanf("%s", pass);
        if(exit_option(pass)){puts("Cancelled. Now exiting...\n"); return 0;}

    printf("Initial Deposit: ");
    scanf("%f", &deposit);
    limit = deposit * 1.3;

    // checking for exisiting customer
    char check_path[200];
    snprintf(check_path, sizeof(check_path), "Customers/%s%s.txt", first, last);
    FILE *errorcheck = fopen(check_path, "r");

    if (errorcheck != NULL)
    {
        printf("%s %s is already a member. Please navigate to the Customer View Page", first, last);
        return 0;
    } // if it doesn't return null(or that there is no file), that means the customer exists

    // CREATING USER FILE
    char file_path[200];
    snprintf(file_path, sizeof(file_path), "Customers/%s%s.txt", first, last);
    FILE *fpointer = fopen(file_path, "w"); // opening file (use a to append just in case of overwrite)

    // writing info in their file
    fprintf(fpointer, "First Name: %s\nLast Name: %s\nDate of Birth: %s\n\nUsername: %s\nPassword: %s\n\nAccount Number: %06d\n\nBalance: $%.2f\n\nTransaction History:\nInitial depostit $%.2f, new balance: $%.2f ", first, last, dob, usern, pass, acctnum, deposit, deposit, deposit);
    fclose(fpointer);

    // Adding the username and passwords to login
    char append_path[200]; // I really don't understand why adding snprintf worked, but it did
    snprintf(append_path, sizeof(append_path), "Customers/clogins.txt");

    FILE *add_to_login = fopen("Customers/clogins.txt", "a");
    if (add_to_login == NULL)
    { // errorchecking
        printf("Error opening file logins.txt.\n");
        return 1;
    }

    fprintf(add_to_login, "\n%s %s", usern, pass);
    fclose(add_to_login); // add and close

    // add to summary file
    char append_path_summary[200]; // I really don't understand why adding snprintf worked, but it did
    snprintf(append_path_summary, sizeof(append_path_summary), "Customers/summary.txt");

    FILE *add_to_sum = fopen("Customers/summary.txt", "a");
    if (add_to_sum == NULL)
    { // errorchecking
        printf("Error opening file summary.txt.\n");
        return 1;
    }

    fprintf(add_to_sum, "\n%s %s %d\n", first, last, acctnum);
    fclose(add_to_sum);
    printf("\n%s %s has been added to database\n Going back to admin page...\n", first, last);
    return 0;
}



int view_customers()
{
    char customer[20], exitkey[5] = "exit"; // Customer search
    printf("Please enter Customer's first and last name with NO space between\n(type 'exit' to return to admin page): ");
    scanf("%s", customer);
    if (strcmp("exit", customer) == 0)
    {
        puts("returning to admin page\n");
        return 0;
    }

    // search for file
    // snprintf to concatinate any username to the file path so long as it exists
    char file_path[200];
    snprintf(file_path, sizeof(file_path), "Customers/%s.txt", customer);

    // open the file
    FILE *fpointer = fopen(file_path, "r");

    // check if exists
    if (fpointer == NULL) {
        printf("Customer does not exist. Please check your spelling and try again.\n");
    }

    // output user info
    char data[100];
    while (fgets(data, 100, fpointer)) {
        printf("%s", data);
    }

    fclose(fpointer); // close the file

    // admin action choices
    int action;
    do {
        printf("\nActions:  1. Edit Client Information  2. Archive Client  3. Back\n"); // ask admin what they want to do with the user
        scanf("%d", &action);

        int arc; // for archive warning
        switch (action) {
        case 1:
            puts("Editing Client");
            break;
        case 2: // if they archive, make them verify; do while to prevent infinite loop
            do {
                puts("Are you sure you want to archive this customer? 1. Yes  2. No");
                scanf("%1d", &arc);
                if (arc == 1) {
                    archive_customer(file_path);
                     break;
                } else if (arc == 2) {
                    break;
                } else {
                    printf("Invalid input, please try again.\n");
                }
            } while (arc != 1 && arc != 2);
        case 3:
            return 0;
            break;
        default:
            puts("Invalid Input");
            break;
        }
    } while (action != 3);

    return 1;
} // end of view customer



void view_previous_transactions(char filename[200]){
    char filepath[200], line[100];
    snprintf(filepath, sizeof(filepath), "Customers/%s", filename);    // Use snprintf to concatenate the parameter to the file name
    FILE *file = fopen(filepath, "r");

     if (file == NULL) {
        puts("Error opening file");
        return;
    }

    bool transactionFound = false, notFound = true;

    puts("Hello! Thank you for continually banking with us\n");

    while (fgets(line, sizeof(line), file) != NULL) { 
         if (transactionFound) {
              if (strcmp(line, "\n") != 0) {
                notFound = false; //assume its empty at first so notFound = true and if it isnt, then it is found
            }
            fputs(line, stdout);
        } else if (strstr(line, "Transaction History:") != NULL) {
            transactionFound = true;
        }  
    }

    if (notFound) {
        puts("At this time, you have no previous transactions with us.");
    }

    puts("\nThank you for banking with us. Have a great day!");
    fclose(file);
    exit(0);
}



typedef struct { //structure for customers for sorting function
    char firstName[20];
    char lastName[20];
    char account[20];
} Customer;



int compareByFirstName(const void *a, const void *b) { // cast pointers to customer structs and use strcmp to compare first names
    return strcmp(((Customer *)a)->firstName, ((Customer *)b)->firstName);
}



int compareByAccount(const void *a, const void *b) { // cast pointers to customer structs and use strcmp to compare account numbers
    return strcmp(((Customer *)a)->account, ((Customer *)b)->account);
}



void sorting() { //function to sort customer info depending on sorting preference
    FILE *file = fopen("Customers/summary.txt", "r"); //open file
    if (file == NULL) {
        //check for error
        perror("Error opening file");
        return;
    }

    // allocate memory for customers
    Customer *customers;
    int numCustomers = 0;

    char line[100];

    // count the number of customers in the file
    while (fgets(line, sizeof(line), file) != NULL) {
        numCustomers++;
    }

    // allocate memory for customers
    customers = malloc(numCustomers * sizeof(Customer));
    if (customers == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return;
    }

    // rewind the file to read customers
    rewind(file);

    // read customers from the file and store in memory
    for (int i = 0; i < numCustomers; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%s %s %s", customers[i].firstName, customers[i].lastName, customers[i].account);
        }
    }

    // get user's choice of sorting
    int sortBy;
    puts("Please enter an integer value to represent your filtered sorting.\n1. Sort by First Name  2. Sort by Account Number");
    scanf("%d", &sortBy);

    // sort customers
    if (sortBy == 1) { //prints out "sort by first name"
        qsort(customers, numCustomers, sizeof(Customer), compareByFirstName);
        //formatting
        printf("%-20s %-20s %-20s\n", "First Name", "Last Name", "Account Number");
        printf("-------------------------------------------------------------\n");
        for (int i = 0; i < numCustomers; i++) {
            printf("%-20s %-20s %-20s\n", customers[i].firstName, customers[i].lastName, customers[i].account);
        } printf("\n");

    } else if (sortBy == 2) { //prints out "sort by account number"
        qsort(customers, numCustomers, sizeof(Customer), compareByAccount);
        //formatting
        printf("%-20s %-20s %-20s\n", "First Name", "Last Name", "Account Number");
        printf("-------------------------------------------------------------\n");
        for (int i = 0; i < numCustomers; i++) {
            printf("%-20s %-20s %-20s\n", customers[i].firstName, customers[i].lastName, customers[i].account);
        } printf("\n");
    } else {
        printf("Invalid sort option\n"); //check if option typed is invalid
        free(customers);
        fclose(file);
        return;
    }
    // close file
    fclose(file);
}



void user_banking(char filename[200]) {
    char filepath[200], line[256];
    snprintf(filepath, sizeof(filepath), "Customers/%s", filename);    // Use snprintf to concatenate the parameter to the file name
    FILE *file = fopen(filepath, "r");
    FILE *temp = fopen("Temp_folder/withdrawal_balance.txt", "w");

    if (file == NULL || temp == NULL)
    {
        puts("Error opening file");
        return;
    }
    float balance = 0;
    float amount;
    bool balanceUpdated = false;
    int banking_choice;

    puts("Welcome to the Banking Portal");
    printf("Please enter an integer value to represent your choice. 1. Withdraw  2. Deposit  3. Exit\n");
    scanf("%d", &banking_choice);
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Balance:") != NULL) {         // Check if the line contains "Balance:"
            if (sscanf(line, "Balance: $%f", &balance) == 1) { //found the balance value
                bool validchoice = false;
                while (!validchoice) {
                    if (banking_choice == 1) {
                        printf("Enter the amount you would like to withdraw: ");
                        scanf("%f", &amount);
                        if (amount > balance) {
                            printf("Insufficient balance. Your current balance is %.2f\n", balance);
                            exit(0);
                        } else {
                            balance -= amount;
                            printf("Withdrawn %.2f. Your new balance is %.2f\n", amount, balance);
                            balanceUpdated = true;
                            fprintf(temp, "Balance: $%.2f\n", balance);
                        }
                        validchoice = true;
                    } else if (banking_choice == 2) {
                        printf("Enter the amount you would like to deposit: ");
                        scanf("%f", &amount);
                        balance += amount;
                        printf("Deposited %.2f. Your new balance is %.2f\n", amount, balance);
                        balanceUpdated = true;
                        fprintf(temp, "Balance: $%.2f\n", balance);
                        validchoice = true; 
                    } else if (banking_choice == 3) {
                        puts("You have been logged out");
                        exit(0);
                    } else {
                        while (banking_choice != 1 && banking_choice != 2 && banking_choice != 3){
                            puts("Invalid input, try again");
                            scanf("%d", &banking_choice);
                        }   
                    }  
                }
            }
        } else {
            fputs(line, temp);
        }
    }
    if (balanceUpdated && banking_choice == 1){
        fprintf(temp, "Withdrew %.2f, new balance is %.2f\n", amount, balance);
    } else if(balanceUpdated && banking_choice == 2){
        fprintf(temp, "Deposited %.2f, new balance is %.2f\n", amount, balance);
    }

    fclose(temp);

    if (balanceUpdated) {
        // Copy the temp file to the original file
        file = fopen(filepath, "w");
        temp = fopen("Temp_folder/withdrawal_balance.txt", "r");

        // Copy the content of the temporary file to the original file
        while (fgets(line, sizeof(line), temp) != NULL) {
            fputs(line, file);
        }

        fclose(file);
        fclose(temp);
    }
    puts("End of transaction! have a great day");
    return 0;
}



void admin_login() {
    char password[20], username[20], fileUsername[20], filePassword[20];
    bool found = false;
    FILE *file = fopen("admins/alogins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }  

    puts("Welcome to the Admin portal. Please sign in: ");

    while (!found){
        printf("Username: ");
        scanf("%s", username);
        if (strcmp(username, "exit") != 0) {
            printf("Password: ");
            scanf("%s", password);
        }
        if (strcmp(username, "exit") == 0) {
            puts("You have been exited from the bank");
            exit(0);
        }
        if (strstr(username, "-adm") == NULL) {
            puts("Error. You cannot sign into the admin portal with a user login information. Please try again or type 'exit' to exit");
        }
    

        // Read each line from the file and compare the login info
        while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                    puts("Admin Login Successful");
                    found = true;
                    break;
            }
        }
    

        if (!found && strstr(username, "-adm") != NULL) {
            puts("Invalid login. Please try again or type 'exit' to exit");
            fseek(file, 0, SEEK_SET); //return the file pointer to the beginning of the file
        } 
    }

    if (found) {
        int choice;
            puts("Please choose what you want to do today. Please enter an integer value to represent your choice.\n\n1. View Customer Info  2. Add Customers  3. Sort  4. Logout");
        do {
            if (scanf("%d", &choice) == 1) {
            // Process the choice
                if (choice == 1) {
                    view_customers();
                    break;
                } else if (choice == 2) {
                    add_customer();
                    break;
                } else if (choice == 3) {
                    sorting();
                    break;
                } else if (choice == 4) {
                    puts("You have been logged out\n\n");
                    return;
                } else {
                puts("Invalid input, try again");
                }
            } else {
            // Clear the input buffer
            int c;
            puts("Invalid input, try again");
            while ((c = getchar()) != '\n' && c != EOF);
            }
        } while (1);
    }
    fclose(file);
}



// Function to search for a username in a customer file
char* searchForUsername(char folderPath[], char username[]) {
    DIR *dir;
    struct dirent *ent;
    char *foundFilename = NULL;

    if ((dir = opendir(folderPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            char filePath[100];
            snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, ent->d_name);
            FILE *file = fopen(filePath, "r");
            if (file != NULL) {
                char line[100];
                int lineCount = 0;
                // Read each line in the file
                while (fgets(line, sizeof(line), file) != NULL) {
                    lineCount++;
                    // Check if the line contains "Username:" followed by the target username
                    if (lineCount == 4 && strstr(line, "Username:") != NULL && strstr(line, username) != NULL) {
                        fclose(file);
                        closedir(dir);
                        // Allocate memory for the filename
                        foundFilename = malloc(strlen(ent->d_name) + 1);
                        strcpy(foundFilename, ent->d_name);

                        return foundFilename;
                    }
                }
                fclose(file);
            }
        }
        closedir(dir);
    } else {
        puts("Error opening directory");
    }
    return foundFilename;
}



//invalid login option
void user_login() {
    char password[20], username[20], fileUsername[20], filePassword[20], *foundFilename;
    bool found = false;

    FILE *file = fopen("Customers/clogins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }

    puts("Welcome to the User portal. Please sign in");

    while (!found){
        printf("Username: ");
        scanf("%s", username);
        if (strcmp(username, "exit") != 0) {
            printf("Password: ");
            scanf("%s", password);
        }
        if (strcmp(username, "exit") == 0) {
            puts("You have been exited from the bank");
            exit(0);
        }
        if (strstr(username, "-adm") != NULL) {
            puts("Error. You cannot sign into the user portal with an admin login information. Please try again or type 'exit' to exit");
        }

           // Read each line from the file and compare the login info
        while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                puts("User Login Successful");
                found = true;
                break;
            }
        }

        if (!found && strstr(username, "-adm") == NULL) {
            puts("Invalid login. Please try again or type 'exit' to exit");
            fseek(file, 0, SEEK_SET); ///return the file pointer to the beginning of the file

        }
    }
  
    if (found){
        int choice; // User selection
        foundFilename = searchForUsername("Customers", username);

        if (foundFilename != NULL) {
        puts("Welcome! Please enter an integer value to represent your input.\n1. Withdraw/Deposit  2. View previous transactions  3. Logout");
        // printf("Found username in file: %s\n", foundFilename); // Debugging
          do {
            if (scanf("%d", &choice) == 1) {
            // Process the choice
                if (choice == 1) {
                    user_banking(foundFilename);
                    break;
                } else if (choice == 2) {
                    view_previous_transactions(foundFilename);
                    break;
                } else if (choice == 3) {
                   puts("You have been logged out");
                exit(0);
                } else {
                puts("Invalid input, try again");
                }
            } else {
            // Clear the input buffer
            int c;
            puts("Invalid input, try again");
            while ((c = getchar()) != '\n' && c != EOF);
            }
        } while (1);

        } else {
        printf("At this time, we do not have the details of your account\n");
        puts("Please contact our customer service for further assistance");
        exit(0);
        }
    }
    fclose(file);
}



int main(void) { //,main menu
    int choice;   

   do {
    puts("Welcome to MSM Bank (Please enter an integer value to represent your choice)\n1.User Portal  2.Admin Portal  3.Exit");
        if (scanf("%d", &choice) == 1) {
            // Process the choice
            if (choice == 1) {
                user_login();
            } else if (choice == 2) {
                admin_login();
            } else if (choice == 3) {
                puts("Thank you for banking with us. Have a great day!");
                return 0;
            } else {
                puts("Invalid input, try again");
            }
        } else {
            // Clear the input buffer
            int c;
            puts("Invalid input, try again");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (1);

    return 0;
}