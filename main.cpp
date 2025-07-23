#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
  string value;
  Node *left;
  Node *right;
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

int main() {
  Node a = Node();
  Node *b = new Node();
  Node *c = new Node();
  Node *d = new Node();
  Node *e = new Node();
  Node *f = new Node();

  a.value = "a";
  b->value = "b";
  c->value = "c";
  d->value = "d";
  e->value = "e";
  f->value = "f";

  //        a
  //       / \
  //      b   c
  //     / \    \
  //    d   e    f

  a.left = b;
  a.right = c;

  b->left = d;
  b->right = e;

  c->right = f;

  vector<Node *> results = breadthFirstWalk(&a);

  string output = "";

  for (int i = 0; i < results.size(); i++) {
    output.append(results[i]->value);
  }

  cout << output << endl;
}