#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "visualize/flow.h"

namespace visualize
{
    class Menu
    {
		static const std::string FILE_NAME_INITIAL;
		static const std::string FILE_NAME_LIST_FIGURES;

		std::vector<global::str_pair>
		caption_and_code_v;

		void append(
			const std::vector<global::str_pair>&
			caption_and_code_new_v
		);

        public:
        // strings<file_name, file_content>
        void flow(
			const nst::nst::States& states
		);

		std::vector<global::str_pair> out() const;
    };
}

#endif
