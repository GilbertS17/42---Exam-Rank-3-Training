#include "rip.h"

static int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

static t_dfs ft_scan(char *set, int n)
{
	t_dfs temp;
	temp.open = 0;
	temp.rm_open = 0;
	temp.rm_close = 0;
	for (int i = 0; i < n; i++)
	{
		if (set[i] == '(')
				temp.open++;
		if (set[i] == ')')
		{
			if (temp.open > 0)
				temp.open--;
			else
				temp.rm_close++;
		}
	}
	temp.rm_open = temp.open;
	temp.open = 0;
	return temp;
}

void solve(char *set, int n, char *out, int index, int open, int rm_open, int rm_close)
{
	if (index == n)
	{
		if (open == 0 && rm_close == 0 && rm_open == 0)
		{
			write(1, out, n);
			write(1, "\n", 1);
		}
		return ;
	}
	if (set[index] == '(')
	{
		if (rm_open > 0)
		{
			out[index] = ' ';
			solve(set, n, out, index + 1, open, rm_open - 1, rm_close);
		}
		out[index] = '(';
		solve(set, n, out, index + 1, open + 1, rm_open, rm_close);
	}
	else if (set[index] == ')')
	{
		if (rm_close > 0)
		{
			out[index] = ' ';
			solve(set, n, out, index + 1, open, rm_open, rm_close - 1);

		}
		if (open > 0)
		{
			out[index] = ')';
			solve(set, n, out, index + 1, open - 1, rm_open, rm_close);
		}
	}
	else
	{
		out[index] = set[index];
		solve(set, n, out, index + 1, open, rm_open, rm_close);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *set = argv[1];
	int n = ft_strlen(set);
	char out[1024];
	t_dfs dfs = ft_scan(set, n);
	solve(set, n, out, 0, 0, dfs.rm_open, dfs.rm_close);
	return 0;
}