#include <iostream>
#include <fstream>
#include <string>
#include "Window.h"
using namespace std;

class Sim
{
  public:
    Sim(); //constructor
    Sim(string fileName); //overloaded constructor
    ~Sim(); //destructor

    /*Class Functions:
      1. void method that runs the simulation
      2. progresses the clock
      3. prints out the statistics calculated from the simulation
      4. function to calculate the avg amount of time windows are spent idle
      5. function to calculate the longest time a window is spent idle
      6. function to calculate how many windows are idle for more than 5 minutes */
    void Run(); //#1
    void TimeStep(); //#2
    void PrintStats(); //#3
    double Mean_Window_Idle(); //#4
    int Longest_Window_Idle(); //#5
    int Windows_Idle_More_Than_Five(); //#6

    /*Class Variables:
      1. file name as a string given by the cmd line argument
      2. line of the file
      3. the number of windows
      4. time that a student arrives
      5. number of students that arrived at a given time
      6. amount of time a student needs to spend at a window
      7. the time that a student goes to the window (possibly after waiting)
      8. total amount of wait time of a student 
      9. the total number of students that arrived */
    string fileName; //#1
    string line; //#2
    int num_windows; //#3
    int _time; //#4
    int num_students, time_needed, new_time; //#5~#7
    int total_wait_time; //#8
    int total_students; //#9

    //instances of other classes, i.e. windows and queue classes
    Window** windows;
    GenQueue<Student*>* Q;
} ;
