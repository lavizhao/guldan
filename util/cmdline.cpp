#include "cmdline.h"

PARAM::PARAM(const PARAM& v){
  this->name = v.name;
  this->type = v.type;
  this->value = v.value;
  this->dft = v.dft;
  this->help = v.help;
}

void PARAM::print(){
  std::cout<<"名字: "<<std::setw(10)<<name<<"|";
  std::cout<<"     数据种类 "<<std::setw(10)<<type<<"|";
  std::cout<<"     值 "<<std::setw(10)<<value<<"|";
  std::cout<<"     说明 "<<std::setw(10)<<help<<"|";
  std::cout<<std::endl;
}


//--------------------------------------------------------------

CMDLine::CMDLine(int argc,char* argv[]){
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

CODE CMDLine::register_param(string name,string type,string dft,string help){
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

PARAM CMDLine::get_param(string name){
  if(cmd.count(name)==0)
    return PARAM();
    
  return cmd[name];
}

CODE CMDLine::check_param(){
  return SUCCESS;
}

bool CMDLine::has_name(string n){
  return cmd.count(n);
}

void CMDLine::print(){
  //得到指针
  std::map<std::string,PARAM>::const_iterator cmd_iter = cmd.begin();
  std::cout<<"***************** CMD *********************"<<std::endl;
  while(cmd_iter!=cmd.end()){
    
    PARAM v = cmd_iter->second;
    v.print();
    
    cmd_iter ++ ;
  }
}

void CMDLine::set_default(){
  std::map<string,PARAM>::iterator it = cmd.begin();
  while(it!=cmd.end()){
    PARAM p = it->second;

    if(p.value==error_string)
      (it->second).value = p.dft;
    
    it ++ ;
  }
}
