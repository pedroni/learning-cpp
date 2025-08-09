#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

template <class T>
struct Node {
  T value;
  Node<T> *left;
  Node<T> *right;

  Node() : value(), left(NULL), right(NULL) {}
};

template <class T>
ostream &operator<<(ostream &os, const Node<T> &node) {
  os << node.value;
  return os;
}

template <class T>
vector<Node<T> *> breadthFirstWalk(Node<T> *node) {

  vector<Node<T> *> results;

  if (node == NULL) {
    return results;
  }

  Node<T> *current;

  queue<Node<T> *> inProgress;

  inProgress.push(node);

  while (!inProgress.empty()) {
    current = inProgress.front();
    inProgress.pop();

    if (current->left != NULL) {
      inProgress.push(current->left);
    }

    if (current->right != NULL) {
      inProgress.push(current->right);
    }

    results.push_back(current);
  }

  return results;
};

/**
 * This function will run until there are values on the stack.
 * To walk through the binary tree we first start from the root,
 * the root will be our first value in the stack, the condition
 * that we use to check if we still can "walk" on our binary tree
 * is checking whether there are any value in the stack.
 *
 * When we start walking on the binary tree we first remove the most
 * recent node that was added to the stack. In JS we can do `.pop`
 * which will remove the most recent item from the array and return it
 * at the same time.
 *
 * Once we have the current value on the stack we check the left and
 * right values and push them onto our stack ONLY if they exist
 *
 * After pushing them to the stack we continue from those nodes
 * we do the same thing that we did with our root until there are
 * no more items on the stack. Thats why we have while(stack.length > 0)
 */
template <class T>
vector<Node<T> > depthFirstWalkLoop(Node<T> *node) {
  vector<Node<T> > results;

  if (node == NULL) {
    return results;
  }

  // you can only push or pop to a stack. This is an important definition.
  // you can only add items to the top of the stack, and can only remove
  // items from the top of the stack, you cannot mess with its beginnign
  // nor with the middle of the stack.

  // a stack is graphicaly represented vertically
  //
  // | d |
  // | c |
  // | b |
  // | a |
  //
  // in this stack we have 4 items. the top most item is D, which is the last
  // item in the stack, to perform soem work on a stack we start from
  // the top most item, ALWAYS. Let's say we perform some work on D
  // after D is finished we remove it from the stack resulting in
  // the following stack:
  //
  // | c |
  // | b |
  // | a |
  //
  // we continue working on our stack from the last item always.

  stack<Node<T> *> stack;

  Node<T> *current;

  stack.push(node);

  while (!stack.empty()) {
    // always get the top most element on a stack to be the current, while
    // removing it from the stack if we were not working with js we could get
    // the last item by doing

    // pseudo-code
    // stack[stack.length - 1]
    // then we'd have to delete the top most item
    // stack.removeLast()

    current = stack.top();
    results.push_back(*current);

    stack.pop();

    // never push to the stack if they don't exist
    // because we want to walk through the left side first
    // we first push to the stack the right first
    // then the left side, this is because left will
    // be added last to the stack, thus being the next
    // one it will be worked on after the current node
    if (current->right != NULL) {
      stack.push(current->right);
    }

    if (current->left != NULL) {
      stack.push(current->left);
    }

    // the reason we push left last is to end up with this stack
    // | left  |
    // | right |

    // since left is added last, it will be the top most item in our stack.
  }

  // because of the while loop it will continue work until there is no more
  // items in the stack we always remove the current item from the stack on the
  // beginning but add more items to the stack as we walk down the tree. they're
  // only added if they exist, so if they don't they arent added. Eventually the
  // stack will have no values

  return results;
}

