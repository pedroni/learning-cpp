#include <cstddef>
#include <iostream>
#include <stdexcept>

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

    cout << "(" << this->length << "): ";
    while (temp != NULL) {
      cout << temp->value;
      temp = temp->next;
      if (temp) {
        cout << " | ";
      }
    }

    cout << endl;
    for (int i = 1; i < (this->length + 2) * 3; i++) {
      cout << "-";
    }
    cout << endl;
  }

  void printHead() { cout << "Head: " << this->head->value << endl; }
  void printTail() { cout << "Tail: " << this->tail->value << endl; }
  void printLength() { cout << "Length: " << this->length << endl; }

  void prepend(int value) {
    Node *temp = new Node(value);

    if (this->tail == NULL) {
      this->tail = temp;
    }

    temp->next = this->head;
    this->head = temp;
    this->length++;
  }

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

  void deleteFirst() {
    if (this->head == NULL) {
      return;
    }

    Node *next = this->head->next;
    if (next == NULL) {
      delete this->head;
      this->head = this->tail = NULL;
      this->length = 0;
      return;
    }

    delete this->head;
    this->head = next;
    this->length--;
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

    while (current->next) {
      if (current->next == this->tail) {
        // found the item that hold tail as last, the penultimate. the second to
        // last, from this moment we no longer need to continue iterating
        break;
      }

      current = current->next;
    }

    // free up the memory of tail, we no longer use it
    delete this->tail;

    // set next as NULL, we no longer use it, the next in this case was the tail
    current->next = NULL;

    // make the tail be the current item
    this->tail = current;

    // update the length
    this->length--;
  }

  Node *get(int index) {
    if (index < 0 || index > this->length - 1) {
      return NULL;
    }

    int currentIndex = 0;
    Node *temp = this->head;
    while (temp) {
      if (currentIndex == index) {
        return temp;
      }
      temp = temp->next;

      currentIndex++;
    }

    return NULL;
  };

  void set(int index, int value) {
    if (index < 0 || index > this->length - 1) {
      throw out_of_range("Index out of bounds");
    }

    Node *temp = this->get(index);
    temp->value = value;
  }

  void insert(int index, int value) {
    if (index < 0 || index > this->length) {
      throw out_of_range("Index out of bounds");
    }

    if (index == 0) {
      this->prepend(value);
      return;
    }

    if (index == this->length) {
      this->append(value);
      return;
    }

    Node *prev = this->get(index - 1);
    Node *current = prev->next;

    Node *newNode = new Node(value);
    prev->next = newNode;
    newNode->next = current;

    this->length++;
  }

  void deleteNode(int index) {
    if (index < 0 || index > this->length - 1) {
      throw out_of_range("Index out of bounds");
    }

    if (index == 0) {
      this->deleteFirst();
      return;
    }

    if (index == this->length - 1) {
      this->deleteLast();
      return;
    }

    Node *prev = this->get(index - 1);

    Node *current = prev->next;
    prev->next = current->next;

    delete current;

    this->length--;
  }

  int getLength() { return this->length; }

  void reverse() {
    if (this->length <= 1) {
      return;
    }

    cout << "----------" << endl;
    cout << "start reverse" << endl;

    Node *current = this->head;

    // swap head and tail
    this->head = this->tail;
    this->tail = current;

    Node *before = NULL;
    Node *after = current->next;

    // visual algorithmic, imagine a linked list: 0,1,2,3
    //
    // this is how we start
    // before  current after
    // NULL     0 ->    1 -> 2 -> 3
    //
    // after the first iteration this is what we have, `[]` represents a broken
    // linked list, the 0 no longer points to the next item properly, instead it
    // points to null
    //
    //      before  current  after
    // NULL <- 0 []   1  ->  2  -> 3
    //
    // on the second iteration we make 1 has the next pointer pointing to 0,
    // which breaks the path to 2. 1 is no longer connected to 2
    //
    //            before  current  after
    // NULL <- 0 <- 1   []  2  -> 3
    //
    // with these 3 helper variables: before, current and after
    // on every iteration permits us to continue iterating through even with a
    // broken path
    //
    // at the first iteration, we set the next pointer of 0 to NULL
    // instead of "1", in this example 1 was previously the next item, now we
    // set the before which is NULL to the current.
    //
    // at the second iteration, we set the next pointer of 1 to 0, instead of
    // the "2" causing this to break the loop if we were using a while loop, in
    // this case we continue iterating because we have the length information,
    // and for each iteration we set the current pointer that we're working on
    // to keep repeating these steps.
    for (int i = 0; i < this->length; i++) {
      // update after pointer, to the next of the current item
      // we will soon lose the next current item, because it will be set to the
      // before item
      after = current->next;

      // mark the current next item to be the before one.
      // in the first iteration all we do is set this to null
      // but in future occurences the next will be the before item
      current->next = before;

      // we've finished working on current, now current becomes the
      // before item and we will start working on the after item
      before = current;

      // start working on the after item, mark current as after
      current = after;
    }
    cout << "----------" << endl;
  }
};

int main() {
  LinkedList *myLinkedList = new LinkedList(0);

  myLinkedList->append(1);
  myLinkedList->append(2);
  myLinkedList->append(3);
  myLinkedList->append(4);

  myLinkedList->printList();

  cout << "Reverse it!" << endl;
  myLinkedList->reverse();

  myLinkedList->printList();

  cout << "Linked List :)" << endl;
}
