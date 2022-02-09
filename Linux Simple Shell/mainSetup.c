/* Hasan Senyurt - 150120531
 * Melisa Durmus - 150119727
 * 
 * Note: Dear teacher, We completed part A totally, but when background process is terminated, 'myshell:' is not printed
 * on terminal, but myshell still works. You can enter some inputs to it. Only print issue.
 * In B part, Alias/Unalias is completed but signal part is not completed.
 * In C part, truncate output (>) and append output (>>) are completed, but input(<) and input-output (<..>) part
 * is not completed exactly.
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
 
/* The setup function below will not return any value, but it will just: read
in the next command line; separate it into distinct arguments (using blanks as
delimiters), and set the args array entries to point to the beginning of what
will become null-terminated, C-style strings. */

int ct; //counter for arguments

void setup(char inputBuffer[], char *args[],int *background)
{

    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start;  /* index where beginning of next command parameter is */
                /* index of where to place the next parameter into args[] */
    
    ct = 0;
        
    /* read what the user enters on the command line */
    length = read(STDIN_FILENO,inputBuffer,MAX_LINE);  

    /* 0 is the system predefined file descriptor for stdin (standard input),
       which is the user's screen in this case. inputBuffer by itself is the
       same as &inputBuffer[0], i.e. the starting address of where to store
       the command that is read, and length holds the number of characters
       read in. inputBuffer is not a null terminated C-string. */

    start = -1;
    if (length == 0)
        exit(0);            /* ^d was entered, end of user command stream */

/* the signal interrupted the read system call */
/* if the process is in the read() system call, read returns -1
  However, if this occurs, errno is set to EINTR. We can check this  value
  and disregard the -1 value */
    if ( (length < 0) && (errno != EINTR) ) {
    	perror("error reading the command");
	exit(-1);           /* terminate with error code of -1 */
    }

	//printf(">>%s<<",inputBuffer);
    for (i=0;i<length;i++){ /* examine every character in the inputBuffer */

        switch (inputBuffer[i]){
	    case ' ':
	    case '\t' :               /* argument separators */
		if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
		    ct++;
		}
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
		start = -1;
		break;

            case '\n':                 /* should be the final char examined */
		if (start != -1){
                    args[ct] = &inputBuffer[start];     
		    ct++;
		}
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
		break;

	    default :             /* some other character */
		if (start == -1)
		    start = i;
                if (inputBuffer[i] == '&'){
		    *background  = 1;
                    inputBuffer[i-1] = '\0';
		}
	} /* end of switch */
     }    /* end of for */
     args[ct] = NULL; /* just in case the input line was > 80 */

	/*for (i = 0; i <= ct; i++)
		printf("args %d = %s\n",i,args[i]);*/
} /* end of setup routine */

//finding path of processes.
int findPath(const char name[], char *fullpath, size_t size) {
    const char *token;
    int found = 0;
    char *paths = strdup(getenv("PATH"));
    char *temporary = paths;
    
    while ((token = strsep(&paths, ":")) != NULL) {
    	
        snprintf(fullpath, size, "%s/%s", token, name);
        
        if (access(fullpath, F_OK | X_OK) != -1) {
            found = 1;
            break;
        }
    }
    
    free(temporary);
    return found;
}

