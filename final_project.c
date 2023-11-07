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
    puts("Please enter your username and password below:");
    scanf("%s", password);
    scanf("%s", username);
}

void admin_login(){
    char password[20];
    char username[20];
    printf("Welcome to the Admin portal. Please sign in:\n");
    puts("Please enter your username and password below:");
    scanf("%s", password);
    scanf("%s", username);
}