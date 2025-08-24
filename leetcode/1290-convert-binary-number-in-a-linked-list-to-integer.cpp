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

  int getDecimalValue(ListNode *head) {

    // first I will try with length. That will be the easiest one. I can use kth
    // strategy

    int length = 0;
    ListNode *temp = head;

    while (temp != NULL) {
      length++;
      temp = temp->next;
    }

    // the first item is the biggest value, the last item is 1
    // e.g. binary:  1 1 1 1
    //      decimal: 8+4+2+1=15
    //      k pos:   3 2 1 0
    // to find the decimal value of a position you use k^2, where k is the index
    // position backwards of the items

    int decimalValue = 0;
    int i = 1;
    int k = length;

    temp = head;

    while (temp != NULL) {
      k = length - i;
      cout << k << endl;
      decimalValue += temp->val * pow(2, k);
      temp = temp->next;
      i++;
    }

    return decimalValue;
  };

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
