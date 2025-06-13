#ifndef GRID_H
#define GRID_H

#include <stdint.h>
#include <raylib.h>


typedef struct
{
	uint32_t id; // 32 bits
	float lifetime; // 32 bits
	Color color; // 24 bits
	_Bool updated_this_frame;
} Particle;

typedef struct  
{  
uint16_t width;  
uint16_t height;  
uint8_t cell_size;  
Particle** cells; // Dynamic 2D array
} Grid;

Grid* create_grid(uint16_t width, uint16_t height, uint8_t cell_size);
void destroy_grid(Grid* grid);

Particle init_particle(Color color, uint32_t id, float lifetime);
Particle get_cell(Grid* grid, uint16_t x, uint16_t y);
void set_cell(Grid* grid, uint16_t x, uint16_t y, Particle particle);
void swap_cells(Grid* grid, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
_Bool cell_in_bounds(Grid* grid, uint16_t x, uint16_t y);

uint16_t particle_count(Grid * grid);

#endif