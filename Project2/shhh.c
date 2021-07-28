#include <fcntl.h>  // open
#include <stdio.h>  // printf
#include <stdlib.h> // exit
#include <string.h> // strcmp
#include <unistd.h> // fork, pipe, dup
#include <sys/wait.h>  // wait



int main()
{
//-------------- CODE IN THIS SECTION IS STRAIGHT FROM lab2.c --------------------//
    char *path, *argv[20], buf[80], n, *p;
    
    int m, status, inword, continu;

    //Mainloop that will only terminate once "exit" is typed into consol.
    while (1)
    {
        inword = 0;
        p = buf;
        m = 0;
        continu = 0;

        printf ("\nshhh>");

        while ((n = getchar()) != '\n' || continu)
        {
            if (n == ' ')
            {
                if (inword)
                {
                    inword = 0;
                    *p++ = 0;
                }
            }
            else if (n == '\n') 	   { continu = 0; }
            else if (n == '\\' && !inword) { continu = 1; }
            else
            {
                if (!inword)
                {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                }
                else
			*p++ = n;
            }
        }
        *p++ = 0;
        argv[m] = 0;
//------------- CODE GOES AFTER THIS. DO NOT TOUCH ANYTHING ABOVE -------------------//

        if (strcmp(argv[0], "exit") == 0) { exit(0); }

	//Variables to find any pipes or redirects ( |, <, > )
        int pipeCount = 0, pipes[10], inloc = -1, outloc = -1, cmdCount = 0, cmds[10];       

        cmds[cmdCount++] = 0;
        
	int i;
        for (i = 1; i < m; ++i)
        {
	    //Finds any pipe and replaces it with 0. Stores the position of the next command
            if (strcmp(argv[i], "|") == 0) 
            {
                pipes[pipeCount++] = i;
                argv[i] = 0;
                cmds[cmdCount++] = i + 1;
            }
	    //Finds any input redirects and replaces it with 0. Stores position of the next command
            else if (strcmp(argv[i], "<") == 0) 
            {
                inloc = i + 1;
                argv[i] = 0;
            }
	    //Finds and output redirects and replaces with 0. Stores the position of the next command
            else if (strcmp(argv[i], ">") == 0) 
            {
                outloc = i + 1;
                argv[i] = 0;
            }
        }

        int l_fd[2], r_fd[2], pid, inf = -1, outf = -1;  

	int cmd;
        for (cmd = 0; cmd <= pipeCount; ++cmd)
        {
            //Creates pipe to next command
            if (cmd < pipeCount) { pipe(r_fd); }

            pid = fork();

            if (pid < 0) { exit(-1); }
            //Child process
            else if (pid == 0)
            {
                //Input redirection
                if (cmd == 0 && inloc >= 0)
                {
                    //Open file to read
                    inf = open(argv[inloc], O_RDONLY);
                    if (inf < 0) { exit(-1); }

                    //Modify input
                    close(0);
                    dup(inf);
                    close(inf);
                }

                if (pipeCount > 0) {
		    //Edge case. First command
                    if (cmd == 0)
                    {
			//Only allows write to pipe 
                        close(1);
                        dup(r_fd[1]);
                        close(r_fd[1]);
                        close(r_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                    }
                    //Any command that is not first or last
                    else if (cmd < pipeCount)
                    {
                        //Allows read from pipe and write to pipe
                        close(0);
                        dup(l_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                    }
                    //Edge case. Last command
                    else
                    {
                        //Only allows read from pipe
                        close(0);
                        dup(l_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                        close(r_fd[0]);
                        close(r_fd[1]);
                    }
                }

                //Redirection for output
                if (cmd == pipeCount && outloc >= 0)
                {
                    //Opens the file to write
                    outf = open(argv[outloc], O_CREAT | O_WRONLY, 0754);
                    if (outf < 0) { exit(-1); }

                    //Modify output
                    close(1);
                    dup(outf);
                    close(outf);
                }

                execvp(argv[cmds[cmd]], &argv[cmds[cmd]]);
                printf(" didn't exec \n ");
            }
            //Parent process
            else
            {
                //Closes left pipe if it is opened from a previous command
                if (cmd > 0)
                {
                    close(l_fd[0]);
                    close(l_fd[1]);
                }

                //Move right pipe to left pipe
                l_fd[0] = r_fd[0];
                l_fd[1] = r_fd[1];

                wait(&status);
            }
        }
    }
}
