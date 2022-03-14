/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 13:08:59 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 11:40:46 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars *g_vars;
char        **g_env;

static char	**init_env(char **env)
{
	char	**mini_env;
	int		len;

	len = 0;
	while (env[len])
		len++;
	mini_env = ft_calloc(len + 1, sizeof(char *));
	ft_check_malloc(mini_env, "init_env");
	while (len)
	{
		len--;
		mini_env[len] = ft_strdup(env[len]);
		ft_check_malloc(mini_env[len], "init_env");
	}
	return (mini_env);
}

static void	process_cmd(char *raw_line, t_mini_vars *vars)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, vars->env, vars);
	if (!cmd)
		return ;
	executor(cmd, vars);
	free_cmd_list(&cmd);
}

void    setUp(void) {
    g_vars->env = init_env(g_env);
	g_vars->last_pid = 0;
	g_vars->paths = NULL;
}

void    tearDown(void) {
    ft_free_char_array(g_vars->env);
}

// if find == true, line should be found
// if fine == false, line should not be found
static void	assert_find(char *line, bool find) {
	bool	found = false;
	int		len = ft_strlen(line);
	char	**env;
	int		i = 0;

	env = g_vars->env;
	while (env[i])
	{
		if (!ft_strncmp(env[i], line, len)) {
			found = true;
			break ;
		}
		i++;
	}
	TEST_ASSERT_MESSAGE(found == find, "assert_find");
}

// does not work correctly with pipes
static void    do_cmd(char *line, int expected_pid) {
    process_cmd(line, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected_pid, g_vars->last_pid);
}

static void	trial_1()
{
	do_cmd("export hallo=daan", 0);
	assert_find("hallo=daan", true);
}

static void	trial_2()
{
	do_cmd("export env_var=blablabla", 0);
	assert_find("env_var=blablabla", true);
}

static void	trial_3()
{
	do_cmd("export env_var=", 0);
	assert_find("env_var=", true);
}

static void	trial_4()
{
	do_cmd("export env_var=1", 0);
	assert_find("env_var=1", true);
}

static void	trial_5()
{
	do_cmd("export env_var=123456", 0);
	assert_find("env_var=123456", true);
}

static void	trial_6()
{
	do_cmd("export env_var=123456", 0);
	do_cmd("export env_var=1234", 0);
	assert_find("env_var=123456", false);
	assert_find("env_var=1234", true);
}

static void	trial_7()
{
	do_cmd("export env_var=$env_var:/rcappend", 0);
	assert_find("env_var=blabla:/rcappend", true);
}

static void	trial_8()
{
	do_cmd("export env_var=$env_var:/$env_var", 0);
	assert_find("env_var=blabla:/blabla", true);
}

static void	trial_9()
{
	do_cmd("export 1=error", 1);
	assert_find("1=error", false);
}

static void	trial_10()
{
	do_cmd("export daan=\'test\'", 0);
	assert_find("daan=test", true);
}

static void	trial_11()
{
	do_cmd("export daan=$env_var", 0);
	assert_find("daan=blabla", true);
}

static void	trial_12()
{
	do_cmd("export daan= lorem ipsum", 0);
	assert_find("daan=", true);
	assert_find("lorem", false);
	assert_find("ipsum", false);
}

static void	trial_13()
{
	do_cmd("export a=\nexport a=42\nexport", 0);
	assert_find("a=42\nexport", true);
}

static void	trial_14()
{
	do_cmd("export $env_var=blabla", 0);
	assert_find("blabla=blabla", true);
}

static void	trial_15()
{
	do_cmd("export foo=baz", 0);
	assert_find("foo=baz", true);
	do_cmd("unset foo", 0);
	assert_find("foo=baz", false);
}

static void	trial_16()
{
	do_cmd("export foo=baz daan=nee", 0);
	assert_find("foo=baz", true);
	assert_find("daan=nee", true);
	do_cmd("unset foo daan", 0);
	assert_find("foo=baz", false);
	assert_find("daan=nee", false);
}

static void	trial_17()
{
	do_cmd("unset bestaat niet", 0);
}

