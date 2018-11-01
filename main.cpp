#include "Sim.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  string cmd = argv[1];
  Sim* sim = new Sim(cmd);
  sim->Run();
  sim->PrintStats();
}
