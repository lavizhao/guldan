#include "amath.h"

double sigmoid(double x){
  return 1.0/(1.0+exp(-x));
}

double sgn(double x){
  if (x>0)
    return 1.0;
  else if (x==0)
    return 0.0;
  else
    return -1.0;
}

double abs(double value){
  if(value < 0)
    return -value;
  return value;
}

float sqrt1( float number )  {  
  int i;  
  float x2, y;  
  const float threehalfs = 1.5F;  
  
  x2 = number * 0.5F;  
  y  = number;  
  i  = * ( int * ) &y;       
  i  = 0x5f375a86 - ( i >> 1 );   
  y  = * ( float * ) &i;  
  y  = y * ( threehalfs - ( x2 * y * y ) );   
  y  = y * ( threehalfs - ( x2 * y * y ) );     
  y  = y * ( threehalfs - ( x2 * y * y ) );   
  return number*y;  
}

double logloss1(double z){
  if (z >= 0)
    return log(1+exp(-z));
  else
    return -z + log(1+exp(z));
}

