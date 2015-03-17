#include "file_control.h"

void File_Control::print_info(){
  std::cout<<"文件名"<<fname<<std::endl;
}

void File_Control::print_file(){
  int indx = 0;
  while(!file.eof()){
    std::string temp;
    getline(file,temp);
    std::cout<<indx<<" "<<temp<<std::endl;
    indx ++ ;
  }
}


