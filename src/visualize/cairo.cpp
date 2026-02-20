#include "visualize/cairo.h"
#include "global/decl.h"
#include <filesystem>

const int visualize::Cairo::length_shortest_side = 2000;
const int visualize::Cairo::margin = 100;
const std::string visualize::Cairo::png_extension = ".png";
const std::string visualize::Cairo::folder_name = decl::nps_latex_plot::nps_folder::results + "flow/images/";

const visualize::Cairo::Color visualize::Cairo::Color::white = visualize::Cairo::Color(1.00, 1.00, 1.00);
const visualize::Cairo::Color visualize::Cairo::Color::grey_light = visualize::Cairo::Color(0.83, 0.83, 0.83);
const visualize::Cairo::Color visualize::Cairo::Color::grey = visualize::Cairo::Color(0.50, 0.50, 0.50);
const visualize::Cairo::Color visualize::Cairo::Color::grey_dark = visualize::Cairo::Color(0.25, 0.25, 0.25);
const visualize::Cairo::Color visualize::Cairo::Color::black = visualize::Cairo::Color(0.00, 0.00, 0.00);
const visualize::Cairo::Color visualize::Cairo::Color::brown = visualize::Cairo::Color(0.55, 0.34, 0.29);
const visualize::Cairo::Color visualize::Cairo::Color::red = visualize::Cairo::Color(0.84, 0.15, 0.16);
const visualize::Cairo::Color visualize::Cairo::Color::orange = visualize::Cairo::Color(1.00, 0.50, 0.05);
const visualize::Cairo::Color visualize::Cairo::Color::yellow = visualize::Cairo::Color(1.00, 1.00, 0.00);
const visualize::Cairo::Color visualize::Cairo::Color::cabbage = visualize::Cairo::Color(0.56, 0.93, 0.56);
const visualize::Cairo::Color visualize::Cairo::Color::green = visualize::Cairo::Color(0.17, 0.63, 0.17);
const visualize::Cairo::Color visualize::Cairo::Color::cyan = visualize::Cairo::Color(0.09, 0.75, 0.81);
const visualize::Cairo::Color visualize::Cairo::Color::blue = visualize::Cairo::Color(0.12, 0.47, 0.71);
const visualize::Cairo::Color visualize::Cairo::Color::violet = visualize::Cairo::Color(0.58, 0.40, 0.74);
const visualize::Cairo::Color visualize::Cairo::Color::puple = visualize::Cairo::Color(0.58, 0.40, 0.74);  // Note: Typo in original "puple"

visualize::Cairo::Color::Color(const double red, const double green, const double blue):
	r(red),
	g(green),
	b(blue)
{}

visualize::Cairo::Color::Color():
	r(-1),
	g(-1),
	b(-1)
{}


visualize::Cairo::Cairo(
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


visualize::Cairo::~Cairo()
{
	std::filesystem::create_directories(folder_name);
	const std::string& full_name = folder_name + file_name + png_extension;
	cairo_status_t status = cairo_surface_write_to_png(surface, full_name.c_str());

	if (status != CAIRO_STATUS_SUCCESS)
	{
		std::cerr << "Error saving " << full_name << ": "
		<< cairo_status_to_string(status) << std::endl;
	}
}

std::pair<double, double> visualize::Cairo::transform(
	const double x,
	const double y
)
{
	return {x * scale, - y * scale};
}

void visualize::Cairo::rectangle(
	const double x,
	const double y,
	const double width,
	const double height
)
{
	cairo_rectangle(cr, x, y, width, height);
	cairo_fill(cr);
}


void visualize::Cairo::circle(
	const double x,
	const double y,
	const double radius
)
{
	cairo_arc(cr, x, y, radius, 0, 2.0 * decl::pi);
	cairo_fill(cr);
}



void visualize::Cairo::rectangle(
	const double x,
	const double y,
	const double width,
	const double height,
	const visualize::Cairo::Color& color
)
{
	cairo_set_source_rgb(cr, color.r, color.g, color.b);
	rectangle(x, y, width, height);
}


void visualize::Cairo::circle(
	const double x,
	const double y,
	const double radius,
	const visualize::Cairo::Color& color
)
{
	cairo_set_source_rgb(cr, color.r, color.g, color.b);
	circle(x, y, radius);
}


double visualize::Cairo::find_scale(const double width, const double height)
{
	const double short_side = (length_shortest_side - 2 * margin);
	return short_side / std::min(width, height);
}

int visualize::Cairo::find_width(const double width, const double height)
{
	return width * scale + 2 * margin;
}

int visualize::Cairo::find_height(const double width, const double height)
{
	return height * scale + 2 * margin;
}


void visualize::Cairo::begin_shift_rotate(
	const double x,
	const double y,
	const double angle
)
{
	cairo_save(cr);
	cairo_translate(cr, x, y);
	cairo_rotate(cr, angle);
}


void visualize::Cairo::end_shift_rotate()
{
	cairo_restore(cr);
}


void visualize::Cairo::set_text_mode()
{
	cairo_identity_matrix(cr);
	cairo_translate(cr, margin, height - margin);
}
