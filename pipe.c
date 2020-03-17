#include  <fcntl.h>                              
#include  <stdio.h>                              
#include  <stdlib.h>                             
#include  <string.h>                             
#include  <sys/types.h>                          
#include  <sys/wait.h>                           
#include  <sys/stat.h>                           
#include  <termios.h>                            
#include  <unistd.h>                             

#define INPUT_END 1                              
#define OUTPUT_END 0                             
                                                 
int main(int argc, char* argv[])                 
{                                                
    pid_t pid1;                                  
    pid_t pid2;                                  
    int fd[2];                                   

    pipe(fd);                                    
    printf("comand exec ls-l | grep a* \n") ;   

    if (fork() == 0)
    {  
        close(fd[INPUT_END]);                    
        dup2(fd[OUTPUT_END], STDIN_FILENO);
        close(fd[OUTPUT_END]);                   
        execlp("cut", "cut", "-d"," ","-f9",(char*) NULL);   
    }                                            
    else                                         
    {                                            

        if (fork() == 0)                             
        {                                        
            close(fd[OUTPUT_END]);               
            dup2(fd[INPUT_END], STDOUT_FILENO);  
            close(fd[INPUT_END]);                
            execlp("ls","ls","-l",(char*) NULL); 
        }                                        
       
        close(fd[OUTPUT_END]);                   
        close(fd[INPUT_END]);                    
        waitpid(-1, NULL, 0);                    
        waitpid(-1, NULL, 0);                    
      
    }                                            
}      
