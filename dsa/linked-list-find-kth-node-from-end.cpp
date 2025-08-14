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

public:
  LinkedList(int value) {
    Node *newNode = new Node(value);
    head = newNode;
    tail = newNode;
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

  Node *getTail() { return tail; }

  void makeEmpty() {
    Node *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
    tail = NULL;
  }

  void append(int value) {
    Node *newNode = new Node(value);
    if (head == NULL) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
  }

  //   +======================================================+
  //   |                 WRITE YOUR CODE HERE                 |
  //   | Description:                                         |
  //   | - Find the k-th node from the end of the list        |
  //   | - Return type: Node*                                 |
  //   |                                                      |
  //   | Tips:                                                |
  //   | - Use two pointers: 'slow' and 'fast'                |
  //   | - Move 'fast' k nodes ahead first                    |
  //   | - If 'fast' reaches null, k is too large             |
  //   | - Then move both 'slow' and 'fast' until end         |
  //   | - Return 'slow' as the k-th node from the end        |
  //   +======================================================+

  // if i knew the length this would be easier, lets try to solv with the
  // length first then we will try to solve with the Floyd's algorithm
  Node *findKthFromEnd(int k) {
    int length = 0;

    Node *temp = this->head;

    while (temp) {
      length++;
      temp = temp->next;
    }

    if (k > length) {
      return NULL;
    }

    if (k == 0) {
      return this->tail;
    }

    if (k == length) {
      return this->head;
    }

    // 1 -> length-1
    // 2 -> length-2
    // 3 -> length-3
    // 4 -> length-4
    // index = length-(k);

    int expectedIndex = length - (k);
    cout << "expectedIndex: " << expectedIndex << endl;
    cout << "length: " << length << endl;
    int i = 0;

    temp = this->head;
    while (temp) {
      if (i == expectedIndex) {
        break;
      }
      i++;
      temp = temp->next;
    }

    return temp;
  }
};

// Function to convert NULL to string for easy comparison
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
  // Test: EmptyList
  {
    cout << "\n------ LinkedList Test: EmptyList ------\n";

    LinkedList list(1);
    list.makeEmpty();

    list.printList();

    Node *result = list.findKthFromEnd(1);

    cout << "f(" << 1 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result == NULL);
  }

  // Test: KGreaterThanListLength
  {
    cout << "\n------ LinkedList Test: KGreaterThanListLength ------\n";

    LinkedList list(1);
    list.append(2);

    list.printList();

    Node *result = list.findKthFromEnd(3);

    cout << "f(" << 3 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result == NULL);
  }

  // Test: KEqualsListLength
  {
    cout << "\n------ LinkedList Test: KEqualsListLength ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);

    list.printList();

    Node *result = list.findKthFromEnd(3);

    cout << "f(" << 3 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 1);
  }

  {
    cout << "\n------ LinkedList Test: KSecondFromEnd ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    Node *result = list.findKthFromEnd(2);

    cout << "f(" << 2 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 4);
  }

  {
    cout << "\n------ LinkedList Test: KthLastItem ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    Node *result = list.findKthFromEnd(0);

    cout << "f(" << 0 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 5);
  }

  {
    cout << "\n------ LinkedList Test: KthFirstItem ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    Node *result = list.findKthFromEnd(5);

    cout << "f(" << 5 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 1);
  }
}
