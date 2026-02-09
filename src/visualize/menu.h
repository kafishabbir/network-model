#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "visualize/flow.h"
#include "global/decl.h"

namespace visualize
{
    class Menu
    {

		std::vector<dst::str_pair> caption_and_code_v;

		void append(
			const std::vector<dst::str_pair>& caption_and_code_new_v
		);

		static std::string generate_file_name_from_index(const int i);
        public:
        // strings<file_name, file_content>
        void flow(
			dst::States& states
		);

		std::vector<dst::str_pair> out() const;
    };
}

#endif
