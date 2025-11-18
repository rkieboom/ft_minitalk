/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkieboom <rkieboom@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:33:55 by rkieboom          #+#    #+#             */
/*   Updated: 2025/11/18 22:51:27 by rkieboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_signal_data	*add_signal_bit_to_client\
(t_signal_data **clients, int pid, t_bit bit)
{
	t_signal_data	*client;

	if (*clients)
		client = get_client(*clients, pid);
	else
		client = NULL;
	if (!*clients || !client)
		client = create_new_signal_data(clients, pid);
	if (!client)
		return (NULL);
	if (bit)
		client->bit_value = (client->bit_value << 1) | 1;
	else
		client->bit_value = (client->bit_value << 1) | 0;
	client->bit_index++;
	return (client);
}

static t_signal_data	*add_char_to_message(t_signal_data *client)
{
	char	*tmp;
	char	buffer[2];

	buffer[0] = (char)client->bit_value;
	buffer[1] = '\0';
	if (!client->message)
		client->message = ft_strdup(buffer);
	else
	{
		tmp = client->message;
		client->message = ft_strjoin(client->message, buffer);
		if (!client->message)
			return (ft_putstr_fd("Error: Adding char to message failed\n", 2), NULL);
		free(tmp);
	}
	client->bit_value = 0;
	client->bit_index = 0;
	if (!client->message)
		return (ft_putstr_fd("Error: Adding bit to message failed\n", 2), NULL);
	return (client);
}

t_signal_data	*check_bits_full(t_signal_data **clients, int pid)
{
	t_signal_data	*client;

	client = get_client(*clients, pid);
	if (!client)
		return (ft_putstr_fd("Error: Couldn't find client\n", 2), NULL);
	if (client->bit_index == 8 && client->bit_value == 255)
	{
		if (DEBUG)
			ft_printf("Received message from PID %d: %s\n", \
client->pid, client->message);
		else
			ft_printf("%s\n", client->message);
		remove_signal_data(clients, client->pid);
	}
	else if (client->bit_index == 8)
		client = add_char_to_message(client);
	return (client);
}
