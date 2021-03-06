/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 11:49:05 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_token 	*tokens;
t_token 	*i;
t_mini_vars	*g_vars;
int		g_ret_expected;
int		g_ret_actual;
bool	skip_check;

static void	init_test(char *line)
{
	tokens = tokenizer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	i = tokens;
    g_ret_actual = parse_quotes_and_expand(i, g_vars->env, g_vars);
}

static void		assert_token(t_type type, char *text)
{
	long	len;

	TEST_ASSERT_NOT_NULL(i);
	TEST_ASSERT_EQUAL_INT16(type, i->type);
	if (!text)
	{
		TEST_ASSERT_NULL(i->text);
		i->len = 0;
	}
	else
	{
		len = strlen(text);
		TEST_ASSERT_EQUAL_STRING(text, i->text);
		TEST_ASSERT_EQUAL_UINT64(len, i->len);
	}
	i = i->next;
}

void	setUp(void) {
    g_ret_expected = 0;
	g_vars->last_pid = 42;
	skip_check = false;
}

void	tearDown(void) {
	if (!skip_check)
    	assert_token(TOKEN_EOF, NULL);
	free_tokens(&tokens);
	tokens = NULL;
	i = NULL;
	TEST_ASSERT_EQUAL_UINT8(g_ret_expected, g_ret_actual);
}

static void	trial_1()
{
	init_test("  test  ");
	assert_token(WORD, "test");
}

static void	trial_2()
{
	init_test("  test  test test  test test test       test     test    test ");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
}

static void	trial_3()
{
	init_test("      ");
}

static void	trial_4()
{
	init_test("");
}

static void	trial_5()
{
	init_test(" ls -l");
	assert_token(WORD, "ls");
	assert_token(WORD, "-l");
}

static void	trial_6()
{
	init_test("echo \"string\" hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "string");
	assert_token(WORD, "hi");
}

static void	trial_7()
{
	init_test("echo hi\"string\"hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "histringhi");
}

static void	trial_8()
{
	init_test("echo hi\"\'string\'\"hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "hi\'string\'hi");
}

static void	trial_9()
{
	init_test("echo hi\"\"\'string\'\"\"hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "histringhi");
}

static void	trial_10()
{
	init_test("echo hi\"\"\'string\'\"\"hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "histringhi");
}

static void	trial_11()
{
	init_test("\'\"\' ");
	assert_token(WORD, "\"");
}

static void	trial_12()
{
	init_test("\"\'\" ");
	assert_token(WORD, "\'");
}

static void	trial_13()
{
	init_test("echo hi\"hi ");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_14()
{
	init_test("echo hi\'hi ");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_15()
{
	init_test("echo hi\'hi\'\" ");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_16()
{
	init_test("echo hi\"hi\"\' ");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_17()
{
	init_test("\'");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_18()
{
	init_test("\"");
	skip_check = true;
	g_ret_expected = 1;
}

static void	trial_19()
{
	init_test("$env_var");
	assert_token(WORD, "blabla");
}

static void	trial_20()
{
	init_test("\"$env_var\"");
	assert_token(WORD, "blabla");
}

static void	trial_21()
{
	init_test("\'$env_var\'");
	assert_token(WORD, "$env_var");
}

static void	trial_22()
{
	init_test("\"\'$env_var\'\"");
	assert_token(WORD, "\'blabla\'");
}

static void	trial_23()
{
	init_test("\"  $env_var  \"");
	assert_token(WORD, "  blabla  ");
}

static void	trial_24()
{
	init_test("\"  $?  \"");
	assert_token(WORD, "  42  ");
}

static void	trial_25()
{
	init_test("\"  $$  \"");
	assert_token(WORD, "    ");
}

static void	trial_26()
{
	init_test("\"  $  \"");
	assert_token(WORD, "  $  ");
}

static void	trial_27()
{
	init_test("\"     $\"");
	assert_token(WORD, "     $");
}

static void	trial_28()
{
	init_test("echo hi\"$env_var\"$env_var");
	assert_token(WORD, "echo");
	assert_token(WORD, "hiblablablabla");
}

static void	trial_29()
{
	init_test("\"123$double_var123\"");
	assert_token(WORD, "123");
}

static void	trial_30()
{
	init_test("\"  $doesnt_exist  \"");
	assert_token(WORD, "    ");
}

static void	trial_31()
{
	init_test("\"123$double_var 123\"");
	assert_token(WORD, "123blabla 123");
}

static void	trial_32()
{
	init_test("echo$?echo");
	assert_token(WORD,"echo42echo");
}

static void	trial_33()
{
	init_test("echo$?echo");
	assert_token(WORD,"echo42echo");
}

static void trial_34()
{
	init_test("echo \'\"$USER\"\'");
	assert_token(WORD, "echo");
	assert_token(WORD, "\"$USER\"");
}

static void trial_35()
{
	init_test("echo $9a");
	assert_token(WORD, "echo");
	assert_token(WORD, "a");
}

static void trial_36()
{
	init_test("echo $a9");
	assert_token(WORD, "echo");
	assert_token(WORD, "jup");
}

static void trial_37()
{
	init_test("echo $*");
	assert_token(WORD, "echo");
	assert_token(WORD, NULL);
}

static void trial_38()
{
	init_test("echo $$");
	assert_token(WORD, "echo");
	assert_token(WORD, NULL);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	g_vars = ft_calloc(1, sizeof(t_mini_vars));
	if (!g_vars)
		exit(-1);
	g_vars->env = env;
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
	RUN_TEST(trial_20);
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
