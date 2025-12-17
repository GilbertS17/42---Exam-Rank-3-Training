#include <stdlib.h>
#include <stdio.h>

void powerset(int *set, int n, int cur_sum, int *sub_set, int subset_size, int goal, int pos)
{
    if (pos == n)
    {
        if (cur_sum == goal)
        {
            for (int i = 0; i < subset_size; i++)
            {
                printf("%d", sub_set[i]);
                if (i < subset_size - 1)
                    printf(" ");
            }
            printf("\n");
        }
        return ;
    }
    sub_set[subset_size] = set[pos];
    powerset(set, n, cur_sum + set[pos], sub_set, subset_size + 1, goal, pos + 1);
    powerset(set, n ,cur_sum, sub_set, subset_size, goal, pos + 1);
}

int main (int argc, char **argv)
{
    if (argc <= 2)
        return 1;
    int goal = atoi(argv[1]);
    int n = argc - 2;
    int *set;
    set = malloc(n * sizeof(int));
    if (!set)
        return 1;
    for (int i = 2; i < argc; i++)
        set[i - 2] = atoi(argv[i]);
    int *sub_set;
    sub_set = malloc(n * sizeof(int));
    if (!sub_set)
        return (free(set), 1);
    powerset(set, n, 0, sub_set, 0, goal, 0);
    free(set);
    free(sub_set);
    return 0;
}
