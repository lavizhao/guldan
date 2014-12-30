#include <iostream>
#include "../cmdline.h"


using namespace std;

// for test
// g++ test_opt.cpp
// ./a.out -dim 1 -iter 2

int main(int argc, char *argv[])
{

  CMDLine fuck = CMDLine(argc,argv);

  fuck.print();

  fuck.registerParam("dim","int","特征维度");
  fuck.registerParam("iter","int","迭代次数");

  fuck.print();

  cout<<"得到iter"<<endl;
  PARAM v = fuck.getParam("fuck");
  v.print();
  
  return 0;
}
