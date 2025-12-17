#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void sort(char *set, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (set[i] > set[j])
            {
                char temp = set[i];
                set[i] = set[j];
                set[j] = temp;
            }
        }
    }
}

void permutate(char *set, int n, char *perm, int *used, int pos)
{
    if (pos == n)
    {
        for (int i = 0; i < n; i++)
            write(1, &perm[i], 1);
        write( 1, "\n", 1);
        return ;
    }
    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            used[i] = 1;
            perm[pos] = set[i];
            permutate(set, n,perm, used, pos + 1);
            used[i] = 0;
        }
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = ft_strlen(argv[1]);
    char *set = malloc ((n + 1) * sizeof(char));
    if (!set)
        return 1;
    for (int i = 0; i < n; i++)
        set[i] = argv[1][i];
    set[n] = '\0';
    char *perm = malloc ((n + 1) * sizeof(char));
    if (!perm)
        return (free(set), 1);
    perm[n] = '\0';
    int *used = calloc(n, sizeof(int));
    if (!used)
    {
        free(set);
        free(perm);
        return 1;
    }
    sort (set, n);
    permutate(set, n, perm, used, 0);
    free(set);
    free(perm);
    free(used);
    return 0;
}