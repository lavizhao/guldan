#ifndef LR_H_
#define LR_H_

#include <string>
#include <map>
#include <math.h>
#include <time.h>
#include <vector>
#include <set>
#include <fstream>

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

  int iter;
  int verbose;

  long pos ;
  long neg ;

 public:

  //构造函数
  logistic_regression(double alpha1,double beta1,double l1,double l2,	\
		      int iter1,int vb):					\
  alpha(alpha1),beta(beta1),L1(l1),L2(l2),z(),n(),sigma(),g(),w(),iter(iter1),verbose(vb){
    
  }

  void print(){
    std::cout<<"lr"<<std::endl;
  }

  void fit(std::string train_dir,double stop);

  void one_round(int label,Sparse_Vector& x);
  void one_round1(int label,Sparse_Vector& x);

  double predict(std::string test_dir,std::string out_dir);

};

void logistic_regression::fit(std::string train_dir,double stop){
  srand(time(0));
  File_Control fc(train_dir);

  stop *= (1000*1000);
  //double stop = 200000;
  long pos = 0;
  long neg = 0;
  
  //训练第几遍文件
  int indx = 0;
  for(int i=0;i<iter;i++){
    std::cout<<"训练第"<<i<<"遍文件"<<std::endl;
    while(fc.has_next() && indx <= stop){
      string next = fc.next();
      if(next.size()>3){
	std::pair<int,Sparse_Vector> result = sparse_vector_form(next);
	if (result.first==1)
	  pos ++ ;
	else if (result.first==0)
	  neg ++ ;
	  
	one_round(result.first,result.second);
	
	indx ++ ;
	if (indx%(verbose*1000)==0)
	  std::cout<<"indx "<<indx<<" |w  "<<w.size()<<" |z  "<<z.size() \
		   <<" |g "<<g.size()<<" |sigma "<<sigma.size()<<" |n "<<n.size() \
		   <<" |pos "<<pos<<" |neg "<<neg<<std::endl;
	
      }
    }

    if(indx>=stop){
      indx = 0;
    }
    
    fc.restart();
  }

}

void logistic_regression::one_round(int label,Sparse_Vector& x) {
  //----------------------更新w---------------------------------
  sp_iter it;

  z.restart();
  w.empty();
  
  while(z.has_next()) {
    it = z.next();
    long indx = it->first;
    double value = it->second;
    if(abs(value)<=L1){
    }
    else{
      double a1 = -(value - sgn(value)*L1);
      double a2 = (beta+sqrt(n.get_value(indx)))/alpha + L2;
      w.set_value(indx,a1/a2);
    }
  }
  w.clear(BIG,-BIG);
  

  //-----------------------预测p--------------------------------
  double p = w.dot_sum(x);
  g = x*(p-label);
  //g.print_value();

  //-----------------------更新sigma----------------------------
  sigma.empty();
  g.restart();
  while(g.has_next()){
    it = g.next();
    long indx = it->first;
    double value = it->second;
    double nvalue = n.get_value(indx);
    sigma.set_value(indx,(sqrt(nvalue+value*value)-sqrt(nvalue))/alpha);
  }

  //----------------------更新z---------------------------------
  Sparse_Vector ws(w*sigma);
  Sparse_Vector gws(g-ws);

  z += gws;

  
  if(rand()%100<=1)
    z.clear(SMALL,-SMALL);

  //----------------------更新n----------------------------------
  g = g*g;
  n += g;
  if(rand()%100<=1)
    n.clear(SMALL,-SMALL);

}


double logistic_regression::predict(std::string test_dir,std::string out_dir){
  File_Control fc(test_dir);
  fc.restart();

  long total = 0;
  std::ofstream out(out_dir.c_str());
  
  while(fc.has_next() && total <= 100000){
    string next = fc.next();
    if(next.size()>3){
      std::pair<int,Sparse_Vector> result = sparse_vector_form(next);
      int label = result.first;
      Sparse_Vector x = result.second;

      int plabel = -1;
      double ds = w.dot_sum(x);
      double p = sigmoid(ds);
      out<<label<<" "<<p<<std::endl;

      total ++ ;
    }
  }

  out.close();
  
  return 0;
}


#endif
