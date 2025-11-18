/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkieboom <rkieboom@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:33:59 by rkieboom          #+#    #+#             */
/*   Updated: 2025/11/15 23:35:24 by rkieboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_signal_data
{
	int						pid;
	char					*message;

	int						bit_value;
	int						bit_index;

	int						sender_pid;

	struct s_signal_data	*next;
	struct s_signal_data	*previous;
}							t_signal_data;

typedef int		t_bit;

t_signal_data	*get_client(t_signal_data *clients, int pid);
t_signal_data	*get_last_client(t_signal_data *clients);

t_signal_data	*add_signal_bit_to_client(t_signal_data **clients,\
	int pid, t_bit bit);
t_signal_data	*check_bits_full(t_signal_data **clients, int pid);
t_signal_data	*create_new_signal_data(t_signal_data **clients, int pid);
void			remove_signal_data(t_signal_data **clients, int pid);

#endif
