#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void permute(char *set, int n, int *used, char *perm, int pos)
{
    if (pos == n - 1)
    {
        for (int i = 0; i < n; i++)
            write(1, &set[i], 1);
        write(1, "\n", 1);
        return ;
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = ft_strlen(argv[1]);
    char *set = malloc((n + 1) * sizeof(char));
    if (!set)
        return 1;
    for (int i = 0; i < n; i++)
        set [i] = argv[1][i];
    set[n] = '\0';
    int *used = calloc(n ,sizeof(int));
    if (!used)
    {
        free(set);
        return 1;
    }
    for (int i = 0; i < n; i++)
        write(1, &used[i], 1);
    write(1, "\n", 1);
    char *perm = malloc((n + 1) * sizeof(char));
    if (!perm)
    {
        free(set);
        free(used);
        return 1;
    }
    perm[n] = '\0';
    // permute(set, n, used, perm, 3);
    free(set);
    free(used);
    free(perm);
    return 0;
}