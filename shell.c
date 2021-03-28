#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    
    char commandstr[BUFSIZ];
    memset(commandstr, 0, BUFSIZ);

    int c;
    
    char tempStr[BUFSIZ];
    memset(tempStr, 0 , BUFSIZ);

    char *argsHist[MAX_LINE/2 + 1]; /* command line arguments from previous */



    while (should_run) {
        printf("osh>");
        fflush(stdout);
         unsigned int isString = 0; // flag to tell if we are in a string
         unsigned int includeAmp = 0; // flag to tell if the ampersand is included in the args list
         int argsIter = 0; //Iterator of args
         int strIter = 0; // iterator for recorded strings
         int id; // Used for fork();
         int id2;

         char * tempStr;
         
         int tempstrIter = 0;



        /* Commands recorded */
        fgets(commandstr, BUFSIZ, stdin);
        printf("Debug Echo: %s", commandstr);

        /* Parsing commands*/

        for (int i = 0; commandstr[i] != '\0'; ++i)
        {
            if (commandstr[i] != ' ')
            {
                tempStr[tempstrIter++] = commandstr[i]; // we place the character in a temp string
            }
            else{
                args[argsIter++] = tempStr; // we record the string in args.
                memset(tempStr, 0 ,BUFSIZ);// Clear tempStr
                tempstrIter = 0;

            }
            args[argsIter] == "EOF";

        }

        for(int i = 0; strcmp("EOF", args[i]) == 0; ++i)
        {
            printf("%s\n", args[i]);
        }





/*
        while((c = getchar()) != EOF)
        {
            printf("gotten\n");
            if((c == ' ' || c == EOF) && isString == 1)
            {
                
                tempStr[strIter] = '\0';
                args[argsIter++] = tempStr;
                memset(tempStr, 0 , BUFSIZ);
                strIter = 0;
                isString = 0;
            }
            else
            {   
                tempStr[strIter++] = c;
                isString = 1;
            }
        }
        args[argsIter] = NULL;
        */

        /* Are we using the previous command? */
        if (args[0] == "!!")
        {

            if (argsHist[0] == NULL) // Error checking
            {
                printf("No commands in history\n");
            }
            else
            {
                memset(args, NULL, sizeof(args)); // We clear our arguments that just consists of !!

                while(argsHist != NULL)
                {
                    int i = 0; int j = 0; 
                    strcpy(args[i++], argsHist[j++]); // We copy our previous arg into current arg and carry on as usual
                    //args[i++] = argsHist[j++];
                }
            }
        }

        /* Remember the command: */

        {
            int i = 0; int j = 0;
            strcpy(argsHist[i++], args[j++]);
        }


        


        /*Flagging for ampersand*/
        if(args[--argsIter] == "&")
        {
            printf("Ampersand detected\n");
            fflush(stdout);
            includeAmp = 1;
        }
        
        if(args[1] == ">") // Redirecting Output and Input
        {
            int redirect_fd = open(args[2], O_CREAT | O_TRUNC | O_WRONLY);
            dup2(redirect_fd, STDOUT_FILENO);
            close(redirect_fd);


        }
        else if( args[1] == "<")
        {
            int redirect_fd = open(args[0], O_RDONLY);
            dup2(STDIN_FILENO, redirect_fd);
            close(redirect_fd);
        }
        else {
            /**
            * After reading user input, the steps are:
            * (1) fork a child process using fork()
            * (2) the child process will invoke execvp()
            *  (3) parent will invoke wait() unless command included &
            */
            id = fork(); // We fork into a child and parent

            if(id == 0) // if we are in the child process
            {
                execvp(args[0], args);
            }
            else // if we are in the parent process
            {
                if(includeAmp = 0)
                {
                    printf("Parent is waiting\n");
                    fflush(stdout);
                    wait();
                }
            }
        }

     memset(args, NULL, sizeof(args));
    }
    return 0;
} 
----------------------------------