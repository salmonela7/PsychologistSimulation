#pragma once

typedef int Queue_type;

class Queue
{
private:
    struct Node
    {
        Queue_type el;
        Node *next;
    };
    Node *front, *rear;
    int size;
public:
    Queue();
    ~Queue();
    bool isEmpty();
    bool isFull();
    void addElement(Queue_type);
    Queue_type remove();
    Queue_type first();
    int length();
    void clear();
    void display();
 //   void emptyQ();
};
