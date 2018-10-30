#include "Student.h"
#include <iostream>
using namespace std;

Student::Student()
{
  task_time = 0;
  time = 0;
}

Student::Student(int task_time)
{
  this->task_time = task_time;
  time = 0;
}

Student::~Student()
{
  task_time = 0;
  time = 0;
}
