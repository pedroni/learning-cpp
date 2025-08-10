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
  ListNode *middleNode(ListNode *head) {
    int length = 0;
    ListNode *temp = head;
    while (temp) {
      length++;
      temp = temp->next;
    }

    cout << "length is " << length << endl;

    int middle = floor(length / 2);

    int current = 0;
    temp = head;
    while (temp) {
      cout << "entering " << temp->val << endl;

      if (current == middle) {
        break;
      }

      current++;
      temp = temp->next;
    }
    cout << "middle is at " << middle << endl;

    if (temp) {
      cout << "middle has the value " << temp->val << endl;
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

  solution.middleNode(NULL);
}
