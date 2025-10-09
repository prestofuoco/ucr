#include "IntList.h"
#include <ostream>
using namespace std;

IntList::IntList() : head(nullptr) { }

void IntList::push_front(int val) {
   if (head == nullptr) {
      head = new IntNode(val);
   } 
   else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

bool IntList::exists(int val) const {
   return exists(head, val);
}

bool IntList::exists(IntNode *curr, int val) const {
   if (curr == nullptr) {
      return false;
   } 
   else if (curr->value == val) {
      return true;
   }
   return exists(curr->next, val);
}

ostream & operator<<(ostream &out, const IntList &list) {
   return out << list.head;
}

ostream & operator<<(ostream &out, IntNode *curr) {
   if (curr == nullptr) {
      return out;
   } 
   out << curr->value;
   if (curr->next) {
      out << ' ';
   }
   return operator<<(out, curr->next);
}