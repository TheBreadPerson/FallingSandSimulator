#include <simulation.h>
#include <grid.h>
#include <stdio.h>

Grid* grid;
Color sand_color;
Particle sand_particle;

void simulation_init()
{
    grid = create_grid(800, 800, 1);
    sand_color.r = 163;
    sand_color.g = 157;
    sand_color.b = 114;
    sand_color.a = 255;
    sand_particle.color = sand_color;
    sand_particle.id = 1;
    sand_particle.lifetime = -1.0;
    /*set_cell(grid, 4, 3, sand_particle);
    set_cell(grid, 4, 5, sand_particle);*/
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

  return mouse_pos;  
}

void simulate_grid()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        grid->cells[(uint16_t)cell_mouse_in().y][(uint16_t)cell_mouse_in().x] = sand_particle;
        grid->cells[(uint16_t)cell_mouse_in().y-1][(uint16_t)cell_mouse_in().x] = sand_particle;
        grid->cells[(uint16_t)cell_mouse_in().y+1][(uint16_t)cell_mouse_in().x] = sand_particle;
        grid->cells[(uint16_t)cell_mouse_in().y][(uint16_t)cell_mouse_in().x-1] = sand_particle;
        grid->cells[(uint16_t)cell_mouse_in().y][(uint16_t)cell_mouse_in().x+1] = sand_particle;
    }
    for (uint16_t y = 0; y < grid->height; y++)
    {
        for (uint16_t x = 0; x < grid->width; x++)
        {
            if (grid->cells[y][x].id == 0) continue; // If cell is empty, next

            if (y + 1 >= grid->height) continue; // If below cell is outside grid, next

            Particle* below_particle = &grid->cells[y + 1][x];
            
            if (below_particle->id == 0 && !grid->cells[y][x].updated_this_frame) // Below cell is empty
            {
                swap_cells(grid, x, y, x, y + 1);
                grid->cells[y][x].updated_this_frame = 0;
                continue;
            }
            
            Particle* below_left_particle = &grid->cells[y + 1][x - 1];
            if (below_left_particle->id == 0 && !grid->cells[y][x].updated_this_frame) // Below cell is empty
            {
                swap_cells(grid, x, y, x-1, y + 1);
                grid->cells[y][x].updated_this_frame = 0;
                continue;
            }

            Particle* below_right_particle = &grid->cells[y + 1][x + 1];
            if (below_right_particle->id == 0 && !grid->cells[y][x].updated_this_frame) // Below cell is empty
            {
                swap_cells(grid, x, y, x + 1, y + 1);
                grid->cells[y][x].updated_this_frame = 0;
                continue;
            }
            grid->cells[y][x].updated_this_frame = 0;
        }
    }
}
