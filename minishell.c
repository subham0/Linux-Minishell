#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
char** ps_split_string(const char* str, const char* delimiter, int* count) 
{
int delimiter_len = strlen(delimiter);
int str_len = strlen(str);
// Allocate memory for the result array
char** result = (char**) malloc(sizeof(char*) * str_len);
*count = 0;
// Pointers to keep track of the current position in the input string
const char* start = str;
const char* end = strstr(start, delimiter);
while (end != NULL)
	{
	// Allocate memory for the token
	result[*count] = (char*) malloc(end - start + 1);
	// Copy the token from the input string to the result array
	memcpy(result[*count], start, end - start);
	result[*count][end - start] = '\0';
	// Increment the count and move the pointers to the next position
	(*count)++;
	start = end + delimiter_len;
	end = strstr(start, delimiter);
	}
// Add the last token to the result array
result[*count] = strdup(start);
(*count)++;
// Reallocate memory to fit the exact number of tokens
result = (char**) realloc(result, sizeof(char*) * (*count));
return result;
}
void redirection1(char input[])
{
	int count_args;
	char **args = ps_split_string(input," ", &count_args);
	char *argv[] = {};
	int m=0;
	while(m<count_args-2)
	    {
	    argv[m] = args[m];
	    //printf("\n%s",argv[m]);
	    //strip_spaces(argss[k]);
	    m++;
	    }
	argv[m] = '\0';
	pid_t pid = fork();

	if (pid == 0) 
	{
	// Child process
		//printf("\nK: %d\n",count_args-1);
		//printf("\nFileName: %s\n",args[count_args-1]);
		int output_fd = open(args[count_args-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1) 
		{
		    perror("open");
		    exit(1);
		}

		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);

		//char *argv[] = {"ls", NULL};
		execvp(argv[0], argv);

		// If execvp returns, an error occurred
		perror("execvp");
		exit(1);
	} 
	else if (pid > 0) 
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
	} 
	else 
	{
		perror("fork");
		exit(1);
	}
	
}


void  redirection2(char input[]) 
{
	int count_args;
	char **args = ps_split_string(input," ", &count_args);
	char *argv[] = {};
	int m=0;
	while(m<count_args-2)
	    {
	    argv[m] = args[m];
	    //printf("\n%s",argv[m]);
	    //strip_spaces(argss[k]);
	    m++;
	    }
	argv[m] = '\0';
	pid_t pid = fork();

	if (pid == 0) 
	{
		// Child process
		int output_fd = open(args[count_args-1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1) 
		{
		    perror("open");
		    exit(1);
		}

		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);

		//char *argv[] = {"ls", NULL};
		execvp(argv[0], argv);

		// If execvp returns, an error occurred
		perror("execvp");
		exit(1);
	}
	else if (pid > 0) 
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
	} 
	else 
	{
	perror("fork");
	exit(1);
	}

}

void redirection3(char input[]) 
{
	int count_args;
	char **args = ps_split_string(input," ", &count_args);
	char *argv[] = {};
	int m=0;
	while(m<count_args-2)
	    {
	    argv[m] = args[m];
	    //printf("\n%s",argv[m]);
	    //strip_spaces(argss[k]);
	    m++;
	    }
	argv[m] = '\0';
	pid_t pid = fork();

	if (pid == 0) 
	{
		// Child process
		int input_fd = open(args[count_args-1], O_RDONLY);
		if (input_fd == -1) 
		{
		    perror("open");
		    exit(1);
		}

		dup2(input_fd, STDIN_FILENO);
		close(input_fd);

		//char *argv[] = {"sort", NULL};
		execvp(argv[0], argv);

		// If execvp returns, an error occurred
		perror("execvp");
		exit(1);
	} 
	else if (pid > 0) 
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
	} 
	else 
	{
		perror("fork");
		exit(1);
	}

}
void background_processing(char input[])
{
	int count_args;
	char **args = ps_split_string(input," ", &count_args);
	char *argv[] = {};
	int m=0;
	while(m<count_args-1)
	    {
	    argv[m] = args[m];
	    //printf("\n%s",argv[m]);
	    //strip_spaces(argss[k]);
	    m++;
	    }
	argv[m] = '\0';
	pid_t pid = fork();
	if (pid == 0) 
	{
		// Child process
		//char *argv[] = {"sleep", "10", NULL};
		execvp(argv[0], argv);

		// If execvp returns, an error occurred
		perror("execvp");
		exit(1);
	}
	else if (pid > 0) 
	{
	// Parent process
		//printf("Child process with PID %d is running in the background.\n", pid);
	} 
	else
	{
		perror("fork");
		exit(1);
	}
}
void __stack_chk_fail() {
    //printf("Stack smashing detected.\n");
    exit(1);
}
void handler(int sig) 
{
    printf("Caught segmentation fault (signal %d).\n", sig);
    exit(1);
}

