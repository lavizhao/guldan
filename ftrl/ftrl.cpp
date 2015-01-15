#include <iostream>

#include "../util/cmdline.h"
#include "lr.h"

using namespace std;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{

  cout<<"------------------------------------------------"<<endl;
  cout<<"这是online logistic regression"<<endl;
  cout<<"版本 1.1"<<endl;
  cout<<"作者:赵惜墨(Lavi Zhao)"<<endl;
  cout<<"作者邮箱:zhaoximo@hotmail.com"<<endl;
  cout<<"本软件遵从GPLv3.0 协议, 软件中应该包含GPLv3.0协议的license, 如果没有请自行下载"<<endl;
  cout<<"------------------------------------------------"<<endl;

  /*
    参数设置
    alpha,beta  学习速率参数
    l1,l2       正则项参数
    train test  训练,测试数据位置
    iter        迭代次数
    out         输出文件
    verbose     每隔多少输出信息默认是XXK, K自带, 不需要设置
    stop        最多训练多少次, 这个算是测试用的数字, 默认是XXM
  */

  CMDLine cmd = CMDLine(argc,argv);

  cmd.register_param("alpha",double_string,"1.0","学习速率参数");
  cmd.register_param("beta",double_string,"1.0","学习速率参数");
  
  cmd.register_param("l1",double_string,"0.0","l1正则项权重");
  cmd.register_param("l2",double_string,"1.0","l2正则项权重");

  cmd.register_param("train",string_string,dir_dft,"训练文件存放位置");
  cmd.register_param("test",string_string,dir_dft,"测试文件存放位置");

  cmd.register_param("iter",int_string,"1","迭代次数");

  cmd.register_param("out",string_string,dir_dft,"输出文件");

  cmd.register_param("verbose",int_string,"20","输出文件");

  cmd.register_param("stop",double_string,"1","输出文件");

  cmd.set_default();

  //判断打印帮助文件
  if (cmd.has_name("help")){
    cmd.print();
    return 0;
  }


  //判断有没有训练文件
  if(cmd.get_param("train").value==dir_dft){
    cout<<"训练文件没有指定"<<endl;
    return 0;
  }

  if(cmd.get_param("test").value==dir_dft){
    cout<<"测试文件没有指定"<<endl;
    return 0;
  }

  if(cmd.get_param("out").value==dir_dft){
    cout<<"输出文件没有指定"<<endl;
    return 0;
  }

  //------------------调整参数---------------------

  double alpha = cmd.get_param("alpha").get_double();
  double beta = cmd.get_param("beta").get_double();
  double L1 = cmd.get_param("l1").get_double();
  double L2 = cmd.get_param("l2").get_double();

  int iter = cmd.get_param("iter").get_long();
  int verbose = cmd.get_param("verbose").get_long();
  double stop = cmd.get_param("stop").get_double();

  string train_dir = cmd.get_param("train").get_string();
  string test_dir = cmd.get_param("test").get_string();
  string out_dir = cmd.get_param("out").get_string();

  logistic_regression lr(alpha,beta,L1,L2,iter,verbose);


  //----------------------训练--------------------------
  lr.fit(train_dir,stop);

  double ans = lr.predict(test_dir,out_dir);
  
  return 0;
}
