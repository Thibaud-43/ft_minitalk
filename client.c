#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <libft.h>
#include <unistd.h>

#include<stdio.h>

int main(int argc, char const *argv[])
{
	pid_t	server_pid;
	if (argc != 3)
		write(1, "./client [server PID] [string to send]", 38);
	server_pid = ft_atoi(argv[1]);
	printf("sending signals to pid : %d\n", server_pid);
	kill(server_pid, SIGUSR1);

	return 0;
}