/*int main() {
    signal(SIGSEGV, sigsegv_handler);

    // The following line will cause a segmentation fault
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}*/

//int num_commands;	
//char *commands_arguments_array[6][7] = {0};
//int condition_index;
//char *conditions[5] = {0};
//char *delimiters[] = {0};
//char *delimiters[];
int check_all_zero_occurrences(int *occurrence)
{
	int all_occurrence_zero = 0;
	for(int i = 0;i< 8;i++)
	{
		if(occurrence[i]==0)
		{
			continue;
		}
		else
		{
			all_occurrence_zero = 1;
			break;
		}
	}
	//printf("\nALL ZERO: %d\n",all_occurrence_zero);
	return(all_occurrence_zero);
}
int check_multiple_presence(int *occurrence)
{
	int pos1=0,pos2=0;
	int count=0;
	int multiple_flag=0;
	/*for(int i = 0; i < 8; i++)
	{
		if(i==5)
		{
			continue;
		}
		else if(occurrence[i]>0)
		{
			count++;
			if(count==2)
			{
				multiple_flag = 1;
				break;
			}
		}
	}*/
	for(int i = 0; i < 8; i++)
	{
		if(occurrence[i]>0)
		{
			count++;
			if(count==1)
			{
				pos1=i;
			}
			if(count==2)
			{
				pos2=i;
			}
			
		}
	}
	if(count==2)
	{
		if(pos1==3 && pos2==5)
			multiple_flag = 0;
		else
			multiple_flag = 1;
	}
	else if(count>2)
	{
		multiple_flag = 1;
	}
	//printf("\nMultiple Flag: %d\n",multiple_flag);
	return multiple_flag;
}


int check_others_presence(int *occurrence, int delimeter_index)
{
	int other_flag=0;
	char *all_delimiters[] = {">>", ">", "<", "||", "|", "&&", "&", ";"};
	for (int i = 0; i < 8; i++) 
	{
		if(i != delimeter_index)
		{
			if(occurrence[i] > 0)
			{
				other_flag=1;
				break;
			}
		}
	}
	return other_flag;
}
void find_occurrence(char *str, int *occurrence, char *delimiters[]) 
{
	int i, j, length, delim_length;
	int delimiter_found;
	int num_delimiters = 8;
	length = strlen(str);

	for (i = 0; i < length; i++) 
	{
		delimiter_found = 0;
		for (j = 0; j < num_delimiters; j++) 
		{
			delim_length = strlen(delimiters[j]);
			if (strncmp(str + i, delimiters[j], delim_length) == 0) 
			{
				occurrence[j]++;
				i = i + delim_length - 1;
				delimiter_found = 1;
				break;
			}
		}
		if (delimiter_found) 
		{
			continue;
		}
	}
}
void strip_spaces(char* str) 
{
	int len = strlen(str);
	int i = 0, j = len - 1;

	// Strip spaces from the start of the string
	while (i < len && isspace(str[i])) 
	{
	i++;
	}

	// Strip spaces from the end of the string
	while (j >= 0 && isspace(str[j])) 
	{
	j--;
	}

	// Shift the characters to the start of the string
	int k = 0;
	for (int m = i; m <= j; m++) 
	{
	str[k++] = str[m];
	}

	// Add a null terminator to the end of the string
	str[k] = '\0';
}
void split_string(char *str, char *delimiters[], int num_delimiters, char ***output, int *num_splits) 
{
	int i, j, k, length, delim_length;
	int delimiter_found;
	length = strlen(str);
	*num_splits = 0;

	for (i = 0; i < length; i++) 
	{
		delimiter_found = 0;
		for (j = 0; j < num_delimiters; j++) 
		{
			delim_length = strlen(delimiters[j]);
			k = 0;
			while (str[i + k] == delimiters[j][k] && k < delim_length) 
			{
				k++;
			}
			if (k == delim_length) 
			{
				str[i] = '\0';
				*output = (char**)realloc(*output, ((*num_splits) + 1) * sizeof(char*));
				(*output)[*num_splits] = strdup(str);
				strip_spaces((*output)[*num_splits]);
				(*num_splits)++;
				str = str + i + delim_length;
				i = -1;
				length = strlen(str);
				delimiter_found = 1;
				break;
			}
		}
		if (delimiter_found) 
		{
			continue;
		}
	}
	*output = (char**)realloc(*output, ((*num_splits) + 1) * sizeof(char*));
	(*output)[*num_splits] = strdup(str);
	strip_spaces((*output)[*num_splits]);
	(*num_splits)++;
}

