#include <iostream>
using namespace std;

#include "IntList.h"

IntList::IntList() {
    head = nullptr;
    tail = nullptr;
}

IntList::~IntList() {
    clear();
}

void IntList::clear() {
    while (!empty()) {
        pop_front();
    }
}

void IntList::push_front(int value) {
    IntNode *temp = new IntNode(value);
    if (empty()) {
        head = temp;
        tail = temp;
    } 
    else {
        temp->next = head;
        head = temp;
    }
}

void IntList::pop_front() {
    if (!empty()) {
        IntNode *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
}

bool IntList::empty() const {
    return head == nullptr;
}

const int & IntList::front() const {
    return head->value;
}

const int & IntList::back() const {
    return tail->value;
}

ostream & operator<<(ostream &out, const IntList &list) {
    IntNode *temp = list.head;
    while (temp != nullptr) {
        out << temp->value;
        temp = temp->next;
        if (temp != nullptr) {
            out << " ";
        }
    }
    return out;
}