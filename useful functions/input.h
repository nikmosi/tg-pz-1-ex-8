#pragma once
#include <istream>
#include <vector>


namespace useful_func
{
   /// <summary>
   /// creates a graph view from an input stream
   /// </summary>
   /// <param name="input"></param>
   /// <returns> graph representation </returns>
   std::vector<std::vector<int>> *input(std::istream &input);
}