#include "../inc/server.h"
#include <signal.h>
#include <stdint.h>

/*
* - we initalize the char as 00000000.
* - we shift it every time we get a signal.
* - if it is a 1 we put it, else we dont.
* - when the char is fully read, we print it.
* - lastly, we reset the char.
*/
void handle_sig(int sig, siginfo_t *info, void *context)
{
	static int count = 0;
	static char current = 0;

	(void)context;
	(void)info;
	current <<= 1; 
	count++;	
	if (sig == SIGUSR2)
		current |= 1;
	if (count == 8)
	{
		write(1, &current, 1);
		if (current == '\0')
			write(1, "\n", 1);
		count = 0;
		current = 0;	
	}
}

int set_signals(void)
{
	struct sigaction sig_act;

	sig_act.sa_sigaction = &handle_sig;
	sig_act.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_act.sa_mask);
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);

	return (0);
}

int main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		return (ft_err("Please use without arguments", 1));

	if (set_signals() == 1)
		return (ft_err("set_signals failed", 1));
	ft_printf("set_signals succesfully initalized\n");
	ft_printf("Server PID: %d\n", getpid());
	
	while(1 != 11)
		pause();
	
	return 0;
}