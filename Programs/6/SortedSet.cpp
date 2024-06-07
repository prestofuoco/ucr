#include <iostream>
#include "SortedSet.h"

using namespace std;

SortedSet::SortedSet() : IntList() { }

SortedSet::SortedSet(const SortedSet &set) : IntList(set) { }

SortedSet::SortedSet(const IntList &list) : IntList(list) { 
    selection_sort();
    remove_duplicates();
}

SortedSet::~SortedSet() { }

bool SortedSet::in(int value) const {
    IntNode *temp = head;
    while (temp != nullptr) {
        if (temp->value == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

SortedSet SortedSet::operator|(const SortedSet &set) const {
    SortedSet newSet;
    IntNode *temp = head;
    while (temp != nullptr) {
        newSet.push_back(temp->value);
        temp = temp->next;
    }
    temp = set.head;
    while (temp != nullptr) {
        if (!newSet.in(temp->value)) {
            newSet.push_back(temp->value);
        }
        temp = temp->next;
    }
    return newSet;
}

SortedSet SortedSet::operator&(const SortedSet &set) const {
    SortedSet newSet;
    if (empty() || set.empty()) {
        return newSet;
    }
    IntNode *temp = head;
    while (temp != nullptr) {
        if (set.in(temp->value)) {
            newSet.push_back(temp->value);
        }
        temp = temp->next;
    }
    return newSet;
}

void SortedSet::add(int value) {
    if (!in(value)) {
        push_back(value);
        selection_sort();
    }
}

void SortedSet::push_front(int value) {
    IntNode *temp = new IntNode(value);
    if (empty()) {
        head = temp;
        tail = temp;
    } 
    else {
        temp->next = head;
        head = temp;
    }
    selection_sort();
}

void SortedSet::push_back(int value) {
    IntNode *temp = new IntNode(value);
    if (empty()) {
        head = temp;
        tail = temp;
    } 
    else {
        tail->next = temp;
        tail = temp;
    }
    selection_sort();
}

void SortedSet::insert_ordered(int value) {
    IntNode *temp = new IntNode(value);
    if (head == nullptr || value < head->value) {
        temp->next = head;
        head = temp;
    } else {
        IntNode *current = head;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }
    remove_duplicates();
}

SortedSet & SortedSet::operator|=(const SortedSet &set) {
    *this = *this | set;
    return *this;
}

SortedSet & SortedSet::operator&=(const SortedSet &set) {
    if (empty() || set.empty()) {
        clear();
        return *this;
    }
    *this = *this & set;
    return *this;
}