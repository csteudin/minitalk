#include "../inc/server.h"
#include <signal.h>

void handle_sig(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
	{

	}
	else if (sig == SIGUSR2)
	{

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