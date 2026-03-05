#ifndef OUTPUT_JSON_H
#define OUTPUT_JSON_H

#include "dst/system.h"
#include <nlohmann/json.hpp>

namespace output
{
	struct Json
	{
		const std::string file_name;
		nlohmann::json j;
		
	public:
		Json(const std::string& file_name);
		~Json();
		
		void add(const dst::System& system, const int id_simulation);
	};
}

#endif
