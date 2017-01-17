#include "functions.h"

void SignUpAdmin (void)
{
    FILE * Users;
    UserProp newUser;
    Users = fopen("users.bin", "wb");
    if (Users == NULL)
        return;
    fprintf(stdout, "\t%s\n\t%s\n", "The First Use of The Program", "Please sign up as the system administrator");
    newUser.clearance = 0;
    newUser.tAvailable = {};
    newUser.id = 0;
    printf("%s\n%s\n", "Enter your name", "It has to be less than 20 characters, newline and space aren't allowed.");
    printf("%s\n", "If you enter more than 20 characters, only the first valid ones are considered as your name");
    scanf("%19s", newUser.name);
    fprintf(stdout, "%s\n%s\n", "Enter your username", "It has to be less than 20 characters, space and newline aren't allowed.");
    fprintf(stdout, "%s\n", "If you enter more than 20 characters, only the first valid ones are considered as user name");
    scanf("%19s", newUser.username);
    fseek(Users, 0 , SEEK_END);

    int flag =1;
    char pass[20]={}, pass2[20]={};
    do {
        fprintf(stdout, "%s\n%s\n", "Enter your password",
                "It has to be less than 20 characters, space and newline aren't allowed.");
        fprintf(stdout, "%s\n",
                "If you enter more than 20 characters, only the first valid ones are considered as password");
        int i = 0;
        while ((pass[i] = (char) getch()) != '\n' && pass[i] != '\r' && i < 19) {
            if (pass[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
            putchar('*');
            i++;
        }
        pass[i] = '\0';

        printf("%s\n", "Enter your password again:");
        i = 0;
        while ((pass2[i] = (char) getch()) != '\n' && pass2[i] != '\r' && i < 19) {
            if (pass2[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
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
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory((DWORD)MAX_PATH, (LPSTR)path)) { //saving the pwd of the program
        puts("Error finding the main directory.");
        return 0;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the user's database.");
        return 0;
    }
    FILE * Users;
    UserProp newUser;
    Users = fopen("users.bin", "a+b");
    if (Users == NULL)
        return -1;
    UserProp temp;
    fseek(Users, 0, SEEK_SET);
    while (1) {
        fread(&temp, sizeof(struct user), 1, Users);
        if (feof(Users)){
            newUser.id = temp.id + 1;
            break;
        }
    }
    fseek(Users, 0, SEEK_SET);
    printf("%s\n%s\n", "Enter User's clearance.", "It can later be changed with chclr command.");
    scanf("%u", &newUser.clearance);
    printf("%s\n%s\n%s\n", "Enter User's time available.", "It can later be changed with psswrd -l command.", "Enter dd-mm-yyyy");
    struct tm import;
    int x, y, z;
    scanf("%d-%d-%d", &x, &y,&z);
    import.tm_year = z + 1970;
    import.tm_mon = y + 1;
    import.tm_mday = x;
    newUser.tAvailable = mktime(&import);
    printf("%s\n%s\n", "Enter the name", "It has to be less than 20 characters, newline isn't allowed.");
    printf("%s\n", "If you enter more than 20 characters, only the first valid ones are considered as the name");
    scanf("%19s", newUser.name);
    fprintf(stdout, "%s\n%s\n", "Enter the username", "It has to be less than 20 characters, space and newline aren't allowed.");
    fprintf(stdout, "%s\n", "If you enter more than 20 characters, only the first valid ones are considered as username");
    scanf("%19s", newUser.username);
    UserProp *list;
    list = (UserProp *) malloc (sizeof(UserProp));
    for (int i = 0; i < newUser.id; ++i) {
        fread (list, sizeof(UserProp), 1, Users);
        while (strcmp (list->username , newUser.username) == 0)
        {
            fprintf(stdout, "%s\n", "This username already exists.");
            fprintf(stdout, "%s\n%s", "Enter the username", "It has to be less than 20 characters, space and newline aren't allowed.");
            fprintf(stdout, "%s\n", "If you enter more than 20 characters, only the first valid ones are considered as username");
            scanf("%19s", newUser.username);
        }
    }
    free (list);
    fseek(Users, 0, SEEK_END);

    int flag =1;
    char pass[20]={}, pass2[20]={};
    do {
        fprintf(stdout, "%s\n%s\n", "Enter your password",
                "It has to be less than 20 characters, space and newline aren't allowed.");
        fprintf(stdout, "%s\n",
                "If you enter more than 20 characters, only the first valid ones are considered as password");
        int i = 0;
        while ((pass[i] = (char) getch()) != '\n' && pass[i] != '\r' && i < 19) {
            if (pass[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
            putchar('*');
            i++;
        }
        pass[i] = '\0';
        printf("%s\n", "Enter your password again:");
        i = 0;
        while ((pass2[i] = (char) getch()) != '\n' && pass2[i] != '\r' && i < 19) {
            if (pass2[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
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
    if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
        puts("Error Finding the user's database.");
        return 0;
    }
    free(path);
    SignIn();
    return 0;
}

int SignIn (void)
{
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory(MAX_PATH, path)) { //saving the pwd of the program
        puts("Error Finding the user's database.");
        return -2;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the user's database.");
        return -1;
    }
    FILE * Users;
    Users = fopen("users.bin", "rb");
    if (Users == NULL)
        return -12;

        fprintf(stdout, "%s\n", "Enter your username:");
        char usernamec[20];
        scanf ("%s", usernamec);
        UserProp list = {};
        int trueuser=0;
        for (int i = 0; ; ++i) {
            if (feof(Users))
                break;
            fread (&list, sizeof(UserProp), 1, Users);
            if (strcmp (list.username , usernamec) == 0)
            {
                trueuser = i+1;
                break;
            }
        }
    int enter = 0, in;
    if (CurUser)
        in = CurUser->id;
    else
        in = -1;
    if (!in && trueuser)
    {
        enter = 1;}
    else if (!in && !trueuser){
        return 0;
    }else{
        fprintf(stdout, "%s\n", "Enter your password:");
        char passc[20];
        int i = 0;
        while ((passc[i] = (char) getch()) != '\n' && passc[i] != '\r' && i < 19) {
            if (passc[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
            putchar('*');
            i++;
        }
        passc[i] = '\0';
        if (trueuser)
        {
            if (strcmp(list.password, passc) == 0)
            {
                if (list.id) {
                    if (difftime(list.tAvailable, time(0)) > 0)
                        enter = 1;
                } else{
                    enter = 1;
                }
            }
        }}
        fclose(Users);
        if (enter)
        {
            printf("\n%s%s!\n", "Welcome, ", list.name);
            CurUser = (UserProp*) malloc(sizeof(UserProp));
            *CurUser = list;
            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            return trueuser;

        }else {
            printf("\n%s\n", "The username/password pair do not match or your account has expired.");
            SignIn();
            return -15;
        }

}

int passwd (char** arguments, int argnum)
{
    if (argnum > 3 || argnum < 2 || (argnum == 3 && strcmp(*(arguments + 1), "-l") != 0))
    {
        printf("Wrong arguments for the %s command.\n", *(arguments));
        printf("Try 'help %s' to get information on the command\n", *arguments);
        return -3;
    }
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory((DWORD)MAX_PATH, (LPSTR)path)) { //saving the pwd of the program
        puts("Error finding the main directory.");
        return 0;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the user's database.");
        return 0;
    }
    if (argnum == 2)
    {
        FILE * Users;
        Users = fopen("users.bin", "r+b");
        if (Users == NULL)
            return -1;
        fseek(Users, 0, SEEK_SET);
        UserProp list = {};
        int trueuser = 0;
        for (int i = 0; ; ++i) {
            if (feof(Users))
                break;
            fread (&list, sizeof(UserProp), 1, Users);
            if (strcmp (list.username , *(arguments + 1)) == 0)
            {
                trueuser = i+1;
                break;
            }
        }
        if (!trueuser)
        {
            printf("%s\n", "This username dosen't exist.");
            fclose(Users);
            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            return -857;
        }
        if (CurUser->id && CurUser->id != list.id)
        {
                puts("Only system administrator can change the password of someone else.");
                puts("Please contact your system administrator.");
                fclose(Users);
                if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                    puts("Error Finding the user's database.");
                    return 0;
                }
            free(path);
                return -1;
        }
        int i = 0;
        char oldpass[20], newpass1[20], newpass2[20];
        if (CurUser->id) {
            printf("%s\n", "Enter the current password.");
            while ((oldpass[i] = (char) getch()) != '\n' && oldpass[i] != '\r' && i < 19) {
                if (oldpass[i] == '\b')
                {
                    printf ("%c", '\b');
                    printf ("%c", ' ');
                    printf ("%c", '\b');
                    i--;
                    continue;
                }
                putchar('*');
                i++;
            }
            oldpass[i] = '\0';
            if (strcmp(oldpass, list.password) != 0)
            {
                printf("%s\n", "This password dosen't match the username.");
                return 3976;
            }
        }
        printf("%s\n", "Enter the new password.");
        i = 0;
        while ((newpass1[i] = (char) getch()) != '\n' && newpass1[i] != '\r' && i < 19) {
            if (newpass1[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
            putchar('*');
            i++;
        }
        newpass1[i] = '\0';
        printf("%s\n", "Enter the new password again.");
        i = 0;
        while ((newpass2[i] = (char) getch()) != '\n' && newpass2[i] != '\r' && i < 19) {
            if (newpass2[i] == '\b')
            {
                printf ("%c", '\b');
                printf ("%c", ' ');
                printf ("%c", '\b');
                i--;
                continue;
            }
            putchar('*');
            i++;
        }
        newpass2[i] = '\0';
        if (strcmp(newpass1, newpass2) != 0)
        {
            printf("%s\n", "The passwords don't match.");
            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            fclose(Users);
            return 3976;
        }
        fseek(Users, trueuser - 1, SEEK_SET);
        UserProp rep;
        rep = list;
        strncpy(rep.password, newpass1, sizeof(newpass1));
        fwrite(&rep, sizeof(UserProp), 1, Users);
        if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
            puts("Error Finding the user's database.");
            return 0;
        }
        free(path);
        fclose(Users);
    }else if (argnum == 3 && strcmp(*(arguments + 1), "-l") == 0)
    {
        if (CurUser->id)
        {
            puts("Only system administrator can change the time settings.");
            puts("Please contact your system administrator.");
            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            return -1;
        }
        FILE * Users;
        Users = fopen("users.bin", "r+b");
        if (Users == NULL)
            return -1;
        UserProp list = {};
        fseek(Users, 0, SEEK_SET);
        int trueuser = 0;
        for (int i = 0; ; ++i) {
            if (feof(Users))
                break;
            fread (&list, sizeof(UserProp), 1, Users);
            if (strcmp (list.username , *(arguments + 1)) == 0)
            {
                trueuser = i+1;
                break;
            }
        }
        if (!trueuser)
        {
            printf("%s\n", "This username dosen't exist.");
            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            fclose(Users);
            return -857;
        }
        printf("%s\n%s\n%s\n", "Enter User's clearance.", "It can later be changed with psswrd -l command.", "Enter dd-mm-yyyy");
        struct tm import;
        scanf("%d-%d-%d", &import.tm_mday, &import.tm_mon, &import.tm_year);
        import.tm_mon =+ 1;
        import.tm_year =+ 1990;
        UserProp rep;
        rep = list;
        rep.tAvailable = mktime(&import);
        fseek(Users, trueuser - 1, SEEK_SET);
        fwrite(&rep, sizeof(UserProp), 1, Users);
        if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
            puts("Error Finding the user's database.");
            return 0;
        }
        free(path);
        fclose(Users);
    }
}

int su (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1))
        return -1;
    int t = SignIn();
    if (t == 0)
    {
        printf ("No user with that user name exists.");
        return 0;
    }

}

int chcl (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    if (strcmp(*(arguments + 1), "-u") == 0){
        if (CurUser->id)
    {
        puts("Only system admin can change the clearance settings");
        puts("Please contact your system admin.");
        return -1;
    }
        char *path = (char *)malloc (MAX_PATH* sizeof(char));
        if (!GetCurrentDirectory((DWORD)MAX_PATH, (LPSTR)path)) { //saving the pwd of the program
            puts("Error finding the main directory.");
            return 0;
        }
        if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
            puts("Error Finding the user's database.");
            return 0;
        }

        FILE * file = fopen("users.bin", "r+b");
        UserProp m;
        int trueuser=0;
        for (int i = 0; ; ++i) {
            if (feof(file))
                break;
            fread (&m, sizeof(UserProp), 1, file);
            if (strcmp (m.username , *(arguments + 2)) == 0)
            {
                trueuser = i+1;
                break;
            }
        }
        if (trueuser)
        {
            fseek(file, trueuser - 1, SEEK_SET);
            if (m.id == 0)
            {
                printf("%s\n", "You can't change the administrator clearance.");
                fclose(file);
                return -2;
            }
            printf("%s\n", "Enter user's new clearance:");
            scanf("%d", &m.clearance);
            if(m.clearance <= 0 && m.id != 0)
                m.clearance = 1;
            fwrite(&m, sizeof(UserProp), 1, file);
            fclose(file);

            if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
                puts("Error Finding the user's database.");
                return 0;
            }
            free(path);
            return 0;
        }
    }
    File n;
    char *path2;
    path2 = (char *) malloc ((strlen(*(arguments + 1)) + 4) * sizeof(char));
    strcpy(path2, *(arguments + 1));
    strncat(path2, ".PROP.dat", 9);
    FILE * f = fopen (path2, "r+b");
    if (f == NULL)
    {
        printf("%s\n", "File dosen't exist.");
        return -9;
    }
    free(path2);
    fread (&n, sizeof(UserProp), 1, f);
    if (CurUser->clearance == 0 || CurUser->clearance == n.clearance) {
        fseek(f, 0, SEEK_SET);
        printf("%s\n", "Enter file's new clearance code:");
        scanf("%d", &n.clearance);
        if (n.clearance < 0)
            n.clearance = 1;
        fseek(f, 0, SEEK_SET);
        fwrite(&n, sizeof(File), 1, f);
    }
    else{
        printf("%s\n", "You can't change this settings.");
        return -2452;
    }
        return 0;
}