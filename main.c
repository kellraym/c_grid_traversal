#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct GridSpace
{
    char ** grid;
    int * grid_size;
    size_t x_pos;
    size_t y_pos;
} GridSpace;

GridSpace * GridSpace_new(size_t x, size_t y)
{
    GridSpace *new_grid = (GridSpace *)calloc(1, sizeof(GridSpace));
    new_grid->grid_size = (int *)calloc(2, sizeof(int));
    new_grid->grid_size[0] = x + 1;
    new_grid->grid_size[1] = y;
    new_grid->x_pos = 0;
    new_grid->y_pos = 0;
    new_grid->grid = (char **)calloc((x + 1) * y, sizeof(char));
    for (int i = 0; i < y; i++)
    {   
        char *row = (char *)calloc(x + 1, sizeof(char));
        for (int j = 0; j < x; j++)
        {
            if (i == 0 && j == 0)
            {
                row[j] = 'x';
            }
            else
            {
                row[j] = 'o';
            }
        }
        new_grid->grid[i] = row;
    }
    return new_grid;
}

void GridSpace_swap(char *c1, char *c2)
{
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void GridSpace_print(GridSpace *g)
{
    for (int i = 0; i < g->grid_size[1]; i++)
        printf("%s\n", g->grid[i]);
}

void GridSpace_free(GridSpace *g)
{
    for (int i = 0; i < g->grid_size[1]; i++)
        free(g->grid[i]);
    free(g->grid);
    free(g->grid_size);
    free(g);
}

void GridSpace_move(GridSpace *g, char c)
{
    size_t x = g->x_pos;
    size_t y = g->y_pos;
    if (c == 'd' && g->x_pos < g->grid_size[0])
    {
        GridSpace_swap(&g->grid[y][x], &g->grid[y][x + 1]);
        g->x_pos++;
    }
    else if (c == 'a' && g->x_pos > 0)
    {
        GridSpace_swap(&g->grid[y][x], &g->grid[y][x - 1]);
        g->x_pos--;
    }
    else if (c == 'w' && g->y_pos > 0)
    {
        GridSpace_swap(&g->grid[y][x], &g->grid[y - 1][x]);
        g->y_pos--;
    }
    else if (c == 's' && g->y_pos < g->grid_size[0])
    {
        GridSpace_swap(&g->grid[y][x], &g->grid[y + 1][x]);
        g->y_pos++;
    }
}

int main()
{
    GridSpace *g = GridSpace_new(20, 20);
    GridSpace_print(g);
    
    char choice;
    while (choice != 'q' && choice != 'Q')
    {
        scanf("%c", &choice);
        GridSpace_move(g, choice);
        // TODO: clear screen instread of next line
        printf("\n");
        GridSpace_print(g);
    }
    GridSpace_move(g, 'd');
    printf("\n");
    GridSpace_print(g);
    GridSpace_move(g, 'a');
    printf("\n");
    GridSpace_print(g);
    GridSpace_move(g, 's');
    printf("\n");
    GridSpace_print(g);
    GridSpace_move(g, 'w');
    printf("\n");
    GridSpace_print(g);
    
    GridSpace_free(g);
    return 0;
}
