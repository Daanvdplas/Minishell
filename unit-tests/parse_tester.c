/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tester.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 06:04:49 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 12:15:04 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

/*
	how to test:
	init_test("line_to_test");

	-----
	if line == incorrect:
	-----
		add nothing else

	-----
	if line == correct:
	-----
	for each command:
		assert_exec(commands and arguments separated by + )
		for each redirect:
			assert_redirect(redirect type, file_name)
		next_command
	-----
	
	dont forget to check for leaks every now and then
*/

t_cmd   	*cmd_list;
t_cmd  		*i;
t_red		*i_input;
t_red		*i_output;
t_mini_vars	*g_vars;

void	setUp(void) {
    i_input = NULL;
	i_output = NULL;
}

static void	init_test(char *line)
{
	t_token *tokens;
    
    tokens = tokenizer(line);
	TEST_ASSERT_NOT_NULL_MESSAGE(tokens, "error making tokens");
    cmd_list = parser(tokens, g_vars->env, g_vars);
    i = cmd_list;
	if (i) {
		i_input = i->input;
		i_output = i->output;
	}
    tokens = NULL;
}

static void next_cmd(void)
{
	TEST_ASSERT_NULL_MESSAGE(i_input, "next cmd input not null");
	TEST_ASSERT_NULL_MESSAGE(i_output, "next cmd output not null");
    i = i->next;
	if (i) {
		i_input = i->input;
		i_output = i->output;
	}
}

static void assert_exec(char *args)
{
	t_exec  *exec;
    char	**args_split = ft_split(args, '+');
    int		len = 0;
	
    exec = i->exec;
    if (!args)
    {
		TEST_ASSERT_NULL(exec);
    	return ;
    }
	while (args_split[len])
		len++;
	TEST_ASSERT_EQUAL_STRING_MESSAGE(args_split[0], exec->cmd, "command");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(args_split, exec->args, len, "arguments");
	TEST_ASSERT_NULL_MESSAGE(exec->args[len], "end of arguments");
	TEST_ASSERT_EQUAL_INT16_MESSAGE(len, exec->len, "exec->len");
	while (len)
	{
		len--;
		free(args_split[len]);
	}
	free(args_split);
}

static void	assert_input(int type, char *file_name)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(i_input, "assert_input");
	TEST_ASSERT_EQUAL_INT16_MESSAGE(type, i_input->type, "input type");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(file_name, i_input->file_name, "input file_name");
	i_input = i_input->next;
}

static void	assert_output(int type, char *file_name)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(i_output, "assert_output");
	TEST_ASSERT_EQUAL_INT16_MESSAGE(type, i_output->type, "output type");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(file_name, i_output->file_name, "output file_name");
	i_output = i_output->next;
}

void	tearDown(void) {
    TEST_ASSERT_NULL_MESSAGE(i, "teardown i not NULL");
	TEST_ASSERT_NULL_MESSAGE(i_input, "teardown i_input not NULL");
	TEST_ASSERT_NULL_MESSAGE(i_output, "teardown output not NULL");
    cmd_list = free_cmd_list(&cmd_list);
}

static void trial_1()
{
    init_test("");
}

static void trial_2()
{
    init_test("      ");
}

static void trial_3()
{
    init_test("  ls   ");
	assert_exec("ls");
	next_cmd();
}

static void trial_4()
{
    init_test("  \"  ls  \" ");
	assert_exec("  ls  ");
	next_cmd();
}

static void trial_5()
{
    init_test("   ls -l   ");
	assert_exec("ls+-l");
	next_cmd();
}

static void trial_6()
{
    init_test("   ls -l    \'  echo$?  \'  ");
	assert_exec("ls+-l+  echo$?  ");
	next_cmd();
}

static void trial_7()
{
    init_test(" echo | echo ");
	assert_exec("echo");
	next_cmd();
	assert_exec("echo");
	next_cmd();
}

static void trial_8()
{
    init_test(" echo | ");
}

static void trial_9()
{
    init_test(" | | ");
}

static void trial_10()
{
    init_test(" | echo | ");
}

static void trial_11()
{
    init_test(" test | ");
}

static void trial_12()
{
    init_test(" |  ");
}

static void trial_13()
{
    init_test("echo | echo | echo");
	assert_exec("echo");
	next_cmd();
	assert_exec("echo");
	next_cmd();
	assert_exec("echo");
	next_cmd();
}

static void trial_14()
{
    init_test("echo \"| echo |\" echo");
	assert_exec("echo+| echo |+echo");
	next_cmd();
}

static void trial_15()
{
    init_test("echo > hi echo");
	assert_exec("echo+echo");
	assert_output(RED_OPUT, "hi");
	next_cmd();
}

static void trial_16()
{
    init_test("echo >> hi echo");
	assert_exec("echo+echo");
	assert_output(RED_OPUT_A, "hi");
	next_cmd();
}

static void trial_17()
{
    init_test("echo < hi echo");
	assert_exec("echo+echo");
	assert_input(RED_IPUT, "hi");
	next_cmd();
}

static void trial_18()
{
    init_test("echo << hi");
	assert_exec("echo");
	assert_input(HERE_DOC, "hi");
	next_cmd();
}

