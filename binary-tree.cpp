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

template <class T>
vector<Node<T> > depthFirstWalkLoop(Node<T> *node) {
  vector<Node<T> > results;

  if (node == NULL) {
    return results;
  }

  stack<Node<T> *> stack;

  Node<T> *current;

  stack.push(node);

  while (!stack.empty()) {
    current = stack.top();
    results.push_back(*current);

    stack.pop();

    if (current->right != NULL) {
      stack.push(current->right);
    }

    if (current->left != NULL) {
      stack.push(current->left);
    }
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

float maxPathSum(const Node<float> *node) {
  if (node == NULL) {
    return 0;
  }

  if (node->left == NULL && node->right == NULL) {
    return node->value;
  }

  return max(node->value + maxPathSum(node->left),
             maxPathSum(node->right) + node->value);
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
  float maxSum = maxPathSum(&root);
  cout << "maxSum: " << maxSum << endl;
}
