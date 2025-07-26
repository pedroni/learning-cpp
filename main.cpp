#include <iostream>

using namespace std;

template <class T>
struct Node {
  T value;
  Node<T> *left;
  Node<T> *right;

  Node() : value(), left(NULL), right(NULL) {}
};

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
float maxPathSum(Node<float> root) {
  float maxSum = 0;

  stack<Node<float> > stack;
  stack.push(root);

  Node<float> current;
  bool stop = false;

  float pathSum = 0;

  vector<Node<float> > paths;

  while (!stack.empty() && !stop) {
    current = stack.top();

    stack.pop();

    pathSum += current.value;
    paths.push_back(current);

    // found a leaf
    if (current.left == NULL && current.right == NULL) {
      if (pathSum > maxSum) {
        maxSum = pathSum;
      }

      printVector(paths);
      paths.clear();
      cout << "sums found " << pathSum << endl;

      // return to the root value
      paths.push_back(root);
      pathSum = root.value;
    }

    if (current.right != NULL) {
      stack.push(*current.right);
    }

    if (current.left != NULL) {
      stack.push(*current.left);
    }
  }

  return maxSum;
}
int main() {
  Node<float> root;
  Node<float> two;
  Node<float> three;
  Node<float> four;
  Node<float> five;
  Node<float> six;

  root.value = 100;
  two.value = 2;
  three.value = 3;
  four.value = 4;
  five.value = 5;
  six.value = 6;

  //       100
  //       / \
    //      2   3
  //     / \    \
    //    4   5    6

  root.left = &two;
  root.right = &three;

  two.left = &four;
  two.right = &five;

  three.right = &six;

  float maxSum = maxPathSum(root);
  cout << "HEYAAello world HA: " << maxSum << endl;
}
