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
      cout << "here" << endl;
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

  int getDecimalValue(ListNode *head) { return 0; };

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

  int finalResult = 15;

  solution.append(1);
  solution.append(1);
  solution.append(1);
  solution.append(1);

  int decimalValue = solution.getDecimalValue(solution.head);

  solution.printList();

  cout << "Expected: " << finalResult << endl;
  cout << "Got: " << decimalValue << endl;
  cout << "Test " << (decimalValue == finalResult ? "✅ Passed" : "❌ Failed")
       << endl;
}
