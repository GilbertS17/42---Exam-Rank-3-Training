#include <stdlib.h>
#include <stdio.h>

void explore(int index, int *set, int n, int current_sum, int target, int *subset, int subset_size)
{
    if (index == n)
    {
        if (current_sum == target)
        {
            for (int i = 0; i < subset_size; i++)
                printf("%d ", subset[i]);
            printf("\n");
        }
        return ;
    }
    //include index
    subset[subset_size] = set[index];
    explore(index + 1, set, n, current_sum + set[index], target, subset, subset_size + 1);
    //exclude index
    explore(index + 1, set, n, current_sum, target, subset, subset_size);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;
    int target = atoi(argv[1]);
    int n = argc - 2;
    int *set;
    set = malloc (sizeof(int) * n);
    if (!set)
        return 1;
    for (int i = 2; i < argc; i++)
        set[i - 2] = atoi(argv[i]);
    int *subset = malloc(sizeof(int) * n);
    if (!subset)
        return (free(set), 1);
    explore(0, set, n, 0, target, subset, 0);
    free(set);
    free(subset);
    return 0;
}
