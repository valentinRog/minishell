/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:07:43 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 20:59:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_tok
{
	char	**seps;
	char	*quotes;
	char	*spaces;
}	t_tok;

/*str*/
size_t	str_len(char *str);
void	str_n_cpy(char *dst, char *src, size_t len);
char	to_upper(char c);

/*str_cmp*/
int		str_n_cmp(char *s1, char *s2, size_t n);
int		str_cmp(char *s1, char *s2);
int		str_cmp_no_case(char *s1, char *s2);

/*str_find*/
bool	in_str(char *str, char c);
char	in_quote(char *str, char *quote, size_t index);
char	*str_chr(char *str, char c);
bool	is_tok(char *str, char *tokens, char sep);

/*str_alloc*/
char	*str_n_dup(char *str, size_t n);
char	*str_dup(char *src);
char	*str_dup1(void);
void	str_n_insert(char **astr, char *str, size_t i, size_t n);
void	str_n_remove(char **astr, size_t i, size_t n);

/*min_max*/
int64_t	min(int64_t a, int64_t b);
int64_t	max(int64_t a, int64_t b);

/*split*/
char	**split(char const *s, char c);

/*str_arr*/
size_t	str_arr_len(char **arr);
void	str_arr_free(char **arr);
char	**lst_to_str_arr(t_list *lst);

/*str_tok*/
char	*str_tok(char **astr, char *src, t_tok *tok);

/*swap*/
void	swap_ptr(void **a, void **b);

/*sort*/
void	lst_sort(t_list *lst, int (*cmp)(void *, void *));

/*put*/
void	put_str_fd(char *str, int fd);

/*lst_str*/
t_list	*new_lst_str(char *str);

/*itoa*/
void	itoa(int n, char buff[], size_t buffer_size);

#endif
