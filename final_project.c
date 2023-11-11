//git pull origin master
//git add .
//git commit -m "Added main menu"
//git push origin master

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <dirent.h>
//#include <conio.h>
//#include <windows.h>

void user_login();
void admin_login();

int archive_customer(const char* filename){
    // search name of file 
    //snprintf to concatinate any username to the file path so long as it exists
    char newFile_path[200];
    snprintf(newFile_path, sizeof(newFile_path), "C:/Users/misti/OneDrive/Desktop/Final Project/bank_management_system/customers/archived customers/arc%s.txt", newFile_path);

    int result = rename(filename, newFile_path);
    result == 0 ? printf("Client successfully archived\n") : printf("Error archiving the client.\n");

    return 0;

     }

int add_customer(){
    char first[20], last[20], usern[20], pass[20]; // shortened to initialize on one line
    float deposit;
    printf("Customer Registration\nCustomer First Name: "); // merged successive print statements
    scanf("%s", first);
    printf("Customer Last Name: ");
    scanf("%s", last);
    printf("Customer Username: ");
    scanf("%s", usern);
    printf("Customer Password: ");
    scanf("%s", pass);
    printf("Initial Deposit: ");
    scanf("%f", &deposit);
        

    //checking for exisiting customer
    char check_path[200];
    snprintf(check_path, sizeof(check_path), "Customers/%s%s.txt", first, last);
    FILE * errorcheck = fopen(check_path, "r");

    if(errorcheck != NULL){printf("%s %s is already a member. Please navigate to the Customer View Page", first, last);
    return 0;} // if it doesn't return null(or that there is no file), that means the customer exists

    
    //CREATING USER FILE
        char file_path[200];        
        snprintf(file_path, sizeof(file_path), "Customers/%s%s.txt", first, last);
        FILE * fpointer = fopen(file_path, "w"); //opening file (use a to append just in case of overwrite)

        //writing info in their file
        fprintf(fpointer, "First Name: %s\nLast Name: %s\n\nUsername: %s\nPassword: %s\n\nBalance: $%.2f\n\nTransaction History: ", first, last, usern, pass, deposit);
        fclose(fpointer);


        // Adding the username and passwords to login
        char append_path[200]; // I really don't understand why adding snprintf worked, but it did
        snprintf(append_path, sizeof(append_path), "Customers/logins.txt");

        FILE * add_to_login = fopen("Customers/logins.txt", "a");
        if (add_to_login == NULL) { // errorchecking
        printf("Error opening file logins.txt.\n");
        return 1;}

        fprintf(add_to_login, "\n%s %s", usern, pass);
        fclose(add_to_login); // add and close

        return 0;
    }

int view_customers(){
    char customer[20], exitkey[5] = "exit";  // Customer search
    printf("Please enter Customer's first and last name with NO space between\n(type 'exit' to return to admin page): ");
    scanf("%s", customer);
    if(strcmp("exit", customer) == 0){
        puts("returning to admin page\n");
        return 0;}

    // search for file 
    //snprintf to concatinate any username to the file path so long as it exists
    char file_path[200];        
    snprintf(file_path, sizeof(file_path), "Customers/%s.txt", customer);
 
    // open the file
    FILE * fpointer = fopen(file_path, "r");  

    // check if exists
    if(fpointer == NULL){printf("Customer does not exist. Please check your spelling and try again.\n");}

    // output user info
    char data[100];
    while(fgets(data, 100, fpointer)){
    printf("%s", data);}
        
    fclose(fpointer); // close the file


    //admin action choices
    int action;    
    do{ printf("\nActions:  1. Edit Client Information  2. Archive Client  3. Back\n"); // ask admin what they want to do with the user
        scanf("%d", &action);

        int arc; // for archive warning
        switch(action){
        case 1:
            puts("Editing Client");
            break;
        case 2: // if they archive, make them verify; do while to prevent infinite loop
            do{
            puts("Are you sure you want to archive this customer? 1. Yes  2. No");
            scanf("%d", &arc);
            if(arc == 1){archive_customer(file_path);} else if(arc == 2){continue;} else{printf("Invalid input, please try again.\n");}}while(arc != 1 && arc != 2);
        case 3:
            return 0;
            break;
        default:
            puts("Invalid Input");
            break;
        }}while(action != 3);

        return 0;
    }//end of view customer



void admin_login(){
    char password[20], username[20]; // added to one line
    printf("\nWelcome to the Admin portal. Please sign in:\n\nUsername: ");  // merged sussesive print statements
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);

    FILE *file = fopen("Customers/logins.txt", "r");    // added the "Customers/" to specify path
    if (file == NULL) { puts("Error opening file");
    return;}

    char fileUsername[20], filePassword[20];
    bool found = false;

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
             if (strstr(fileUsername, "-adm") != NULL) {
                puts("Admin Login Successful\n");
                found = true;
            } else {
                puts("Error. You cannot sign into the admin portal with a Users login information. Please try again");
            }
            break;
        } else {
            puts("Invalid login.Please enter the correct login information");
        }
    }

    fclose(file);

    if (found){
        int choice; 
        while(1){
        puts("\nPlease choose what you want to do today. Please enter an integer value to represent your choice.\n\n1. View Customer Info  2. Add Customers  3. Sort  4. Logout");
        scanf("%d", &choice); //mereged puts^

            // prompt admin user for action
            switch(choice){   
            case 1:
                view_customers();
                break;
            case 2:
                add_customer();
                break;
            case 3:
                puts("sorting");
                break;
            case 4:
                puts("\n\nYou have been logged out\n\n");
                return;
            default:
                puts("Invalid choice");
                break;
        }}
    }
} 

void user_login(){
    char password[20], username[20]; 
    printf("Welcome to the User portal. Please sign in\nUsername: ");  
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *file = fopen("Customers/logins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }

    char fileUsername[20], filePassword[20];
    bool found = false;

    // Read each line from the file and compare the login info
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            puts("Login Successful");
            found = true;
            break;
        } else {
            puts("Invalid login.Please enter the correct login information");
        }
    }
    fclose(file);


    if(found){
        int choice; //User selection
        puts("Welcome %s Enter an integer value to represent your input.\n1. Withdraw  2. Deposit  3. View previous transactions  4. Logout");
        scanf("%d", &choice);

            switch(choice){
            case 1:
                puts("Withdrawing");
                break;
            case 2:
                puts("Depositing");
                break;
            case 3:
                puts("Viewing previous transactions");
                break;
            case 4:
                puts("You have been logged out");
                return;
            default:
                puts("Invalid choice");
                break;
        }
    }

}

int main(void){
int choice;
while(1)
    {puts("Welcome to MSM Bank (Please enter an integer value to represent your choice)\n1.User Portal  2.Admin Portal  3.Exit");
    scanf("%d", &choice);         // merged^^

    input:if(choice == 1){user_login();} else if(choice == 2){admin_login();} else if(choice == 3){puts("\nHave a great rest of your day!\n"); return(0);}                           
        else{while(choice != 1 || choice != 2 || choice != 3){puts("Invalid input, try again: "); scanf("%d", &choice); goto input;}}} //jump statement to retry input

puts("\nHave a great rest of your day!\n"); //when they exit the program

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
    }*/ // left in case of any bug i come across from the if
}