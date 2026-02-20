#include "program/function-trial.h"
#include <cairo/cairo.h>
#include <cmath>
#include <string>
#include <iostream>
#include <unistd.h>
namespace program
{
    void FunctionTrial::flow()
    {
        const int NUM_FILES = 10;
        const double WIDTH = 400;
        const double HEIGHT = 300;

        std::cout << "Saving " << NUM_FILES << " PNG files to: " << std::endl;

        for (int i = 1; i <= NUM_FILES; ++i)
        {
            // Create filename: flow_01.png, flow_02.png, etc.
            std::string filename = "flow_";
            if (i < 10) filename += "0";
            filename += std::to_string(i) + ".png";
			filename = "run/results/flow/figures/" + filename;
            std::cout << "  " << filename << std::endl;

            // Create surface
            cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
            cairo_t* cr = cairo_create(surface);

            // White background
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_paint(cr);

            // Draw something different for each file so you can see they're unique
            cairo_set_source_rgb(cr, 0.2, 0.5, 0.8);  // Blue color

            // Draw a circle that moves/changes with each file
            double x = WIDTH/2 + 50 * sin(i * 0.5);
            double y = HEIGHT/2 + 30 * cos(i * 0.3);
            double radius = 30 + 5 * sin(i);

            cairo_arc(cr, x, y, radius, 0, 2 * M_PI);
            cairo_fill(cr);

            // Add some text to identify the file number
            cairo_set_source_rgb(cr, 0, 0, 0);  // Black text
            cairo_set_font_size(cr, 20);
            cairo_move_to(cr, 20, 40);

            std::string text = "File #" + std::to_string(i);
            cairo_show_text(cr, text.c_str());

            // Save to PNG
            cairo_status_t status = cairo_surface_write_to_png(surface, filename.c_str());

            if (status != CAIRO_STATUS_SUCCESS)
            {
                std::cerr << "Error saving " << filename << ": "
                          << cairo_status_to_string(status) << std::endl;
            }

            // Cleanup
            cairo_destroy(cr);
            cairo_surface_destroy(surface);
        }

        std::cout << "Done! Files saved in: " << std::endl;

        // Print current working directory
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            std::cout << "  " << cwd << std::endl;
        }
    }
}
