#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

#include "sparse_vector.h"

using std::cout;
using std::endl;

std::stringstream ss;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
  //std::stringstream ss(s);
  ss.str("");
  ss.clear();
  ss<<s;
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
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

  for(int i=1;i<sp.size();i++){
    std::vector<std::string> item = split(sp[i],':');
    long indx = stol(item[0].substr(1));
    double value = stod(item[1]);
    sv.set_value(indx,value);
  }

  std::pair<int,Sparse_Vector> tp(label,sv);
  
  return tp;
}


#endif
