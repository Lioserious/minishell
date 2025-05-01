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
