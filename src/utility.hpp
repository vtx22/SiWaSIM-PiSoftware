#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

#include "Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

float constrainMinMax(float value, float min, float max);
float constrainMin(float value, float min);
float constrainMax(float value, float max);

void linearRegression(std::vector<float> x, std::vector<float> y, float *m, float *b);

float calculateAverage(std::vector<float> values);

void cubicRegression(std::vector<float> x, std::vector<float> y, float *a, float *b, float *c, float *d);

float solveCubicForVoltage(float a, float b, float c, float d, float value);

float calculateCubic(float a, float b, float c, float d, float x);
float calculateCubicDeriv(float a, float b, float c, float x);

float bytesToFloat(uint8_t *bytes);

float bytesToFloat(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

void delay();