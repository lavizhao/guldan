#ifndef LR_H_
#define LR_H_



#include <math.h>
#include <time.h>
#include <vector>
#include <set>
#include <fstream>

#include "../util/sparse_vector.h"
#include "../util/string_util.h"
#include "../util/file_control.h"
#include "../util/amath.h"
#include "../util/random.h"

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

  Sparse_Vector bm;

  int iter;
  int verbose;

  long pos ;
  long neg ;

  sp_iter it;
  bool update;
  long no_train;

 public:

  //构造函数
  logistic_regression(double alpha1,double beta1,double l1,double l2,	\
		      int iter1,int vb):					\
  alpha(alpha1),beta(beta1),L1(l1),L2(l2),z(),n(),sigma(),g(),w(),iter(iter1),verbose(vb),bm(){
  }

  void print();

  void fit(std::string train_dir,double stop);

  void one_round(int label,Sparse_Vector& x);

  void update_w(Sparse_Vector& x);
  
  void update_other(Sparse_Vector& x,double p,int label);

  double predict(std::string test_dir,std::string out_dir);

};



#endif
