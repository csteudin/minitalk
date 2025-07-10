#include "../inc/client.h"

int check_input(int ac, char **av)
{	
	int i = 0;
	
	if (ac != 3)
		return (-1);
	while(av[1][i])
		if (ft_isdigit(av[1][i++]) == 0)
			return (ft_err("PID invalid", -1));
	return (0);
}

int send_sig(char current, int offset, pid_t pid)
{
	if (((current >> (7 - offset)) & 1) == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			return (ft_err("Kill failed <SIGUSR1>", -1));
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			return (ft_err("Kill failed <SIGUSR2>", -1));
	}
	return (0);
}

int transmit_message(char *msg, pid_t pid)
{
	int i;
	int offset;
	char current;

	i = 0;
	while(msg[i])
	{
		current = msg[i];
		offset = 0;
		while(offset < 8)
		{
			if (send_sig(current, offset, pid) == -1)
				return (-1);
			usleep(50);
			offset++;
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	pid_t pid;
	
	if (check_input(ac, av) == -1)
		return (ft_err("./client <PID> <MESSAGE>", 1));
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1)
		return (ft_err("The PID is not reachable !", 1));
	return (transmit_message(av[2], pid));
}