int get_commands_arguments(char input[],char *delimiters[],int no_of_delimiters,int *num_commands,char *commands_arguments_array[6][7])
{
	int return_flag=0;
	//char *commands_arguments_array[6][7] = {0};
	char **commands = NULL;
	*num_commands = 0;
	split_string(input, delimiters, no_of_delimiters, &commands, num_commands);
	//printf("\nNUM COMMANDS: %d\n",*num_commands);
	for (int i = 0; i < *num_commands; i++) 
	{
		char *argument_delimiters[] = {" "};
		char **arguments = NULL;
		int num_argument = 0;
		//printf("\nH1\n");
		split_string(commands[i], argument_delimiters, 1, &arguments, &num_argument);
		//printf("\nH2\n");
		//printf("\nNum Argument: %d\n",num_argument);
		if(num_argument>=1 && num_argument<=6)
		{
			/*for(int j=0 ;j< num_argument+1;j++)
			{
				//strcpy(commands_arguments_array[i][j],arguments[j]);
				commands_arguments_array[i][j] = arguments[j];
				//printf("\nArg[%d]: %s\n",j,arguments[j]);
				//printf("\nArg[%d]: %s\n",j,commands_arguments_array[i][j]);
			}*/
		}
		else
		{
			*num_commands=0;
			printf("\nError: Argc of Command: %s is %d\n",commands[i],num_argument);
			return_flag = 1;
			break;
			//return(1);	
		}
	}
	return(return_flag);
}
void get_conditions(char input_string[],char *conditions[5],int *condition_index)
{
	int k=0;
	int i;
	for (i = 0; i < strlen(input_string); i++) 
		{
			if (input_string[i] == '&' && input_string[i+1] == '&') 
			{
				//printf("\n&& %d\n",k);
				conditions[k++] = "&&";
			} 
			else if (input_string[i] == '|' && input_string[i+1] == '|') 
			{
				//printf("\n|| %d\n",k);
				conditions[k++] = "||";
			} 				
		}	
	*condition_index=k;
}
void print_command_arguments(int num_commands, char *commands_arguments_array[6][7])
{
printf("\nNum Commands: %d\n",num_commands);
for(int i=0;i<num_commands;i++)
	{
	int j=0;
	printf("\nCommand %d:\n",i+1);
	while(j<7)
		{
			printf("\nArg[%d]: %s\n",j,commands_arguments_array[i][j]);
			j++;
		}
	printf("\n");
	}	
}
void print_conditions(int condition_index,char *conditions[5])
{
printf("\nCondition Index:%d\n",condition_index);
for(int i=0;i<condition_index;i++)
	{
		printf("\nCondtion %d: %s\n",i+1,conditions[i]);
	}
}
void execute_standalone(char input[])
{
	char buf[200];
        FILE *ptr;

        if ((ptr = popen(input, "r")) != NULL) 
        {
                while (fgets(buf, 200, ptr) != NULL)
                        (void) printf("%s", buf);
                (void) pclose(ptr);
        }

}

