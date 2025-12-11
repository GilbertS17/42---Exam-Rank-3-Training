#include <stdlib.h>
#include <unistd.h>

int is_place (int *pos, int col, int row)
{
    for (int prev = 0; prev < col; prev++)
    {
        if (pos[prev] == row)
            return 0;
        int col_diff = prev - col;
        if (col_diff < 0)
            col_diff = -col_diff;
        int row_diff =  pos[prev] - row;
        if (row_diff < 0)
            row_diff = -row_diff;
        if (col_diff == row_diff)
            return 0;
    }
    return 1;
}

void solve (int n, int col, int *pos)
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
        if(is_place(pos, col, row))
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
    if (n <= 0)
        return 0;
    int pos[n];
    solve(n, 0, pos);
    return 0;
}
