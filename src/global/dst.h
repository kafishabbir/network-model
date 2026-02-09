#ifndef GLOBAL_DST_H
#define GLOBAL_DST_H

#include "nst/state.h"
#include <string>

namespace dst
{
	typedef std::vector<nst::Node> Nodes;
	typedef std::vector<nst::State> States; // Sadly not the United States of America
	typedef std::vector<nst::Tube> Tubes;
	typedef std::vector<std::vector<double>> Matrix;
	typedef std::pair<std::string, std::string> str_pair;
}

#endif