int main(void)
{
	char inputBuffer[MAX_LINE]; /*buffer to hold command entered */
	int background; /* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2 + 1]; /*command line arguments */
	char alias[100][2][100]; // alias list (matrix)
	int alias_ct = 0; // alias counter: how many alias in the matrix?
	while (1){
		background = 0;
		printf("myshell: ");
		fflush(stdout);
		/*setup() calls exit() when Control-D is entered */
		setup(inputBuffer, args, &background);
		
		int i; // for loop.
		int alias_control = 0; //checking alias is written to myshell or not.
		char command[100]; // command in alias ("ls -l" for example).
		
		// checking whether alias name is written to myshell (first argument)
		for(i=0;i<100;i++){
			if(!strcmp(alias[i][1],args[0])){
				alias_control = 1;
				strcpy(command,alias[i][0]); //if it is, then take the command in the alias matrix.
				break;
			}
		}
		// I/O CHECKING TRUNCATE OUT AND APPEND OUT WORK CLEARLY IN OUR CODE. INPUT < IS NOT WORKING WELL.
		int IO=0;
		int out=0;
		int out_append=0;
		int input=0;
		//checking if i/o redirection is the case or not.
		for(i=0;args[i]!=NULL;i++){
			if(!strcmp(args[i],"<") || !strcmp(args[i],">>") || !strcmp(args[i],">")){	
				IO=1;
				break;
			}
		}
		// truncate out
		for(i=0;args[i]!=NULL;i++){
			if(!strcmp(args[i],">")){	
				out=1;
				break;
			}
		}
		// input
		for(i=0;args[i]!=NULL;i++){
			if(!strcmp(args[i],"<")){	
				input=1;
				break;
			}
		}
		// append out
		for(i=0;args[i]!=NULL;i++){
			if(strcmp(args[i],">>")){	
				out_append=1;
				break;
			}
		}
		// INPUT OUTPUT case!
		if(IO){
			if(out){
				//file and command name is taken.
				int i;
				char file[MAX_LINE] = " ";
				strcpy(file,args[ct-1]);
				for(i=0;args[i] != NULL;i++){
					if(!strcmp(args[i],">")){
						args[i] = NULL;
						break;
					}
				}
				
				char fullpath[512]; //path name
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process in the paths.
				if (found) {
					int fd;
					//fd = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
					fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
					if (fd < 0) {
						perror("open failed");
						exit(0);
					}
					pid_t pid = fork();
					if (pid < 0) {
						perror("fork failed");
						exit(0);
					}
					else if (pid == 0) {
						dup2(fd, STDOUT_FILENO);
						close(fd);
						execv(fullpath, args);
					}
					else {
						wait(NULL);
					}
				}
				if(!found){
					perror("Process cannot be found! File cannot be created!");
				}
				
			}
			// >> append output part.
			else if(out_append){
				//file and command name is taken.
				int i;
				char file[MAX_LINE] = " ";
				strcpy(file,args[ct-1]);
				for(i=0;args[i] != NULL;i++){
					if(!strcmp(args[i],">>")){
						args[i] = NULL;
						break;
					}
				}
				
				char fullpath[512]; //path name
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process in the paths.
				if (found) {
					int fd;
					fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
					if (fd < 0) {
						perror("open failed");
						exit(0);
					}
					pid_t pid = fork();
					if (pid < 0) {
						perror("fork failed");
						exit(0);
					}
					else if (pid == 0) {
						dup2(fd, STDOUT_FILENO);
						close(fd);
						execv(fullpath, args);
					}
					else {
						wait(NULL);
					}
				}
				if(!found){
					perror("Process cannot be found! File cannot be created!");
				}
				
			}
			//input part <.
			if(input && !out){
				//file and command name is taken.
				int i;
				char file[MAX_LINE] = " ";
				strcpy(file,args[ct-1]);
				for(i=0;args[i] != NULL;i++){
					if(!strcmp(args[i],"<")){
						args[i] = NULL;
						break;
					}
				}
				
				char fullpath[512]; //path name
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process in the paths.
				
				if (found) {
				   pid_t childpid;
				   int fd[2];
				   if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) {
					   perror("Failed to setup pipeline");
					  return 1;
				   }
				   if (dup2(fd[0], STDIN_FILENO) == -1)               
					   perror("Failed to redirect stdin of sort");
				   else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) 
					   perror("Failed to close extra pipe file descriptors on sort"); 
				   else {
					  execv(fullpath, args);
					  perror("Failed to exec sort");
				   }
				}
				if(!found){
					perror("Process cannot be found! File cannot be created!");
				}
			}
			//input-output part <...>
			if(input && out){
				//file and command name is taken.
				int i;
				int temp_i;
				char output_file[MAX_LINE] = " ";
				char input_file[MAX_LINE] = " ";
				strcpy(output_file,args[ct-1]);
				for(i=0;args[i] != NULL;i++){
					if(!strcmp(args[i],"<")){
						strcpy(input_file,args[i+1]);
						temp_i=i;
						break;
					}
				}
				for(i=0;args[i] != NULL;i++){
					if(!strcmp(args[i],">")){
						args[temp_i] = NULL;
						args[i] = NULL;
						break;
					}
				}
				
				char fullpath[512]; //path name
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process in the paths.			
				if (found) {
				   pid_t childpid;
				   int fd[2];
				 
				   if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) {
					   perror("Failed to setup pipeline");
					  return 1;
				   }
					  
				   if (childpid == 0) {                                  /* ls is the child */
					  if (dup2(fd[1], STDOUT_FILENO) == -1) 
						  perror("Failed to redirect stdout of ls");
					  else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) 
						  perror("Failed to close extra pipe descriptors on ls");
					  else { 
						 execl("/bin/ls", "ls", "-l", NULL);
						 perror("Failed to exec ls");
					  }
				   } 
				   if (dup2(fd[0], STDIN_FILENO) == -1)               /* sort is the parent */
					   perror("Failed to redirect stdin of sort");
				   else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) 
					   perror("Failed to close extra pipe file descriptors on sort"); 
				   else {
					  execl("/bin/sort", "sort", "-n", "+4", NULL);
					  perror("Failed to exec sort");
				   }
				}
				if(!found){
					perror("Process cannot be found! File cannot be created!");
				}
				
			}
		}
		
		// checking name of some alias is called.
		else if(alias_control){
			system(command);
			
		}
		// alias definition checking.
		else if(!strcmp(args[0],"alias")){
			if(!strcmp(args[0],"alias") && args[1] == NULL){
				perror("Not enough argument is entered!");
			}
			//checking argument 1 and 2 is not null to define
			else if(args[1] != NULL && args[2] != NULL && (strcmp(args[1],"-l"))){
				int i;
				char lastitem[MAX_LINE];
				char commands[MAX_LINE]= " ";
				char commands_new[MAX_LINE] = " ";
				// alias name
				for(i=0;args[i]!=NULL;i++){
					if(i!=0){
						strcpy(lastitem,args[i]);	
					}
				}
				//checking whether there is an alias with same name.
				int checking = 0;
				for(i=0;i<alias_ct;i++){
					if(!strcmp(lastitem,alias[i][1])){
						checking = 1;
						break;
					}
				}
				if(checking){
					perror("There is an alias with same name!");
				}
				else{
					
					// taking all command in the alias.
					for(i=0;args[i]!=NULL;i++){
						if(i!=0){
							if(args[i+1]==NULL){
								break;
							}
							else{
								strcat(commands,args[i]);
								strcat(commands," ");
							}
						}									
					}
					
					int ctr=0;
					int bool=0;
					// taking the command that is in the alias without ' " '.
					for(i=2;i<strlen(commands);i++){
						
						if(commands[i]=='"'){
							break;
						}
						else{
							commands_new[ctr]=commands[i];
							ctr++;
						}
					}
					// copying alias name and its command to alias matrix.
					strcpy(alias[alias_ct][0],commands_new);
					strcpy(alias[alias_ct][1],lastitem);
					alias_ct++; //increase alias counter.
				}
			}
			// checking alias -l situation.
			else if(!strcmp(args[1],"-l") && args[2]==NULL){
				int i;
				//printing all aliases.
				if(alias_ct > 0){
					for(i=0;i<alias_ct;i++){
						printf("%s %c%s%c\n",alias[i][1],'"',alias[i][0],'"');
					}
				}
				else{
					perror("No alias found!");
				}
			}
			else{
				perror("Not enough argument is entered!");
			}
		}
		//unalias part.
		else if(!strcmp(args[0],"unalias") && args[1]!=NULL){
			int i,boolJ;
			boolJ=0;
			//chceking args[1] is in alias list or not.
			for(i=0;i<alias_ct;i++){
				if(!strcmp(args[1],alias[i][1])){
					for(i; i<alias_ct; i++)
					// decreasing array one by one.	
					{
						strcpy(alias[i][0],alias[i+1][0]);
						strcpy(alias[i][1],alias[i+1][1]);
					}
					alias_ct--;
					boolJ=1;
					break;
				}
			}
			if(!boolJ){
				perror("No alias is found!");
			}
		}
		//exit situation
		else if(!strcmp(args[0],"exit")){
			break;
		}
		//process creating.
		else{
			//foreground process
			if(background == 0){
				
				char fullpath[512]; //path name
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process in the paths.
				// if it is found, then creating foreground process.
				if (found) {
					pid_t childpid;
					childpid = fork();
					if (childpid == -1) {
						perror("Failed to fork");
					  return 1;
					}
					//child code.
					if (childpid == 0) {                                      
					  execv(fullpath,&args[0]);
					  perror("Child failed to execv the command");
					  return 1;
					}
					int corpse,status;
					//parent waits until child is terminated.
					while ((corpse = wait(&status)) != -1 && corpse != childpid);
					
					
				}
				else{
					perror("Process cannot be found!");
				}
			}
			//background process.
			else{
				// & -> becomes null.
				args[ct-1] = NULL;
				
				char fullpath[512]; //pathname
				int found = findPath(args[0], fullpath, sizeof(fullpath)); //searching process.
				if (found) {
					pid_t childpid;
					childpid = fork();
					if (childpid == -1) {
						perror("Failed to fork");
					  return 1;
					}
					//child code and parent is not waiting children to terminate.
					if (childpid == 0) {	
					  execv(fullpath,args);
					  perror("Child failed to execv the command");
					  return 1;
					}
				}
				else{
					perror("Process cannot be found!");
				}
			}
		}
	}
}

