#include "mlx.h"

// #define WIDTH 800
// #define HEIGHT 600
// #define GRID_SIZE 20

// void draw_grid(void *mlx_ptr, void *win_ptr)
// {
//     int x, y;

//     // Clear the window
//     mlx_clear_window(mlx_ptr, win_ptr);

//     // Draw vertical lines
//     x = GRID_SIZE;
//     while (x < WIDTH)
//     {
//         y = 0;
//         while (y < HEIGHT)
//         {
//             mlx_pixel_put(mlx_ptr, win_ptr, (x + GRID_SIZE), (y + GRID_SIZE), 0xFFFFFF); // Set pixel color to white
//             y += GRID_SIZE;
//         }
//         x += GRID_SIZE;
//     }

//     // Draw horizontal lines
//     y = GRID_SIZE;
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             mlx_pixel_put(mlx_ptr, win_ptr, (x + GRID_SIZE), (y + GRID_SIZE), 0xFFFFFF); // Set pixel color to white
//             x += GRID_SIZE;
//         }
//         y += GRID_SIZE;
//     }
// }

// void draw_map(t_data *map) {
//     int x, y;

//     y = 0;
//     while (y < map->height) {
//         x = 0;
//         while (x < map->width) {
//             if (map->grid[y][x] == '1') {
//                 mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Wall color (white)
//             } else if (map->grid[y][x] == '0') {
//                 mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000); // Floor color (black)
//             } else {
//                 // Handle other map elements (e.g., objects, doors, etc.)
//             }

//             x++;
//         }
//         y++;
//     }
// }

int map[10][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
};


#define TILE_SIZE 32


void draw_map(void *mlx_ptr, void *win_ptr, int width, int height) {
    int x, y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int pixel_x = x * TILE_SIZE;
            int pixel_y = y * TILE_SIZE;

            // Set color based on the cell type
            if (map[y][x] == 1) {
                mlx_pixel_put(mlx_ptr, win_ptr, pixel_x, pixel_y, 0xFFFFFF); // Wall color (white)
            } else if (map[y][x] == 0) {
                mlx_pixel_put(mlx_ptr, win_ptr, pixel_x, pixel_y, 0x000000); // Floor color (black)
            }
        }
    }
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    int x, y;
    int width = 800, height = 600;

    // Initialize the minilibx
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, width, height, "cub3d");
    draw_map(mlx_ptr, win_ptr, width, height);
    // y = 0;
    // while (y < height)
    // {
    //     x = 0;
    //     while (x < width)
    //     {
    //         if (map[y][x] == 1)
    //             mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Wall color (white)
    //         else if (map[y][x] == 0)
    //            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000); // Floor color (black)
    //         x++;
    //     }
    //     y++;
    // }
    // draw_grid(mlx_ptr, win_ptr);

    // Start the event loop
    mlx_loop(mlx_ptr);

    return 0;
}