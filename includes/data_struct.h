/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:06:15 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/29 21:47:36 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "minishell.h"

# define TABLE_SIZE 100

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_var
{
	char	*key;
	void	*data;
}	t_var;

/*lst*/
size_t		lst_size(t_list *lst);
t_list		*lst_last(t_list *lst);
void		lst_add_front(t_list **alst, t_list *new_node);
void		lst_add_back(t_list **alst, t_list *new_node);

/*lst_alloc*/
t_list		*lst_new(void *content);
void		lst_del_one(t_list *node, void (*del)(void*));
void		lst_clear(t_list **lst, void (*del)(void*));
void		lst_remove(t_list **alst, t_list *node, void (*del)(void*));

/*hash_table*/
uint64_t	hash(char *key);
t_list		*table_find(t_list *table[TABLE_SIZE], char *key);
void		table_init(t_list *table[TABLE_SIZE]);
size_t		table_size(t_list *table[TABLE_SIZE]);
void		table_print(t_list *table[TABLE_SIZE]);

/*hash_table_alloc*/
t_list		*table_add(t_list *table[TABLE_SIZE], t_var *var);
void		table_remove(t_list *table[TABLE_SIZE], char *key);
void		table_clear(t_list *table[TABLE_SIZE], void (*del)(void*));

#endif