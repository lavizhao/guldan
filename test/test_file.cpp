#include <iostream>
#include "../util/file_control.h"

using namespace std;

int main(int argc, char *argv[])
{

  File_Control fc("../data/ida/train.csv");

  //fc.print_file();
  fc.print_info();

  
  int indx = 0;
  while(fc.has_next()){
    //cout<<indx<<" "<<fc.next()<<endl;
    fc.next();
    indx ++ ;
  }
  
  
  return 0;
}
