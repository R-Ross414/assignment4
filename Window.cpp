#include "Window.h"
#include <iostream>
using namespace std;

Window::Window()
{
  time = 0;
  start_time = 0;
  idle = true;
  student = NULL;
}

Window::~Window()
{
  time = 0;
  start_time = 0;
  idle = false;
  if (student != NULL)
  {
    delete student;
    student = NULL;
  }
}

void Window::pass(Student* student)
{
  idle = false;
  this->student = student;
  start_time = time;
}

void Window::clear()
{
  if (student != NULL)
  {
    idle = true;
    delete student;
    student = NULL;
  }
}

bool Window::isDone()
{
  if (student != NULL)
  {
    return (time - start_time) >= student->task_time;
  }
  else
  {
    return true;
  }
}

void Window::timeStep()
{
  time++;

  if (isDone())
  {
    clear();
  }
}