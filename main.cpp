#include "Sim.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  //takes file name as a command line argument
  string cmd = argv[1];
  Sim* sim = new Sim(cmd);
  //Runs sim and prints stats
  sim->Run();
  sim->PrintStats();
  cout << endl;
  sim->list->printList();
}
