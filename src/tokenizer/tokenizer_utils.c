/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 21:21:21 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new token list
 * @return Pointer to initialized token list
 */
t_token_list	*create_token_list(void)
{
	t_token_list	*new_list;

	new_list = (t_token_list *)gc_malloc(sizeof(t_token_list));
	if (!new_list)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN_LIST", 1);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

/**
 * @brief Creates a new token with specified type and value
 * @param type Token type
 * @param value Token string value
 * @return Pointer to the created token
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)gc_malloc(sizeof(t_token));
	if (!new_token)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN", 1);
	new_token->type = type;
	new_token->value = gc_strdup(value);
	if (!new_token->value)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN", 1);
	new_token->next = NULL;
	return (new_token);
}

/**
 * @brief Adds a token to the end of a token list
 * @param list Target token list
 * @param token Token to add
 */
void	add_token_to_list(t_token_list *list, t_token *token)
{
	if (!list || !token)
		return ;
	if (list->size == 0)
	{
		list->head = token;
		list->tail = token;
	}
	else
	{
		list->tail->next = token;
		list->tail = token;
	}
	list->size++;
}

/**
 * @brief Initialisiert Basis-Parameter der Quote-Parser-Struktur
 * @param parser Zu initialisierende Struktur
 * @param input Eingabestring
 * @param i_ptr Zeiger auf aktuelle Position
 * @param result Zeiger auf Ergebnisstring
 */
void	init_quote_parser_base(t_quote_parser *parser, char *input, int *i_ptr,
		char **result)
{
	parser->input = input;
	parser->i_ptr = i_ptr;
	parser->result = result;
	parser->start_ptr = NULL;
	parser->env_list = NULL;
}

/**
 * @brief Vervollständigt Quote-Parser-Struktur mit zusätzlichen Parametern
 * @param parser Zu ergänzende Struktur
 * @param start_ptr Zeiger auf Startposition
 * @param env_list Umgebungsvariablen-Liste
 */
void	complete_quote_parser(t_quote_parser *parser, int *start_ptr,
		t_env_list *env_list)
{
	parser->start_ptr = start_ptr;
	parser->env_list = env_list;
}
