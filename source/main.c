#include <raylib.h>
#include <renderer.h>
#include <simulation.h>
#include <main.h>

extern const int screen_width = 800;
extern const int screen_height = 800;
uint16_t particle_count_text;

int init(void)
{
    
    InitWindow(screen_width, screen_height, "Simulation");
    
    SetTargetFPS(0);

	simulation_init();

    particle_count_text = particle_count(grid);

	return 0;
}

int main(void)
{
    init();

    // Main game loop
    while (!WindowShouldClose())
    {
        draw_loop();
        simulate_grid(0.0);
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, DARKGRAY);
        if ((int)GetTime() % 2 == 0) particle_count_text = particle_count(grid);
        DrawText(TextFormat("PARTICLES: %i", particle_count_text), screen_width - 300, 10, 20, DARKGRAY);
    }

    CloseWindow();
    destroy_grid(grid);

    return 0;
}