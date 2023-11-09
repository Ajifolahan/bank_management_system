//git pull origin master
//git add .
//git commit -m "Added main menu"
//git push origin master

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

void user_login();
void admin_login();

int archive_customer(const char* filename){
    // search name of file 
    //snprintf to concatinate any username to the file path so long as it exists
    char newFile_path[200];
    snprintf(newFile_path, sizeof(newFile_path), "C:/Users/misti/OneDrive/Desktop/Final Project/bank_management_system/customers/archived customers/arc%s.txt", newFile_path);

    int result = rename(filename, newFile_path);
    result == 0 ? printf("Client successfully archived\n") : printf("Error archiving the client.\n");
     }

int add_customer(){
    char first[20]; // getting the user information
    char last[20];
    char usern[20];
    char pass[20];
    float deposit;
    printf("Customer Registration\n");
    printf("Customer First Name: ");
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

    if(errorcheck != NULL) // if it doesn't return null(or that there is no file), that means the customer exists
    {printf("%s %s is already a member. Please navigate to the Customer View Page", first, last);
        return 0;}

    
    //creating user file
        char file_path[200];        
        snprintf(file_path, sizeof(file_path), "Customers/%s%s.txt", first, last);
        FILE * fpointer = fopen(file_path, "w"); //opening file (use a to append just in case of overwrite)

        //writing info in their file
        fprintf(fpointer, "First Name: %s\nLast Name: %s\n\nUsername: %s\nPassword: %s\n\nBalance: $%.2f\n\nTransaction History: ", first, last, usern, pass, deposit);
        fclose(fpointer);
    }

int view_customers(){
    char customer[20];  // Customer search
    printf("Please enter Customer's first and last name with NO space between: ");
    scanf("%s", customer);

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
            admin_login();
            break;
        default:
            puts("Invalid Input");
            break;
        }}while(action != 3);
    }//end of view customer




void admin_login(){
    char password[20];
    char username[20];
    printf("Welcome to the Admin portal. Please sign in:\n");  
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *file = fopen("logins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }

    char fileUsername[20];
    char filePassword[20];
    bool found = false;

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
             if (strstr(fileUsername, "-adm") != NULL) {
                puts("Admin Login Successful");
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

    if (found) {
        int choice; 
        puts("Please choose what you want to do today. Please enter an integer value to represent your choice.");
        puts("1. View Customer Info  2. Add Customers  3. Remove Customers  4. Sort");
        scanf("%d", &choice);


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
            default:
                puts("Invalid choice");
                break;
        }
    }
} 

void user_login(){
    char password[20];
    char username[20]; 
    printf("Welcome to the User portal. Please sign in:\n");  
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *file = fopen("Customers/logins.txt", "r");
    if (file == NULL) {
        puts("Error opening file");
        return;
    }

    char fileUsername[20];
    char filePassword[20];
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
        puts("Please choose what you want to do today?. Please enter an integer value to represent your choice.\n");
        puts("1. Withdraw  2. Deposit  3. View previous transactions"); 
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
            default:
                puts("Invalid choice");
                break;
        }
    }

}


int main(void){
    int choice;
    puts("Welcome to the Bank Management System. Please enter an integer value to represent your choice:");
    puts("1. User Portal  2. Admin Portal");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            user_login();
            break;
        case 2:
            admin_login();
            break;
        default:
            puts("Invalid choice");
            break;
    }
}