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

  // the edge cases are killing me.
  // input: [1,1] x: 0 output: [1,1]
  // input: [1,1] x: 2 output: [1,1]
  ListNode *partition(ListNode *head, int x) {
    if (head == NULL) {
      return head;
    }

    if (head->next == NULL) {
      // if only one item always return it
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
          smallTail = smallHead;
        }

        smallTail->next = temp->next;
        smallTail = temp->next;

        temp->next = tempNext;
        smallTail->next = NULL;

        // continue iteration so that we don't change `temp` this is necessary
        // so we can continue looking forward. without skipping the current item
        // the current item in this case is always bigger than the next value.
        //
        // say we had: x = 5, temp = 10
        // temp->next = 2 // this needs to become 1, bcs its lower than 5
        // temp->next->next = 1
        //
        // and on the following iteration we will have
        // temp = 10
        // temp->next = 1
        // which will allow us to work on the 1 item and will give the ability
        // to remove the next pointer of 10. if we were to change temp to
        // temp->next then we'd skip working on 10, and there could be a skipped
        // value, this is better seen in the whiteboard.
        continue;
      } else {
        if (bigHead == NULL) {
          bigHead = temp->next;
        }
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

    if (smallTail == NULL) {
      // when there's no small tail it means all items were bigger than x and we
      // do not have a small list
      return bigHead;
    }

    // merge both partitions, the small at the start and the big at the end!
    smallTail->next = bigHead;

    // then we return the smallHead which is the newest head that contains
    return smallHead;
  }
};

int main() {
  Solution solution;

  // ListNode *head = solution.append(3);
  // solution.append(8);
  // solution.append(5);
  // solution.append(10);
  // solution.append(2);
  // solution.append(1);

  ListNode *head = solution.append(0);
  solution.append(1);
  // solution.append(2);
  // solution.append(5);
  // solution.append(2);

  printList(head);

  ListNode *result = solution.partition(solution.head, 2);

  printList(result);

  int expectedResult = 3;

  cout << "Expected: " << expectedResult << endl;
  if (result != NULL) {
    cout << "Got: " << result->val << endl;
    cout << "Test "
         << (result->val == expectedResult ? "✅ Passed" : "❌ Failed") << endl;
  } else {
    cout << "Result is NULL" << endl;
  }
}
