#include <string.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head) {
  struct ListNode *previousNode = NULL;
  struct ListNode *currentNode = head;

  while (currentNode) {
    struct ListNode *temp = (*currentNode).next;

    (*currentNode).next = previousNode;
    previousNode = currentNode;
    currentNode = temp;
  }

  return previousNode;
}
