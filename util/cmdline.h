#ifndef CMDLINE_H_
#define CMDLINE_H_

#include <iostream>
#include <string>
#include <map>
#include <iomanip>

#include "string_util.h"

enum CODE {SUCCESS,FAIL};

using std::string;

string error_string = "error";
string int_string = "INT";
string double_string = "DOUBLE";
string string_string = "STRING";

string emp_string = "emp";

string dir_dft = "./fuck";
  

//每个参数单元
class PARAM{
 public:
  std::string name;//表明类型
  std::string type;//type表明是什么类型, 默认是支持INT,DOUBLE,STRING三种
  std::string value;//给定的值
  std::string dft;//默认值
  std::string help;

  PARAM(){
    this->name = error_string;
    this->type = error_string;
    this->value = error_string;
    this->help = error_string;
    this->dft = error_string;
  }
  
 PARAM(string name,string type,string dft,string help)	\
   :name(name),type(type),value(error_string),dft(dft),help(help){
  }
 PARAM(string name,string value):name(name),value(value){}

  PARAM(const PARAM& v){
    this->name = v.name;
    this->type = v.type;
    this->value = v.value;
    this->dft = v.dft;
    this->help = v.help;
  }
  
  void set_help(std::string help){
    this->help = help;
  }
  void set_type(std::string type){
    this->type = type;
  }

  void set_dft(std::string dft){
    this->dft = dft;
  }

  void print(){
    std::cout<<"名字: "<<std::setw(10)<<name<<"|";
    std::cout<<"     数据种类 "<<std::setw(10)<<type<<"|";
    std::cout<<"     值 "<<std::setw(10)<<value<<"|";
    std::cout<<"     说明 "<<std::setw(10)<<help<<"|";
    std::cout<<std::endl;
  }

  std::string get_string(){
    return value;
  }

  double get_double(){
    if(type==double_string)
      return stod(value);
    else
      return -1.0;
  }

  long get_long(){
    if(type==int_string)
      return stol(value);
    else
      return -1;
  }

};

class CMDLine{
 public:
  
  int argc;
  std::map<string,PARAM> cmd;
  
  CMDLine(int argc, char*argv[]){
    cmd = std::map<string,PARAM>();
    
    this->argc = argc;
    int i = 1;
    while(i<argc){
      char* current = argv[i];
      //如果首字母为-, 说明是参数名
      if(current[0]=='-'){
	current ++ ;
	std::string name(current);
	
	if(name=="help"){
	  PARAM v(name,emp_string);
	  cmd[name] = v;
	  i ++ ;
	}
	else{
	  i ++ ;
	  string value = string(argv[i]);
	  PARAM v = PARAM(name,value);
	  cmd[name] = v;
	  i++;
	}
	
      }
      else{
	std::cout<<"error"<<std::endl;
	i++;
      }
    }
  }

  //注册参数
  CODE register_param(string name,string type,string dft,string help){
    //如果没有这个名字, 现注册
    if(cmd.count(name)==0){
      PARAM v(name,type,dft,help);
      cmd[name] = v;
    }
    else{
      cmd[name].set_type(type);
      cmd[name].set_help(help);
    }
    return SUCCESS;
  }

  PARAM get_param(string name){
    if(cmd.count(name)==0)
      return PARAM();
    
    return cmd[name];
  }

  //检查参数
  CODE check_param(){
    //这个暂时先不写把, 反正也不会输错了
    
    return SUCCESS;
  }

  //设置初始值
  void set_default();

  bool has_name(string n){
    return cmd.count(n);
  }
  
  //打印
  void print(){
    //得到指针
    std::map<std::string,PARAM>::const_iterator cmd_iter = cmd.begin();
    std::cout<<"***************** CMD *********************"<<std::endl;
    while(cmd_iter!=cmd.end()){

      PARAM v = cmd_iter->second;
      v.print();
      
      cmd_iter ++ ;
    }
    
  }

};

void CMDLine::set_default(){
  std::map<string,PARAM>::iterator it = cmd.begin();
  while(it!=cmd.end()){
    PARAM p = it->second;

    if(p.value==error_string)
      (it->second).value = p.dft;
    
    it ++ ;
  }
}

#endif
