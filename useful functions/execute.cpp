#include "execute.h"


#include <chrono>
#include <ratio>


double execute(const std::function<void()> &func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}
