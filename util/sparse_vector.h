#ifndef SPARSE_VECTOR_H_
#define SPARSE_VECTOR_H_

#include <iostream>
#include <map>
#include <vector>
#include <tr1/unordered_map>

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
 Sparse_Vector(std::vector< std::pair<long,double> >& content):vc(),iter(vc.begin()){
    for(long i=0;i<content.size();i++){
      vc.insert(content[i]);
    }
  }
  
 Sparse_Vector(void):vc(),iter(vc.begin()){
  }

 Sparse_Vector(const Sparse_Vector& sp):vc(sp.vc),iter(vc.begin()){
  }

  bool has_indx(long indx){
    return vc.count(indx);
  }

  double get_value(long indx){
    sp_iter tit = vc.find(indx);
    if(tit != vc.end()){
      return tit->second;
    }
    else
      return 0;
  }

  void set_value(long indx,double value){
    vc[indx] = value;
  }

  long size(){
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

  void empty(){
    vc.clear();
  }
  
  void print_value(){
    sp_const_iter it = vc.begin();
    std::cout<<"size "<<size()<<std::endl;
    while(it!=vc.end()){
      std::pair<long,double> kv = (*it);
      std::cout<<"indx "<<kv.first<<" value "<<kv.second<<std::endl;
      it ++ ;
    }
    std::cout<<"============="<<std::endl;
  }

  bool has_next(){
    return !(iter == vc.end());
  }

  void restart(){
    iter = vc.begin();
  }

  sp_iter next();

};


sp_iter Sparse_Vector::next(){
  return iter++;
}



void Sparse_Vector::clear(double upper=SMALL,double lower=-SMALL){
  sp_iter it = vc.begin();
  while(it!=vc.end()){
    double value = it->second;
    if(value>upper || value<-upper){
      it ++ ;
    }
    else{
      vc.erase(it++);
    }
  }
}

Sparse_Vector& Sparse_Vector::operator+=(Sparse_Vector& sp1){
  
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){
    long indx = it->first;
    double value = it->second + get_value(indx);
    set_value(indx,value);
    it ++ ;
  }

  return *this;
  
}

Sparse_Vector& Sparse_Vector::operator-=(Sparse_Vector& sp1){
  
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){
    long indx = it->first;
    double value = get_value(indx) - it->second;
    set_value(indx,value);
    it ++ ;
  }

  return *this;
  
}

Sparse_Vector Sparse_Vector::operator+(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  sp_iter it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second += num;
    it ++ ;
  }

  return nsp;
}

Sparse_Vector Sparse_Vector::operator-(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  sp_iter it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second -= num;
    it ++ ;
  }

  return nsp;
}

Sparse_Vector Sparse_Vector::operator*(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  sp_iter it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second *= num;
    it ++ ;
  }

  return nsp;
}


Sparse_Vector Sparse_Vector::operator+(Sparse_Vector& sp1){

  //得到一个新的
  Sparse_Vector nsp(*this);
    
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){

    long indx = (*it).first;
    double value = (*it).second;
      
    if(has_indx(indx)){
      nsp.set_value(indx,nsp.get_value(indx)+value);
    }
    else{
      nsp.set_value(indx,nsp.get_value(indx)+value);
    }
      
    it ++ ;
  }

  return nsp;
}


Sparse_Vector Sparse_Vector::operator-(Sparse_Vector& sp1){

  //得到一个新的
  Sparse_Vector nsp(*this);
    
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){

    long indx = (*it).first;
    double value = (*it).second;
      
    if(has_indx(indx)){
      nsp.set_value(indx,nsp.get_value(indx)-value);
    }
    else{
      nsp.set_value(indx,nsp.get_value(indx)-value);
    }
      
    it ++ ;
  }

  return nsp;
}


Sparse_Vector Sparse_Vector::operator*(Sparse_Vector& sp1){

  std::vector< std::pair<long,double> > mult;
    
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){

    long indx = it->first;
    double value = it->second;
      
    if(has_indx(indx)){
      std::pair<long,double> tp(indx,value*get_value(indx));
      mult.push_back(tp);
    }
      
    it ++ ;
  }

  Sparse_Vector nsp(mult);
  
  return nsp;
}

double Sparse_Vector::dot_sum(Sparse_Vector& sp1){
  double result = 0.0;
    
  //遍历加
  sp_iter it = sp1.vc.begin();
  while(it!=sp1.vc.end()){

    long indx = it->first;
    double value = it->second;
      
    if(has_indx(indx)){
      double mvalue = get_value(indx);
      double ans = value*mvalue;
      result += ans;
    }
      
    it ++ ;
  }
  return result;
}


#endif