static void	trial_18()
{
	do_cmd("unset env_var=hi", 1);
	assert_find("env_var=blabla", true);
}

static void	trial_19()
{
	do_cmd("unset", 0);
}

static void	trial_21()
{
	do_cmd("unset HOME", 0);
	do_cmd("cd", 1);
}

// check deze error message
static void	trial_22()
{
	do_cmd("export \'$home\'=nope", 1);
}

// check error message
static void	trial_23()
{
	do_cmd("unset %", 1);
}

static void trial_24()
{
	do_cmd("export 3daan=hallo", 1);
}

static void trial_25()
{
	do_cmd("export d4aan=hallo", 0);
	assert_find("d4aan=hallo", true);
}

static void trial_26()
{
	do_cmd("export _4daan=hallo", 0);
	assert_find("_4daan=hallo", true);
}

static void trial_27()
{
	do_cmd("export _$env_var=hallo", 0);
	assert_find("_blabla=hallo", true);
}

static void trial_28()
{
	do_cmd("export _hallo$USERja=daan", 0);
	assert_find("_hallo=daan", true);
}

// Dit is een hele rare, maar we skotten hem
static void trial_29()
{
	do_cmd("export _=hallo", 0);
	assert_find("_=hallo", true);
}

static void trial_30()
{
	do_cmd("unset hskjgdh#hs", 1);
}

static void trial_31()
{
	do_cmd("export _$env_var:hallo=hallo", 1);
}

static void trial_32()
{
	do_cmd("export _$44HALLO=hallo", 0);
	assert_find("_4HALLO=hallo", true);
}

static void trial_33()
{
	do_cmd("export HALLO=hallo", 0);
	assert_find("_4HALLO=hallo", false);
}

static void trial_34()
{
	do_cmd("export HALLO=hallo$env_var:hallo$env_var%hallo$env_var/hallo", 0);
	assert_find("HALLO=halloblabla:halloblabla%halloblabla/hallo", true);
}

static void trial_35()
{
	do_cmd("export HALLO=hallo$env_var$", 0);
	assert_find("HALLO=halloblabla$", true);
}

static void trial_36()
{
	do_cmd("export =", 1);
}

static void trial_37()
{
	do_cmd("export =10", 1);
}

static void trial_38()
{
	do_cmd("export A=bla", 0);
	do_cmd("export A=$A-bloe", 0);
	assert_find("A=bla-bloe", true);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	g_vars = ft_calloc(1, sizeof(t_mini_vars));
	if (!g_vars) {
		exit(-1);
	}
	g_env = init_env(env);
	UNITY_BEGIN();
	RUN_TEST(trial_1);
	RUN_TEST(trial_2);
	RUN_TEST(trial_3);
	RUN_TEST(trial_4);
	RUN_TEST(trial_5);
	RUN_TEST(trial_6);
	RUN_TEST(trial_7);
	RUN_TEST(trial_8);
	RUN_TEST(trial_9);
	RUN_TEST(trial_10);
	RUN_TEST(trial_11);
	RUN_TEST(trial_12);
	RUN_TEST(trial_13);
	RUN_TEST(trial_14);
	RUN_TEST(trial_15);
	RUN_TEST(trial_16);
	RUN_TEST(trial_17);
	RUN_TEST(trial_18);
	RUN_TEST(trial_19);
	RUN_TEST(trial_21);
	RUN_TEST(trial_22);
	RUN_TEST(trial_23);
	RUN_TEST(trial_24);
	RUN_TEST(trial_25);
	RUN_TEST(trial_26);
	RUN_TEST(trial_27);
	RUN_TEST(trial_28);
	RUN_TEST(trial_29);
	RUN_TEST(trial_30);
	RUN_TEST(trial_31);
	RUN_TEST(trial_32);
	RUN_TEST(trial_33);
	RUN_TEST(trial_34);
	RUN_TEST(trial_35);
	RUN_TEST(trial_36);
	RUN_TEST(trial_37);
	RUN_TEST(trial_38);
	return (UNITY_END());
}