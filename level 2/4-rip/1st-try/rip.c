#include "rip.h"

static int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

static data_t ft_scan(char *set, int n)
{
    data_t tmp;
    tmp.open = 0;
    tmp.rm_open = 0;
    tmp.rm_close = 0;

    for (int i = 0; i < n; i++)
    {
        if (set[i] == '(')
        {
            tmp.open++;
        }
        if (set[i] == ')')
        {
            if (tmp.open > 0)
                tmp.open--;
            else
                tmp.rm_close++;
        }
    }
    tmp.rm_open = tmp.open;
    tmp.open = 0;
    return tmp;
}

static void solve(char *set, int n, int open, int rm_open, int rm_close, char *out, int i)
{
    if (i == n)
    {
        if (open == 0 && rm_open == 0 && rm_close == 0)
        {
            write(1, out, n);
            write(1, "\n", 1);
        }
        return ;
    }
    if (set[i] == '(')
    {
        if (rm_open > 0)
        {
            out[i] = ' ';
            solve(set, n, open, rm_open - 1, rm_close, out, i + 1);
        }
        out[i] = '(';
        solve(set, n, open + 1, rm_open, rm_close, out, i + 1);
    }
    else if (set[i] == ')')
    {
        if (rm_close > 0)
        {
            out[i] = ' ';
            solve(set, n, open, rm_open, rm_close - 1, out, i + 1);
        }
        if (open > 0)
        {
            out[i] = ')';
            solve(set, n, open - 1, rm_open, rm_close, out, i + 1);
        }
    }
    else
    {
        out[i] = set[i];
        solve(set, n, open, rm_open, rm_close, out, i + 1);
    }
}

int main (int argc, char **argv)
{
    if (argc != 2) return 1;
    char *set = argv[1];
    int n = ft_strlen(set);
    data_t data = ft_scan(set, n);
    char out[1024];
    solve(set, n, data.open, data.rm_open, data.rm_close, out, 0);
    return 0;
}