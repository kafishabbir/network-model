#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "visualize/flow.h"

namespace visualize
{
    class Menu
    {
		static const std::string FOLDER_NAME_FIGURES;
		static const std::string FILE_NAME_INITIAL;
		static const std::string FILE_NAME_LIST_FIGURES;

		std::vector<std::pair<std::string, std::string>>
		caption_and_code_v;

		void append(
			const std::vector<std::pair<std::string, std::string>>&
			caption_and_code_new_v
		);

        public:
        // strings<file_name, file_content>
        void flow(
			const States& states
		);

		std::vector<std::pair<std::string, std::string>> out() const;
    };
}

#endif
