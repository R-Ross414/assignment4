#include <iostream>
#include <fstream>
#include <string>
//#include "GenQueue.h"
using namespace std;

class Sim
{
  public:
    Sim();
    ~Sim();

  int num_windows;
  ifstream inp;
  //Window** windows = new Window*[num_windows];
  void nextStudent();

} ;
