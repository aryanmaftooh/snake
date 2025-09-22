#include "LinkedList.h"
#include <iostream>

inline void print_Node(Node n)
{
    std::cout << '(' << n.c.x << ", " << n.c.y << ")";
}

LinkedList::LinkedList() : head{nullptr}, tail{nullptr}, sz{0}
{
}

void LinkedList::AddNode(Node m)
{
    Node *new_member = new Node;
    new_member->c = m.c;
    new_member->next = nullptr;
    new_member->prev = nullptr;
    if (sz == 0)
    {
        head = new_member;
        tail = new_member;
    }
    else
    {
        tail->next = new_member;
        new_member->prev = tail;
        tail = new_member;
    }
    sz++;
}

void LinkedList::print_linkedList()
{
    Node move = *head;
    print_Node(move);
    while (move.next != NULL)
    {
        move = *move.next;
        print_Node(move);
    }
    std::cout << std::endl;
}

coordinate LinkedList::getbyelem(int i)
{
    int l = sz;
    int c = 0;
    for (Node move = *head; l != 0; move = *move.next)
    {
        if (c == i)
        {
            return move.c;
        }
        c++;
        l--;
    }
}

void LinkedList::update_head(coordinate point)
{
    Node *new_node = new Node;
    new_node->c = point;
    new_node->prev = nullptr;
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
}

void LinkedList::remove_tail()
{
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

Node *LinkedList::Get_Head()
{
    return head;
}

Node *LinkedList::Get_Tail()
{
    return tail;
}
LinkedList::~LinkedList()
{
    for (Node *curr = head->next; sz != 0; curr = curr->next)
    {
        if (curr == NULL)
        {
            delete tail;
            tail = nullptr;
            head = nullptr;
        }
        else
        {
            delete curr->prev;
            curr->prev = nullptr;
        }
        sz--;
    }
}
