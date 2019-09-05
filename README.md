# linux-unix-shell-in-cpp
i have cpp code for linux/unix shell 
DESCRIPTION
First a command is entered in shell, then it is divided into command name and other arguments. According to the command name entered, the argument is pushed into the corresponding function and executed separately.All the commands are stored in history. For execution, child is forked and execvp() is called. To handle these external commands, the shell creates a new process, using the fork() system call and within each process we need to use the execl() family system call to run the individual program. The parent program also waits for the child program to terminate using the wait() family of system calls.
Functions
int startprocess(char arr[], int i)
This function is the initial function which is called for checking the REDIRECTIONS. It passes the processed output to function process
int process(char arr[])
This function does the major part of the program. It tokenizes and checks for various possibilities of commands. 
Helper functions:
void phist()
Prints the history text file on the STDIN
void writehist(char arr[])
checks whether the threshold is crossed or not in the text file. If it is than rotates and shifts the data. And then write the character array which is input to the function in the text file.
Five internal commands - cd, echo, history, pwd and exit are handled. 
Five external commands - ls, cat, date, rm and mkdir are also handled.
COMMANDS
Internal
1. cd - It is used to go to the required directory. 
 
2. echo - It is used to print an argument.
 
3. history - It is used to print the history of all commands previously entered.
 
4. pwd - It is used to know the current directory.
 
5. exit - It is used to exit from the shell.
 
External
1. ls - It is used to show all the files in the current directory.
 
2. cat - It is used to show the contents of the file.

3. date - It is used to print the current date and time( in GMT ).
 
4. rm - It is used to remove the specified (file) but unable to delete folder.
 
5. mkdir - It is used to make a new directory with the given name.
 
