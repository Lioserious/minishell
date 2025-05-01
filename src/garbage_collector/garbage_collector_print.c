#include "minishell.h"

/**
 * @brief Zeigt Informationen über alle verwalteten Speicherbereiche an
 * 
 * Diese Funktion gibt Debugging-Informationen über alle im
 * Garbage Collector verwalteten Speicherbereiche aus.
 * Nützlich zur Fehlersuche bei Speicherproblemen und zum Überprüfen
 * des Inhalts der verwalteten Speicherbereiche.
 */
void garbage_collector_print(void)
{
    t_list *temp;
    size_t i;
    temp = *garbage_holder();
    i = 0;
    while (temp != NULL)
     {
        printf("Pointer %zu: %p, %s\n", i, temp->content, (char *)temp->content);
        temp = temp->next;
        i++;
     }
}
