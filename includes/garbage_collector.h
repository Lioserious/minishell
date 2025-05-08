/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:43 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/08 16:19:35 by mimalek          ###   ########.fr       */
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
char	*gc_readline(const char *prompt);
char	*gc_strdup(const char *s);
char	*gc_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**gc_split(const char *s, char c);

#endif
