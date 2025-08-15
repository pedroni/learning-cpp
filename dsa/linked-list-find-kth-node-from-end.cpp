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

  // In my previous commit 4d7110c69edf45ddd75382b167933d9f2804764f
  // I used an approach with two while loops to come with the solution. For that
  // I didn't use an whiteboard. This time I used Floyd's algorithm (Tortoise
  // and Hare algorithm) that was suggested to be used by Scott Barret on the
  // Udemy course.
  Node *findKthFromEnd(int k) {
    if (k == 0) {
      return NULL;
    }

    if (k == 1) {
      return this->tail;
    }

    if (this->head == NULL) {
      return NULL;
    }

    Node *slow = this->head;
    Node *fast = this->head;

    int i = 0;
    int length = 1;

    while (slow != NULL) {
      slow = slow->next;
      i += 1;

      // this allow us to continue couting the length until we have items to
      // iterate through on the linked list. Once we've finished counting we can
      // start checking for the k node in the slow variable.
      if (fast->next != NULL && fast->next->next != NULL) {
        // eventually fast will also be null
        fast = fast->next->next;
        length += 2;
      } else {
        if (k > length) {
          return NULL;
        }

        if (k == length - i) {
          break;
        }

        // if k matches the length it wants the first item
        if (k == length) {
          slow = this->head;
          break;
        }

        // if we didnt find it yet, it was too soon to find it, for example: As
        // an argument k=4 this means we want the second item from the start of
        // the list: 1,2,3,4,5 4, the result would be 2 but at that moment
        // length was not fully computed, so we need to restart the loop.
        //
        // I didn't spot this case until testing with random lists. I also
        // didn't spot this case on the whiteboard. I'm proud of myself.
        i = 0;
        slow = this->head;
      }
    }

    return slow;
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
  {
    cout << "\n------ LinkedList Test: EmptyList ------\n";

    LinkedList list(1);
    list.makeEmpty();

    list.printList();

    Node *result = list.findKthFromEnd(1);

    cout << "f(" << 1 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result == NULL);
  }

  {
    cout << "\n------ LinkedList Test: KGreaterThanListLength ------\n";

    LinkedList list(1);
    list.append(2);

    list.printList();

    Node *result = list.findKthFromEnd(3);

    cout << "f(" << 3 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result == NULL);
  }

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
    cout << "\n------ LinkedList Test: KSecondFromStart ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    int k = 4;
    Node *result = list.findKthFromEnd(k);

    cout << "f(" << k << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 2);
  }
  {
    cout << "\n------ LinkedList Test: KSecondFromEnd ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    int k = 2;
    Node *result = list.findKthFromEnd(k);

    cout << "f(" << k << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result && result->value == 4);
  }

  {
    cout << "\n------ LinkedList Test: Kth0NotSupportedStartsFrom1 ------\n";

    LinkedList list(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.printList();

    Node *result = list.findKthFromEnd(0);

    cout << "f(" << 0 << "): kth from end: " << ptrToNum(result) << endl;

    checkTestResult(result == NULL);
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
