/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_tester.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/14 12:06:59 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_token		*tokens;
t_token		*i;

static void	init_test(char *line)
{
	tokens = tokenizer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	i = tokens;
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

void    setUp(void) {
    
}

void    tearDown(void) {
	assert_token(TOKEN_EOF, NULL);
	free_tokens(&tokens);
	tokens = NULL;
	i = NULL;
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
	init_test(" ls > test");
	assert_token(WORD, "ls");
	assert_token(OUTPUT_S, NULL);
	assert_token(WORD, "test");
}

static void	trial_7()
{
	init_test(" ls >> test");
	assert_token(WORD, "ls");
	assert_token(OUTPUT_D, NULL);
	assert_token(WORD, "test");
}

static void	trial_8()
{
	init_test(" ls >>> test");
	assert_token(WORD, "ls");
	assert_token(OUTPUT_D, NULL);
	assert_token(OUTPUT_S, NULL);
	assert_token(WORD, "test");
}

static void	trial_9()
{
	init_test(" ls < test");
	assert_token(WORD, "ls");
	assert_token(INPUT_S, NULL);
	assert_token(WORD, "test");
}

static void	trial_10()
{
	init_test(" ls << test");
	assert_token(WORD, "ls");
	assert_token(INPUT_D, NULL);
	assert_token(WORD, "test");
}

static void	trial_11()
{
	init_test(" ls <<< test");
	assert_token(WORD, "ls");
	assert_token(INPUT_D, NULL);
	assert_token(INPUT_S, NULL);
	assert_token(WORD, "test");
}

static void	trial_12()
{
	init_test(" ls | | | test");
	assert_token(WORD, "ls");
	assert_token(PIPE, NULL);
	assert_token(PIPE, NULL);
	assert_token(PIPE, NULL);
	assert_token(WORD, "test");
}

static void	trial_13()
{
	init_test("echo hi\"hello\"hi>test|hello");
	assert_token(WORD, "echo");
	assert_token(WORD, "hi\"hello\"hi");
	assert_token(OUTPUT_S, NULL);
	assert_token(WORD, "test");
	assert_token(PIPE, NULL);
	assert_token(WORD, "hello");
}

static void	trial_14()
{
	init_test("echo |hi\"hello\"hi>>test|hello");
	assert_token(WORD, "echo");
	assert_token(PIPE, NULL);
	assert_token(WORD, "hi\"hello\"hi");
	assert_token(OUTPUT_D, NULL);
	assert_token(WORD, "test");
	assert_token(PIPE, NULL);
	assert_token(WORD, "hello");
}

static void	trial_15()
{
	init_test("echo \'hi \"string\" hi \'");
	assert_token(WORD, "echo");
	assert_token(WORD, "\'hi \"string\" hi \'");
}

static void	trial_16()
{
	init_test("echo \'hi \"string\" hi ");
	assert_token(WORD, "echo");
	assert_token(WORD, "\'hi \"string\" hi ");
}

static void	trial_17()
{
	init_test("echo \"hi \'string\'\'string\'\" hi \"");
	assert_token(WORD, "echo");
	assert_token(WORD, "\"hi \'string\'\'string\'\"");
	assert_token(WORD, "hi");
	assert_token(WORD, "\"");
}

static void	trial_18()
{
	init_test("cat > file1 >> file2 < file3 -e | echo hallo");
	assert_token(WORD, "cat");
	assert_token(OUTPUT_S, NULL);
	assert_token(WORD, "file1");
	assert_token(OUTPUT_D, NULL);
	assert_token(WORD, "file2");
	assert_token(INPUT_S, NULL);
	assert_token(WORD, "file3");
	assert_token(WORD, "-e");
	assert_token(PIPE, NULL);
	assert_token(WORD, "echo");
	assert_token(WORD, "hallo");
}

int main(void)
{
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
	return UNITY_END();
}
