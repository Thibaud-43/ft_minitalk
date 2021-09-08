#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <libft.h>
#include <unistd.h>

#include<stdio.h>

void	error(char *str)
{
	(void)str;
}

int	send_end(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(str);
		return (0);
	}
	return (1);
}

int	send_message(pid_t server_pid, char *string)
{
	static char	*message = 0;
	static int	s_pid = 0;
	static int	bits = -1;

	if (string)
		message = ft_strdup(string);
	if (!message)
		error(0);
	if (server_pid)
		s_pid = server_pid;
	if (message[++bits / 8])
	{
		if (message[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(s_pid, SIGUSR2) == -1)
				error(message);
		}
		else if (kill(s_pid, SIGUSR1) == -1)
			error(message);
		return (0);
	}
	if (!send_end(s_pid, message))
		return (0);
	free(message);
	return (1);
}

void	handler_sigusr(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_message(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd( "client: server ended unexpectdly.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_putstr_fd( "client: operation successful.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char  *argv[])
{
	pid_t	server_pid;
	if (argc != 3 /*|| !ft_isnum(argv[1])*/)
		return write(1, "./client [server PID] [string to send]", 38);
	server_pid = ft_atoi(argv[1]);

	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);

	printf("sending message to pid : %d\n", server_pid);
	send_message(server_pid, argv[2]);
	while(1)
		pause();
	return 0;
}
