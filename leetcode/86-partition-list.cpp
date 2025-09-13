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

  ListNode *partition(ListNode *head, int x) {
    if (head == NULL) {
      return head;
    }
    if (head->next == NULL) {
      return head;
    }

    ListNode smallHead = ListNode(0);
    ListNode bigHead = ListNode(0);

    ListNode *smallPrev = &smallHead;
    ListNode *bigPrev = &bigHead;

    ListNode *temp = head;

    while (temp) {
      if (temp->val < x) {
        smallPrev->next = temp;
        smallPrev = temp;
      } else {
        bigPrev->next = temp;
        bigPrev = temp;
      }

      temp = temp->next;
    }

    // end the second list. end the big list. this is important we dont want to
    // continue going, this is the end of the list.
    bigPrev->next = NULL;

    // connects the head of big with tail of small
    smallPrev->next =
        bigHead.next; // use big head next, because big head is a dummy node

    return smallHead.next;
  }
};

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

  // ListNode *head = solution.append(1);
  // solution.append(1);

  // printList(head);
  // ListNode *result = solution.partition(solution.head, 0);
  // printList(result);

  cout << "------------------------------" << endl;
  cout << "Are you reading things correctly?" << endl;

  // doesn't look like i did. even the warning was wrong. I had this warning
  // because i often fucked up with the test code, swaping variables for
  // example, i'd `cout << "small: " < big`, so i read on the terminal that
  // small was a value, but actually i was printing big...
}
