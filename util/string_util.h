#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cstring>

#include "sparse_vector.h"

using std::cout;
using std::endl;

std::vector<std::string> split(const std::string &s,const char delim) {

  std::vector<std::string> result;

  const char* str = s.c_str();
  do{
    const char *begin = str;

    while(*str != delim && *str)
      str++;

    result.push_back(std::string(begin, str));
  } while (0 != *str++);

  return result;
}

long stol(const std::string& s){
  return atol(s.c_str());
}

double stod(const std::string& s){
  return atof(s.c_str());
}

std::pair<int,Sparse_Vector> sparse_vector_form(const std::string& s){
  std::vector<std::string> sp = split(s,' ');

  int label = stol(sp[0]);

  Sparse_Vector sv;
  std::pair<int,Sparse_Vector> tp(label,sv);

  for(int i=1;i<sp.size();i++){
    std::vector<std::string> item = split(sp[i],':');
    long indx = stol(item[0].substr(1));
    double value = stod(item[1]);
    tp.second.set_value(indx,value);
  }


  
  return tp;
}


#endif
