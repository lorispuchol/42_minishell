/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:26:51 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:50 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

typedef struct s_minishell	t_minishell;
typedef struct s_cmds		t_cmds;
typedef struct s_vars		t_vars;
typedef struct s_env		t_env;

int							g_xcode[2];

struct s_env
{
	char	*str;
	t_env	*next;
};

struct s_vars
{
	int	i;
	int	j;
	int	k;
};

struct s_cmds
{
	char		**cmd;
	char		*infile;
	char		*outfile;
	int			fd_infile;
	int			fd_outfile;
	int			intype;
	int			fd_pipe[2];
	int			index_cmd;
	t_minishell	*ptr_mnsh;
};

struct s_minishell
{
	char	*pwd;
	int		pipe;
	t_cmds	*cmds;
	t_env	*lst_env;
	char	**tab_env;
	int		nb_cmd;
	pid_t	*id_fork;
};

// exec_utlis.c
char	*l_strdup(char *s1);
char	*l_strnstr(char *haystack, char *needle, size_t len);
int		l_strncmp(char *s1, char *s2, size_t n);
int		l_strcmp(char *s1, char *s2);
int		l_strchr(char *s, char c);

// exec_utlis_2.c
void	ft_xerror(char *s1, char *sp1, char *s2, int nb_exit);
void	*ft_xmalloc(size_t size);
void	ft_display_tab(char **tabl);
char	*l_strjoin(char *s1, char *s2);

// exec_utlis_3.c
int		l_isdigit(int a);
int		l_isalpha(int a);
void	*l_calloc(size_t count, size_t size);

// ft_atoi_and_itoa
int		l_atoi(const char *str);
char	*l_itoa(int n);

// l_split.c
char	**l_split(char *s, char c);
int		l_nb_word(char *s, char c);
int		l_free_split(char **tabl);

// envp.c
t_env	*l_no_env_at_launch(t_minishell *mnsh);
void	set_mandatory_var(t_env *tmp, t_env *lst_env, t_minishell *mnsh);
void	set_mandatory_var_2(t_env *tmp, t_env *lst_env);
t_env	*ft_get_env(char **env, t_minishell *mnsh, int i);
void	ft_display_lst_env(t_minishell *minishell);
void	ft_convert_env_in_tab(t_minishell *mnsh);
void	ft_free_lst_env(t_minishell *mnsh);
void	ft_free_tab_env(t_minishell *minishell);

// pipe.c
char	**get_paths_with_cmd(char **envp, char *cmd);
void	ft_close_pipe(t_cmds *cmds);
void	ft_dup_infile(t_cmds *cmds);
void	ft_dup_outfile(t_cmds *cmds);
void	ft_dup_pipe(t_cmds *cmds);

// exec.c
void	ft_bad_cmd(t_cmds *cmds);
void	ft_exec_child(t_cmds *cmds);
int		ft_fork_ps(t_minishell *mnsh);
void	ft_exec(t_minishell *mnsh);

// get pwd
char	*ft_get_pwd(void);

/////////////////////// builtins ////////////////
// check bt
int		bt_outfile(t_cmds *cmds);
int		ft_check_bt(t_cmds *cmds);

//	export only
char	**ft_sort_ascii(char **tab_env);
char	**convert_in_tab(t_env *env);
void	bt_export_only(t_cmds *cmds, int i, int j, int open);

//	export 
void	bt_export(t_cmds *cmds, int i, int pos, char **split_var);

//	export 
int		check_valid_var(char *name);
int		check_valid_var_2(char *name);

//	env only
void	bt_env_only(t_cmds *cmds);

//  unset
void	bt_unset(t_cmds *cmds);

//  pwd
void	bt_pwd(t_cmds *cmds);

//  echo
void	bt_echo(t_cmds *cmds);

// exit
void	bt_exit(t_cmds *cmds);

// cd 
void	bt_cd(t_cmds *cmds);

// cd 2
int		l_putstr_fd_3(char *s1, char *s2, char *s3, int fd);
void	change_pwds(t_cmds *cmds, int position, char *tmp);

#endif