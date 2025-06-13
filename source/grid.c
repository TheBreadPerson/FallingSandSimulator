#include <grid.h>
#include <stdlib.h>

Grid* create_grid(uint16_t width, uint16_t height, uint8_t cell_size)
{
    Grid* grid = (Grid*)malloc(sizeof(Grid));
    if (!grid)
    {
        printf("Failed to allocate memory for grid\n");
        return NULL;
    }

    grid->width = width;
    grid->height = height;
    grid->cell_size = cell_size;

    // Allocate memory for the 2D array
    grid->cells = (Particle**)malloc(height * sizeof(Particle*));
    if (!grid->cells)
    {
        free(grid);
        printf("Failed to allocate memory for grid cells\n");
        return NULL;
    }

    for (uint16_t i = 0; i < height; i++)
    {
        grid->cells[i] = (Particle*)calloc(width, sizeof(Particle));
        if (!grid->cells[i])
        {
            // Free previously allocated rows
            for (uint16_t j = 0; j < i; j++)
            {
                free(grid->cells[j]);
            }
            free(grid->cells);
            free(grid);
            printf("Failed to allocate memory for grid row\n");
            return NULL;
        }
    }

    return grid;
}

void destroy_grid(Grid* grid)
{
    if (grid)
    {
        for (uint16_t i = 0; i < grid->height; i++)
        {
            free(grid->cells[i]);
        }
        free(grid->cells);
        free(grid);
    }
}

Particle init_particle(Color color, uint32_t id, float lifetime)
{
    Particle temp_particle;
    temp_particle.color = color;
    temp_particle.id = id;
    temp_particle.lifetime = lifetime;
    return temp_particle;
}

Particle get_cell(Grid* grid, uint16_t x, uint16_t y)
{
    if (x >= grid->width || y >= grid->height)
    {
        printf("Coordinates out of bounds\n");
        Particle empty_particle = { 0 }; // Return an empty particle as a safe fallback
        return empty_particle;
    }
    return grid->cells[y][x];
}

void set_cell(Grid* grid, uint16_t x, uint16_t y, Particle particle)
{
    if (x < grid->width && y < grid->height)
    {
        grid->cells[y][x] = particle;
    }
}

void swap_cells(Grid* grid, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (x1 < grid->width && y1 < grid->height && x2 < grid->width && y2 < grid->height)
    {
        Particle temp = grid->cells[y1][x1];
        grid->cells[y1][x1] = grid->cells[y2][x2];
        grid->cells[y2][x2] = temp;

        grid->cells[y1][x1].updated_this_frame = 1;
        grid->cells[y2][x2].updated_this_frame = 1;
    }
    else
    {
        printf("One or more coordinates are outside of the grid: Can't swap\n");
    }
}

_Bool cell_in_bounds(Grid* grid, uint16_t x, uint16_t y)
{
	return (x < grid->width && y < grid->height);
}

uint16_t particle_count(Grid* grid)
{
    uint16_t count = 0;
    for (size_t x = 0; x < grid->width; x++)
    {
        for (size_t y = 0; y < grid->height; y++)
        {
            if (grid->cells[y][x].id != 0) count++;
        }
    }
    return count;
}
