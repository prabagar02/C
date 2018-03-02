#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <ctype.h>
#define BUFFERSIZE 1024
#define FILENAME "passwd"

void addentry(char *username, char *password)
{
    FILE *passwdfile = fopen(FILENAME, "a");

    fprintf(passwdfile, "%s:%s:::::\n", username, crypt(password, "xx"));
   
    fclose(passwdfile);
}

int gethash(char *username, char *hash)
{
    char line[BUFFERSIZE + 1];
    char *tmpusername;
    char *tmphash;
    char *fields;

    FILE *passwdfile = fopen(FILENAME, "r");

    if (passwdfile == NULL)
    {
        return 0;
    }

    fgets(line, sizeof(char) * BUFFERSIZE, passwdfile);

    while(!feof(passwdfile))
    {

        tmpusername = strtok(line, ":"); 
        tmphash = strtok(NULL, ":");

        if (strcmp(username, tmpusername) == 0)
        {
            strcpy(hash, tmphash);
            return 1;
        }
        fgets(line, sizeof(char) * BUFFERSIZE, passwdfile);

    }

    return 0;
}

// enforce some criteria for the password
// length < 13, only uppercase, lowercase, and numbers
void getacceptablepassword(char password[13])
{
    int acceptable;
    int first = 1;

    do
    {
        acceptable = 1;

        if (!first)
        {
            printf("Passwords can only contain uppercase letters, lowercase letters, and numbers,\n");
            printf("and must not be longer than 12 characters. Please try again.\n");
            printf("Please enter a password:\n");
        }

        scanf("%s", password);

        if (strlen(password) > 12) acceptable = 0;
        
        for(int i=0; i < strlen(password); i++)
        {
            if (!isdigit(password[i]) && !isupper(password[i]) && !islower(password[i]))
            {
                acceptable = 0;
            }
        }

        first = 0;

    } while (acceptable == 0);

}

int main(int argc, char *argv[])
{
    int numrecords = 0;
    char *username = NULL;
    char password[13] = "";
    char *hash = malloc(sizeof(char) * 33);
    strcpy(hash, "");
    int attemptsallowed = 0;

    if (argc < 3)
    {
        printf("Usage: %s <user id> <number of attempts (n)>\n", argv[0]);
    }

    username = argv[1];
    if (strlen(username) < 3 || strlen(username) > 32)
    {
        printf("Username must be minimum 3 characters and maximum 32 characters. Try again with a new input\n");
        exit(1);
    }

    attemptsallowed = atoi(argv[2]);

    printf("Entered userID: %s\n", username);
    printf("Looking for user...\n");

    if (gethash(username, hash))
    {
        printf("Found. Welcome back %s, please enter your password:\n", username); 
        scanf("%s", password);
        int c = 1;

        while((c++ < attemptsallowed) && (strcmp(crypt(password, "xx"), hash) != 0))
        {
            printf("Wrong password, please try again:\n");
            scanf("%s", password);
        }

        if (strcmp(crypt(password, "xx"), hash) != 0)
        {
            printf("You have exceeded the limit of login attempts! Login unsuccessful.\n");
        }
        else
        {
            printf("Login Successful!\n");
        }
    }
    else
    {
        printf("No match found. Creating new profile...\n"); 
        printf("Please enter a password:\n"); 
        getacceptablepassword(password);
        addentry(username, password);
    } 
}
