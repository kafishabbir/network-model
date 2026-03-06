#ifndef OUTPUT_JSON_H
#define OUTPUT_JSON_H

#include "dst/system-output.h"
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
		
		void add(const dst::SystemOutput& system, const int id_simulation);
	};
}

#endif
