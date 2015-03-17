#include "sparse_vector.h"

Sparse_Vector::Sparse_Vector(std::vector< std::pair<long,double> >& content):vc(),iter(vc.begin()){
  for(long i=0;i<content.size();i++){
    vc.insert(content[i]);
  }
}

double Sparse_Vector::get_value(long indx){
  sp_iter tit = vc.find(indx);
  if(tit != vc.end()){
    return tit->second;
  }
  else
    return 0;
}

void Sparse_Vector::print_value(){
  sp_const_iter it = vc.begin();
  std::cout<<"size "<<size()<<std::endl;
  while(it!=vc.end()){
    std::pair<long,double> kv = (*it);
    std::cout<<"indx "<<kv.first<<" value "<<kv.second<<std::endl;
    it ++ ;
  }
  std::cout<<"============="<<std::endl;
}

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

void Sparse_Vector::bloom_filter(Sparse_Vector& bm,int ct) {
  sp_iter it = vc.begin();
  
  sp_iter bm_it;
  while(it!=vc.end()){
    long indx = it->first;
    bm_it = bm.vc.find(indx);

    if(bm_it != bm.vc.end()){
      int tct = bm_it->second;
      if(tct>ct){
	it ++ ;
      }else{
	vc.erase(it++);
      }
      bm_it->second += 1;
    }
    else{
      bm.vc[indx] = 1;
    }
    
  }
}

void Sparse_Vector::poisson_filter() {
  sp_iter it = vc.begin();
  while(it!=vc.end()){
    double value = it->second;
    double ran = ran_uniform();
    if(ran<0.03){
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


