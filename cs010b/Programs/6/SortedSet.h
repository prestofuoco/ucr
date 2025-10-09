#ifndef SORTEDSET_H
#define SORTEDSET_H

#include <iostream>
#include "IntList.h"

using namespace std;

class SortedSet : public IntList {
    public:
        SortedSet();
        SortedSet(const SortedSet &);
        SortedSet(const IntList &);
        ~SortedSet();
        bool in(int) const;
        SortedSet operator|(const SortedSet &) const;
        SortedSet operator&(const SortedSet &) const;
        void add(int);
        void push_front(int) override;
        void push_back(int) override;
        void insert_ordered(int) override;
        SortedSet & operator|= (const SortedSet &);
        SortedSet & operator&= (const SortedSet &);
};

#endif