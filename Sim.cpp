#include <iostream>
#include <fstream>
#include <string>
#include "Sim.h"

Sim::Sim()
{
  num_windows = 0;
  _time = 0;
  line = "";
  num_students = 0;
  time_needed = 0;
  new_time = 0;
  wait_time = 0;
  total_students = 0;
  windows = new Window*[1];
  Q = new GenQueue<Student*>();
}

Sim::Sim(string fileName)
{
  num_windows = 0;
  _time = 0;
  line = "";
  num_students = 0;
  time_needed = 0;
  new_time = 0;
  wait_time = 0;
  total_students = 0;
  Q = new GenQueue<Student*>();

  this->fileName = fileName;
  ifstream inp;
  inp.open(fileName);

  cout << endl;
  inp >> num_windows;
  inp.close();

  windows = new Window*[num_windows];

  for (int i = 0; i < num_windows; i++)
  {
    windows[i] = new Window();
  }

  cout << "Number of windows: " << num_windows << endl;

  Q->printQueue();
}

Sim::~Sim() {}

void Sim::Run()
{
  ifstream inp;
  inp.open(fileName);

  cout << endl;
  inp >> num_windows;

  while(!inp.eof())
  {
    inp >> new_time;
    while (_time < new_time)
    {
      TimeStep();
    }

    cout << "Exact time which students arrive: " << new_time << endl;
    inp >> num_students;
    cout << "Number of students: " << num_students << endl;
    total_students += num_students;

    for(int i = 0; i < num_students; i++)
    {
      inp >> time_needed;
      cout << "Student " << i << ", time needed: " << time_needed << endl;
      Q->insert(new Student(time_needed, _time));
    }
    for (int i = 0; i < num_windows; i++)
    {
      if (windows[i]->idle && !Q->isEmpty())
      {
        windows[i]->pass(Q->remove());
        wait_time += _time - windows[i]->student->start_time;
      }
    }
  }

  while (!Q->isEmpty())
  {
    TimeStep();
  }
  inp.close();
}

void Sim::TimeStep()
{
  for (int i = 0; i < num_windows; i++)
  {
    windows[i]->timeStep();
    if (windows[i]->idle && !Q->isEmpty())
    {
      windows[i]->pass(Q->remove());
      wait_time += _time - windows[i]->student->start_time;
    }
  }
  _time++;
}

void Sim::PrintStats()
{
  for (int i = 0; i < num_windows; i++)
  {
    cout << "Window " << i << ", total idle time " << windows[i]->total_idle_time << endl;
  }
  double mean_window_idle = Mean_Window_Idle();
  cout << "Mean Window Idle Time: " << mean_window_idle << endl;
}

double Sim::Mean_Window_Idle()
{
  int total = 0;
  for (int i = 0; i < num_windows; i++)
  {
    total += windows[i]->total_idle_time;
  }
  double avg = total/(double)num_windows;
  return avg;
}
