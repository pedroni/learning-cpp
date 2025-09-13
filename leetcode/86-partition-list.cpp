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

    ListNode *temp = head;

    ListNode *smallPrev = new ListNode();
    ListNode *smallHead = smallPrev;

    ListNode *bigPrev = new ListNode();
    ListNode *bigHead = bigPrev;

    while (temp) {
      // such a chame, i had to clone the node... how can i achieve without a
      // copy? is it possible
      ListNode *current = new ListNode(temp->val) if (temp->val < x) {
        smallPrev->next = current;
        smallPrev = current;
      }
      else {
        bigPrev->next = current;
        bigPrev = current;
      }

      ListNode *toDelete = temp; // memory clean up
      temp = temp->next;
      delete toDelete; // memory clean up
    }

    smallHead = smallHead->next;
    bigHead = bigHead->next;

    smallPrev->next = bigHead;

    if (smallHead == NULL) {
      return bigHead;
    }
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

  // printList(head);
  // ListNode *result = solution.partition(solution.head, 5);
  // printList(result);

  ListNode *head = solution.append(1);
  solution.append(1);

  printList(head);
  ListNode *result = solution.partition(solution.head, 0);
  printList(result);

  cout << "------------------------------" << endl;
  cout << "Are you test reading this correctly?" << endl;
}
