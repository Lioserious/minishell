#include "minishell.h"

/**
 * @brief Gibt Zugriff auf den internen Garbage Collector Speicher
 * 
 * Diese Funktion liefert einen Zeiger auf die statische Liste,
 * die alle Speicheradressen im Garbage Collector verwaltet.
 * Sie wird intern von anderen GC-Funktionen verwendet.
 * 
 * @return Zeiger auf die Liste der verwalteten Speicherbereiche
 */
t_list **garbage_holder(void)
{
    static t_list *ptr = NULL;
    return (&ptr);
}

/**
 * @brief Fügt einen Speicherbereich zum Garbage Collector hinzu
 * 
 * Diese Funktion registriert einen dynamisch allozierten Speicherbereich
 * im Garbage Collector, damit er später automatisch freigegeben werden kann.
 * 
 * @param ptr Der zu verwaltende Speicherbereich (von malloc, calloc, etc.)
 */
void garbage_collector_add(void *ptr)
{
    t_list *neu;
    neu = ft_lstnew(ptr);
    if(!neu)
        error_handler("MEMORY ALLOCATION FAILED: GARBAGE COLLECTOR", 2);
    ft_lstadd_front(garbage_holder(), neu);
}

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
