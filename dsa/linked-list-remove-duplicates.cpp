#include <cstddef>
#include <iostream>
#include <sstream>

using namespace std;

class Node {
public:
  int value;
  Node *next;
  Node(int value) {
    this->value = value;
    next = NULL;
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
    head = newNode;
    tail = newNode;
    length = 1;
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
    if (temp == NULL) {
      cout << "empty";
    } else {
      while (temp != NULL) {
        cout << temp->value;
        temp = temp->next;
        if (temp != NULL) {
          cout << " -> ";
        }
      }
    }
    cout << endl;
  }

  Node *getHead() { return head; }

  int getLength() { return length; }

  void makeEmpty() {
    Node *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
    length = 0;
  }

  void append(int value) {
    Node *newNode = new Node(value);
    if (head == NULL) {
      head = newNode;
    } else {
      Node *currentNode = head;
      while (currentNode->next != NULL) {
        currentNode = currentNode->next;
      }
      currentNode->next = newNode;
    }
    length++;
  }

  //   +======================================================+
  //   |                 WRITE YOUR CODE HERE                 |
  //   | Description:                                         |
  //   | - Remove duplicate nodes from the list               |
  //   | - Return type: void                                  |
  //   |                                                      |
  //   | Tips:                                                |
  //   | - Use two pointers: 'current' and 'runner'           |
  //   | - 'current' scans each node                          |
  //   | - 'runner' checks for duplicates ahead               |
  //   | - If duplicate found, delete it                      |
  //   | - Update 'next' pointers and reduce length           |
  //   | - No return value, list updated in-place             |
  //   +======================================================+
  //

  void removeDuplicates() {
    Node *outer = this->head;

    while (outer != NULL) {

      Node *inner = this->head;
      Node *previousInner = NULL;

      int count = 0;

      while (inner != NULL) {
        if (outer->value == inner->value) {
          count++;
        }

        if (count >= 2 && previousInner != NULL) {
          previousInner->next = inner->next;
          delete inner;
          this->length--;
          count = 0;
          // could this be improved? I'm restarting to the begginning of the
          // loop
          inner = this->head;
          previousInner = NULL;
        } else {
          previousInner = inner;
          inner = inner->next;
        }
      }

      outer = outer->next;
    }

    cout << "ended" << endl;
  }
};

string ptrToNum(Node *ptr) {
  if (ptr == NULL) {
    return "NULL";
  } else {
    ostringstream oss;
    oss << ptr->value;
    return oss.str();
  }
}

// Helper function to check test result
void checkTestResult(bool condition) {
  cout << (condition ? "✅ PASS" : "❌ FAIL") << endl;
}

int main() {
  {
    cout << "\n------ Test: RemoveDuplicatesEmptyList ------\n";

    LinkedList list(1);
    list.makeEmpty();

    cout << "BEFORE:    ";
    list.printList();

    list.removeDuplicates();

    cout << "AFTER:     ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head == NULL);
  }

  {
    cout << "\n------ Test: RemoveDuplicatesSingleElement ------\n";

    LinkedList list(1);

    cout << "BEFORE:    ";
    list.printList();

    list.removeDuplicates();

    cout << "AFTER:     ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head && head->value == 1);
  }

  {
    cout << "\n------ Test: RemoveDuplicates ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(3);
    list.append(4);
    list.append(2);
    list.append(1);
    list.append(3);

    cout << "BEFORE:    ";
    list.printList();

    list.removeDuplicates();

    cout << "AFTER:     ";
    list.printList();

    checkTestResult(list.getLength() == 4);
  }

  {
    cout << "\n------ Test: RemoveDuplicatesNoDuplicates ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);

    cout << "BEFORE:    ";
    list.printList();

    list.removeDuplicates();

    cout << "AFTER:     ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head && head->value == 1);
  }

  {
    cout << "\n------ Test: RemoveDuplicatesHasDuplicates ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(2);
    list.append(3);

    cout << "BEFORE:    ";
    list.printList();

    list.removeDuplicates();

    cout << "AFTER:     ";
    list.printList();

    // Check for duplicates
    Node *current = list.getHead();
    bool noDuplicates = true;

    while (current && current->next) {
      if (current->value == current->next->value) {
        noDuplicates = false;
        break;
      }
      current = current->next;
    }

    checkTestResult(noDuplicates);
  }
}
