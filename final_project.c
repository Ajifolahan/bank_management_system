//git pull origin master
//git add .
//git commit -m "Added main menu"
//git push origin master

#include <stdio.h>

void user_login();
void admin_login();
int main(void){
    int choice;
    puts("Welcome to the Bank Management System. Please select from the following options:");
    puts("Please enter an integer value to represent your choice:");
    puts("1. User");
    puts("2. Admin");
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

void user_login(){
    char password[20];
    char username[20];
    printf("Welcome to the User portal. Please sign in:\n");
    puts("Please enter your username below:");
    scanf("%s", username);
    puts("Please enter your password below:");
    scanf("%s", password);
    //read file and check for values
    int choice; 
    puts("Please choose what you want to do today?. Please enter an integer value to represent your choice:");
    puts("1. Withdraw");
    puts("2. Deposit");
    puts("3. View previous transactions");
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

void admin_login(){
    char password[20];
    char username[20];
    printf("Welcome to the Admin portal. Please sign in:\n");
    puts("Please enter your username below:");
    scanf("%s", username);
    puts("Please enter your password below:");
    scanf("%s", password);

    //read file and check for values
    int choice; 
    puts("Please choose what you want to do today?. Please enter an integer value to represent your choice:");
    puts("1. View Customer Info");
    puts("2. Add Customers");
    puts("3. Remove Customers");
    puts("4. Sort");

    scanf("%d", &choice);
        switch(choice){
        case 1:
            puts("viewing");
            break;
        case 2:
            puts("adding");
            break;
        case 3:
            puts("removing");
            break;
        case 4:
            puts("sorting");
            break;
        default:
            puts("Invalid choice");
            break;
    }

    //give options to View Customer Info, Add Customers, Remove Customers, Sort.
}