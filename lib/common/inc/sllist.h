/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

/* Copyright (c) 2009 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Singly_linked_list_(C_Plus_Plus)?action=history&offset=20060517203723

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Singly_linked_list_(C_Plus_Plus)?oldid=4813
*/

#ifndef LP_SLLIST_H
#define LP_SLLIST_H

#include <iterator>
#include <cstddef>

namespace literateprograms {

template <typename T>
class sllist
{
  private:
    struct node
    {
      node(T val)
        : next(NULL), value(val)
      {}

      node* next;
      T     value;
    };

    node* _head;
    node* _tail;

    int _size;


  public:
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
    class const_iterator : public std::iterator<std::forward_iterator_tag, T, size_t, T const*, T const&>
    {
      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T         value_type;
        typedef ptrdiff_t difference_type;
        typedef T const*  pointer;
        typedef T const&  reference;

        const_iterator(node* cur_node = NULL, const sllist<T>* container = NULL) : _curpos(cur_node), _list(container)
        {}

        virtual ~const_iterator() {}

        reference operator*()
        {
          return _curpos->value;
        }

        pointer operator ->()
        {
          return &(**this);
        }

        // The lack of arguments indicates that this is prefix ++
        const_iterator& operator++()
        {
          _curpos = _curpos->next;
          return *this;
        }

        // The dummy argument indicates that this is the postfix ++
        const_iterator operator++(int)
        {
          const_iterator old_it = *this;
          ++(*this);
          return old_it;
        }

        // The lack of arguments indicates that this is prefix --
        const_iterator& operator--()
        {
          node *last = NULL;
          node *current = _list->_head;
          while (current != _curpos) {
            last = current;
            current = current->next;
          }
          _curpos = last;
          return *this;
        }

        bool operator ==(const_iterator const& rhs) const
        {
          return _curpos == rhs._curpos;
        }

        bool operator !=(const_iterator const& rhs) const
        {
          return !(*this == rhs);
        }

      protected:
        node* _curpos;
        const sllist<T>* _list;

    };
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    class iterator : public const_iterator
    {
      public:
        iterator(node* iter_node = NULL, const sllist<T>* container = NULL) : const_iterator(iter_node, container)
        {}

        typedef std::forward_iterator_tag iterator_category;
        typedef T      value_type;
        typedef size_t difference_type;
        typedef T*     pointer;
        typedef T&     reference;

        using const_iterator::_curpos;
        using const_iterator::_list;

        reference operator*() const
        {
          return _curpos->value;
        }

        pointer operator ->() const
        {
          return &(**this);
        }

        iterator& operator++()
        {
          _curpos = _curpos->next;
          return *this;
        }

        iterator operator++(int)
        {
          iterator old_it = *this;
          ++(*this);
          return old_it;
        }

        iterator& operator--()
        {
          node *last = NULL;
          node *current = _list->_head;
          while (current != _curpos) {
            last = current;
            current = current->next;
          }
          _curpos = last;
          return *this;
        }

    };


    sllist();
    sllist(sllist<T> const& rhs);
    ~sllist();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    void push_front(T const& elt);
    void push_back(T const& elt);
    void insert_after(iterator where, T const& elt);
    iterator insert(iterator where, T const& elt);

    iterator erase_after(iterator it);
    iterator erase(iterator it);
    iterator erase(iterator first, iterator last);
    void clear();
    void pop_front();

    sllist& operator =(sllist<T> const& rhs);

    size_t size() const;
    bool empty() const;

