#include "utility.hpp"

float constrainMinMax(float value, float min, float max)
{
   return constrainMax(constrainMin(value, min), max);
}

float constrainMin(float value, float min)
{
   if (value < min)
   {
      return min;
   }
   return value;
}

float constrainMax(float value, float max)
{
   if (value > max)
   {
      return max;
   }
   return value;
}