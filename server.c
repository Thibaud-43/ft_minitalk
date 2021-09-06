#include <stdbool.h> 
#include <sys/wait.h>
#include <libft.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

bool end = false;

void	print_pid(void)
{
	pid_t	server_pid;
	server_pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr_fd(server_pid, 1);
	write(1, "\n", 1);

}

void signal_handler(int signo) { 
  printf("Received: signal %d\n", signo);
  end = true; 
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
  	struct sigaction s; 
 	 s.sa_handler = signal_handler; 
	print_pid();
	while (!end)
	{
 		int retval = sigaction(SIGUSR1, &s, NULL); 
  		if(retval < 0) { 
    		perror("sigaction failed"); 
    		exit(0); 
  		} 
		
	}
	
	return 0;
}
