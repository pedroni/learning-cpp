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
  /**
   * Works by having two tracking variables. Slow and fast. Slow will walk one
   * by one from head. And fast will walk two by two from head. Meaning it will
   * go twice as fast as slow. It will only iterate when slow and fast are not
   * NULL. Once it's NULL we know slow has reached the middle. Fast will be NULL
   * once it goes over the tail node, the tail has next set to NULL, always.
   */
  ListNode *middleNode(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    if (head->next == NULL) {
      return head;
    }

    while (slow && fast) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow;
  };

  /**
   * This was the first implementation I did, without help. Though it is not the
   * most optimized, it did the job. It finds the middle node by first finding
   * the length of the linked list using a loop. Then it calculates the middle
   * of the linked list. After finding the middle it loops through the linked
   * list again until it finds the middle item. Once it finds it we break out of
   * the loop and return it. The problem here is that we use two loops, instead
   * of one.
   */
  ListNode *middleNodeIterating(ListNode *head) {
    int length = 0;
    ListNode *temp = head;

    while (temp) {
      length++;
      temp = temp->next;
    }

    int middle = floor(length / 2);

    int current = 0;

    temp = head;
    while (temp) {
      if (current == middle) {
        break;
      }

      current++;
      temp = temp->next;
    }

    return temp;
  };
};

int main() {
  ListNode zero(0);
  ListNode one(1);
  ListNode two(2);
  ListNode three(3);
  ListNode four(4);
  ListNode five(5);

  zero.next = &one;
  one.next = &two;
  two.next = &three;
  three.next = &four;
  four.next = &five;

  Solution solution;

  ListNode *middle = solution.middleNode(&zero);

  if (middle) {
    cout << "Found middle value: " << middle->val << endl;
  } else {
    cout << "Middle not found" << endl;
  }
}
