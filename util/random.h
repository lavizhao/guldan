/*
	Sampling methods

	Author:   Steffen Rendle, http://www.libfm.org/
	modified: 2012-01-04

	Copyright 2010-2012 Steffen Rendle, see license.txt for more information
*/

#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdlib.h>
#include <cmath>
#include <assert.h>


double ran_gaussian();
double ran_gaussian(double mean, double stdev);
double ran_left_tgaussian(double left);
double ran_left_tgaussian(double left, double mean, double stdev);
double ran_left_tgaussian_naive(double left);
double ran_uniform();
double ran_exp();			
double ran_gamma(double alpha, double beta);
double ran_gamma(double alpha);
bool ran_bernoulli(double p);

double erf(double x);	
double cdf_gaussian(double x, double mean, double stdev);
double cdf_gaussian(double x);




#endif /*RANDOM_H_*/
