#include "functions.h"

void SignUpAdmin (void)
{
    FILE * Users;
    UserProp newUser;
    Users = fopen("users.bin", "wb");
    if (Users == NULL)
        return;
    fprintf(stdout, "%s\n%s", "The First Use of The Program", "Please sign up as the system admin");
    newUser.clearance = 0;
    newUser.tAvailable = 0;
    newUser.id = 0;
    printf("%s\n%s", "Enter your name", "It has to be less than 20 characters, newline isn't allowed.");
    printf("%s\n", "If you enter more than 20 characters, only the first valid ones are considered as your name");
    fgets(newUser.name, 19, stdin);
    fprintf(stdout, "%s\n%s", "Enter your username", "It has to be less than 20 characters, space and newline aren't allowed.");
    fprintf(stdout, "%s\n", "If you enter more than 20 characters, only the first valid ones are considered as user name");
    scanf("%19s", newUser.username);
    UserProp *list;
    list = (UserProp *) malloc (sizeof(UserProp));
    for (int i = 0; i < newUser.id; ++i) {
        fread (list, sizeof(UserProp), 1, Users);
        while (strcmp (list->username , newUser.username) == 0)
        {
            fprintf(stdout, "%s\n", "This username already exists.");
            fprintf(stdout, "%s\n%s", "Enter your username", "It has to be less than 20 characters, space and newline aren't allowed.");
            fprintf(stdout, "%s\n", "If you enter more than 20 characters, only the first valid ones are considered as user name");
            scanf("%19s", newUser.username);
        }
    }
    free (list);
    fseek(Users, 0 , SEEK_END);

    int i = 0,flag =1;
    char pass[20], pass2[20];
    do {
        fprintf(stdout, "%s\n%s", "Enter your password",
                "It has to be less than 20 characters, space and newline aren't allowed.");
        fprintf(stdout, "%s\n",
                "If you enter more than 20 characters, only the first valid ones are considered as password");
        while ((pass[i] = (char) getch()) != '\n' && pass[i] != '\r' && i < 19) {
            putchar('*');
            i++;
        }
        pass[i] = '\0';
        printf("%s\n", "Enter your password again:");
        i = 0;
        while ((pass2[i] = (char) getch()) != '\n' && pass2[i] != '\r' && i < 19) {
            putchar('*');
            i++;
        }
        pass2[i] = '\0';
        if (strcmp(pass, pass2) != 0) {
            printf("%s\n", "The passwords do not match.");
        }
        else
        {
            strncpy(newUser.password, pass, sizeof(pass));
            flag =0;
        }
    }while (flag);
    fwrite(&newUser, sizeof(UserProp), 1, Users);
    fclose(Users);
    fprintf(stdout, "\n%s%s%s\n%s\n", "Welcome ", newUser.name, "  ,you've been registered!", "Now you can sign in the system.");
    SignIn();
    return;
}

int createuser (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1))
        return -1;
    if (CurUser->id)
    {
        puts("Only system admin can create a new user.");
        puts("Please contact your system administrator.");
        return -1;
    }
    return 0;
}

void SignIn (void)
{
    /*char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory(MAX_PATH, path)) { //saving the pwd of the program
        puts("Error Finding the user's database.");
        return;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the user's database.");
        return;
    }
    FILE * Users;
    Users = fopen("users.bin", "r");
    if (Users == NULL)
        return;
    if (!CurUser)
    {
        fprintf(stdout, "%s\n", "Enter your username:");
        char usernamec[20];
        scanf ("%s", usernamec);
        UserProp *list;
        list = (UserProp *) malloc (sizeof(UserProp));
        int trueuser=0, total;
        fseek(Users, 0, SEEK_END);
        total = ftell(Users);
        for (int i = 0; i < (total); ++i) {
            fread (list, sizeof(UserProp), 1, Users);
            if (strcmp (list->username , usernamec) == 0)
            {
                trueuser = i;
                break;
            }
        }
        free (list);
        fprintf(stdout, "%s\n", "Enter your password:");
        int i = 0;
        char pass[20];
        while( (pass[i] = (char)getch()) != '\n' && pass[i] != '\r' && i<19 )
        {
            putchar('*');
            i++;
        }
        pass[i]='\0';
        int enter = 0;
        UserProp check;
        if (trueuser)
        {
            fseek(Users, (trueuser - 1), SEEK_SET);
            fread(&check, sizeof(UserProp), 1, Users);
            if (strcmp(check.password, pass) == 0)
            {
                time_t raw;
                time (&raw);
                struct tm * timenow = localtime(&raw);
                if (difftime(check.tAvailable, mktime(timenow)) > 0)
                    enter = 1;
            }
        }
        fclose(Users);
        if (enter)
        {
            printf("\n%s%s!\n", "Welcome, ", check.name);
            CurUser = (UserProp*) malloc(sizeof(UserProp));
            *CurUser = check;
        }else {
            printf("\n%s\n", "The username/password pair do not match or your account has expired.");
            SignIn(CurUser);
            return;
        }
    }*/
}

int passwd (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2)) //it's wrong
        return -1;
    return 0;
}

int su (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    return 0;
}

int chcl (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    if (CurUser->id)
    {
        puts("Only system admin can change the clearance settings");
        puts("Please contact your system admin.");
        return -1;
    }
    return 0;
}