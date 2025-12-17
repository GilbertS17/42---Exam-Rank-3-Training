#include <stdlib.h>
#include <stdio.h>

void solve(int *set, int n, int target, int *subset, int subset_size, int current_sum, int pos)
{
    if (pos == n)
    {
        if (current_sum == target)
        {
            for (int i = 0; i < subset_size; i++)
            {
                printf("%d", subset[i]);
                if (i < subset_size - 1)
                    printf(" ");
            }
            printf("\n");
        }
        return ;
    }
    subset[subset_size] = set[pos];
    solve(set, n, target, subset, subset_size + 1, current_sum + set[pos], pos + 1);
    solve(set, n, target, subset, subset_size, current_sum, pos + 1);
}

int main (int argc, char **argv)
{
    if (argc <= 2) return 1;
    int target = atoi(argv[1]);
    int n = argc - 2;
    int *set = malloc ((n + 1) * sizeof(int));
    if (!set)
        return 1;
    int *subset = malloc ((n + 1) * sizeof(int));
    if (!subset)
        return(free(set), 1);
    for (int i = 2; i < argc; i++)
        set[i - 2] = atoi(argv[i]);
    solve(set, n ,target, subset, 0, 0, 0);
    free(set);
    free(subset);
    return 0;
}