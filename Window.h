#include "Student.h"
#include "GenQueue.h"
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
    int idle_time;
    int total_idle_time;
    Student* student;

    void pass(Student* student);
    void clear();
    bool isDone();
    void timeStep();
} ;
