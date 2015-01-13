#ifndef LR_H_
#define LR_H_

#include <string>
#include <map>
#include <math.h>
#include <time.h>
#include <vector>

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

  double predict(std::string test_dir);

};

void logistic_regression::fit(std::string train_dir){
  File_Control fc(train_dir);

  double st = 0.0;
  double tn = 0.0;
  
  //训练第几遍文件
  int indx = 0;
  for(int i=0;i<iter;i++){
    std::cout<<"训练第"<<i<<"遍文件"<<std::endl;
    while(fc.has_next() && indx <= 100000){
      string next = fc.next();
      if(next.size()>3){
	//std::cout<<"训练第"<<indx<<"个数据"<<std::endl;
	clock_t t1 = clock();
	std::pair<int,Sparse_Vector> result = sparse_vector_form(next);
	clock_t t2 = clock();
	one_round(result.first,result.second);
	clock_t t3 = clock();

	st += t2-t1;
	tn += t3-t2;
	indx ++ ;
	if (indx%1000==0)
	  cout<<"indx "<<indx<<" |w  "<<w.size()<<" |z  "<<z.size()	\
	      <<" |g "<<g.size()<<" |sigma "<<sigma.size()<<" |n "<<n.size()<<endl;
      }
    }
    
    fc.restart();
  }

  cout<<"split time "<<st<<endl;
  cout<<"train time "<<tn<<endl;

  cout<<"w size "<<w.size()<<endl;
}

void logistic_regression::one_round(int label,Sparse_Vector& x) {

  //更新w
  sp_iter it;
  z.restart();
  
  w.empty();
  while(z.has_next()){
    it = z.next();
    
    long indx = it->first;
    double value = it->second;
    
    double wti = 0;
    double a1 = value - ((double)sgn(value))*L1;
    double a2 = 1.0/( (beta+sqrt(n.get_value(indx)))/alpha + L2);

    if(abs(value)>L1){
      wti = -(a1*a2);
      w.set_value(indx,wti);
    }
    else{
    }


  }
  w.clear();
  
  //====================================================================
  //预测一下
  double p = sigmoid(w.dot_sum(x));

  //=====================================================================

  //更新g
  g = x * (p-label);
  //g.clear();

  //更新sigma
  g.restart();
  sigma.empty();
  while(g.has_next()){
    it = g.next();
    long indx = it->first;
    double value = it->second;

    double a1 = sqrt(value*value + n.get_value(indx)) - sqrt(n.get_value(indx));
    sigma.set_value(indx,a1/alpha);

  }
  sigma.clear();
  
  //更新z
  Sparse_Vector ws(w*sigma);
  Sparse_Vector temp(g-ws);
  z += temp;
  if (z.size()%100 <= 30)
    z.clear();

  //更新n
  //Sparse_Vector gsqrt(g*g);
  //n += gsqrt;
  g.restart();
  while(g.has_next()){
    it = g.next();
    long indx = it->first;
    double value = it->second;
    n.set_value(indx,n.get_value(indx)+value*value);
  }
  if (n.size()%100 <= 30)
    n.clear();

}
 

double logistic_regression::predict(std::string test_dir){
  File_Control fc(test_dir);

  double right = 0.0;
  double total = 0.0;
  int wrong = 0;
  
  while(fc.has_next()){
    string next = fc.next();
    if(next.size()>3){
      std::pair<int,Sparse_Vector> result = sparse_vector_form(next);
      int label = result.first;
      Sparse_Vector x = result.second;

      int plabel = -1;
      double p = sigmoid(w.dot_sum(x));
      if(p>0.5)
	plabel = 1;
      else
	plabel = 0;

      if(plabel!=label)
	wrong ++ ;

      right += (1-abs(plabel-label));
      total ++ ;
      
    }
  }
  cout<<"total "<<total<<endl;
  cout<<"right "<<right<<endl;
  cout<<"wrong "<<wrong<<endl;
  return right/total;
}



#endif
