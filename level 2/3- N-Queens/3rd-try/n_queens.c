#include <stdlib.h>
#include <unistd.h>

int is_place(int *pos, int col, int row)
{
    for (int prev = 0; prev < col; prev++)
    {
        if (pos[prev] == row) return 0;
        int row_diff = row - pos[prev];
        if (row_diff < 0) row_diff *= -1;
        int col_diff = col - prev;
        if (col_diff < 0) col_diff *= -1;
        if (row_diff == col_diff) return 0;
    }
    return 1;
}

void ft_putnbr(int nbr)
{
    if (nbr > 9)
        ft_putnbr(nbr / 10);
    char c = (nbr % 10) + '0';
    write(1, &c, 1);
}

void solve(int *pos, int n, int col)
{
    if (col == n)
    {
        for (int i = 0; i < n; i++)
        {
            ft_putnbr(pos[i]);
            if (i < n -1)
                write(1, " ", 1);
        }
        write(1, "\n", 1);
        return ;
    }
    for (int row = 0; row < n; row++)
    {
        if (is_place(pos, col, row))
        {
            pos[col] = row;
            solve(pos, n, col + 1);
        }
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = atoi(argv[1]);
    int *pos = malloc (n * sizeof(int));
    if (!pos)
        return 1;
    solve(pos, n, 0);
    free(pos);
    return 0;
}