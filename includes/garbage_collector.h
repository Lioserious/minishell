/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:43 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:02:24 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "libft.h"

t_list	**garbage_holder(void);
void	garbage_collector_add(void *ptr);
void	garbage_collector_empty(void);
void	garbage_collector_print(void);
void	*gc_malloc(size_t size);

#endif
