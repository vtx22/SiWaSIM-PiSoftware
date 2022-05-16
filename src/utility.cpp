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
Calculates a linear regression f(x)=mx+b for a dataset of x and y values

*/
void linearRegression(std::vector<float> x, std::vector<float> y, float *m, float *b)
{
   if (x.size() != y.size())
   {
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

void cubicRegression(std::vector<float> x, std::vector<float> y, float *a, float *b, float *c, float *d)
{
   MatrixXd base{
       {1, 0, 0, 0},
       {1, 1, 1, 1},
       {1, 2, 4, 8},
       {1, 3, 9, 27},
       {1, 4, 16, 64},
       {1, 5, 25, 125},
       {1, 6, 36, 216},
       {1, 7, 49, 343},
       {1, 8, 64, 512},
       {1, 9, 81, 729},
       {1, 10, 100, 1000},
   };

   std::cout << "X is: " << base.rows() << "  ::  " << base.cols() << "\n\n";

   VectorXd values{{y[0]}, {y[1]}, {y[2]}, {y[3]}, {y[4]}, {y[5]}, {y[6]}, {y[7]}, {y[8]}, {y[9]}, {y[10]}};

   std::cout << "Y is: " << values.rows() << "  ::  " << values.cols() << "\n\n";

   MatrixXd baseTrans = base.transpose();

   std::cout << "XT is: " << baseTrans.rows() << "  ::  " << baseTrans.cols() << "\n\n";

   base *= baseTrans;

   std::cout << "XTX is: " << base.rows() << "  ::  " << base.cols() << "\n\n";

   MatrixXd result = base.inverse();

   std::cout << "(XTX)-1 is: " << result.rows() << "  ::  " << result.cols() << "\n\n";

   result *= baseTrans;

   std::cout << "(XTX)-1XT is: " << result.rows() << "  ::  " << result.cols() << "\n\n";

   MatrixXd newResult = result * values;

   std::cout << newResult << std::endl;
}