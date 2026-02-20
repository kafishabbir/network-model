#include "visualize/cairo.h"



Cairo::Cairo(
	const double width_network,
	const double height_network,
	const std::string& file_name
):
	width(find_width(width_network, height_network)),
	height(find_height(width_network, height_network)),
	scale(find_scale(width_network, height_network)),
	surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height)),
	cr(cairo_create(surface)),
	file_name(file_name)
{
	// Paint it white
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb(cr, 0, 0, 0);
}


Cairo::~Cairo()
{

	const std::string& full_name = folder_name + file_name + png_extension;

	cairo_status_t status = cairo_surface_write_to_png(surface, full_name.c_str());

	if (status != CAIRO_STATUS_SUCCESS)
	{
		std::cerr << "Error saving " << full_name << ": "
		<< cairo_status_to_string(status) << std::endl;
	}
}

const Cairo::Color Cairo::Color::white = Cairo::Color(1.00, 1.00, 1.00);
const Cairo::Color Cairo::Color::grey_light = Cairo::Color(0.83, 0.83, 0.83);
const Cairo::Color Cairo::Color::grey = Cairo::Color(0.50, 0.50, 0.50);
const Cairo::Color Cairo::Color::grey_dark = Cairo::Color(0.25, 0.25, 0.25);
const Cairo::Color Cairo::Color::black = Cairo::Color(0.00, 0.00, 0.00);
const Cairo::Color Cairo::Color::brown = Cairo::Color(0.55, 0.34, 0.29);
const Cairo::Color Cairo::Color::red = Cairo::Color(0.84, 0.15, 0.16);
const Cairo::Color Cairo::Color::orange = Cairo::Color(1.00, 0.50, 0.05);
const Cairo::Color Cairo::Color::yellow = Cairo::Color(1.00, 1.00, 0.00);
const Cairo::Color Cairo::Color::cabbage = Cairo::Color(0.56, 0.93, 0.56);
const Cairo::Color Cairo::Color::green = Cairo::Color(0.17, 0.63, 0.17);
const Cairo::Color Cairo::Color::cyan = Cairo::Color(0.09, 0.75, 0.81);
const Cairo::Color Cairo::Color::blue = Cairo::Color(0.12, 0.47, 0.71);
const Cairo::Color Cairo::Color::violet = Cairo::Color(0.58, 0.40, 0.74);
const Cairo::Color Cairo::Color::puple = Cairo::Color(0.58, 0.40, 0.74);  // Note: Typo in original "puple"


Cairo::Color::Color(const double red, const double green, const double blue):
	r(red),
	g(green),
	b(blue)
{}

Cairo::Color::Color():
	r(-1),
	g(-1),
	b(-1)
{}

bool Cairo::Color::is_invalid() const
{
	return r < 0 || g < 0 || b < 0;
}

const int Cairo::length_shortest_side = 2000;
const int Cairo::margin = 10;
const std::string Cairo::png_extension = ".png";
const std::string Cairo::folder_name = "images/";

int Cairo::find_width(const double width, const double height)
{
	const double scale = find_scale(width, height);

	return width * scale + 2 * margin;
}

int Cairo::find_height(const double width, const double height)
{
	const double scale = find_scale(width, height);

	return height * scale + 2 * margin;
}

double Cairo::find_scale(const double width, const double height)
{
	const double short_side = (length_shortest_side - 2 * margin);
	if(width < height)
	{
		return short_side / width;
	}

	return short_side / height;
}


std::pair<int, int> Cairo::transform(
	const double x,
	const double y
)
{
	const int x_int = x * scale + margin;
	const int y_int = - y * scale + height - margin;

	return {x_int, y_int};
}

int Cairo::transform(
	const double x
)
{
	return scale * x;
}

void Cairo::rectangle(
	const double x_d,
	const double y_d,
	const double width_d,
	const double height_d,
	const Color& color
)
{
	const auto& [x, y] = transform(x_d, y_d);
	const int width = transform(width_d);
	const int height = transform(height_d);

	cairo_set_source_rgb(cr, color.r, color.g, color.b);
	cairo_rectangle(cr, x, y, width, height);
	cairo_fill(cr);

}
