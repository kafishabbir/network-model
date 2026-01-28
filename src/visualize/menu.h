#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "visualize/flow.h"

namespace visualize
{
    class Menu
    {
        public:
        // strings<file_name, file_content>
        std::vector<std::pair<std::string, std::string>> flow(const State& state);
    };
}

#endif
