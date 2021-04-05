#pragma once
#include <functional>

namespace useful_func
{
   /// <summary>
   /// calculates the running time of func
   /// </summary>
   /// <param name="func"></param>
   /// <returns></returns>
   double execute(const std::function<void()> &func);
   
}

