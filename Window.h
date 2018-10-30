#include "Student.h"
#include <iostream>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();

    int time;
    int start_time;
    bool idle;
    Student* student;

    void pass(Student* student);
    void clear();
    bool isDone();
    void timeStep();
} ;
