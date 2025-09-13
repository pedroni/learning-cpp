class ListNode {
  val;
  next;

  constructor(val = 0, next = null) {
    this.val = val;
    this.next = next;
  }
}

function printList(head) {
  temp = head;
  while (temp) {
    console.log(temp.val);

    if (temp.next) {
      console.log(" | ");
    }

    temp = temp.next;
  }
  console.log("\n");
}

class Solution {
  append(value) {
    const newNode = new ListNode(value);

    if (this.head == null) {
      this.head = newNode;
    } else {
      let currentNode = head;
      while (currentNode.next != null) {
        currentNode = currentNode.next;
      }
      currentNode.next = newNode;
    }

    return newNode;
  }

  // the edge cases are killing me.
  // input: [1,1] x: 0 output: [1,1]
  // input: [1,1] x: 2 output: [1,1]
  partition(head, x) {
    if (head == null) {
      return head;
    }

    if (head.next == null) {
      // if only one item always return it
      return head;
    }

    let temp = head;

    let smallHead = temp.val < x ? temp : null;
    let smallTail = temp.val < x ? temp : null;

    let bigHead = temp.val >= x ? temp : null;

    let tempNext = temp.next;

    while (temp.next) {
      tempNext = temp.next.next;
      if (temp.next.val < x) {
        if (smallHead == null) {
          smallHead = temp.next;
          smallTail = smallHead;
        }

        smallTail.next = temp.next;
        smallTail = temp.next;

        temp.next = tempNext;
        smallTail.next = null;

        continue;
      } else {
        if (bigHead == null) {
          bigHead = temp.next;
        }
      }

      temp = temp.next;
    }

    console.log("--------------------");
    const smallHeadValue = smallHead != null ? smallHead.val : -1;
    console.log("small head: ", smallHeadValue);

    const smallTailValue = smallTail != null ? smallTail.val : -1;
    console.log("small tail: ", smallTailValue);

    const bigHeadValue = bigHead != null ? bigHead.val : -1;
    console.log("big head: ", bigHeadValue);

    const headValue = head != null ? head.val : -1;
    console.log("head: ", headValue);

    const smallHeadNextValue =
      smallHead != null && smallHead.next != null ? smallHead.next.val : -1;
    console.log("small head next: ", smallHeadNextValue);

    console.log("--------------------");

    if (smallTail == null) {
      // when there's no small tail it means all items were bigger than x and we
      // do not have a small list
      return bigHead;
    }

    // merge both partitions, the small at the start and the big at the end!
    smallTail.next = bigHead;

    // then we return the smallHead which is the newest head that contains
    return smallHead;
  }
}

const solution = new Solution();

// head = solution.append(3);
// solution.append(8);
// solution.append(5);
// solution.append(10);
// solution.append(2);
// solution.append(1);

// printList(head);
// result = solution.partition(solution.head, 5);
// printList(result);

// head = solution.append(0);
// solution.append(1);

// printList(head);
// result = solution.partition(solution.head, 2);
// printList(result);

console.log("------------------------------");
console.log("Are you reading this correctly?");
