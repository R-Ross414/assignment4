#include <iostream>
#include <fstream>
#include <string>
#include "Window.h"
using namespace std;

class Sim
{
  public:
    Sim();
    Sim(string fileName);
    ~Sim();

  void Run();
  void TimeStep();
  void PrintStats();
  double Mean_Window_Idle();

  string fileName;
  string line;
  int num_windows;
  int _time;
  int num_students, time_needed, new_time;
  int wait_time;
  int total_students;
  Window** windows;
  GenQueue<Student*>* Q;
} ;
