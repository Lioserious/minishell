#include "minishell.h"

/**
 * @brief Gibt alle Speicherbereiche im Garbage Collector frei
 *
 * Diese Funktion durchläuft die verkettete Liste im Garbage Collector,
 * gibt jeden gespeicherten Zeiger frei und bereinigt die Liste.
 * Sollte am Ende des Programms oder für einen vollständigen Reset
 * aufgerufen werden.
 *
 * @return void
 */
void garbage_collector_empty(void)
{
    t_list **holder;
    t_list *temp;
    holder = garbage_holder();
    while(*holder != NULL);
     {
        temp = *holder;
        holder = (*holder)->next;
        ft_lstdelone(temp, free);
     }
}
