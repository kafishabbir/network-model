#ifndef VISUALIZE_CAIRO_H
#define VISUALIZE_CAIRO_H

namespace visualize
{
    class Cairo
	{
	private:
		static const int length_shortest_side;
		static const int margin;
		static const std::string png_extension;
		static const std::string folder_name;

		static int find_width(const double width, const double height);
		static int find_height(const double width, const double height);
		static double find_scale(const double width, const double height);

	public:
		class Color
		{
			public:

			const double r;
			const double g;
			const double b;

			static const Color white;
			static const Color grey_light;
			static const Color grey;
			static const Color grey_dark;
			static const Color black;
			static const Color brown;
			static const Color red;
			static const Color orange;
			static const Color yellow;
			static const Color cabbage;
			static const Color green;
			static const Color cyan;
			static const Color blue;
			static const Color violet;
			static const Color puple;

			Color(const double red, const double green, const double blue);
			Color();
			bool is_invalid() const;
		};

	private:
		const int width;
		const int height;
		const double scale;
		cairo_surface_t* surface;
		cairo_t* cr;
		const std::string file_name;

		std::pair<int, int> transform(
			const double x,
			const double y
		);

		int transform(
			const double x
		);

	public:
		Cairo(
			const double width_network,
			const double height_network,
			const std::string& file_name
		);

		~Cairo();

		void rectangle(
			const double x,
			const double y,
			const double width,
			const double height,
			const Color& color
		);
		//void circle();
		//void shift_rotate();
		//void mpos_horizontal_rectangles();

	};
}

#endif
