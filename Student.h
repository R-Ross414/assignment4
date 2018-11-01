#include <iostream>
using namespace std;

class Student
{
  public:
    Student();
    Student(int task_time, int start_time);
    ~Student();

    int start_time;
    int task_time;

};
