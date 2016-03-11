#include "binaryTree.h"

void BT_Preorder_traversal(ptr t) {
  if(t != NULL) {
    printf("%d ", t->data);
    BT_Preorder_traversal(t->left);
    BT_Preorder_traversal(t->right);
  }
}

void BT_Postorder_traversal(ptr t) {
  if(t != NULL) {
    BT_Postorder_traversal(t->left);
    BT_Postorder_traversal(t->right);
    printf("%d ", t->data);
  }
}

void BT_Inorder_traversal(ptr t) {
  if(t != NULL) {
    BT_Inorder_traversal(t->left);
    printf("%d ", t->data);
    BT_Inorder_traversal(t->right);
  }
}

// Node insertion
void BT_Insert_node(ptr *pt, int x) {
  ptr t;
  t = *pt;
  if(t == NULL) {
    t = malloc(sizeof(struct treenode));
    t->data = x;
    t->left = NULL;
    t->right = NULL;
  } else {
    if(x < t->data) {
      BT_Insert_node(&(t->left), x);
    } else {
      BT_Insert_node(&(t->right), x);
    }
  }
  *pt = t;
}

// Delete node
// @todo: is not working yet.
void BT_Delete_node(ptr *pt, int x) {
  ptr tmp, current, r, prev;
  tmp = *pt;

  printf("---------- iteration print ----------\n");
  // printf("Value reading: %d\n", tmp->data);

  if(tmp == NULL) {
    printf("The node is not in the tree.\n");
  } else if(x < tmp->data) {
    printf("Moving on the left subtree\n\n");
    BT_Delete_node(&(tmp->left), x);
  } else if(x > tmp->data) {
    printf("Moving on the right subtree\n\n");
    BT_Delete_node(&(tmp->right), x);
  } else {
    printf("Node found %d\n", tmp->data);
    current = tmp;
  }
}
