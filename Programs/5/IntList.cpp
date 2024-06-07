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
    delete temp;
    return out;
}

IntList::IntList(const IntList &cpy) {
    head = nullptr;
    tail = nullptr;
    IntNode *temp = cpy.head;
    while (temp != nullptr) {
        push_back(temp->value);
        temp = temp->next;
    }
}


IntList & IntList::operator=(const IntList &rhs) {
    if (this != &rhs) {
        clear();
        IntNode *temp = rhs.head;
        while (temp != nullptr) {
            push_back(temp->value);
            temp = temp->next;
        }
    }
    return *this;
}

void IntList::push_back(int value) {
    IntNode *temp = new IntNode(value);
    if (empty()) {
        head = temp;
        tail = temp;
    } 
    else {
        tail->next = temp;
        tail = temp;
    }
}

void IntList::selection_sort() {
    for (IntNode *i = head; i != nullptr; i = i->next) {
        IntNode *min = i;
        for (IntNode *j = i->next; j != nullptr; j = j->next) {
            if (j->value < min->value) {
                min = j;
            }
        }
        if (min != i) {
            int temp = i->value;
            i->value = min->value;
            min->value = temp;
        }
    }
}

void IntList::insert_ordered (int value) {
    IntNode *temp = new IntNode(value);
    if (head == nullptr || value < head->value) {
        temp->next = head;
        head = temp;
    } 
    else {
        IntNode *current = head;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
        delete current;
    }
}

void IntList::remove_duplicates() {
    IntNode *temp = head;
    while (temp != nullptr) {
        IntNode *temp2 = temp;
        while (temp2->next != nullptr) {
            if (temp->value == temp2->next->value) {
                IntNode *dup = temp2->next;
                temp2->next = temp2->next->next;
                if (dup == tail) {
                    tail = temp2;
                }
                delete dup;
            } 
            else {
                temp2 = temp2->next;
            }
        }
        temp = temp->next;
        delete temp2;
    }
    delete temp;
}