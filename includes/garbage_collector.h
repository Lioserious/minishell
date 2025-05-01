#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "libft.h"

t_list    **garbage_holder(void);
void garbage_collector_add(void *ptr);
void garbage_collector_empty(void);

#endif

