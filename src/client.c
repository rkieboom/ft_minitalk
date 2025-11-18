/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkieboom <rkieboom@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:33:44 by rkieboom          #+#    #+#             */
/*   Updated: 2025/11/18 22:39:41 by rkieboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	send_single_bit(int pid, int bit);
static int	sent_character_binary(int pid, char c);
static int	validate_pid(int pid);
static int	sent_end_message_binary(int pid);

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (validate_pid(pid) != 0)
		return (1);
	while (argv[2][i] != '\0')
	{
		if (!sent_character_binary(pid, argv[2][i]))
			return (1);
		i++;
	}
	if (!sent_end_message_binary(pid))
		return (1);
	return (0);
}

static int	send_single_bit(int pid, int bit)
{
	if (bit)
	{
		if (kill(pid, SIGUSR1) == -1)
			return (ft_putstr_fd("Error: Failed to send signal\n", 2), 1);
		if (DEBUG)
			ft_printf("1");
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			return (ft_putstr_fd("Error: Failed to send signal\n", 2), 1);
		if (DEBUG)
			ft_printf("0");
	}
	if (usleep(50) == -1)
		return (ft_putstr_fd("Error: usleep failed\n", 2), 1);
	return (0);
}

static int	sent_character_binary(int pid, char c)
{
	int	i;
	int	byte_value;

	byte_value = (int)c;
	if (byte_value < 32 || byte_value > 126)
		return (ft_putstr_fd("Error: Non-printable character found\n", 2), 1);
	if (DEBUG)
		ft_printf("Sending binary: ");
	i = 7;
	while (i >= 0)
	{
		if (!send_single_bit(pid, (byte_value >> i) & 1))
			return (1);
		i--;
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

static int	validate_pid(int pid)
{
	if (pid <= 0)
		return (ft_printf("Error: Invalid PID %d\n", pid), 1);
	if (kill(pid, 0) == -1)
		return (ft_printf("Error: No process with PID %d\n", pid), 1);
	return (0);
}

static int	sent_end_message_binary(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			return (ft_putstr_fd("Error: Failed to send signal\n", 2), 1);
		if (usleep(50) == -1)
			return (ft_putstr_fd("Error: usleep failed\n", 2), 1);
		i++;
	}
	if (DEBUG)
		ft_printf("Sent end of message signal.\n");
	return (0);
}
