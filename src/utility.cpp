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

/*!
Calculates a linear regression f(x) = mx + b for a dataset of x and y values
@param x Vector of x-values of the dataset
@param y Vector of y-values of the dataset
@param m Pointer to the slope m
@param b Pointer to the y-intercept b
*/
void linearRegression(std::vector<float> x, std::vector<float> y, float *m, float *b)
{
   if (x.size() != y.size())
   {
      std::cout << "ERROR: Regression is only possible if the number of x and y values is the same!\n";
      return;
   }

   float averageX = calculateAverage(x);
   float averageY = calculateAverage(y);

   float denominator = 0;
   for (auto const &i : x)
   {
      denominator += (i - averageX) * (i - averageX);
   }

   float numerator = 0;
   for (int i = 0; i < y.size(); i++)
   {
      numerator += (x[i] - averageX) * (y[i] - averageY);
   }

   *m = numerator / denominator;
   *b = averageY - *m * averageX;
}

/*!
Calculates the average of values of a vector
@param values The vector that contains the values
@return Returns the average of the values in the vector
*/
float calculateAverage(std::vector<float> values)
{
   float average = 0;
   for (auto const &i : values)
   {
      average += i;
   }
   return average / values.size();
}

/*!
Calculates a cubic regression f(x)=ax^3+bx^2+cx+d for a dataset of x and y values
@param x Vector of x-values of the dataset
@param y Vector of y-values of the dataset
@param a Coefficient in front of x^3
@param b Coefficient in front of x^2
@param c Coefficient in front of x^1
@param d Coefficient in front of x^0
*/
void cubicRegression(std::vector<float> x, std::vector<float> y, float *a, float *b, float *c, float *d)
{
   if (x.size() != y.size())
   {
      std::cout << "ERROR: Regression is only possible if the number of x and y values is the same!\n";
      return;
   }

   /*
   Calculates a cubic regression based on the following instructions:
   https://www.omnicalculator.com/statistics/cubic-regression

   The formula for the result vector which contains the function coefficients a,b,c,d is

   result = (X^T * X)^-1 * X^T * y\f$

   where...

   X is the base matrix
   X^T is the transposed base matrix
   * represents the matrix multiplication
   ^-1 represents the inverse of a matrix
   y is the vector that contains all y-values in the same order as the x-values in the base matrix

   */

   // Base matrix contains the x values as their powers from 0 - 3
   MatrixXd base(x.size(), 4);

   for (uint8_t row = 0; row < x.size(); row++)
   {
      for (uint8_t col = 0; col < 4; col++)
      {
         base(row, col) = pow(x[row], col);
      }
   }

   // Values vector contains the corresponding y values
   VectorXd values(y.size());

   for (uint8_t element = 0; element < y.size(); element++)
   {
      values(element) = y[element];
   }

   MatrixXd baseTrans = base.transpose();

   base = baseTrans * base;

   MatrixXd result = base.inverse();

   result = result * baseTrans;
   result = result * values;

   *d = result(0, 0);
   *c = result(1, 0);
   *b = result(2, 0);
   *a = result(3, 0);
}

/*!
Newton-Raphson Method for finding the x-value that corresponds to a y-value of a cubic function \f$f(x)=ax^3+x^2+cx+d=\text{value}\f$, only for the range 0 - 10
@param a Coefficient in front of \f$x^3\f$
@param b Coefficient in front of \f$x^2\f$
@param c Coefficient in front of \f$x^1\f$
@param d Coefficient in front of \f$x^0\f$
@param value y-value of the cubic function that corresponds to the wanted x-value
@return Returns the x-value that corresponds to the y-value
*/
float solveCubicForVoltage(float a, float b, float c, float d, float value)
{
   // Polynom needs the form ax^3+bx^2+cx+d = 0 as the methods finds roots
   d -= value;

   float root = 5.f; // Start for approximation is the middle between 0 - 10V
   for (uint8_t iteration = 0; iteration < 15; iteration++)
   {
      root = root - (calculateCubic(a, b, c, d, root)) / (calculateCubicDeriv(a, b, c, root));
   }

   return root;
}

/*!
Calculates a y-value of a cubic function with \f$f(x)=ax^3 + bx^2 + cx + d\f$
@param a Coefficient in front of \f$x^3\f$
@param b Coefficient in front of \f$x^2\f$
@param c Coefficient in front of \f$x^1\f$
@param d Coefficient in front of \f$x^0\f$
@param x X-value for which the function should be calculated
@return Returns the y-value \f$y=f(x)\f$
*/
float calculateCubic(float a, float b, float c, float d, float x)
{
   return a * x * x * x + b * x * x + c * x + d;
}

/*!
Calculates a y-value of a cubic derivative function \f$f'(x)\f$ with \f$f(x)=ax^3 + bx^2 + cx + d\f$ and \f$f'(x)=3ax^2 + 2bx + cx\f$
@param a Coefficient in front of \f$x^3\f$
@param b Coefficient in front of \f$x^2\f$
@param c Coefficient in front of \f$x^1\f$
@param x X-value for which the function should be calculated
@return Returns the y-value \f$y=f'(x)\f$
*/
float calculateCubicDeriv(float a, float b, float c, float x)
{
   return 3 * a * x * x + 2 * b * x + c;
}

float calculateQuartic(float a, float b, float c, float d, float e, float x)
{
   return a * x * x * x * x + b * x * x * x + c * x * x + d * x + e;
}

float calculateQuarticDeriv(float a, float b, float c, float d, float x)
{
   return 4 * a * x * x * x + 3 * b * x * x + 2 * c * x + d;
}

/*!
Interprets four bytes as a float in the byte order of the SIWAREX-Module
@param bytes Byte Array
@return Bytes interpreted as float in the byte order 2-3-0-1
*/
float bytesToFloatSWRX(uint8_t *bytes)
{
   return bytesToFloat(bytes[2], bytes[3], bytes[0], bytes[1]);
}

/*!
Interprets four bytes as a float
@param bytes Byte Array where the 0th element is the MSB
@return Bytes interpreted as float
*/
float bytesToFloat(uint8_t *bytes)
{
   return bytesToFloat(bytes[0], bytes[1], bytes[2], bytes[3]);
}

/*!
Interprets four bytes as a float
@param b3 Most significant byte
@param b2 2nd byte
@param b1 3rd byte
@param b0 Least significant byte
@return Bytes interpreted as float
*/
float bytesToFloat(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
   uint32_t bytes = (b3 << 24) + (b2 << 16) + (b1 << 8) + b0;
   return *(float *)&bytes;
}

void delay(std::chrono::milliseconds delayMS)
{
   static std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> _lastCommand = std::chrono::system_clock::now();

   auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _lastCommand).count();

   if (diff < delayMS.count())
   {
      std::this_thread::sleep_for(std::chrono::milliseconds(delayMS.count() - diff));
   }

   // Save the time the current command was executed for next calculation
   _lastCommand = std::chrono::system_clock::now();
}
