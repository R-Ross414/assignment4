#include <iostream>
#include <fstream>
#include <string>
#include "Sim.h"

Sim::Sim()
{
  num_windows = 0;
  _time = 0;
  line = "";
  windows = new Window*[num_windows];
  Q = new GenQueue<int>();
}

Sim::Sim(string fileName)
{
  this->fileName = fileName;
  ifstream inp;
  inp.open(fileName);

  cout << endl;
  inp >> num_windows;

 for (int i = 0; i < num_windows; i++)
  {
    windows[i] = new Window();
  }

  cout << "Number of windows: " << num_windows << endl;

  while(!inp.eof())
  {
    inp >> new_time;
    while (_time < new_time)
    {
      for (int i = 0; i < num_windows; i++)
      {
        windows[i]->timeStep();
        nextStudent(i);
      }
      _time++;
    }

      cout << "Exact time which students arrive: " << new_time << endl;
      inp >> num_students;
      cout << "Number of students: " << num_students << endl;

      for(int i = 0; i < num_students; i++)
      {
        inp >> time_needed;
        cout << "Student " << i << ", time needed: " << time_needed << endl;
        Q->insert(time_needed);
      }
      for (int i = 0; i < num_windows; i++)
      {
        nextStudent(i);
      }
  }

  while (!Q->isEmpty())
  {
    for (int i = 0; i < num_windows; i++)
    {
      windows[i]->timeStep();
      nextStudent(i);
    }
    _time++;
  }

  Q->printQueue();
}

void Sim::nextStudent(int i)
{
  if (windows[i]->idle && !Q->isEmpty())
  {
    Student* student = new Student(Q->remove());
    windows[i]->pass(student);
  }
}

Sim::~Sim() {}
