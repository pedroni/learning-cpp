
#include <cmath>
#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;

  ListNode() : val(0), next(NULL) {}
  ListNode(int x) : val(x), next(NULL) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {

public:
  ListNode *head;
  Solution() { this->head = NULL; }

  ListNode *append(int value) {

    ListNode *newNode = new ListNode(value);
    if (this->head == NULL) {
      head = newNode;
    } else {
      ListNode *currentNode = head;
      while (currentNode->next != NULL) {
        currentNode = currentNode->next;
      }
      currentNode->next = newNode;
    }

    return newNode;
  }

  ListNode *partition(ListNode *head, int x) {
    ListNode *smallHead = new ListNode();
    return smallHead;
  }

  void printList() {
    ListNode *temp = this->head;
    while (temp) {
      cout << temp->val;

      if (temp->next) {
        cout << " | ";
      }

      temp = temp->next;
    }
    cout << endl;
  }
};

int main() {
  Solution solution;

  solution.append(3);
  solution.append(8);
  solution.append(5);
  solution.append(10);
  solution.append(2);
  solution.append(1);

  ListNode *result = solution.partition(solution.head, 5);

  solution.printList();

  int expectedResult = 3;

  cout << "Expected: " << expectedResult << endl;
  cout << "Got: " << result->val << endl;
  cout << "Test " << (result->val == expectedResult ? "✅ Passed" : "❌ Failed")
       << endl;
}
