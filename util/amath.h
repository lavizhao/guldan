#ifndef AMATH_H_
#define AMATH_H_

//#include "sparse_vector.h"
#include <math.h>

double sigmoid(double x){
  return 1.0/(1.0+exp(-x));
}

double sgn(double x){
  if (x>0)
    return 1;
  else if (x==0)
    return 0;
  else
    return -1;
}

double abs(double value){
  if(value < 0)
    return -value;
  return value;
}



#endif
