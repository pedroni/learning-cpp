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

  ListNode *partition(ListNode *head, int x) { return head; }
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

  // ListNode *head = solution.append(0);
  // solution.append(1);

  // printList(head);
  // ListNode *result = solution.partition(solution.head, 2);
  // printList(result);

  cout << "------------------------------" << endl;
  cout << "Are you reading this correctly?" << endl;
}
