#include <iostream>

using namespace std;
template<class X> class ListNode
{
  public:
    ListNode();
    ~ListNode();
    ListNode(X d);

    X data;
    ListNode *next;
    ListNode *prev;
};

///////////////////////////////////

template<class X>
ListNode<X>::ListNode()
{
  //we will implement this
}

template<class X>
ListNode<X>::ListNode(X d)
{
  data = d;
  next = NULL; //nullptr
  prev = NULL;
}

template<class X>
ListNode<X>::~ListNode()
{
  if (next != NULL)
  {
    delete next;
    next = NULL;
  }
  if (prev != NULL)
  {
    delete prev;
    prev = NULL;
  }
}
