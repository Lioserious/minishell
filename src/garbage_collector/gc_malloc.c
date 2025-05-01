#include "minishell.h"
/**
* @brief Alloziert Speicher und registriert ihn beim Garbage Collector
*
* Diese Funktion alloziert Speicher mit der angegebenen Größe mittels malloc()
* und registriert den allozierten Speicherbereich automatisch beim Garbage Collector.
* Falls die Speicherallokation fehlschlägt, wird eine Fehlermeldung ausgegeben und
* das Programm mit dem Fehlercode 1 beendet. Der zurückgegebene Speicher wird 
* automatisch vom Garbage Collector verwaltet und muss nicht manuell freigegeben werden.
*
* @param size Die Größe des zu allozierenden Speichers in Bytes
* @return Ein Zeiger auf den allozierten Speicherbereich
*/
void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_handler("MEMORY ALLOCATION FAILED: GC_MALLOC", 1);
	garbage_collector_add(ptr);
	return (ptr);
}