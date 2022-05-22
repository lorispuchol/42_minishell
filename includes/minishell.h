/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:14:18 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/07 18:54:27 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "minishell_exec.h"

int		ft_strlen(char *s);
int		ft_tab_len(char	**tb);
int		d_empty_cmd(char **tb);
int		d_check_if_arg(char *s);
int		d_check_end(char *input);
int		d_get_intype(char **cmds);
int		d_count_bf(char *s, int i);
int		d_check_heredoc(char *tmp);
int		d_syntax_error(char *error);
int		ft_putstr_fd(char *s, int fd);
int		d_check_quote_pos(char *s, int i);
int		d_check_quote(char *input, char c);
int		d_skip_loop(const char *str, int j);
int		d_quote_first_level(char *s, int i);
int		d_count_words(char const *s, char c);
int		d_malloc_loop(const char *str, int i);
int		ft_parse(char *input, t_minishell *mnsh);
int		d_count_word_loop(const char *str, char c, int i);
int		d_strncmp(const char *s1, const char *s2, size_t n);
int		d_fill_loop(const char *str, char **tmp, t_vars *ijk);

void	ft_sigterm(int code);
void	ft_exit_code_sig(void);
void	ft_init_sig(void);
void	ft_free_tab(char **tb);
void	ft_bzero(void *s, size_t n);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

char	*d_trim(char *str);
char	*d_fill_name(int i);
char	*d_clear_quote(char *s);
char	*d_strjoin(char *s1, char *s2);
char	*d_clear_empty_quotes(char *s);
char	*d_get_heredoc(char **cmds, int i);

char	**d_sprim(char *tb);
char	**d_cpy_trim(char **tb);
char	**d_rmv_quote(char **tb);
char	**d_split(char const *s, char c);
char	**d_rpl_arg(char **tb, char **env, int i);

char	*d_get_infile(char **cmds);
char	*d_get_outfile(char **cmds);
char	**d_without_redirections(char **tmp, int i, int j);

#endif

/*
	====

	while (true) do ; clear ; leaks -q 52923 ; sleep 1 ; done

	execute to avoid '^C' : stty -echoctl
	
	====
*/