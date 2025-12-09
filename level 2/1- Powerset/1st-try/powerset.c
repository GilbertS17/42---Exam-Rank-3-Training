#include <stdio.h>
#include <stdlib.h>

void discover (int *set, int n, int index,int current_sum, int target, int *subset, int subset_size)
{
    if (index == n)
    {
        if (current_sum == target)
        {
            for (int i = 0; i < subset_size; i++)
            {
                printf("%d ", subset[i]);
            }
            printf("\n");
        }
            return ;
    }

    subset[subset_size] = set[index];
    discover(set, n, index + 1, current_sum + set[index], target, subset, subset_size + 1);

    discover(set, n, index + 1, current_sum, target, subset, subset_size);
}

int main (int argc, char **argv)
{
    if (argc < 2)
        return 1;
    int target = atoi(argv[1]);
    int n = argc - 2;
    int *set = malloc (n * sizeof(int));
    if (!set)
        return 1;
    for (int i = 2; i < argc; i++)
        set[i -2] = atoi(argv[i]);
    int *subset = malloc (n * sizeof(int));
    if (!subset)
    {
        free(set);
        return 1;
    }
    discover(set, n, 0, 0, target, subset, 0);
    free(set);
    free(subset);
    return 0;
}