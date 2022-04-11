#include "utility.hpp"

float constrainMinMax(float value, float min, float max)
{
   if (value > max)
   {
      return max;
   }
   if (value < min)
   {
      return min;
   }
   return value;
}