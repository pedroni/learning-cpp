#include <cstddef>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Node {
  string value;
  Node *left;
  Node *right;

  Node() : value(""), left(NULL), right(NULL) {}
};

vector<Node *> breadthFirstWalk(Node *node) {
    
  vector<Node *> results;

  if (node == 0) {
    return results;
  }

  Node *current;

  queue<Node *> inProgress;

  inProgress.push(node);

  while (!inProgress.empty()) {
    current = inProgress.front();
    inProgress.pop();

    if (current->left != 0) {
      inProgress.push(current->left);
    }

    if (current->right != 0) {
      inProgress.push(current->right);
    }

    results.push_back(current);
  }

  return results;
};

vector<Node> depthFirstWalk(Node *node) {
  // for depth first walk we can simply use a recursive approach
  vector<Node> results;

  if (node == NULL) {
    return results;
  }

  results.push_back(*node);

  vector<Node> left = depthFirstWalk(node->left);
  vector<Node> right = depthFirstWalk(node->right);

  for (int j = 0; j < left.size(); j++) {
    results.push_back(left[j]);
  }

  for (int i = 0; i < right.size(); i++) {
    results.push_back(right[i]);
  }

  return results;
}

vector<Node> depthFirstWalkLoop(Node *node) {
  vector<Node> results;

  if (node == NULL) {
    return results;
  }

  stack<Node *> stack;

  Node *current;

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

int main() {
  Node a;
  Node b;
  Node c;
  Node d;
  Node e;
  Node f;

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

  vector<Node> results = depthFirstWalkLoop(&a);

  string output = "";

  for (int i = 0; i < results.size(); i++) {
    output.append(results[i].value);
  }

  cout << output << endl;
}
