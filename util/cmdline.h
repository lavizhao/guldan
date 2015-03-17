#ifndef CMDLINE_H_
#define CMDLINE_H_

#include <iostream>
#include <string>
#include <map>
#include <iomanip>

#include "string_util.h"

enum CODE {SUCCESS,FAIL};

using std::string;

static string error_string = "error";
static string int_string = "INT";
static string double_string = "DOUBLE";
static string string_string = "STRING";

static string emp_string = "emp";

static string dir_dft = "./fuck";
  

//每个参数单元
class PARAM{
 public:
  std::string name;//表明类型
  std::string type;//type表明是什么类型, 默认是支持INT,DOUBLE,STRING三种
  std::string value;//给定的值
  std::string dft;//默认值
  std::string help;

 PARAM():name(error_string),type(error_string),value(error_string),help(error_string),dft(error_string){

  }
  
 PARAM(string name,string type,string dft,string help)	\
   :name(name),type(type),value(error_string),dft(dft),help(help){
  }
  
 PARAM(string name,string value):name(name),value(value){}

  PARAM(const PARAM& v);
  
  inline void set_help(std::string help){
    this->help = help;
  }
  inline void set_type(std::string type){
    this->type = type;
  }

  inline void set_dft(std::string dft){
    this->dft = dft;
  }

  void print();

  inline std::string get_string(){
    return value;
  }

  inline double get_double(){
    if(type==double_string)
      return stod(value);
    else
      return -1.0;
  }

  inline long get_long(){
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
  
  CMDLine(int argc, char*argv[]);

  //注册参数
  CODE register_param(string name,string type,string dft,string help);

  PARAM get_param(string name);

  //检查参数
  CODE check_param();

  //设置初始值
  void set_default();

  bool has_name(string n);
  
  //打印
  void print();
    


};


#endif
