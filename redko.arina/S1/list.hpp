#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <memory>
#include <cassert>

namespace redko
{
  template< typename T >
  struct ListElem
  {
    ListElem();
    ListElem(T d);

    T data;
    ListElem< T > * next;
  };

  template< typename T >
  struct Iterator
  {
    ListElem< T > * node;
    using this_t = Iterator< T >;

    Iterator();
    ~Iterator() = default;
    Iterator(const this_t &) = default;
    Iterator(ListElem< T > * ptr);
    this_t& operator=(const this_t &) = default;

    this_t& operator++();
    this_t operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
  };

  template< typename T >
  class List
  {
  public:
    List(): head_() {};
    List(const List & l);
    List(List< T > && l);
    ~List();

    List< T > & operator=(const List< T > & other);
    List< T > & operator=(List< T > && other);

    Iterator< T > eraseAfter(Iterator< T > pos);

    ListElem< T > & front();

    void pushBack(const T & value);
    void pushBack(T && value);
    void popFront();

    bool isEmpty();

    Iterator< T > beforeBegin();
    Iterator< T > begin();
    Iterator< T > end();

    void swap(List< T > & other);
    void clear();

  private:
    ListElem< T > head_;
  };
}

template < typename T >
redko::ListElem< T >::ListElem() : data(), next(nullptr)
{}
template < typename T >
redko::ListElem< T >::ListElem(T d) : data(d), next(nullptr)
{}

template < typename T >
redko::Iterator< T >::Iterator() : node(nullptr)
{}
template < typename T >
redko::Iterator< T >::Iterator(ListElem< T >* ptr) : node(ptr) {}
template< typename T >
redko::Iterator< T >& redko::Iterator< T >::operator++() {
  assert(node != nullptr);
  node = node->next;
  return *this;
}
template< typename T >
redko::Iterator< T > redko::Iterator< T >::operator++(int) {
  assert(node != nullptr);
  this_t result(*this);
  ++(*this);
  return result;
}
template< typename T >
T & redko::Iterator< T >::operator*() {
  assert(node != nullptr);
  return node->data;
}
template< typename T >
T * redko::Iterator< T >::operator->() {
  assert(node != nullptr);
  return std::addressof(node->data);
}
template< typename T >
bool redko::Iterator< T >::operator==(const this_t & rhs) const {
  return node == rhs.node;
}
template< typename T >
bool redko::Iterator< T >::operator!=(const this_t & rhs) const {
  return !(rhs == *this);
}

template< typename T >
redko::List< T >::List(const List & other)
{
  ListElem< T > * othrElem = other.head_.next;
  ListElem< T > * thisElem = head_.next;

  while (othrElem != nullptr)
  {
    thisElem = new ListElem< T >(othrElem->data);
    thisElem = thisElem->next;
    othrElem = othrElem->next;
  }
}

template< typename T >
redko::List< T >::List(List< T > && other)
{
  head_.next = other.head_.next;
  other.head_.next = nullptr;
}

template< typename T >
redko::List< T >::~List()
{
  clear();
}
template< typename T >
void redko::List< T >::pushBack(const T & value)
{
  redko::ListElem< T > * tmp = new redko::ListElem< T >(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< T > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
void redko::List< T >::pushBack(T && value)
{
  redko::ListElem< T > * tmp = new redko::ListElem< T >(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< T > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
redko::Iterator< T > redko::List< T >::eraseAfter(Iterator< T > pos)
{
  redko::ListElem< T > * p = pos.node->next;
  if (p != nullptr)
  {
    pos.node->next = p->next;
    delete p;
  }
  return pos++;
}
template< typename T >
void redko::List< T >::popFront()
{
  eraseAfter(beforeBegin());
}

template< typename T >
redko::ListElem< T > & redko::List< T >::front()
{
  return head_.next;
}
template< typename T >
redko::List< T > & redko::List< T >::operator=(const redko::List< T > & other)
{
  if (&other != this)
  {
    clear();
    redko::Iterator< T > otherElem = other.begin();
    while (otherElem != other.end())
    {
      pushBack(*otherElem);
      otherElem++;
    }
  }
  return *this;
}
template< typename T >
redko::List< T > & redko::List< T >::operator=(redko::List< T > && other)
{
  if (&other != this)
  {
    clear();
    redko::ListElem< T > * tmp = other.front();
    head_.next = tmp;
    other.head_.next = nullptr;
  }
  return *this;
}
template< typename T >
bool redko::List< T >::isEmpty()
{
  return head_.next == nullptr;
}
template< typename T >
redko::Iterator< T > redko::List< T >::beforeBegin()
{
  return { &head_ };
}
template< typename T >
redko::Iterator< T > redko::List< T >::begin()
{
  return { head_.next };
}
template< typename T >
redko::Iterator< T > redko::List< T >::end()
{
  Iterator< T > curr = begin();
  while (curr.node != nullptr)
  {
    curr++;
  }
  return curr;
}
template< typename T >
void redko::List< T >::swap(List< T > & other)
{
  ListElem< T > tmp = other.head_;
  other.head_ = head_;
  head_ = tmp;
}
template< typename T >
void redko::List< T >::clear()
{
  while (begin() != end())
  {
    popFront();
  }
}

#endif
