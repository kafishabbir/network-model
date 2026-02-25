#include "output-raster/cairo.h"
#include "global/decl.h"
#include <filesystem>

const int output_raster::Cairo::length_shortest_side = 2000;
const int output_raster::Cairo::margin = 30;

const output_raster::Cairo::Color output_raster::Cairo::Color::white = output_raster::Cairo::Color(1.00, 1.00, 1.00);
const output_raster::Cairo::Color output_raster::Cairo::Color::grey_light = output_raster::Cairo::Color(0.8, 0.8, 0.8);
const output_raster::Cairo::Color output_raster::Cairo::Color::grey = output_raster::Cairo::Color(0.55, 0.55, 0.55);
const output_raster::Cairo::Color output_raster::Cairo::Color::grey_dark = output_raster::Cairo::Color(0.3, 0.3, 0.3);
const output_raster::Cairo::Color output_raster::Cairo::Color::black = output_raster::Cairo::Color(0.00, 0.00, 0.00);
const output_raster::Cairo::Color output_raster::Cairo::Color::brown = output_raster::Cairo::Color(0.55, 0.34, 0.29);
const output_raster::Cairo::Color output_raster::Cairo::Color::red = output_raster::Cairo::Color(0.84, 0.15, 0.16);
const output_raster::Cairo::Color output_raster::Cairo::Color::orange = output_raster::Cairo::Color(1.00, 0.50, 0.05);
const output_raster::Cairo::Color output_raster::Cairo::Color::yellow = output_raster::Cairo::Color(1.00, 1.00, 0.00);
const output_raster::Cairo::Color output_raster::Cairo::Color::cabbage = output_raster::Cairo::Color(0.56, 0.93, 0.56);
const output_raster::Cairo::Color output_raster::Cairo::Color::green = output_raster::Cairo::Color(0.17, 0.63, 0.17);
const output_raster::Cairo::Color output_raster::Cairo::Color::cyan = output_raster::Cairo::Color(0.09, 0.75, 0.81);
const output_raster::Cairo::Color output_raster::Cairo::Color::blue = output_raster::Cairo::Color(0.12, 0.47, 0.71);
const output_raster::Cairo::Color output_raster::Cairo::Color::violet = output_raster::Cairo::Color(0.58, 0.40, 0.74);
const output_raster::Cairo::Color output_raster::Cairo::Color::purple = output_raster::Cairo::Color(0.58, 0.40, 0.74);  // Note: Typo in original "puple"

output_raster::Cairo::Color::Color(const double red, const double green, const double blue):
	r(red),
	g(green),
	b(blue)
{}

output_raster::Cairo::Color::Color():
	r(-1),
	g(-1),
	b(-1)
{}


output_raster::Cairo::Cairo(
	const double width_network,
	const double height_network,
	const std::string& file_name
):
	scale(find_scale(width_network, height_network)),
	width(find_width(width_network, height_network)),
	height(find_height(width_network, height_network)),
	surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height)),
	cr(cairo_create(surface)),
	file_name(file_name)
{
	// Paint it white
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_translate(cr, margin, height - margin);
	cairo_scale(cr, scale, -scale);
}


output_raster::Cairo::~Cairo()
{
	const std::string& full_name = file_name + ".png";
	cairo_status_t status = cairo_surface_write_to_png(surface, full_name.c_str());

	if (status != CAIRO_STATUS_SUCCESS)
	{
		std::cerr << "Error saving " << full_name << ": "
		<< cairo_status_to_string(status) << std::endl;
	}
}

std::pair<double, double> output_raster::Cairo::transform(
	const double x,
	const double y
)
{
	return {x * scale, - y * scale};
}

void output_raster::Cairo::rectangle(
	const double x,
	const double y,
	const double width,
	const double height
)
{
	cairo_rectangle(cr, x, y, width, height);
	cairo_fill(cr);
}


void output_raster::Cairo::circle(
	const double x,
	const double y,
	const double radius
)
{
	cairo_arc(cr, x, y, radius, 0, 2.0 * decl::pi);
	cairo_fill(cr);
}



void output_raster::Cairo::rectangle(
	const double x,
	const double y,
	const double width,
	const double height,
	const output_raster::Cairo::Color& color
)
{
	cairo_set_source_rgb(cr, color.r, color.g, color.b);
	rectangle(x, y, width, height);
}


void output_raster::Cairo::circle(
	const double x,
	const double y,
	const double radius,
	const output_raster::Cairo::Color& color
)
{
	cairo_set_source_rgb(cr, color.r, color.g, color.b);
	circle(x, y, radius);
}


double output_raster::Cairo::find_scale(const double width, const double height)
{
	const double short_side = (length_shortest_side - 2 * margin);
	return short_side / std::min(width, height);
}

int output_raster::Cairo::find_width(const double width, const double height)
{
	return width * scale + 2 * margin;
}

int output_raster::Cairo::find_height(const double width, const double height)
{
	return height * scale + 2 * margin;
}


void output_raster::Cairo::begin_shift_rotate(
	const double x,
	const double y,
	const double angle
)
{
	cairo_save(cr);
	cairo_translate(cr, x, y);
	cairo_rotate(cr, angle);
}


void output_raster::Cairo::end_shift_rotate()
{
	cairo_restore(cr);
}


void output_raster::Cairo::set_text_mode()
{
	cairo_identity_matrix(cr);
	cairo_translate(cr, margin, height - margin);
}
