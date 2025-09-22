

#ifndef SNAKEPROJECT_LINKEDLIST_H
#define SNAKEPROJECT_LINKEDLIST_H

struct coordinate
{
    int x;
    int y;
};

struct Node
{
    coordinate c;
    Node *next = nullptr;
    Node *prev = nullptr;
};

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int sz;

public:
    LinkedList();
    LinkedList &operator=(const LinkedList &) = delete;
    void AddNode(Node m);
    void print_linkedList();
    coordinate getbyelem(int i);
    void update_head(coordinate c);
    void remove_tail();
    Node *Get_Head();
    Node *Get_Tail();
    ~LinkedList();
};

#endif
