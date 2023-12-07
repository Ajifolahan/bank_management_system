//copy paste
char password[20], username[20], fileUsername[20], filePassword[20], *foundFilename;
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
        if (strstr(username, "-adm") = NULL) {
            puts("Error. You cannot sign into the admin portal with user login information. Please try again or type 'exit' to exit");
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
            fseek(file, 0, SEEK_SET); ///return the file pointer to the beginning of the file

        }
    }

        do {
            int choice;
            puts("Please choose what you want to do today. Please enter an integer value to represent your choice.\n\n1. View Customer Info  2. Add Customers  3. Sort  4. Logout");

        
            if (scanf("%d", &choice) == 1) {
            // Process the choice
                if (choice == 1) {
                    view_customers();
                } else if (choice == 2) {
                    add_customer();
                } else if (choice == 3) {
                    puts("Sorting");
                    exit(0);
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