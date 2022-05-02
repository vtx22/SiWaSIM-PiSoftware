#include "utility.hpp"

/*!
Constrain a value between an upper and a lower limit to clip the value
@param value The value to be clipped
@param min The lower limit
@param max The upper limit
@return Returns the clipped / constrained value
*/
float constrainMinMax(float value, float min, float max)
{
   return constrainMax(constrainMin(value, min), max);
}

/*!
Constrain a value to a lower limit if the value is below that limit
@param value The value to be clipped
@param min The lower limit
@return Returns the clipped / constrained value
*/
float constrainMin(float value, float min)
{
   if (value < min)
   {
      return min;
   }
   return value;
}

/*!
Constrain a value to an upper limit if the value is above that limit
@param value The value to be clipped
@param max The upper limit
@return Returns the clipped / constrained value
*/
float constrainMax(float value, float max)
{
   if (value > max)
   {
      return max;
   }
   return value;
}