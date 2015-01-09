#include <iostream>
#include <vector>
#include <time.h>

#include "../util/file_control.h"
#include "../util/string_util.h"
#include "../util/sparse_vector.h"



using namespace std;

typedef pair<int,Sparse_Vector> shabi;

int main(int argc, char *argv[])
{

  double total = 0.0;
  for(int i=0;i<2000;i++){
    File_Control fc("../data/ida/train.csv");
    cout<<"turn "<<i<<endl;

    //string content1 = fc.next();
    //shabi ans = sparse_vector_form(content);

    double tt = 0.0;

    double tt1 = 0.0;

    clock_t start1 = clock();
    int indx = 0;
    while(fc.has_next()){
      string content = fc.next();
      if(content.size()>3){
	clock_t start = clock();
	shabi ans = sparse_vector_form(content);
	
	Sparse_Vector fuck = ans.second;
	Sparse_Vector cao(fuck *fuck);
	//fuck.print_value();
	//cao.print_value();
	//cout<<"----------"<<endl;

	clock_t end = clock();
	tt += end - start;
      }
      //ans.second.print_value();
      indx ++ ;
    }

    clock_t end1 = clock();
    
    tt = tt/CLOCKS_PER_SEC;
    tt1 = (double)(end1-start1)/CLOCKS_PER_SEC;
    cout<<"解析时间 "<<tt<<" 总时间 "<<tt1<<" indx "<<indx<<endl;
  }
  
  return 0;
}
