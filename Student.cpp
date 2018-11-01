#include "Student.h"
#include <iostream>
using namespace std;

Student::Student()
{
  //initializes the class variables
  task_time = 0;
  start_time = 0;
}

/////////////////////////////////////////////////////////////////
Student::Student(int task_time, int start_time)
{
  //sets the variables
  this->task_time = task_time;
  this->start_time = start_time;
}

/////////////////////////////////////////////////////////////////
Student::~Student()
{
  task_time = 0;
  start_time = 0;
}
