#ifndef SIMULATION_H
#define SIMULATION_H

#include <grid.h>

extern Grid* grid;

void simulation_init();
void simulate_grid();
void simulate_sand(Grid* grid, uint16_t x, uint16_t y);
void simulate_water(Grid* grid, uint16_t x, uint16_t y);

#endif