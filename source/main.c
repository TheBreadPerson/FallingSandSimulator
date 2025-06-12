#include <raylib.h>
#include <renderer.h>
#include <simulation.h>
#include <main.h>

extern const int screen_width = 800;
extern const int screen_height = 800;

int init(void)
{
    
    InitWindow(screen_width, screen_height, "Simulation");
    
    SetTargetFPS(300);

	simulation_init();

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
    }

    CloseWindow();
    destroy_grid(grid);

    return 0;
}