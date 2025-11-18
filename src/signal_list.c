/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkieboom <rkieboom@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:00:00 by rkieboom          #+#    #+#             */
/*   Updated: 2025/11/18 22:06:51 by rkieboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_signal_data	*get_client(t_signal_data *clients, int pid)
{
	t_signal_data	*current;

	current = clients;
	while (current != NULL)
	{
		if (current->pid == pid)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_signal_data	*get_last_client(t_signal_data *clients)
{
	t_signal_data	*current;

	current = clients;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

t_signal_data	*create_new_signal_data(t_signal_data **clients, int pid)
{
	t_signal_data	*client;
	t_signal_data	*last;

	client = ft_calloc(1, sizeof(t_signal_data));
	if (!client)
		return (ft_putstr_fd("Error: Creating signal data\n", 2), NULL);
	client->pid = pid;
	if (!*clients)
		*clients = client;
	else
	{
		last = get_last_client(*clients);
		client->previous = last;
		last->next = client;
	}
	if (DEBUG)
		ft_printf("Creating new client with PID: %d\n", client->pid);
	return (client);
}

void	remove_signal_data(t_signal_data **clients, int pid)
{
	t_signal_data	*client;

	if (!*clients)
		return ;
	client = get_client(*clients, pid);
	if (!client)
		return ;
	if (client->previous)
		client->previous->next = client->next;
	else
		*clients = client->next;
	if (client->next)
		client->next->previous = client->previous;
	if (DEBUG)
		ft_printf("Removing client with PID: %d\n", client->pid);
	free(client->message);
	free(client);
}
