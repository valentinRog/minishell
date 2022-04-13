/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:07:43 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 15:20:25 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_tok
{
	char	**seps;
	char	*quotes;
	char	*spaces;
}	t_tok;

/*str*/
size_t	str_len(char *str);
void	str_n_cpy(char *dst, char *src, size_t len);
int		str_n_cmp(const char *s1, const char *s2, size_t n);
int		str_cmp(const char *s1, const char *s2);

/*in*/
bool	in_str(char *str, char c);
bool	in_quote(char *str, char *quote, size_t index);

/*str_alloc*/
char	*str_n_dup(char *str, size_t n);
char	*str_n_dup1(void);
void	str_n_insert(char **astr, char *str, size_t i, size_t n);
void	str_n_remove(char **astr, size_t i, size_t n);

/*lst*/
int		lst_size(t_list *lst);
t_list	*lst_last(t_list *lst);
void	lst_add_front(t_list **alst, t_list *new_node);
void	lst_add_back(t_list **alst, t_list *new_node);

/*lst_alloc*/
t_list	*lst_new(void *content);
void	lst_clear(t_list **lst, void (*del)(void*));

/*get_next_line*/
char	*get_next_line(int fd);

/*min_max*/
int64_t	min(int64_t a, int64_t b);
int64_t	max(int64_t a, int64_t b);

/*split*/
char	**split(char const *s, char c);

/*str_arr*/
void	str_arr_add(char ***arr, char *str);
void	str_arr_free(char **arr);

/*str_tok*/
char	*str_tok(char **astr, char *src, t_tok *tok);

#endif
