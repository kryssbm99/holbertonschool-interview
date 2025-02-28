#include "sandpiles.h"

/**
 * is_stable - Determines if a sandpile is stable
 * @grid: A 3x3 matrix representing the sandpile
 *
 * Description: A sandpile is considered stable if no cell contains more than 3 grains.
 *
 * Return: 1 if the sandpile is stable, 0 if it is unstable.
 */
int is_stable(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i][j] > 3)
                return (0);
        }
    }
    return (1);
}

/**
 * topple - Redistributes grains from unstable cells in a sandpile
 * @grid: A 3x3 matrix representing the sandpile
 *
 * Description: Any cell with 4 or more grains will topple, distributing one grain
 *              to each of its adjacent cells (up, down, left, right).
 *
 * Return: Nothing (modifies the grid in place).
 */
void topple(int grid[3][3])
{
    int i, j, copy_grid[3][3];

    /* Create a copy of the grid to store the new state */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            copy_grid[i][j] = grid[i][j];
        }
    }

    /* Topple unstable cells */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i][j] >= 4)
            {
                copy_grid[i][j] -= 4;
                if (i + 1 < 3) copy_grid[i + 1][j] += 1;
                if (i - 1 >= 0) copy_grid[i - 1][j] += 1;
                if (j + 1 < 3) copy_grid[i][j + 1] += 1;
                if (j - 1 >= 0) copy_grid[i][j - 1] += 1;
            }
        }
    }

    /* Update the original grid */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            grid[i][j] = copy_grid[i][j];
        }
    }
}

/**
 * sandpiles_sum - Adds two stable sandpiles and stabilizes the result
 * @grid1: The first 3x3 sandpile (modified in place to store the result)
 * @grid2: The second 3x3 sandpile
 *
 * Description: This function adds the corresponding cells of both sandpiles.
 *              If the resulting sandpile is unstable, it repeatedly topples
 *              until stability is reached, printing intermediate unstable states.
 *
 * Return: Nothing (modifies grid1 in place).
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
    int i, j;

    /* Add corresponding cells of grid1 and grid2 */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            grid1[i][j] += grid2[i][j];
        }
    }

    /* Stabilize the grid if necessary */
    while (!is_stable(grid1))
    {
        printf("=\n");
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (j)
                    printf(" ");
                printf("%d", grid1[i][j]);
            }
            printf("\n");
        }
        topple(grid1);
    }
}
