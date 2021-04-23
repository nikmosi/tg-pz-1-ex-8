#pragma once

#include <ostream>
#include <vector>
#include <set>

namespace useful_func
{
	/// <summary>
	/// creates a graph view in an output stream
	/// </summary>
	/// <param name="output"></param>
	/// <param name="graph"> graph representation </param>
	inline void output(std::ostream& output, std::vector<std::vector<int>>& graph)
	{
		const auto n = graph.size();
		auto m = 0;

		for (const auto& i : graph)
			m += i.size();
		m /= 2;
		output << n << " " << m << std::endl;

		std::set<int>* marked = new std::set<int>();
		for (size_t i = 0; i < n; ++i)
		{
			marked->insert(i);
			const auto& e = graph.at(i);
			const auto s = e.size();
			for (size_t j = 0; j < s; ++j)
				if (marked->count(e.at(j)) == 0)
					output << i << " " << e.at(j) << std::endl;
		}
	}
}
