#pragma once
#include <functional>
#include <chrono>
#include <ratio>

namespace useful_func
{
   /// <summary>
   /// calculates the running time of func
   /// </summary>
   /// <param name="func"></param>
   /// <returns></returns>
   inline double execute(const std::function<void()> &func)
   {
      const auto start = std::chrono::high_resolution_clock::now();
      func();
      const auto end = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
   }
   
}

