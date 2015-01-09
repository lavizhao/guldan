#ifndef SPARSE_VECTOR_H_
#define SPARSE_VECTOR_H_

#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;

const double SMALL = 1e-3;

//sparse vector 简单封装
//以后感觉可以扩展成模板的
class Sparse_Vector{
 private:
  std::map<long,double> vc;
  
 public:
 Sparse_Vector(std::vector< std::pair<long,double> >& content):vc(){
    for(long i=0;i<content.size();i++){
      vc.insert(content[i]);
    }
  }
  
 Sparse_Vector(void):vc(){
  }

 Sparse_Vector(const Sparse_Vector& sp):vc(sp.vc){
  }

  bool has_indx(long indx){
    return vc.count(indx);
  }

  double get_value(long indx){
    return vc[indx];
  }

  void set_value(long indx,double value){
    vc[indx] = value;
  }

  long size(){
    return vc.size();
  }

  Sparse_Vector operator+(double num);
  Sparse_Vector operator+(Sparse_Vector& sp1);

  Sparse_Vector operator-(double num);
  Sparse_Vector operator-(Sparse_Vector& sp1);
  
  
  Sparse_Vector operator*(double num);
  Sparse_Vector operator*(Sparse_Vector& sp1);

  //清除map中有0的元素
  void clear();
  
  void print_value(){
    std::map<long,double>::const_iterator it = vc.begin();
    cout<<"size "<<size()<<endl;
    while(it!=vc.end()){
      std::pair<long,double> kv = (*it);
      cout<<"indx "<<kv.first<<" value "<<kv.second<<endl;
      it ++ ;
    }
    cout<<"============="<<endl;
  }

};

void Sparse_Vector::clear(){
  std::map<long,double>::iterator it = vc.begin();
  while(it!=vc.end()){
    double value = it->second;
    if(value>SMALL || value<-SMALL){
      it ++ ;
    }
    else{
      vc.erase(it++);
    }
  }
}

Sparse_Vector Sparse_Vector::operator+(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second += num;
    it ++ ;
  }

  nsp.clear();
  return nsp;
}

Sparse_Vector Sparse_Vector::operator-(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second -= num;
    it ++ ;
  }

  nsp.clear();
  return nsp;
}

Sparse_Vector Sparse_Vector::operator*(double num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second *= num;
    it ++ ;
  }

  nsp.clear();
  return nsp;
}


Sparse_Vector Sparse_Vector::operator+(Sparse_Vector& sp1){

  //得到一个新的
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = sp1.vc.begin();
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

  nsp.clear();
  return nsp;
}


Sparse_Vector Sparse_Vector::operator-(Sparse_Vector& sp1){

  //得到一个新的
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = sp1.vc.begin();
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

  nsp.clear();
  return nsp;
}


Sparse_Vector Sparse_Vector::operator*(Sparse_Vector& sp1){

  std::vector< std::pair<long,double> > mult;
    
  //遍历加
  std::map<long,double>::iterator it = sp1.vc.begin();
  while(it!=sp1.vc.end()){

    long indx = (*it).first;
    double value = (*it).second;
      
    if(has_indx(indx)){
      std::pair<long,double> tp(indx,value*get_value(indx));
      mult.push_back(tp);
    }
      
    it ++ ;
  }

  Sparse_Vector nsp(mult);
  nsp.clear();
  
  return nsp;
}




#endif
