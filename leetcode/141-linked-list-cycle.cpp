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
  /** The solution for this is very similar to the
   * 876-middle-of-the-linked-list.cpp but we start from the second iteration,
   * meaning we start from head->next instead of head, or else the if condition
   * inside the while loop would always return true, because slow and fast would
   * be head and then would fail.
   *
   * I read that one could not simply solve this issue if they never heard of
   * the Floyd's cycle-finding algorithm aka Tortoise and the hare algorithm.
   * Because the possibilities of finding this on your own would be almost 0.
   *
   * For a better understanding see 876-middle-of-the-linked-list.pdf it's
   * mostly the same algorithm, except that now we want to see if slow ever
   * reaches fast, slow would eventually catchup with fast if there's a cycle.
   */
  bool hasCycle(ListNode *head) {
    if (!head || !head->next) {
      return false;
    }

    ListNode *slow = head->next;
    ListNode *fast = head->next->next;

    while (slow != fast && fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow == fast;
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

  bool cycle = solution.hasCycle(&zero);

  if (cycle) {
    cout << "Has a cycle" << endl;
  } else {
    cout << "Cycle not found" << endl;
  }
}