template <class T>
vector<Node<T> > depthFirstWalk(Node<T> *node) {
  // for depth first walk we can simply use a recursive approach
  vector<Node<T> > results;

  if (node == NULL) {
    return results;
  }

  results.push_back(*node);

  vector<Node<T> > left = depthFirstWalk(node->left);
  vector<Node<T> > right = depthFirstWalk(node->right);

  for (int j = 0; j < left.size(); j++) {
    results.push_back(left[j]);
  }

  for (int i = 0; i < right.size(); i++) {
    results.push_back(right[i]);
  }

  return results;
}

float treeSum(Node<float> *node) {
  if (node == NULL) {
    return 0;
  }

  float sum = 0;

  stack<Node<float> *> pending;

  pending.push(node);

  Node<float> *current;

  while (!pending.empty()) {
    current = pending.top();

    sum = sum + current->value;

    pending.pop();

    if (current->left != NULL) {
      pending.push(current->left);
    }

    if (current->right != NULL) {
      pending.push(current->right);
    }
  }

  return sum;
}

float treeMin(Node<float> node) {
  float min = node.value;

  stack<Node<float> > pending;
  pending.push(node);

  Node<float> current;

  while (!pending.empty()) {
    current = pending.top();
    pending.pop();

    if (current.value < min) {
      min = current.value;
    }

    if (current.right != NULL) {
      pending.push(*current.right);
    }

    if (current.left != NULL) {
      pending.push(*current.left);
    }
  }

  return min;
}

template <typename T>
void printVector(vector<Node<T> > vector) {

  cout << "[ (" << vector.size() << ") ";
  for (int i = 0; i < vector.size(); i++) {
    cout << vector[i].value;
    if (i + 1 != vector.size()) {
      cout << ", ";
    }
  }

  cout << "]" << endl;
}

float maxPathSum(const Node<float> &node) {
  float leftSum = node.left == NULL ? 0 : maxPathSum(*node.left);
  float rightSum = node.right == NULL ? 0 : maxPathSum(*node.right);

  cout << "----------" << endl;
  cout << "working on node: " << node.value << endl;
  cout << "left sum: " << leftSum << endl;
  cout << "right sum: " << rightSum << endl;

  return node.value + max(leftSum, rightSum);
};

int main() {
  {
    Node<string> a;
    Node<string> b;
    Node<string> c;
    Node<string> d;
    Node<string> e;
    Node<string> f;

    a.value = "a";
    b.value = "b";
    c.value = "c";
    d.value = "d";
    e.value = "e";
    f.value = "f";

    //        a
    //       / \
     //      b   c
    //     / \    \
     //    d   e    f

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    c.right = &f;

    vector<Node<string> > results = depthFirstWalkLoop(&a);

    string output = "";

    for (int i = 0; i < results.size(); i++) {
      output.append(results[i].value);
    }

    cout << output << endl;
  }

  cout << "----------------" << endl;
  cout << "Tree Operations" << endl;

  Node<float> root;
  Node<float> two;
  Node<float> three;
  Node<float> four;
  Node<float> five;
  Node<float> six;
  Node<float> seven;

  root.value = 100;
  two.value = 2;
  three.value = 3;
  four.value = 4;
  five.value = 5;
  six.value = 6;
  seven.value = 7;

  //       100
  //       / \
  //      2   3
  //     / \    \
  //    4   5    6
  //         \
  //          7

  cout << "//       100" << endl;
  cout << "//       / \\" << endl;
  cout << "//      2   3" << endl;
  cout << "//     / \\    \\" << endl;
  cout << "//    4   5    6" << endl;
  cout << "//         \\" << endl;
  cout << "//          7" << endl;

  root.left = &two;
  root.right = &three;

  two.left = &four;
  two.right = &five;

  three.right = &six;

  five.right = &seven;

  float sum = treeSum(&root);
  cout << "Sum: " << sum << endl;

  cout << "----------------" << endl;
  float min = treeMin(root);
  cout << "Min: " << min << endl;

  cout << "----------------" << endl;
  float maxSum = maxPathSum(root);
  cout << "maxSum: " << maxSum << endl;
}
