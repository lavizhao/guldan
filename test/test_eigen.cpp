#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

// g++ 

using namespace std;
using namespace Eigen;

typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::Triplet<double> T;

int main(int argc, char *argv[])
{

  cout<<"测试权重用的密集向量"<<endl;
  Matrix<double,1,3> mv;
  Matrix<double,1,3> mp;

  mv(0,0) = 1;
  mv(0,1) = 2;
  mv(0,2) = 3;

  mp(0,0) = 2;
  mp(0,1) = 3;
  mp(0,2) = 4;

  cout<<"mv is "<<mv<<endl;
  cout<<"mp is "<<mp<<endl;

  cout<<"mv * mp' is "<<mv*(mp.transpose())<<endl;
  cout<<"mv' * mp is "<<endl<<(mv.transpose())*mp<<endl;
  cout<<"mv.sum is "<<mv.sum()<<endl;
  cout<<"mv * 2 is "<<mv*2<<endl;

  cout<<"=========================="<<endl;

  cout<<"测试稀疏向量"<<endl;

  SparseMatrix<double,RowMajor> sp(1,3); 
  //SparseVector<double,RowMajor> sp(3);
  
  sp.insert(0,1) = 2.0;
  cout<<"sp is "<<sp<<endl;

  cout<<"sp * 2 is "<<sp*2<<endl;
  mv += sp;
  //cout<<"sp + mv is"<<sp+=mv<<endl;
  
  
  
  return 0;
}