static void trial_19()
{
    init_test("echo > file1 >> file2 > file3 >> file4");
	assert_exec("echo");
	assert_output(RED_OPUT, "file1");
	assert_output(RED_OPUT_A, "file2");
	assert_output(RED_OPUT, "file3");
	assert_output(RED_OPUT_A, "file4");
	next_cmd();
}

static void trial_20()
{
    init_test("echo > file1 >> file2 echo > file3 echo >> file4");
	assert_exec("echo+echo+echo");
	assert_output(RED_OPUT, "file1");
	assert_output(RED_OPUT_A, "file2");
	assert_output(RED_OPUT, "file3");
	assert_output(RED_OPUT_A, "file4");
	next_cmd();
}

static void trial_21()
{
    init_test("echo > file1 >> file2 echo < file3 echo >> file4 << file5");
	assert_exec("echo+echo+echo");
	assert_output(RED_OPUT, "file1");
	assert_output(RED_OPUT_A, "file2");
	assert_output(RED_OPUT_A, "file4");
	assert_input(RED_IPUT, "file3");
	assert_input(HERE_DOC, "file5");
	next_cmd();
}

static void trial_22()
{
    init_test("echo > file1 echo >> file2 | echo < file3 >> file4 echo");
	assert_exec("echo+echo");
	assert_output(RED_OPUT, "file1");
	assert_output(RED_OPUT_A, "file2");
	next_cmd();
	assert_exec("echo+echo");
	assert_input(RED_IPUT, "file3");
	assert_output(RED_OPUT_A, "file4");
	next_cmd();
}

static void	trial_23()
{
	init_test("echo \"> file1\" > file2");
	assert_exec("echo+> file1");
	assert_output(RED_OPUT, "file2");
	next_cmd();
}

static void	trial_24()
{
	init_test("echo \"> file1\" > $double_var");
	assert_exec("echo+> file1");
	assert_output(RED_OPUT, "blabla");
	next_cmd();
}

static void	trial_25()
{
	init_test("echo < > echo");
}

static void	trial_26()
{
	init_test("echo >");
}

static void	trial_27()
{
	init_test("echo \'>\'");
	assert_exec("echo+>");
	next_cmd();
}

static void	trial_28()
{
	init_test("echo > |");
}

static void	trial_29()
{
	init_test("echo hai\'hai\'hai");
	assert_exec("echo+haihaihai");
	next_cmd();
}

static void	trial_30()
{
	init_test("sleep 3>cat");
	assert_exec("sleep+3");
	assert_output(RED_OPUT, "cat");
	next_cmd();
}

static void	trial_31()
{
	init_test("> cat");
	assert_output(RED_OPUT, "cat");
	next_cmd();
}

static void	trial_32()
{
	init_test("< file2 cat > file1 | echo shiet");
	assert_exec("cat");
	assert_input(RED_IPUT, "file2");
	assert_output(RED_OPUT, "file1");
	next_cmd();
	assert_exec("echo+shiet");
	next_cmd();
}

static void	trial_33()
{
	init_test("< cat");
	assert_input(RED_IPUT, "cat");
	next_cmd();
}

static void	trial_34()
{
	init_test("> cat < cat");
	assert_output(RED_OPUT, "cat");
	assert_input(RED_IPUT, "cat");
	next_cmd();
}

static void	trial_35()
{
	init_test("||| cat");
}

static void	trial_36()
{
	init_test("> $9");
	assert_output(RED_OPUT, NULL);
	next_cmd();
}

static void	trial_37()
{
	init_test(">> $9");
	assert_output(RED_OPUT_A, NULL);
	next_cmd();
}

static void	trial_38()
{
	init_test("<< $9");
	assert_input(HERE_DOC, NULL);
	next_cmd();
}

static void	trial_39()
{
	init_test("< $9");
	assert_input(RED_IPUT, NULL);
	next_cmd();
}

static void	trial_40()
{
	init_test("\"$ls\"l");
	assert_exec("ls -ll");
	next_cmd();
}


static void	trial_41()
{
	init_test("echo \"\" \"\" ");
	assert_exec("echo+ ");
	next_cmd();
}

static void	trial_42()
{
	init_test("$ls");
	assert_exec("ls+-l");
	next_cmd();
}

static void	trial_43()
{
	init_test("\'$ls\'");
	assert_exec("$ls");
	next_cmd();
}

static void	trial_44()
{
	init_test("\"$ls\"");
	assert_exec("ls -l");
	next_cmd();
}

static void	trial_45()
{
	init_test("$ls2");
	assert_exec("ls+-l");
	next_cmd();
}

static void	trial_46()
{
	init_test("export HALLO=hallo$env_var:hallo$env_var%hallo$env_var/hallo");
	assert_exec("export+export HALLO=halloblabla:halloblabla%halloblabla/hallo");
	next_cmd();
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	g_vars = ft_calloc(1, sizeof(t_mini_vars));
	if (!g_vars)
		exit(-1);
	g_vars->last_pid = 42;
	g_vars->env = env;
	g_vars->paths = NULL;
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
	RUN_TEST(trial_39);
	RUN_TEST(trial_40);
	RUN_TEST(trial_41);
	RUN_TEST(trial_42);
	RUN_TEST(trial_43);
	RUN_TEST(trial_44);
	RUN_TEST(trial_45);
	RUN_TEST(trial_46);
    return (UNITY_END());
}
