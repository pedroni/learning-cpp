#include <cstddef>
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
    if (head == NULL) {
      return head;
    }

    ListNode *temp = head;

    ListNode *smallHead = temp->val < x ? temp : NULL;
    ListNode *smallTail = temp->val < x ? temp : NULL;

    ListNode *bigHead = temp->val >= x ? temp : NULL;

    ListNode *tempNext = temp->next;

    while (temp->next) {
      tempNext = temp->next->next;
      if (temp->next->val < x) {
        if (smallHead == NULL) {
          smallHead = temp->next;
          smallHead->next = NULL;
          smallTail = smallHead;

          continue;
        }
        // smallTail->next = temp->next;
        //
        // temp->next = NULL;
        // smallTail = temp->next;
        //
        temp->next = tempNext;

      } else {
        if (bigHead == NULL) {
          bigHead = temp->next;
        }
      }

      if (temp->next->next == NULL) {
        //  how do i remove the last?
        cout << "jump is null" << temp->next->val << endl;
      }

      temp = temp->next;
    }

    cout << "--------------------" << endl;
    int smallHeadValue = smallHead != NULL ? smallHead->val : -1;
    cout << "small head: " << smallHeadValue << endl;

    int smallTailValue = smallTail != NULL ? smallTail->val : -1;
    cout << "small tail: " << smallTailValue << endl;

    int bigHeadValue = bigHead != NULL ? bigHead->val : -1;
    cout << "big head: " << bigHeadValue << endl;

    int headValue = head != NULL ? head->val : -1;
    cout << "head: " << headValue << endl;

    cout << "--------------------" << endl;
    return bigHead;
  }
};

void printList(ListNode *head) {
  ListNode *temp = head;
  while (temp) {
    cout << temp->val;

    if (temp->next) {
      cout << " | ";
    }

    temp = temp->next;
  }
  cout << endl;
}

int main() {
  Solution solution;

  ListNode *head = solution.append(3);
  solution.append(8);
  solution.append(5);
  solution.append(10);
  solution.append(2);
  solution.append(1);

  printList(head);

  ListNode *result = solution.partition(solution.head, 5);

  printList(result);

  int expectedResult = 3;

  cout << "Expected: " << expectedResult << endl;
  cout << "Got: " << result->val << endl;
  cout << "Test " << (result->val == expectedResult ? "✅ Passed" : "❌ Failed")
       << endl;
}