void npipes(char input_string[])
{
strip_spaces(input_string);
const char delimiter[] = "|";
int count;
char** tokens = ps_split_string(input_string, delimiter, &count);
int fd[2];
int prev_fd = 0;
for (int i = 0; i < count; i++) 
{
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) 
		{
		    // Child process
		    dup2(prev_fd, 0);
		    if (i < count - 1) 
			    {
				dup2(fd[1], 1);
			    }
		    close(fd[0]);
		    int count_args;
		    strip_spaces(tokens[i]);
		    char **args = ps_split_string(tokens[i]," ", &count_args);
		    char *argss[] = {};
		    int k=0;
		    while(k<count_args)
			    {
			    argss[k] = args[k];
			    strip_spaces(argss[k]);
			    k++;
			    }
		    argss[k] = '\0';
		    execvp(args[0], argss);     
		    perror("\nExecvp Failed\n");
		    _exit(1);
		} 
	else 
		{
		    // Parent process		    
		    wait(NULL);
		    close(fd[1]);
		    prev_fd = fd[0];
		}
}
}
void nsequential_executions(char input_string[])
{
strip_spaces(input_string);
const char delimiter[] = ";";
int count;
pid_t pid;
char** tokens = ps_split_string(input_string, delimiter, &count);
for (int i = 0; i < count; i++) 
{
	int count_args;
	strip_spaces(tokens[i]);
	char **args = ps_split_string(tokens[i]," ", &count_args);
	char *argss[] = {};
	int k=0;
	while(k<count_args)
	    {
	    argss[k] = args[k];
	    strip_spaces(argss[k]);
	    k++;
	    }
	argss[k] = '\0';
	pid = fork();
	if (pid < 0) 
	{
		perror("\nFork failed\n");
		_exit(1);
	} 
	else if (pid == 0) 
	{
		execvp(args[0], argss);
		perror("\nExecvp Failed\n");
		_exit(1);
	} 
	else 
	{
		int status;
		waitpid(pid, &status, 0);
		//wait(NULL);
	}
}
}

int execute_command(char *args[]) 
{
//for(int i=0;i<7;i++)
//{
//printf("\nARGS[%d]: %s\n",args[i]);
//}
pid_t pid = fork();
int status;
if (pid == 0) 
{
	execvp(args[0], args);
	perror("\nExecvp Failed\n");
	_exit(1);
} 
else if (pid > 0) 
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) 
	{
	    //printf("\nSTAT %d\n", WEXITSTATUS(status));
	    return WEXITSTATUS(status);
	}
} 
else 
{
	perror("\nFork Failed\n");
}
return -1;
}

void nconditional_executions(char input[], char *conditions[5])
{
char **commands = NULL;
int num_commands = 0;
char *delimiters[] = {"||","&&"};
split_string(input, delimiters, 2, &commands, &num_commands);
//printf("\nNUM COMMANDS: %d\n",*num_commands);
int last_status = 0;
int k=-1;
for (int i = 0; i <num_commands; i++) 
{
	//printf("\ni:%d\n",i);
	char *argument_delimiters[] = {" "};
	char **arguments = NULL;
	int num_argument = 0;
	split_string(commands[i], argument_delimiters, 1, &arguments, &num_argument);
	//printf("\nNum Argument: %d\n",num_argument);
	if(i==0)
	{
	last_status = execute_command(arguments);
	//printf("\ni:%d Last Status %d\n",i,last_status);
	}
	else if(i>0)
	{
		k++;
		//printf("\nk:%d\n",k);
		//printf("\nCondition: %s\n",conditions[k]);
		if (strcmp(conditions[k], "&&") == 0) 
		{
		    //printf("\nAnd\n");
		    if (last_status == 0) 
		    {
			last_status = execute_command(arguments);
			//printf("\ni:%d Last Status %d\n",i,last_status);
		    } 
		    else 
		    {
			last_status = 1;
			//printf("\ni:%d Last Status %d\n",i,last_status);
			continue;
		    }
		} 
		else if (strcmp(conditions[k], "||") == 0) 
		{
		    //printf("\nOR\n");
		    if (last_status == 0) 
		    {
			last_status = 1;
			//printf("\ni:%d Last Status %d\n",i,last_status);
			continue;
		    } 
		    else 
		    {
			last_status = execute_command(arguments);
			//printf("\ni:%d Last Status %d\n",i,last_status);
		    }
		} 
	}
	//printf("\ni:%d Last Status %d\n",i,last_status);

}
}

