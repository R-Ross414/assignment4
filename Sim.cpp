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
  list = new DoublyLinkedList<int>();
  wait_time_max = 0;
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
  list = new DoublyLinkedList<int>();
  wait_time_max = 0;
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

  Q->printQueue();
}

/////////////////////////////////////////////////////////////////
Sim::~Sim() {}

/////////////////////////////////////////////////////////////////
void Sim::Run()
{
  ifstream inp;
  inp.open(fileName);

  inp >> num_windows;
  ///////////////////////////////////////////////////
  while(!inp.eof())
  {
    inp >> new_time;
    while (_time < new_time)
    {
      TimeStep();
    }

    inp >> num_students;
    total_students += num_students;
    ///////////////////////////////////////////////////
    for(int i = 0; i < num_students; i++)
    {
      inp >> time_needed;
      Q->insert(new Student(time_needed, _time));
    }
    for (int i = 0; i < num_windows; i++)
    {
      if (windows[i]->idle && !Q->isEmpty())
      {
        windows[i]->pass(Q->remove());
        int wait_time = _time - windows[i]->student->start_time;
        list->insertBack(wait_time);
        total_wait_time += wait_time;
        if (wait_time > wait_time_max)
        {
          wait_time_max = wait_time;
        }
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
      int wait_time = _time - windows[i]->student->start_time;
      list->insertBack(wait_time);
      total_wait_time += wait_time;
      if (wait_time > wait_time_max)
      {
        wait_time_max = wait_time;
      }
    }
  }
  _time++;
}

/////////////////////////////////////////////////////////////////
void Sim::PrintStats()
{
  //Statistics About Window Idle Time
  double mean_window_idle = Mean_Window_Idle();
  cout << "Mean Window Idle Time: " << mean_window_idle << endl;

  int longest_idle_time = Longest_Window_Idle();
  cout << "Longest Window Idle Time: " << longest_idle_time << endl;

  int windows_idle_more_than_five = Windows_Idle_More_Than_Five();
  cout << "Number of Windows Idle for More Than 5 Minutes: " << windows_idle_more_than_five << endl;
  cout << endl;

  //Statistics About Student Wait Times
  double mean_wait_time = Mean_Wait_Time(total_wait_time, total_students);
  cout << "Mean Student Wait Time: " << mean_wait_time << endl;
  cout << "Longest Student Wait Time: " << wait_time_max << endl;
  int waiting_more_than_ten = Waiting_More_Than_Ten(total_students);
  cout << "Number of Students Waiting for More Than 10 Minutes: " << waiting_more_than_ten << endl;
  double median = Median_Wait_Time();
  cout << "Median Wait Time: " << median << endl;
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

/////////////////////////////////////////////////////////////////
double Sim::Mean_Wait_Time(int total_wait_time, int total_students)
{
  double mean = (double)total_wait_time/(double)total_students;
  return mean;
}

/////////////////////////////////////////////////////////////////
int Sim::Waiting_More_Than_Ten(int total_wait_time)
{
  int students_waiting = 0;
  for (int i = 0; i < total_students; i++)
  {
    if (total_wait_time > 10)
    {
      students_waiting++;
    }
  }
  return students_waiting;
}

/////////////////////////////////////////////////////////////////
double Sim::Median_Wait_Time()
{
  list->BubbleSort();

  if (list->getSize() % 2 == 0)
  {
    int mid = list->getSize()/2;
    double median = (double)(list->get(mid - 1) + list->get(mid))/2.0;
  }
  else
  {
    int mid = list->getSize()/2;
    double median = (double)list->get(mid);
  }
}
