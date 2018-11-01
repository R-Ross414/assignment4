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
  total_wait_time = 0;
  total_students = 0;
  windows = new Window*[1];
  Q = new GenQueue<Student*>();
}

/////////////////////////////////////////////////////////////////
Sim::Sim(string fileName)
{
  num_windows = 0;
  _time = 0;
  line = "";
  num_students = 0;
  time_needed = 0;
  new_time = 0;
  total_wait_time = 0;
  total_students = 0;
  Q = new GenQueue<Student*>();
  ///////////////////////////////////////////////////
  this->fileName = fileName;
  ifstream inp;
  inp.open(fileName);
  ///////////////////////////////////////////////////
  cout << endl;
  inp >> num_windows;
  inp.close();
  ///////////////////////////////////////////////////
  windows = new Window*[num_windows];

  for (int i = 0; i < num_windows; i++)
  {
    windows[i] = new Window();
  }

  cout << "Number of windows: " << num_windows << endl;

  Q->printQueue();
}

/////////////////////////////////////////////////////////////////
Sim::~Sim() {}

/////////////////////////////////////////////////////////////////
void Sim::Run()
{
  ifstream inp;
  inp.open(fileName);

  cout << endl;
  inp >> num_windows;
  ///////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////
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
        total_wait_time += _time - windows[i]->student->start_time;
      }
    }
  }
  ///////////////////////////////////////////////////
  while (!Q->isEmpty())
  {
    TimeStep();
  }
  inp.close();
}

/////////////////////////////////////////////////////////////////
void Sim::TimeStep()
{
  for (int i = 0; i < num_windows; i++)
  {
    windows[i]->timeStep();
    if (windows[i]->idle && !Q->isEmpty())
    {
      windows[i]->pass(Q->remove());
      total_wait_time += _time - windows[i]->student->start_time;
    }
  }
  _time++;
}

/////////////////////////////////////////////////////////////////
void Sim::PrintStats()
{
  for (int i = 0; i < num_windows; i++)
  {
    cout << "Window " << i << ", total idle time " << windows[i]->total_idle_time << endl;
  }

  //Statistics About Window Idle Time
  double mean_window_idle = Mean_Window_Idle();
  cout << "Mean Window Idle Time: " << mean_window_idle << endl;

  int longest_idle_time = Longest_Window_Idle();
  cout << "Longest Window Idle Time: " << longest_idle_time << endl;

  int windows_idle_more_than_five = Windows_Idle_More_Than_Five();
  cout << "Windows Idle for More Than 5 Minutes: " << windows_idle_more_than_five << endl;

  cout << endl;

  //Statistics About Student Wait Times
}

/////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////
int Sim::Longest_Window_Idle()
{
  int longest_idle = 0;
  for (int i = 0; i < num_windows; i++)
  {
    if (windows[i]->total_idle_time >= longest_idle)
    {
      longest_idle = windows[i]->total_idle_time;
    }
  }
  return longest_idle;
}

/////////////////////////////////////////////////////////////////
int Sim::Windows_Idle_More_Than_Five()
{
  bool win_mtf;
  int idle_more_than_five = 0;
  for (int i = 0; i < num_windows; i++)
  {
    win_mtf = windows[i]->moreThanFive(windows[i]->total_idle_time);
    if (win_mtf)
    {
      idle_more_than_five++;
    }
  }
  return idle_more_than_five;
}
