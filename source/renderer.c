#include <renderer.h>
#include <raylib.h>
#include <grid.h>
#include <simulation.h>
#include <main.h>



void draw_grid()
{

    for (uint16_t y = 0; y < grid->height; y++)
    {
        for (uint16_t x = 0; x < grid->width; x++)
        {
            //DrawRectangleLines(x * grid->cell_size, y * grid->cell_size, grid->cell_size, grid->cell_size, GRAY);
            if (grid->cells[y][x].id != 0)
            {
                DrawRectangle(x * grid->cell_size, y * grid->cell_size, grid->cell_size, grid->cell_size, grid->cells[y][x].color);
            }
        }
    }
}

void draw_loop()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    draw_grid();

    EndDrawing();
}
