#include <iostream>
#include <vector>
#include <time.h>

#include "../util/file_control.h"
#include "../util/string_util.h"
#include "../util/sparse_vector.h"


using namespace std;

int main(int argc, char *argv[])
{

  Sparse_Vector ex;
  ex.set_value(1,2.0);
  ex.set_value(3,4.0);

  ex.print_value();
  
  return 0;
}
