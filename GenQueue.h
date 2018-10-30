#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

template <class T> class GenQueue
{
  public:
    GenQueue();
    ~GenQueue();

    void insert(T data);
    T remove();
    T peek();


    bool isFull();
    bool isEmpty();
    int getSize();
    void printQueue();

  private:
    int front;
    int rear;
    int numElem;
    int size;
    DoublyLinkedList<T> *myQueue;

  } ;

  //////////////////////////////////////////////////////////
  //implementation

  template <class T>
  GenQueue<T>::GenQueue()
  {
    myQueue = new DoublyLinkedList<T>();
    size = 0;
    front = 0;
    rear = -1;
    numElem = 0;
  }

  template <class T>
  GenQueue<T>::~GenQueue()
  {
    delete myQueue;
    cout << "Queue has been destroyed" << endl;
  }

  template <class T>
  void GenQueue<T>::insert(T data)
  {
    //check if its full before inserting
    myQueue->insertBack(data);
    numElem++;
  }

  template <class T>
  T GenQueue<T>::remove()
  {
    T data = myQueue->removeFront();
    numElem--;
    return data;
  }

  template <class T>
  T GenQueue<T>::peek()
  {
    return myQueue->seeFront();
  }

  template <class T>
  bool GenQueue<T>::isEmpty()
  {
    return numElem == 0;
  }

  template <class T>
  bool GenQueue<T>::isFull()
  {
    return numElem == size;
  }

  template <class T>
  int GenQueue<T>::getSize()
  {
    return numElem;
  }

  template <class T>
  void GenQueue<T>::printQueue()
  {
    myQueue->printList();
  }
