#include "DoubleListNode.h"

//this class represents a doubly linked list
template<class X> class DoublyLinkedList
{
  private:
    ListNode<X> *front;
    ListNode<X> *back;
    unsigned int size;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(X d);
    void insertBack(X d);
    X removeFront();
    X removeBack();
    ListNode<X> *remove(X key);
    X find(X value);
    X seeFront();
    X deletePos(int pos);

    void printList();
    unsigned int getSize();
};

/////////////////////////////////////////////////////////////////
template <class X>
DoublyLinkedList<X>::DoublyLinkedList()
{
  front = NULL;
  back =  NULL;
  size = 0;
}

template <class X>
DoublyLinkedList<X>::~DoublyLinkedList()
{
  if (front != NULL)
  {
    delete front;
    front = NULL;
  }
  if (back != NULL)
  {
    delete back;
    back = NULL;
  }
}

template <class X>
void DoublyLinkedList<X>::insertFront(X d)
{
  ListNode<X> *node = new ListNode<X>(d);
  if (size == 0) //empty list
  {
    back = node;
  }
  else //not empty
  {
    front->prev = node;
    node->next = front;
  }
  front = node;
  size++;
}

template <class X>
void DoublyLinkedList<X>::insertBack(X d)
{
  ListNode<X> *node = new ListNode<X>(d);
  if (size == 0) //empty list
  {
    front = node;
  }
  else //not empty
  {
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

template <class X>
X DoublyLinkedList<X>::removeFront()
{
  ListNode<X> *node = new ListNode<X>();
  ListNode<X> *temp = node;
  X data;
  //check if empty
  if(front->next == NULL) //only node in ListNode
  {
    back = NULL;
    temp = front;
    data = front->data;
    front = NULL;
  }
  else if(size == 0)
  {
    data = 0;
  }
  else //more than one node in list
  {
    data = front->data;
    temp = front;
    front = front->next;
    front->prev = NULL;
  }

  temp->next = NULL;

  data = temp->data;
  delete temp;
  size--;
  return data;
}

template <class X>
X DoublyLinkedList<X>::removeBack()
{
  ListNode<X> *temp = back;
  X data = temp->data;
  if(back == NULL)
  {

  }
  else
  {
    back = back->prev;
    back->next = NULL;
    delete temp;
  }
  size--;
  return data;
}

template <class X>
ListNode<X>* DoublyLinkedList<X>::remove(X key)
{
  ListNode<X> *current = front;
  while(current->data != key)
  {
    current = current->next;

    if(current = NULL)
    {
      return NULL;
    }
    //we found it
    if(current == front)
    {
      front = current->next;
    }
    else
    {
      current->prev->next = current->next;
    }

    if(current == back)
    {
      back = current->prev;
    }
    else
    {
      current->next->prev = current->prev;
      current->prev = NULL;
      --size;
      return current;
    }
  }
}

template <class X>
X DoublyLinkedList<X>::find(X value)
{
  int idx = -1;
  ListNode<X> *curr = front;

  while(curr != NULL) //begin searching for value
  {
    idx++;

    if(curr->data = value)
    {
      break;
    }
    else
    {
      curr = curr->next;
    }
  }

  if(curr == NULL)
  {
    idx = -1;
  }
  return idx;
}

template <class X>
X DoublyLinkedList<X>::seeFront()
{
  return front->data;
}

template <class X>
X DoublyLinkedList<X>::deletePos(int pos)
{
  int idx = 0;

  ListNode<X> *curr = front;
  ListNode<X> *prev = front;

  while(idx != pos) //this loop is responsible for putting our pointers in their respective positions
  {
    prev = curr;
    curr = curr->next;
    ++idx;
  }

  //found the position, lets proceed to delete
  prev->next = curr->next;
  curr->next = NULL;

  X d = curr->data;
  size--;

  delete curr;
  return d;
}

template <class X>
void DoublyLinkedList<X>::printList()
{
  ListNode<X> *curr = front;
  while(curr != NULL)
  {
    cout << curr->data << " ";
    curr = curr->next;
  }
  cout << endl;
}

template <class X>
unsigned int DoublyLinkedList<X>::getSize()
{
  return size;
}
