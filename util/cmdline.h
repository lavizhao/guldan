#ifndef CMDLINE_H_
#define CMDLINE_H_

#include <iostream>
#include <string>
#include <map>

enum CODE {SUCCESS,FAIL};

//每个参数单元
class PARAM{
 private:
  std::string name;//表明类型
  std::string type;//type表明是什么类型, 默认是支持INT,DOUBLE,STRING三种
  std::string value;//给定的值
  std::string help;

 public:
  PARAM(){
    this->name = "error";
    this->type = "error";
    this->value = "error";
    this->help = "error";

  }
  
  PARAM(std::string name,std::string value,std::string type="",std::string help=""){
    this->name = name;
    this->type = type;
    this->value = value;
    this->help = help;
  }

  PARAM(const PARAM& v){
    this->name = v.name;
    this->type = v.type;
    this->value = v.value;
    this->help = v.help;
  }
  
  void set_help(std::string help){
    this->help = help;
  }
  void set_type(std::string type){
    this->type = type;
  }

  void print(){
    std::cout<<"name "<<name<<std::endl;
    std::cout<<"type "<<type<<std::endl;
    std::cout<<"value "<<value<<std::endl;
    std::cout<<"help "<<help<<std::endl;
    std::cout<<"==========================="<<std::endl;
  }

};

class CMDLine{
 public:
  
  int argc;
  std::map<std::string,PARAM> cmd;
  
  CMDLine(int argc, char*argv[]){
    cmd = std::map<std::string,PARAM>();
    
    this->argc = argc;
    int i = 1;
    while(i<argc){
      char* current = argv[i];
      
      //如果首字母为-, 说明是参数名
      if(current[0]=='-'){
	current ++ ;
	std::string name(current);
	
	i ++ ;
	std::string value = std::string(argv[i]);

	PARAM v = PARAM(name,value);
	cmd[name] = v;
	i++;
	
      }
      else{
	std::cout<<"error"<<std::endl;
	i++;
      }
    }
  }

  //注册参数
  CODE registerParam(std::string name,std::string type,std::string help){
    //错误判断
    if(cmd.count(name)==0)
      return FAIL;

    cmd[name].set_type(type);
    cmd[name].set_help(help);
    
    return SUCCESS;
  }

  PARAM getParam(std::string name){
    if(cmd.count(name)==0)
      return PARAM();
    
    return cmd[name];
  }

  //检查参数
  CODE checkParam(){
    //这个暂时先不写把, 反正也不会输错了
    
    return SUCCESS;
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

#endif
