#ifndef LR_H_
#define LR_H_

#include <string>
#include <map>
#include <math.h>

#include "../util/sparse_vector.h"
#include "../util/string_util.h"
#include "../util/file_control.h"
#include "../util/amath.h"

//FTRL的类


class logistic_regression{
 private:
  
  //基本与论文的名称相对应
  double alpha;
  double beta;
  double L1;
  double L2;

  Sparse_Vector z;
  Sparse_Vector n;
  Sparse_Vector sigma;
  Sparse_Vector g;
  Sparse_Vector w;

  //File_Control fc;//用来控制训练文件的, 测试文件的暂时没有写

  int iter;

 public:

  //构造函数
  logistic_regression(double alpha1,double beta1,double l1,double l2,	\
		      int iter1):					\
  alpha(alpha1),beta(beta1),L1(l1),L2(l2),z(),n(),sigma(),g(),w(),iter(iter1){
    
  }

  void print(){
    std::cout<<"lr"<<std::endl;
  }

  void fit(std::string train_dir);

  void one_round(int label,Sparse_Vector& x);

};

void logistic_regression::fit(std::string train_dir){
  File_Control fc(train_dir);
  
  //训练第几遍文件
  int indx = 0;
  for(int i=0;i<iter;i++){
    std::cout<<"训练第"<<i<<"遍文件"<<std::endl;
    while(fc.has_next()  ){
      string next = fc.next();
      if(next.size()>3){
	//std::cout<<"训练第"<<indx<<"个数据"<<std::endl;
	std::pair<int,Sparse_Vector> result = sparse_vector_form(next);
	one_round(result.first,result.second);
	indx ++ ;
      }
    }
    
    fc.restart();
  }

  cout<<"all g is"<<endl;
  g.print_value();

  cout<<"all sigma is"<<endl;
  sigma.print_value();
  
  cout<<"all z is"<<endl;
  z.print_value();
  
  cout<<"all w is"<<endl;
  w.print_value();
}

void logistic_regression::one_round(int label,Sparse_Vector& x) {

  //更新w
  std::map<long,double>::iterator it;
  z.restart();
  
  Sparse_Vector nw;
  w = nw;
  
  while(z.has_next()){
    it = z.next();
    
    long indx = it->first;
    double value = it->second;
    
    double wti = 0;
    double a1 = value - sgn(value)*L1;
    double a2 = 1.0/( (beta+sqrt(n.get_value(indx)))/alpha + L2);

    //这地方写的不对,  有zi 为0 的部分应该也是0
    if(abs(value)>L1)
      wti = -(a1*a2);
    else{
      //cout<<"here"<<endl;
    }

    w.set_value(indx,wti);
    w.clear();
  }
  //cout<<"w is "<<endl;
  //w.print_value();

  //====================================================================
  //预测一下
  double p = sigmoid(w.dot_sum(x));
  //cout<<"p "<<p<<" y "<<label<<endl;


  //=====================================================================

  //更新g
  g = x * (p-label);

  //更新sigma
  g.restart();
  while(g.has_next()){
    it = g.next();
    long indx = it->first;
    double value = it->second;
    //cout<<"indx "<<indx<<" value "<<value<<endl;

    double a1 = sqrt(value*value + n.get_value(indx)) - sqrt(n.get_value(indx));
    sigma.set_value(indx,a1/alpha);

  }
  
  //更新z
  Sparse_Vector ws(w*sigma);
  z = z + g;
  z = z - ws;

  //更新n
  Sparse_Vector gsqrt(g*g);
  n = n + gsqrt;

  //z.print_value();
}
 





#endif
