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

int		add_one(char c, char *message)
{
	char *tmp;
	char s[2];

	s[0] = c;
	s[1] = 0;
	if (!message)
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			return 1;
		tmp[0] = c;
		tmp[1] = 0;
	}
	else
	{
		tmp = ft_strjoin(message, s);
		if (!tmp)
			return 1;
	}
	free(message);
	message = tmp;
	return 0;
}

void signal_handler(int signum, siginfo_t *info, void *context) 
{
	static bool		malloc = true;
	static char		*message = 0;
	static int		bits = 0;
	static pid_t	pid;
	static char		c = 0xFF;
	(void)context;
	if (malloc)
	{
		ft_strdup("");
		malloc = false;
	}
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
	{
		c ^= 0x80 >> bits;
	}
	else if (signum == SIGUSR2)
	{
		c |= 0x80 >> bits;
	}
	if (++bits == 8)
	{
		if (c)
		{
			write(1, &c, 1);
			if (add_one(c, message))
			{
				free(message);
				return;
			}
		}
		else
		{
			ft_putstr_fd(message, 1);
			free(message);
		}
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		write(1, "error\n", 7);
}

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
  	struct sigaction 	s;
	sigset_t			set;
	
	if (sigemptyset(&set) < 0 || sigaddset(&set, SIGINT)< 0 || sigaddset(&set, SIGQUIT) < 0)
	{
		perror("setting signal_set failed"); 
    	exit(0); 
	}
 	s.sa_handler = 0;
	s.sa_flags = SA_SIGINFO;
	s.sa_mask = set;
	s.sa_sigaction = signal_handler;
	if(sigaction(SIGUSR1, &s, NULL) < 0 || sigaction(SIGUSR2, &s, NULL) < 0) 
	{ 
    	perror("sigaction failed"); 
    	exit(0); 
  	} 
	print_pid();
	while (1)
		pause();
	
	return 0;
}
