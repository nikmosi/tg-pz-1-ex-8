#include <iostream>
#include <fstream>

#include "pathfinder.h"


int main()
{
   auto s = std::ifstream("input.txt");
   auto *graph = path::input(s);

   if(graph)
   {
      bool r = 0;
      const double time = path::execute([graph, &r]() { r = path::has_path_dfs(*graph, 1, 4); });
      std::cout << time << " ms" << std::endl << (r ? "route exists" : "route does not exist") << std::endl;
   }


   return 0;
}


