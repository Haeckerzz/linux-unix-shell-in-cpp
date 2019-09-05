#include<stdio.h>
#include<string>
#include <unistd.h> 
#include<ctype.h>
#include<vector>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include <fcntl.h>
#include  <sys/types.h>
#include <sys/wait.h>

using namespace std;
char gpwd()
{
	char buff[1000];

	if (getcwd(buff, sizeof(buff)) != NULL)
		printf("%s",buff);
	else
		perror("Error:");
		
}
void phist()
{
	printf("In history");
	ifstream in ("history.txt");
	int n=1;
	string s;   
	if (in.is_open())
	{
		while (! in.eof() )
		{
			getline (in,s);
			cout<<endl;
			cout<<n<<". "<<s<<"\n";
			n++;
		}
        in.close();
	}
}
void writehist(char arr[])
{
	ifstream in ("history.txt");
	vector<string> v;
	int ch,n=0;
	string s;   
	if (in.is_open())
	{
		while (! in.eof() )
		{
			getline (in,s);
		    v.push_back(s);
			n++;
		}
        in.close();
	}
	v.push_back(arr);
	if(n>=15) 
	{
		ofstream out("temp.txt",std::fstream::out | std::fstream::app);
        if (out.is_open())
		{
		    for(int i=1;i<n;i++)
			{
			
				out<<v[i];
				out<<"\n";
		 	}	
		    out << v[n];
	        out.close();
		}
		else
		{
			perror("\nFile not opened");
		}
	 	    remove("history.txt");
            rename( "temp.txt","history.txt");
	}
	else
	{
		ofstream out("history.txt",std::fstream::out | std::fstream::app);
        if (out.is_open())
		{
			out << v[n];
			out << "\n";
			out.close();
		}
	}
}

int process(char arr[])
{
	    char ext[100];
	    strcpy(ext,arr);
    //Internal Commands
		if(strcmp(arr,"pwd")==0) // pwd
		{
			gpwd();
			return 0;
		}
		if(strcmp(arr,"history")==0) //only history
		{
			phist();
			return 0;
		}
		char *start = strtok(arr," ");
		if(strcmp(start,"cd")==0) // cd
		{
			
			char *path=strtok(NULL," ");
			int ret=chdir(path);
			if(ret==-1)
				perror("Error");
			return 0;
		}
		    if(strcmp(start,"echo")==0)
		{
			
			char *name=strtok(NULL," ");
		
			printf("\n");
			while(name!=NULL)
				{
					printf("%s ",name);
					name = strtok(NULL," ");
				}
			
			return 0;
		}
	        if(strcmp(start,"history")==0)
		{
		
			phist();
			return 0;
		}
		
		//external command here:
		char *args[60];
    	char **next = args;
		char *temp = strtok(ext, " ");
		while (temp != NULL)
		{
			*next++ = temp;
			printf("%s\n", temp);
			temp = strtok(NULL, " ");
		}
		*next = NULL;
	    pid_t pid;
		int s; 
            if ((pid = fork()) < 0) 
		{
			perror("Error in Forking ");
		}
            else if (pid == 0)  
		{
			if (execvp(args[0],args) < 0) 
			{
				perror("Error in Execution");
				
			}
			exit(0);
		}
		else
		{  
			while (wait(&s) != pid);
			
		}
		return 0;
}

int startprocess(char arr[], int i)
{
	   	char cpy[100];
	    strcpy(cpy,arr);
	    char cmd[100] = "";
		char *tok = strtok(cpy," ");
		while(tok!=NULL)
		{
				strcat(cmd,tok);
				strcat(cmd," ");
		    	tok  = strtok(NULL," ");
		}
	    int ret = process(cmd+i);
		if(ret==-1)
		{
			printf("breaking");
				return -1;
		}
	return 0;
}

int main()
{
	char arr[50];
	char *p;
	while(1)
	{
		printf("\nSHELL");
		gpwd();
		printf("$");
		fgets(arr, sizeof(arr), stdin);
		if ((p = strchr(arr, '\n')) != NULL)
			*p = '\0';
		int i=0;
	    for (i = 0; isspace(arr[i]); ++i) ;
		if(strcmp(arr+i,"")==0)
		    continue;
		if(strstr(arr,"!")==NULL)           
			writehist(arr+i); 
		if(strcmp(arr+i,"exit")==0) 
	     	{   
	     	    printf("bubye..\n");
	     		break;
	     	}	
	    int ret1 = startprocess(arr,i);
	    if(ret1==-1)
	       break;
	}
}