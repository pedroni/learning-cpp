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
  //   | - Partition list around value x                      |
  //   | - Return type: void                                  |
  //   |                                                      |
  //   | Tips:                                                |
  //   | - Create two dummy nodes for two new lists           |
  //   | - One list for nodes less than x                     |
  //   | - Another list for nodes greater or equal to x       |
  //   | - Loop through original list                         |
  //   | - Assign nodes to new lists based on value           |
  //   | - Merge the two new lists                            |
  //   | - Update the original list's head                    |
  //   +======================================================+
  void partitionList(int x) {
    if (this->head == NULL) {
      return;
    }
    if (this->head->next == NULL) {
      return;
    }

    Node smallHead = Node(0);
    Node bigHead = Node(0);

    Node *smallPrev = &smallHead;
    Node *bigPrev = &bigHead;

    Node *temp = this->head;
    while (temp) {
      if (temp->value < x) {
        smallPrev->next = temp;
        smallPrev = temp;
      } else {
        bigPrev->next = temp;
        bigPrev = temp;
      }

      temp = temp->next;
    }

    bigPrev->next = NULL;
    smallPrev->next = bigHead.next;

    this->head = smallHead.next;
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
  // Test: PartitionEmptyList
  {
    cout << "\n------ Test: PartitionEmptyList ------\n";

    LinkedList list(1);
    list.makeEmpty();

    cout << "BEFORE:    ";
    list.printList();

    cout << "partitionList(3)\n";
    cout << "EXPECTED:  empty\n";

    list.partitionList(3);

    cout << "ACTUAL:    ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head == NULL);
  }

  // Test: PartitionSingleElement
  {
    cout << "\n------ Test: PartitionSingleElement ------\n";

    LinkedList list(1);

    cout << "BEFORE:    ";
    list.printList();

    cout << "partitionList(3)\n";
    cout << "EXPECTED:  1\n";

    list.partitionList(3);

    cout << "ACTUAL:    ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head && head->value == 1);
  }

  // Test: PartitionAllLessThanX
  {
    cout << "\n------ Test: PartitionAllLessThanX ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);

    cout << "BEFORE:    ";
    list.printList();

    cout << "partitionList(4)\n";
    cout << "EXPECTED:  1 -> 2 -> 3\n";

    list.partitionList(4);

    cout << "ACTUAL:    ";
    list.printList();

    Node *head = list.getHead();
    checkTestResult(head && head->value == 1);
  }

  // Test: PartitionMixedNumbers
  {
    cout << "\n------ Test: PartitionMixedNumbers ------\n";

    LinkedList list(1);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(5);
    list.append(2);

    cout << "BEFORE:    ";
    list.printList();

    cout << "partitionList(3)\n";
    cout << "EXPECTED:  1 -> 2 -> 2 -> 4 -> 3 -> 5\n";

    list.partitionList(3);

    cout << "ACTUAL:    ";
    list.printList();

    // Check if the list is partitioned correctly
    Node *current = list.getHead();
    bool isPartitioned = true;
    bool crossedPartitionValue = false;

    while (current && current->next) {
      if (current->value >= 3) {
        crossedPartitionValue = true;
      }
      if (crossedPartitionValue && current->value < 3) {
        isPartitioned = false;
        break;
      }
      current = current->next;
    }

    checkTestResult(isPartitioned);
  }
}