int main() {
	//signal(SIGSEGV, handler);
	umask(0000);
	while (1) 
	{
        char input[200];
        //printf("\nEnter a string: \n");
        fgets(input, 200, stdin);
        // Removing the newline character from the input string
        input[strcspn(input, "\n")] = 0;
        //printf("\nYou entered: %s\n", input);
        
        char *all_delimiters[] = {">>", ">", "<", "||", "|", "&&", "&", ";"};
	int occurrence[8] = {0};
	int chk_oth_pres = -1;
	int delim_count=-1;
	find_occurrence(input, occurrence,all_delimiters);
	if(check_multiple_presence(occurrence)==1)
	{
		printf("\nEntered Command Contains Combination of  >> > < || | && & ; Special Characters together. Hence unable to process\n");
		continue;
	}
	int conditional_execution_flag=1;
	int num_commands;	
	char *commands_arguments_array[6][7] = {0};
	int condition_index;
	char *conditions[5] = {0};
	for (int i = 0; i < 8; i++) 
	{	
		if(i!=3 && i!=5)
		{
		//printf("\nOccurrence of %s: %d\n", all_delimiters[i], occurrence[i]);
		//printf("\nPresence Other Flag %d\n",check_others_presence(occurrence,i));
		//printf("\n");
		chk_oth_pres = check_others_presence(occurrence,i);
		if(strcmp(all_delimiters[i],">>")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i]==1)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d  >> redirection operation\n",occurrence[i]);
				pid_t pid = fork();
				if (pid == 0) 
				{
				  //Child process
				   redirection2(input);
				   exit(0);
				} 
				else if (pid > 0) 
				{
				  // Parent process
				  int status;
				  waitpid(pid, &status, 0);
				  if (WIFSIGNALED(status)) 
				  	{
				    		//printf("Child process terminated due to stack smashing, but main function continues.\n");
					}
				} 
				else 
				{
					perror("fork");
					exit(1);
				}
				}
				else
				{
				execute_standalone(input);
				}
				break;
			}
			else
			{
			printf("\nEntered Command Contains %d  >> redirection operation which is greater than 1. Hence unable to process \n",occurrence[i]);
			break;
			}
			
		}
		else if(strcmp(all_delimiters[i],">")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i]==1)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d  > redirection operation\n",occurrence[i]);
				pid_t pid = fork();
				if (pid == 0) 
				{
				  //Child process
				   redirection1(input);
				   exit(0);
				} 
				else if (pid > 0) 
				{
				  // Parent process
				  int status;
				  waitpid(pid, &status, 0);
				  if (WIFSIGNALED(status)) 
				  	{
				    		//printf("Child process terminated due to stack smashing, but main function continues.\n");
					}
				} 
				else 
				{
					perror("fork");
					exit(1);
				}
				}
				else
				{
				execute_standalone(input);
				}
				break;
			}
			else
			{
			printf("\nEntered Command Contains %d  > redirection operation which is greater than 1. Hence unable to process \n",occurrence[i]);
			break;
			}
			
		}
		else if(strcmp(all_delimiters[i],"<")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i] == 1)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d  < redirection operation\n",occurrence[i]);
				pid_t pid = fork();
				if (pid == 0) 
				{
				  //Child process
				   redirection3(input);
				   exit(0);
				} 
				else if (pid > 0) 
				{
				  // Parent process
				  int status;
				  waitpid(pid, &status, 0);
				  if (WIFSIGNALED(status)) 
				  	{
				    		//printf("Child process terminated due to stack smashing, but main function continues.\n");
					}
				} 
				else 
				{
					perror("fork");
					exit(1);
				}
				}
				else
				{
				execute_standalone(input);
				}	
				break;
			}
			else
			{
			printf("\nEntered Command Contains %d  < redirection operation which is greater than 1. Hence unable to process \n",occurrence[i]);
			break;
			}
			
		}
		else if(strcmp(all_delimiters[i],"&")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i]==1)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d  background processing operation.\n",occurrence[i]);
				pid_t pid = fork();
				if (pid == 0) 
				{
				  //Child process
				   background_processing(input);
				   exit(0);
				} 
				else if (pid > 0) 
				{
				  // Parent process
				  int status;
				  waitpid(pid, &status, 0);
				  if (WIFSIGNALED(status)) 
				  	{
				    		//printf("Child process terminated due to stack smashing, but main function continues.\n");
					}
				} 
				else 
				{
					perror("fork");
					exit(1);
				}
				}
				else
				{
				execute_standalone(input);
				}
				break;
			}
			else
			{
			printf("\nEntered Command Contains %d  background processing operation which is greater than 1. Hence unable to process \n",occurrence[i]);
			break;
			}
			
		}
		else if(strcmp(all_delimiters[i],"|")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i]>=1 && occurrence[i]<=5)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d pipes which is between 1 and 5\n",occurrence[i]);
				char *delimiters[] = {"|"};
				if(get_commands_arguments(strdup(input),delimiters,1,&num_commands,commands_arguments_array)==0)
				{
					npipes(input);
				}
				}
				else
				{
				execute_standalone(input);
				}
				break;
			}
			else
			{
				printf("\nEntered Command Contains %d pipes which is not between 1 and 5. Hence unable to process.\n",occurrence[i]);
				break;
			}
		}
		else if(strcmp(all_delimiters[i],";")==0 && occurrence[i]>0 && chk_oth_pres==0)
		{
			conditional_execution_flag=0;
			if(occurrence[i]>=1 && occurrence[i]<=5)
			{
				if (strchr(input, '~') == NULL)
				{
				//printf("\nEntered Command Contains %d sequential execution which is between 1 and 5\n",occurrence[i]);
				char *delimiters[] = {";"};
				if(get_commands_arguments(strdup(input),delimiters,1,&num_commands,commands_arguments_array)==0)
				{
					pid_t pid = fork();
					if (pid == 0) 
					{
					  //Child process
					   nsequential_executions(input);
					   exit(0);
				        } 
				        else if (pid > 0) 
				        {
					  // Parent process
					  int status;
					  waitpid(pid, &status, 0);
					  if (WIFSIGNALED(status)) {
					    //printf("Child process terminated due to stack smashing, but main function continues.\n");
					                           }
				        } 
				        else 
				        {
						perror("fork");
						exit(1);
				        }
					//nsequential_executions(input);
				}
				}
				else
				{
				execute_standalone(input);
				}
				break;
			}
			else
			{
				printf("\nEntered Command Contains %d sequential execution which is not between 1 and 5. Hence unable to process.\n",occurrence[i]);
				break;
			}
		}
		}
		
	}
	if(conditional_execution_flag==1 && (occurrence[3] > 0 || occurrence[5] > 0))
	{
		if(occurrence[3]+occurrence[5]>=1 && occurrence[3]+occurrence[5]<=5)
		{
			if (strchr(input, '~') == NULL)
			{
			//printf("\nEntered Command Contains %d || and %d && conditional execution whose sum is between 1 and 5\n",occurrence[3],occurrence[5]);
			char *delimiters[] = {"||","&&"};
			if(get_commands_arguments(strdup(input),delimiters,2,&num_commands,commands_arguments_array)==0)
			{
				//code for calling conditional execution function
				//print_command_arguments(num_commands,commands_arguments_array);
				get_conditions(input,conditions,&condition_index);
				nconditional_executions(input,conditions);
				//print_conditions(condition_index,conditions);
			}
			}
			else
			{
			execute_standalone(input);
			}
		}
		else
		{
			printf("\nEntered Command Contains %d || and %d && conditional execution whose sum is not between 1 and 5. . Hence unable to process.\n",occurrence[3],occurrence[5]);
		}
	}
	else if(check_all_zero_occurrences(occurrence)==0)
	{
		//printf("\nH1\n");
		char *argument_delimiters[] = {" "};
		char **arguments = NULL;
		int num_argument = 0;
		//printf("\nH1\n");
		split_string(strdup(input), argument_delimiters, 1, &arguments, &num_argument);
		//printf("\nNUM ARGUMENT: %d\n",num_argument);
		if(num_argument>=1 && num_argument<=6)
		{
			execute_standalone(input);
		}
		else
		{
			printf("\nError: Argc of Command: %s is %d\n",input,num_argument);	
		}
		//printf("\nH2\n");
	}
	//printf("\nH3\n");
    	}
	return 0;
}

