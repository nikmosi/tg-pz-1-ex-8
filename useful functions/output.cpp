
#include "output.h"

void output(std::ostream &output, const std::vector<std::vector<int>> *&graph)
{
   const auto n = graph->size();
   auto m = 0;

   for(const auto &i : graph)
      m += i.size();
   m /= 2;
   output << n << " " << m << std::endl;

   for(size_t i = 0; i < n; ++i)
   {
      const auto &e = graph->at(i);
      const auto s = e.size();
      for(size_t j = 0; j < s; ++j)
         output << i << e.at(j) << std::endl;
   }
}
