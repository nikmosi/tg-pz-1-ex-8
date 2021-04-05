#include "input.h"

std::vector<std::vector<int>> *input(std::istream &input)
{
   if (input)
   {
      int n, m;
      input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      for (int i = 0; i < m; ++i)
      {
         int a, b;
         input >> a >> b;
         graph->at(a).push_back(b);
         graph->at(b).push_back(a);
      }
      return graph;
   }
   return nullptr;
}
