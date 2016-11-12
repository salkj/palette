#include <iostream>
#include <string>
#include "kimages.h"
using namespace std;

int main(int argc, char* argv[]){
  kimages foo(argv[1], atoi(argv[2]));
  foo.reduceGif(argv[1], atoi(argv[2]));
  return 0;
}
