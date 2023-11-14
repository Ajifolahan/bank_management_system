// git pull origin master
// git add .
// git commit -m "Added main menu"
// git push origin master

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void user_login();
void admin_login();
void user_withdrawing();

int archive_customer(const char *filename)
{
    // search name of file
    // snprintf to concatinate any username to the file path so long as it exists
    char newFile_path[200];
    snprintf(newFile_path, sizeof(newFile_path), "C:/Users/misti/OneDrive/Desktop/Final Project/bank_management_system/customers/archived customers/arc%s.txt", newFile_path);

    int result = rename(filename, newFile_path);
    result == 0 ? printf("Client successfully archived\n") : printf("Error archiving the client.\n");

    return 0;
}

int add_customer()
{
    char first[20], last[20], usern[20], pass[20], dob[20], acctnum[20], limit[20]; // shortened to initialize on one line
    float deposit;
    printf("Customer Registration\nCustomer First Name: "); // merged successive print statements
    scanf("%s", first);
    printf("Customer Last Name: ");
    scanf("%s", last);
    printf("Date of Birth (MM/DD/YY): ");
    scanf("%s", dob);
    printf("Customer Username: ");
    scanf("%s", usern);
    printf("Customer Password: ");
    scanf("%s", pass);
    printf("Initial Deposit: ");
    scanf("%f", &deposit);

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
    fprintf(fpointer, "First Name: %s\nLast Name: %s\n\nUsername: %s\nPassword: %s\n\nBalance: $%.2f\n\nTransaction History: ", first, last, usern, pass, deposit);
    fclose(fpointer);

    // Adding the username and passwords to login
    char append_path[200]; // I really don't understand why adding snprintf worked, but it did
    snprintf(append_path, sizeof(append_path), "Customers/logins.txt");

    FILE *add_to_login = fopen("Customers/logins.txt", "a");
    if (add_to_login == NULL)
    { // errorchecking
        printf("Error opening file logins.txt.\n");
        return 1;
    }

    fprintf(add_to_login, "\n%s %s", usern, pass);
    fclose(add_to_login); // add and close

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
                scanf("%d", &arc);
                if (arc == 1) {
                    archive_customer(file_path);
                } else if (arc == 2) {
                    continue;
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

    return 0;
} // end of view customer

void user_withdrawing(char username[20]) {
    FILE *file = fopen("Customers/customer_info.txt", "r");
    FILE *temp = fopen("Customers/customer_info_temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        puts("Error opening file");
        if (file != NULL)
            fclose(file);
        if (temp != NULL)
            fclose(temp);
        return;
    }

    char fullname[100];
    char fileUsername[20];
    float balance = 0;
    bool found = false;

    while (fscanf(file, "%s %s %f", fullname, fileUsername, &balance) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = true;
            float amount;
            printf("Enter the amount you would like to withdraw: ");
            scanf("%f", &amount);
            if (amount > balance)
            {
                printf("Insufficient balance. Your current balance is %.2f\n", balance);
            }
            else
            {
                balance -= amount;
                printf("Withdrawn %.2f. Your new balance is %.2f\n", amount, balance);
            }
        }
        fprintf(temp, "%s %s %.2f\n", fullname, fileUsername, balance); // Write all lines to temp file
    }

    fclose(file);
    fclose(temp);

    if (!found)
    {
        puts("Your account information has not been added into our database");
    }
    else
    {
        // Copy the temp file to the original file
        file = fopen("Customers/customer_info.txt", "w");
        temp = fopen("Customers/customer_info_temp.txt", "r");

        while (fscanf(temp, "%s %s %f", fullname, fileUsername, &balance) != EOF)
        {
            fprintf(file, "%s %s %.2f\n", fullname, fileUsername, balance);
        }

        fclose(file);
        fclose(temp);
    }
}

void admin_login() {
    char password[20], username[20];   
    FILE *file = fopen("admins/alogins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }  

    puts("Welcome to the Admin portal. Please sign in: ");

     do {
        printf("Username: ");
        scanf("%s", username);
        if (strcmp(username, "exit") == 0) {
            exit(0);
        }
        if (strstr(username, "-adm") == NULL) {
            puts("Error. You cannot sign into the user portal with an admin login information. Please try again or type 'exit' to exit");
        }
    } while (strstr(username, "-adm") == NULL);
    printf("Password: ");
    scanf("%s", password);

    char fileUsername[20], filePassword[20];
    bool found = false;

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                puts("Admin Login Successful");
                found = true;
                break;
        }
    }

    if (!found) {
        puts("Invalid login. You've been exited from the bank");
        exit(0);    
    } else {
        do {int choice;
            puts("Please choose what you want to do today. Please enter an integer value to represent your choice.\n\n1. View Customer Info  2. Add Customers  3. Sort  4. Logout");

        
            if (scanf("%d", &choice) == 1) {
            // Process the choice
                if (choice == 1) {
                    view_customers();
                    break;
                } else if (choice == 2) {
                    add_customer();
                    break;
                } else if (choice == 3) {
                    puts("Sorting");
                    exit(0);
                } else if (choice == 4) {
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
    }
    fclose(file);
}

//invalid login option
void user_login() {
    char password[20], username[20];
    FILE *file = fopen("Customers/clogins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }

    puts("Welcome to the User portal. Please sign in");

    do {
        printf("Username: ");
        scanf("%s", username);
        if (strcmp(username, "exit") == 0) {
            exit(0);
        }
        if (strstr(username, "-adm") != NULL) {
            puts("Error. You cannot sign into the user portal with an admin login information. Please try again or type 'exit' to exit");
        }
    } while (strstr(username, "-adm") != NULL);
    printf("Password: ");
    scanf("%s", password);

    char fileUsername[20], filePassword[20];
    bool found = false;

    // Read each line from the file and compare the login info
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            puts("User Login Successful");
            found = true;
            break;
        }
    }

    if (!found) {
        puts("Invalid login. You've been exited from the bank");
        exit(0);
    } else {
        int choice; // User selection
        puts("Welcome! Please enter an integer value to represent your input.\n1. Withdraw  2. Deposit  3. View previous transactions  4. Logout");
    
        do {
            if (scanf("%d", &choice) == 1) {
            // Process the choice
                if (choice == 1) {
                    user_withdrawing(username);
                    break;
                } else if (choice == 2) {
                    puts("Depositing");
                    exit(0);
                } else if (choice == 3) {
                    puts("Viewing previous transactions");
                    exit(0);
                } else if (choice == 4) {
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
    }
    fclose(file);
}

int main(void) { //,main menu
    int choice;   
    puts("Welcome to MSM Bank (Please enter an integer value to represent your choice)\n1.User Portal  2.Admin Portal  3.Exit");

   do {
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

/* switch(choice){
    case 1:
        user_login();
        break;
    case 2:
        admin_login();
        break;
    default:
        puts("Invalid choice");
        break;
}*/// left in case of any bug i come across from the if statement