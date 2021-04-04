#pragma once

#include <vector>

namespace path
{

   /// <summary>
   /// // checks if there is a way 'from' and 'to' in a 'graph' using breadth-first search
   /// </summary>
   /// <param name="graph"> Graph representation </param>
   /// <param name="from"> start point </param>
   /// <param name="to"> end point </param>
   /// <returns> 1 if there is a path, otherwise 0 </returns>
   bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

}