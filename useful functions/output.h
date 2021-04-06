#pragma once

#include <ostream>
#include <vector>

namespace useful_func
{
   /// <summary>
   /// creates a graph view in an output stream
   /// </summary>
   /// <param name="output"></param>
   /// <param name="graph"> graph representation </param>
   void output(std::ostream &output, std::vector<std::vector<int>> &graph);
}
