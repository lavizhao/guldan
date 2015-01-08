#include <iostream>
#include <vector>
#include "../util/sparse_vector.h"

using namespace std;

int main(int argc, char *argv[])
{

  cout<<"========测试pair========"<<endl;

  pair<long,double> tp(1,2);
  cout<<tp.first<<"  "<<tp.second/5<<endl;

  cout<<"========测试pair+vector========"<<endl;

  pair<long,double> tp1(1,2);
  pair<long,double> tp2(2,3);
  pair<long,double> tp3(4,4);
  pair<long,double> tp4(6,5);

  vector< pair<long,double> > result;
  result.push_back(tp1);
  result.push_back(tp2);
  result.push_back(tp3);
  result.push_back(tp4);

  for(int i=0;i<result.size();i++){
    cout<<result[i].first<<" "<<result[i].second/2<<endl;
  }

  cout<<"======测试sparse vector=========="<<endl;

  pair<long,double> tk1(1,3);
  pair<long,double> tk2(2,5);
  pair<long,double> tk3(3,2);
  pair<long,double> tk4(5,1);

  vector< pair<long,double> > result1;
  result1.push_back(tk1);
  result1.push_back(tk2);
  result1.push_back(tk3);
  result1.push_back(tk4);

  Sparse_Vector sp1(result);
  Sparse_Vector sp2(result1);

  Sparse_Vector fuck = (sp1-2);
  sp1.print_value();
  sp2.print_value();
  fuck.print_value();

  
  
  return 0;
}
