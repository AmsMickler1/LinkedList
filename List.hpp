// ------List<T>.hpp--------
// Amber Mickler
// COP4530 Assignment 2
// List<T>.h Definitions

#include "List.h"

using namespace cop4530;

    /* CONST_ITERATOR */
template <typename T>
List<T>::const_iterator::const_iterator() {
    current = nullptr;
}   // default zero parameter constructor

template <typename T>
const T & List<T>::const_iterator::operator*() const {
    return retrieve();
}   // operator*() to return element

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}   // increment operator prefix

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    const_iterator original = *this;
    ++(*this);
    return original;
}   // increment operator postfix

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}   // decrement operator prefix

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    const_iterator original = *this;
    --(*this);
    return original;
}   // decrement operator postfix

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
    return (current == rhs.current);
}   // comparison operator

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(current == rhs.current);
}   // comparison operator

template <typename T>
T & List<T>::const_iterator::retrieve() const {
    return current->data;
}   // retrieve the element refers to

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) {
    current = p;
}   // protected constructor


    /* ITERATOR */
template <typename T>
List<T>::iterator::iterator() {
    this->current = nullptr;
}   // constructor

template <typename T>
T & List<T>::iterator::operator*() {
    return const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}   // increment operator

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator original = *this;
    ++(*this);
    return original;
}   // increment operator

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}   // decrement operator

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator original = *this;
    --(*this);
    return original;
}   // decrement operator

template <typename T>
List<T>::iterator::iterator(Node *p) {
    this->current = p;
}   // protected constructor


    /* List */
template <typename T>
List<T>::List() {
    init();
}   // default zero parameter constructor

template <typename T>
List<T>::List(const List<T> &rhs) {
    init();
    for (auto &x : rhs)
        push_back(x);
}   // copy constructor

template <typename T>
List<T>::List(List<T> && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}   // move constructor

template <typename T>
List<T>::List(int num, const T& val) {
    init();
    for (int i=0;i<num;i++) {
        push_back(val);
    }
}   // num elements with value of val

template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
    init();
    for (auto itr=start; itr!=end; itr++) {
        push_back(*itr);
    }
}   // constructs with elements [start, end)

template <typename T>
List<T>::List (std::initializer_list<T> iList) {
    init();
    for (auto &x : iList)
        push_back(x);
}   // constructs with a copy of each of the elements in the initalizer_List<T>

template <typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}   // destructor

template <typename T>
const List<T>& List<T>::operator=(const List<T> &rhs) {
    List copy = rhs;
    std::swap(*this,copy);
    return *this;
}   // copy assignment operator

template <typename T>
List<T> & List<T>::operator=(List<T> && rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}   // move assignment operator

template <typename T>
List<T>& List<T>::operator= (std::initializer_list<T> iList) {
    clear();
    for (auto &x : iList)
        push_back(x);
    return *this;
}   // sets List to the elements of the initializer_List<T>

    /* MEMBER FUNCTIONS */
template <typename T>
int List<T>::size() const {
    return theSize;
}   // number of elements

template <typename T>
bool List<T>::empty() const {
    return (size() == 0);
}   // check if List<T> is empty

template <typename T>
void List<T>::clear() {
    while (!empty())
        pop_front();
}   // delete all elements

template <typename T>
void List<T>::reverse() {
    List<T> rev;
    for (iterator itr=begin(); itr!=tail; itr++) {
        rev.push_front(itr.current->data);
    }
    *this = rev;
}   // reverse the order of the elements

template <typename T>
T& List<T>::front() {
    return *begin();
}   // reference to the first element

template <typename T>
const T& List<T>::front() const {
    return *begin();
}

template <typename T>
T& List<T>::back() {
    return *--end();
}   // reference to the last element

template <typename T>
const T& List<T>::back() const {
    return *--end();
}

template <typename T>
void List<T>::push_front(const T & val) {
    insert(begin(), val);
}   // insert to the beginning

template <typename T>
void List<T>::push_front(T && val) {
    insert(begin(),std::move(val));
}   // move version

template <typename T>
void List<T>::push_back(const T & val) {
    insert(end(), val);
}   // insert to the end

template <typename T>
void List<T>::push_back(T && val) {
    insert(end(), std::move(val));
}   // move version

template <typename T>
void List<T>::pop_front() {
    erase(begin());
}   // delete first element

template <typename T>
void List<T>::pop_back() {
    erase(--end());
}   // delete last element

template <typename T>
void List<T>::remove(const T &val) {
    for(auto itr=begin(); itr!=tail; itr++) {
        if (*itr == val) {
            erase(itr);
            itr--;
        }
    }
}   // remove all elements with value = val

template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
    for (auto itr = begin(); itr != tail; itr++) {
        if (pred(itr.retrieve())) {
            erase(itr);
            itr--;
        }
    }
}	// remove all elements for which Predicate pred
    //  returns true. pred can take in a function object

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
    auto itr = begin();
    for (int i=0; i<theSize; i++) {
        if (i == theSize - 1)
            os << *itr;
        else
            os << *itr << ofc;
        itr++;
    }
}   // print out all elements. ofc is deliminitor

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head->next);
}   // iterator to first element

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head->next);
}   // const iterator to first element

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(tail);
}   // end marker iterator

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(tail);
}   // const iterator to end element

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
    Node *n = new Node(val, itr.current->prev, itr.current);
    ++theSize;
    itr.current->prev->next = n;
    itr.current->prev = n;
    return itr;
}   // insert val ahead of itr

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) {
    Node *n = new Node(std::move(val), itr.current->prev, itr.current);
    ++theSize;
    itr.current->prev->next = n;
    itr.current->prev = n;
    return itr;
}   // move version of insert

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {                           // May need to fix so as to not modify the original
    Node *n = itr.current;
    itr++;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    delete n;
    --theSize;
    return itr;
}   // erase one element

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
    for(iterator itr = start; itr!=end;)
        itr = erase(itr);
    return end;
}   // erase [start, end)

template <typename T>
void List<T>::init() {
    theSize = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}   // initialization

template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
    auto itrL = lhs.begin();
    auto itrR = rhs.begin();
    auto end = lhs.end();
    if (lhs.size() != rhs.size())
        return false;
    else {
        for (; itrL != end; itrL++) {
            if (*itrL != *itrR)
                return false;
            itrR++;
        }
        return true;
    }
}   // overloading comparison operator

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
    return !(lhs==rhs);
}   // overloading not equal to operator

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
    l.print(os);
    return os;
}   // overloading output operator
