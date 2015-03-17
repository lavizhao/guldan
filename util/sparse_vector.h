#ifndef SPARSE_VECTOR_H_
#define SPARSE_VECTOR_H_

#include "../util/random.h"

#include <iostream>
#include <map>
#include <vector>
#include <tr1/unordered_map>
#include <tr1/unordered_set>



const double SMALL = 1e-3;
const double BIG = 1e-3;

//typedef std::map<long,double> sp_type;
//typedef std::map<long,double>::iterator sp_iter;
//typedef std::map<long,double>::const_iterator sp_const_iter;

typedef std::tr1::unordered_map<long,double> sp_type;
typedef std::tr1::unordered_map<long,double>::iterator sp_iter;
typedef std::tr1::unordered_map<long,double>::const_iterator sp_const_iter;


//sparse vector 简单封装
//以后感觉可以扩展成模板的
class Sparse_Vector{
 private:
  sp_type vc;
  sp_iter iter;
  
 public:
  Sparse_Vector(std::vector< std::pair<long,double> >& content);
  
 Sparse_Vector(void):vc(),iter(vc.begin()){}

 Sparse_Vector(const Sparse_Vector& sp):vc(sp.vc),iter(vc.begin()){}

  inline bool has_indx(long indx){
    return vc.count(indx);
  }

  double get_value(long indx);

  inline void set_value(long indx,double value){
    vc[indx] = value;
  }

  inline long size(){
    return vc.size();
  }

  Sparse_Vector operator+(double num);
  Sparse_Vector operator+(Sparse_Vector& sp1);
  
  Sparse_Vector& operator+=(Sparse_Vector& sp1);
  Sparse_Vector& operator-=(Sparse_Vector& sp1);  

  Sparse_Vector operator-(double num);
  Sparse_Vector operator-(Sparse_Vector& sp1);
  
  
  Sparse_Vector operator*(double num);
  Sparse_Vector operator*(Sparse_Vector& sp1);

  double dot_sum(Sparse_Vector& sp1);

  //清除map中有0的元素
  void clear(double upper,double lower);

  inline void empty(){
    vc.clear();
  }
  
  void print_value();

  inline bool has_next(){
    return !(iter == vc.end());
  }

  inline void restart(){
    iter = vc.begin();
  }

  sp_iter next();

  void poisson_filter();
  void bloom_filter(Sparse_Vector& bm,int ct);

};




#endif
