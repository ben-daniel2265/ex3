#ifndef EX3_Queue_H
#define EX3_Queue_H

#include <iostream>

template<class T>
struct QNode{
    T data;
    QNode* next;

    QNode(T data){
        this->data = data;
        this->next = NULL;
    }
};

template<class T>
class Queue
{
    QNode<T> *head, *tail;
    int length;

    public:
    Queue();
    Queue(const Queue& q);
    ~Queue();
    Queue& operator=(const Queue& q);

    void pushBack(const T& value);
    T& front() const;
    void popFront();
    int size() const;

    template<class S>
    friend Queue<S> filter(Queue<S> queue, bool (*con)(S));

    template<class S>
    friend void transform(Queue<S>& queue, void (*trans)(S&));

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};
};


template<class T>
Queue<T>::Queue() : 
    head(NULL), tail(NULL), length(0)
{}


template<class T>
Queue<T>::Queue(const Queue<T>& q)
{
    this->length = q.length;
    this->head = new QNode<T>(q.head->data);
    QNode<T>* temp1 = this->head;
    QNode<T>* temp2 = q.head;

    while(temp2->next){
        temp2 = temp2->next;
        temp1->next = new QNode(temp2->data);
        temp1 = temp1->next;
    }

    this->tail = temp1;
}


template<class T>
Queue<T>::~Queue()
{
    QNode<T>* temp = this->head;

    while(this->head){
        this->head = this->head->next;
        delete temp;
        temp = this->head;
    }
}


template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q)
{
    if(this == &q){
        return *this;
    }
    
    (*this).~Queue();

    this->length = q.length;
    this->head = new QNode<T>(q.head->data);
    QNode<T>* temp1 = this->head;
    QNode<T>* temp2 = q.head;

    while(temp2->next){
        temp2 = temp2->next;
        temp1->next = new QNode(temp2->data);
        temp1 = temp1->next;
    }

    this->tail = temp1;

    return *this;
}


template<class T>
void Queue<T>::pushBack(const T& value)
{
    if(tail){
        this->tail->next = new QNode<T>(value);
        this->tail = this->tail->next;
    }
    else{
        this->tail = new QNode<T>(value);
        this->head = this->tail;
    }

    this->length++;
}


template<class T>
T& Queue<T>::front() const
{
    if(!this->head){
        throw Queue<T>::EmptyQueue();
    }
    return this->head->data;
}


template<class T>
void Queue<T>::popFront()
{
    if(!this->head){
        throw Queue<T>::EmptyQueue();
    }

    QNode<T>* temp = this->head;
    this->head = this->head->next;
    delete temp;

    this->length--;
}


template<class T>
int Queue<T>::size() const
{
    return this->length;
}


template<class T>
Queue<T> filter(Queue<T> queue, bool (*con)(T))
{
    Queue<T> result = Queue<T>();
    QNode<T>* temp = queue.head;
    while(temp){
        if(con(temp->data)){
            result.pushBack(temp->data);
        }
        temp = temp->next;
    }

    return result;
}


template<class T>
void transform(Queue<T>& queue, void (*trans)(T&))
{
    QNode<T>* temp = queue.head;
    while(temp){
        trans(temp->data);
        temp = temp->next;
    }

    temp = queue.head;
    while(temp){
        temp = temp->next;
    }
}


template<class T>
class Queue<T>::Iterator
{
    QNode<T>* pointer;

    Iterator(QNode<T>* pointer);

    friend class Queue<T>;

    public:
    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);

    bool operator!=(const Iterator& iterator) const;

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};
};


template<class T>
Queue<T>::Iterator::Iterator(QNode<T>* pointer) : 
    pointer(pointer)
{}


template<class T>
const T& Queue<T>::Iterator::operator*() const
{
    return this->pointer->data;
}


template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(!this->pointer){
        throw Queue<T>::Iterator::InvalidOperation();
    }
    this->pointer = this->pointer->next;

    return *this;
}


template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    if(!this->pointer){
        throw Queue<T>::Iterator::InvalidOperation();
    }
    this->pointer = this->pointer->next;

    return result;
}


template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const
{
    return this->pointer != iterator.pointer;
}


template<class T>
class Queue<T>::ConstIterator
{
    QNode<T>* pointer;

    ConstIterator(QNode<T>* pointer);

    friend class Queue<T>;

    public:
    const T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);

    bool operator!=(const ConstIterator& iterator) const;

    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation{};
};


template<class T>
Queue<T>::ConstIterator::ConstIterator(QNode<T>* pointer) : 
    pointer(pointer)
{}


template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return this->pointer->data;
}


template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(!this->pointer){
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    this->pointer = this->pointer->next;

    return *this;
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    ConstIterator result = *this;
    if(!this->pointer){
        throw Queue<T>::ConstIterator::InvalidOperation();
    }

    this->pointer = this->pointer->next;

    return result;
}


template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{
    return this->pointer != iterator.pointer;
}


template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this->head);
}


template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this->tail);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this->head);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this->tail->next);
}



#endif //EX3_Queue_H