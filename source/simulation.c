#include <simulation.h>
#include <grid.h>
#include <util.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Grid* grid;
Color sand_color;
Color solid_color;
Color water_color;
Color wood_color;

Particle empty_particle;
Particle sand_particle;
Particle solid_particle;
Particle water_particle;
Particle wood_particle;

uint8_t max_color_variation = 10;
uint16_t place_radius = 1; // Multiply of 2 pleaseeee
uint16_t selected_id = 1;

#define sand_id 1
#define water_id 2
#define solid_id 3
#define wood_id 4

void simulation_init()
{
    grid = create_grid(100, 100, 8);

    sand_color = color(163, 157, 114, 255);
    sand_particle = init_particle(sand_color, sand_id, -1.0);

    solid_color = color(85, 45, 45, 255);
    solid_particle = init_particle(solid_color, solid_id, -1.0);

    water_color = color(40, 100, 215, 180);
    water_particle = init_particle(water_color, water_id, -1.0);

    wood_color = color(112, 84, 31, 255);
    wood_particle = init_particle(wood_color, wood_id, -1.0);
}

Vector2 cell_mouse_in()  
{  
  Vector2 mouse_pos;  
  float mouse_x = GetMousePosition().x / grid->cell_size;
  float mouse_y = GetMousePosition().y / grid->cell_size;

  if (mouse_x < 0 || mouse_x >= grid->width || mouse_y < 0 || mouse_y >= grid->height)  
  {  
      mouse_pos.x = 0;  
      mouse_pos.y = 0;  
  }  
  else  
  {  
      mouse_pos.x = mouse_x;
      mouse_pos.y = mouse_y;
  }  
  mouse_pos.x = round(mouse_pos.x);
  mouse_pos.y = round(mouse_pos.y);
  return mouse_pos;
}

void simulate_sand(Grid* grid, uint16_t x, uint16_t y)
{
    Particle* below_particle = &grid->cells[y + 1][x];

    if ((below_particle->id == 0 || below_particle->id == water_id) && !grid->cells[y][x].updated_this_frame) // Below cell is empty or water
    {
        swap_cells(grid, x, y, x, y + 1);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    if (below_particle->id == solid_id || below_particle->id == wood_id) return;
    Particle* below_left_particle = &grid->cells[y + 1][x - 1];
    Particle* below_right_particle = &grid->cells[y + 1][x + 1];

    if ((below_right_particle->id == 0 && below_left_particle->id == 0 || below_right_particle->id == water_id && below_left_particle->id == water_id) && !grid->cells[y][x].updated_this_frame)
    {
        int r = rand();
        r = r % 2 == 0 ? 1 : -1;
        swap_cells(grid, x, y, x + r, y + 1);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    if ((below_left_particle->id == 0 || below_left_particle->id == water_id) && !grid->cells[y][x].updated_this_frame) // Below left cell is empty
    {
        swap_cells(grid, x, y, x - 1, y + 1);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    if ((below_right_particle->id == 0 || below_right_particle->id == water_id) && !grid->cells[y][x].updated_this_frame) // Below right cell is empty
    {
        swap_cells(grid, x, y, x + 1, y + 1);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }
    grid->cells[y][x].updated_this_frame = false;
}
void simulate_water(Grid* grid, uint16_t x, uint16_t y)
{
    Particle* below_particle = &grid->cells[y + 1][x];

    if (below_particle->id == 0 && !grid->cells[y][x].updated_this_frame) // Below cell is empty
    {
        swap_cells(grid, x, y, x, y + 1);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    Particle* left_particle = &grid->cells[y][x - 1];
    Particle* right_particle = &grid->cells[y][x + 1];

    if (right_particle->id == 0 && left_particle->id == 0 && !grid->cells[y][x].updated_this_frame)
    {
        int r = rand();
        r = r % 2 == 0 ? 1 : -1;
        swap_cells(grid, x, y, x + r, y);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    if (left_particle->id == 0 && !grid->cells[y][x].updated_this_frame)
    {
        swap_cells(grid, x, y, x - 1, y);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    if (right_particle->id == 0&& !grid->cells[y][x].updated_this_frame)
    {
        swap_cells(grid, x, y, x + 1, y);
        grid->cells[y][x].updated_this_frame = true;
        return;
    }

    grid->cells[y][x].updated_this_frame = false;
}

void simulate_grid()
{
    // Change place radius
    place_radius += (int)GetMouseWheelMove()*2 + place_radius > 0 ? (int)GetMouseWheelMove() * 2 : 0;
    printf("%u\n",place_radius);
    DrawRectangleLines(cell_mouse_in().x*grid->cell_size,cell_mouse_in().y * grid->cell_size, place_radius/2 * grid->cell_size, place_radius / 2 * grid->cell_size, WHITE);
    uint16_t temp_select = (GetCharPressed());
    if (temp_select)
    {
        selected_id = temp_select - '0';
        printf("%u\n", selected_id);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Particle set_to = sand_particle;
        switch (selected_id)
        {
            case sand_id:
                set_to = sand_particle;
                break;
            case solid_id:
                set_to = solid_particle;
                break;
            case water_id:
                set_to = water_particle;
                break;
            case wood_id:
                set_to = wood_particle;
                break;
            case 0:
                set_to = empty_particle;
                break;
        }
        Color color_variation = set_to.color;
        uint8_t set_variation = rand() % max_color_variation+1;
        color_variation.r = (set_to.color.r - max_color_variation/2) + rand() % max_color_variation + 1;
        color_variation.g = (set_to.color.g - max_color_variation / 2) + rand() % max_color_variation + 1;
        color_variation.b = (set_to.color.b - max_color_variation / 2) + rand() % max_color_variation + 1;
        set_to.color = color_variation;
        if (place_radius != 1)
        {
            for (size_t i = 0; i < (int)place_radius / 2; i++)
            {
                for (size_t j = 0; j < (int)place_radius / 2; j++)
                {
                    if (get_cell(grid, (uint16_t)cell_mouse_in().x + i, (uint16_t)cell_mouse_in().y + j).id != set_to.id)
                    {
                        set_cell(grid, (uint16_t)cell_mouse_in().x + i, (uint16_t)cell_mouse_in().y + j, set_to);
                    }

                }
            }
        }
        else
        {
            if (get_cell(grid, (uint16_t)cell_mouse_in().x, (uint16_t)cell_mouse_in().y).id != set_to.id)
            {
                set_cell(grid, (uint16_t)cell_mouse_in().x, (uint16_t)cell_mouse_in().y, set_to);
            }
        }
    }
    for (uint16_t y = 0; y < grid->height; y++)
    {
        for (uint16_t x = 0; x < grid->width; x++)
        {
            if (grid->cells[y][x].id == 0) continue; // If cell is empty, next

            if (y + 1 >= grid->height) continue; // If below cell is outside grid, next

            switch (grid->cells[y][x].id)
            {
                case sand_id:
                    simulate_sand(grid, x, y);
                    break;
                case water_id:
                    simulate_water(grid, x, y);
                    break;
            }
                
        }
    }
}
