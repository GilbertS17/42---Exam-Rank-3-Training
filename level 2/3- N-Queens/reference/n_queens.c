#include <stdlib.h>
#include <unistd.h>

int is_safe(int *pos, int col, int row)
{
    for (int prev = 0; prev < col; prev++)
    {
        if (pos[prev] == row)
            return 0;
        int rows_diff = pos[prev] - row;
        if (rows_diff < 0)
            rows_diff = -rows_diff;
        int cols_diff = prev - col;
        if (cols_diff < 0)
            cols_diff = -cols_diff;
        if (cols_diff == rows_diff)
            return 0;
    }
    return 1;
}

void solve(int n, int col, int *pos)
{
    if (col == n)
    {
        for (int i = 0; i < n; i++)
        {
            char c = pos[i] + '0';
            write(1, &c, 1);
            if (i < n - 1)
                write(1, " ", 1);
        }
        write(1, "\n", 1);
        return ;
    }
    for (int row = 0; row < n; row++)
    {
        if (is_safe(pos, col, row))
        {
            pos[col] = row;
            solve(n, col + 1, pos);
        }
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;

    int n = atoi(argv[1]);
    int pos[n];
    
    solve(n, 0, pos);
    return 0;
}