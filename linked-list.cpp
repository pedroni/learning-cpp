#include <cstddef>
#include <iostream>

using namespace std;

class Node {
public:
  int value;
  Node *next;

  Node(int value) {
    this->value = value;
    this->next = NULL;
  }
};

class LinkedList {
private:
  Node *head;
  Node *tail;
  int length;

public:
  LinkedList(int value) {
    Node *newNode = new Node(value);

    this->head = newNode;
    this->tail = newNode;
    this->length = 1;
  }

  ~LinkedList() {
    Node *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
  }

  void printList() {
    Node *temp = head;

    cout << endl;
    for (int i = 1; i < this->length * 3; i++) {
      cout << "-";
    }
    cout << endl;

    while (temp != NULL) {
      cout << temp->value;
      temp = temp->next;
      if (temp) {
        cout << " | ";
      }
    }

    cout << endl;
    for (int i = 1; i < this->length * 3; i++) {
      cout << "-";
    }

    cout << endl;
  }

  void printHead() { cout << "Head: " << this->head->value << endl; }
  void printTail() { cout << "Tail: " << this->tail->value << endl; }
  void printLength() { cout << "Length: " << this->length << endl; }

  void append(int value) {
    Node *newNode = new Node(value);

    if (this->head == NULL || this->tail == NULL || this->length == 0) {
      this->head = newNode;
      this->tail = newNode;
    } else {
      this->tail->next = newNode;
      this->tail = newNode;
    }

    this->length++;
  }

  void deleteLast() {
    if (this->length == 0) {
      // list is empty do nothing;
      cout << "list is empty" << endl;
      return;
    }

    if (this->head == this->tail) {
      cout << "list has one item" << endl;
      // only a single item
      delete this->head;
      this->head = this->tail = NULL;
      this->length = 0;
      return;
    }

    Node *current = this->head;

    while (current) {
      cout << "iterating: " << current->value << endl;
      if (current->next == this->tail) {
        cout << "found tail: " << this->tail->value;
        // found the tail at next, from this moment we start working on setting
        // the current item in the iteration as the tail
        Node *tailToDelete = current->next;

        this->tail = current;

        // set next to NULL, which is the definition of what a tail is
        this->tail->next = NULL;

        // free the memory to avoid memory leak
        delete tailToDelete;

        this->length--;
        break;
      } else {
        current = current->next;
      }
    }
  }
};

int main() {

  LinkedList *myLinkedList = new LinkedList(4);
  myLinkedList->append(3);

  myLinkedList->deleteLast();

  myLinkedList->printList();

  cout << "Linked List :)" << endl;
}
