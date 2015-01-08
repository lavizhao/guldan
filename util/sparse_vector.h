#ifndef SPARSE_VECTOR_H_
#define SPARSE_VECTOR_H_

#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;

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

 Sparse_Vector(const Sparse_Vector& sp):vc(sp.vc){
  }

  bool has_indx(long indx){
    return vc.count(indx);
  }

  double get_value(long indx){
    return vc[indx];
  }

  double set_value(long indx,double value){
    vc[indx] = value;
  }
  

  Sparse_Vector operator+(long num);
  Sparse_Vector operator+(Sparse_Vector& sp1);

  Sparse_Vector operator-(long num);
  Sparse_Vector operator-(Sparse_Vector& sp1);
  
  
  Sparse_Vector operator*(long num);
  Sparse_Vector operator*(Sparse_Vector& sp1);


  
  void print_value(){
    std::map<long,double>::const_iterator it = vc.begin();
    while(it!=vc.end()){
      std::pair<long,double> kv = (*it);
      cout<<"indx "<<kv.first<<" value "<<kv.second<<endl;
      it ++ ;
    }
    cout<<"============="<<endl;
  }

};

Sparse_Vector Sparse_Vector::operator+(long num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second += num;
    it ++ ;
  }
    
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
    
  return nsp;
}

Sparse_Vector Sparse_Vector::operator-(long num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second -= num;
    it ++ ;
  }
    
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
    
  return nsp;
}


//这个有问题
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
  
  return nsp;
}



Sparse_Vector Sparse_Vector::operator*(long num){
  Sparse_Vector nsp(*this);
    
  //遍历加
  std::map<long,double>::iterator it = nsp.vc.begin();
  while(it!=nsp.vc.end()){
    (*it).second *= num;
    it ++ ;
  }
    
  return nsp;
}


#endif