    friend class sllist<T>::iterator;

};

template <typename T>
inline typename sllist<T>::iterator sllist<T>::begin()
{
    return iterator(_head, this);
}

template <typename T>
inline typename sllist<T>::iterator sllist<T>::end()
{
    return iterator(NULL, this);
}

template <typename T>
inline typename sllist<T>::const_iterator sllist<T>::begin() const
{
    return const_iterator(_head, this);
}

template <typename T>
inline typename sllist<T>::const_iterator sllist<T>::end() const
{
    return const_iterator(NULL, this);
}

template <typename T>
inline void sllist<T>::insert_after(typename sllist<T>::iterator where, T const& elt)
{
      
    node* newnode = new node(elt);
    newnode->next = where._curpos->next;
    where._curpos->next = newnode;
    _size++;
    if (newnode->next == NULL)
    {
        _tail = newnode;
    }

}

template <typename T>
inline typename sllist<T>::iterator sllist<T>::insert(typename sllist<T>::iterator where, T const& elt)
{

    node* newnode = new node(elt);
    newnode->next = where._curpos;
    _size++;

    if (where._curpos == NULL) {  // insert after the last element 
      if (_tail) {
        _tail->next = newnode;
        _tail = newnode;
      } else {
        _tail = _head = newnode;
      }
      return iterator(newnode, this);
    } 
    
    if (_head == where._curpos) {  // insert before the first element
      _head = newnode;
      return iterator(newnode, this);
    }
    
    // insert somewhere
    node* temp = _head;
    node* last = NULL;
    while (temp != where._curpos)
    {
      last = temp;
      temp = temp->next;
    }

    if (last) {
      last->next = newnode;
      return iterator(newnode, this);
    }

    return iterator(NULL, this);
}



template <typename T>
inline void sllist<T>::push_front(T const& elt)
{
    node* newnode = new node(elt);
    newnode->next = _head;
    _head = newnode;
    if (_tail == NULL)
    {
        _tail = newnode;
    }

    _size++;
}

template <typename T>
inline void sllist<T>::push_back(T const& elt)
{
    if (_tail != NULL)
        insert_after(iterator(_tail, this), elt);
    else
        push_front(elt);
}

template <typename T>
inline typename sllist<T>::iterator sllist<T>::erase_after(typename sllist<T>::iterator it)
{

    node* todelete = it._curpos->next;
    it._curpos->next = it._curpos->next->next;
    _size--;

    if (it._curpos->next == NULL)
    {
        _tail = it._curpos;
    }

    delete todelete;
    return iterator(it._curpos->next, this);
}


template <typename T>
inline typename sllist<T>::iterator sllist<T>::erase(typename sllist<T>::iterator it)
{
    if (it._curpos == NULL)
      return iterator(NULL);

    _size--;

    node* last = NULL;
    node* temp = _head;

    // search for the previous element
    while (temp != it._curpos) {
      last = temp;
      temp = temp->next;
    }
  
    if (last) { // if previous exists
      last->next = it._curpos->next; // unlink the element which we want to delete
      
      if (last->next == NULL) // if it is the last then we have to fix the tail
        _tail = last;

      temp = last->next;
        
    } else { // we want to delete the first element 
      _head = _head->next;   // unlink the element which we want to delete (which is the head) 

      if (_head == NULL)  // if it is the last element in the list then we have ti set the tail to NULL
        _tail = NULL;

      temp = _head;  
    }
    
    delete it._curpos;  // delete the element
    
    return iterator(temp, this);  // return the next element in the list
}

template <typename T>
inline typename sllist<T>::iterator sllist<T>::erase(typename sllist<T>::iterator first, typename sllist<T>::iterator last)
{
    if (first._curpos == last._curpos)
      return last;

    node* previous = NULL;
    node* temp = _head;

    // search for the previous element
    while (temp != first._curpos) {
      previous = temp;
      temp = temp->next;
    }

    // delete elements in [first,last)
    node* todelete = NULL;
    while (temp != last._curpos) {
      if (!temp)
        throw 0;  // invalid range : last < first
      todelete = temp;
      temp = temp->next;
      _size--;
      delete todelete;
    }

    if (previous)
      previous->next = temp; // correct the link
    else
      _head = temp; // fix the head

    if (temp == NULL)
      _tail = previous; // fix the tail

    return iterator(temp, this);
}

template <typename T>
inline void sllist<T>::pop_front()
{
    node* todelete = _head;
    _head = _head->next;
    if (_head == NULL) {
        _tail = NULL;
    }
    _size--;
    delete todelete;
}

template <typename T>
inline void sllist<T>::clear()
{
    if (_size == 0)
      return;

    node* todelete = NULL;
    while (_head) {
      todelete = _head;
      _head = _head->next;
      delete todelete;
    }

    _tail = NULL;
    _size = 0;
}

template <typename T>
sllist<T>& sllist<T>::operator =(sllist<T> const& rhs)
{
    clear();

    const_iterator rhs_it = rhs.begin();
    for (rhs_it = rhs.begin(); rhs_it != rhs.end(); ++rhs_it)
    {
        push_back(*rhs_it);
    }

    return *this;
}

template <typename T>
inline size_t sllist<T>::size() const
{
    return _size;
}

template <typename T>
inline bool sllist<T>::empty() const
{
    return _size == 0;
}

template <typename T>
inline sllist<T>::sllist() : _head(NULL), _tail(NULL), _size(0)
{
}

template <typename T>
inline sllist<T>::sllist(sllist<T> const& rhs) : _head(NULL), _tail(NULL) , _size(0)
{
    *this = rhs;
}

template <typename T>
inline sllist<T>::~sllist()
{
    clear();
}

}

#endif
