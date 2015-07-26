// Binary tree
//
// 1. Insert
// 2. Delete
// 3. Travers
//   i. Preorder
//   ii. Inorder
//   iii. Postorder

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
  int data;
  struct treenode * left;
  struct treenode * right;
};

typedef struct treenode * PTR;

void preorder_traversal(PTR t) {
  if(t != NULL) {
    printf("%d ", t->data);
    preorder_traversal(t->left);
    preorder_traversal(t->right);
  }
}

void postorder_traversal(PTR t) {
  if(t != NULL) {
    postorder_traversal(t->left);
    postorder_traversal(t->right);
    printf("%d ", t->data);
  }
}

void inorder_traversal(PTR t) {
  if(t != NULL) {
    inorder_traversal(t->left);
    printf("%d ", t->data);
    inorder_traversal(t->right);
  }
}

// Node insertion
void insert_node(PTR *pt, int x) {
  PTR t;
  t = *pt;
  if(t == NULL) {
    t = malloc(sizeof(struct treenode));
    t->data = x;
    t->left = NULL;
    t->right = NULL;
  } else {
    if(x < t->data) {
      insert_node(&(t->left), x);
    } else {
      insert_node(&(t->right), x);
    }
  }
  *pt = t;
}

// Delete node
// @todo: is not working yet.
void delete_node(PTR *pt, int x) {
  PTR tmp, current, r, prev;
  tmp = *pt;

  printf("---------- iteration print ----------\n");
  // printf("Value reading: %d\n", tmp->data);

  if(tmp == NULL) {
    printf("The node is not in the tree.\n");
  } else if(x < tmp->data) {
    printf("Moving on the left subtree\n\n");
    delete_node(&(tmp->left), x);
  } else if(x > tmp->data) {
    printf("Moving on the right subtree\n\n");
    delete_node(&(tmp->right), x);
  } else {
    printf("Node found %d\n", tmp->data);
    current = tmp;

    // node with only one child or no child
    // if(tmp->left == NULL) {
    //   free(tmp);
    // } else if(tmp->right == NULL) {
    //   free(tmp);
    // }
  }
}

int main() {
  PTR head = NULL;
  int a;
  int choice;

  insert_node(&head, 20);
  insert_node(&head, 30);
  insert_node(&head, 10);
  insert_node(&head, 40);
  insert_node(&head, 51);
  insert_node(&head, 18);

  printf("\nPreOrder binary tree printing:\n");
  preorder_traversal(head);
  printf("\nPostOrder binary tree printing:\n");
  postorder_traversal(head);
  printf("\nInOrder binary tree printing:\n");
  inorder_traversal(head);
  printf("\n");

  // delete_node(&head, 52);
  // delete_node(&head, 51);

  // printf("\n");
  // inorder_traversal(head);
  // printf("\n");

  // do {
  //   printf("Please give choice: \n");
  //   printf("1. Insert\n");
  //   printf("2. Delete\n");
  //   printf("3. Print\n");
  //   printf("4. Exit\n");
  //   scanf("%d", &choice);
  //   while((choice < 1) || (choice > 4)) {
  //     printf("Error at your choice.. Pleas give again..\n");
  //     printf("1. Insert\n");
  //     printf("2. Delete\n");
  //     printf("3. Print\n");
  //     printf("4. Exit\n");
  //     scanf("%d", &choice);
  //   }

  //   if(choice == 1) {
  //     printf("Please give an int\n");
  //     scanf("%d", &a);
  //     insert_node(&head, a);
  //   } else if(choice == 2) {
  //     printf("Please give an int\n");
  //     scanf("%d", &a);
  //     delete_node(&head, a);
  //   } else if(choice == 3) {
  //     // printf ("%d\n", head->data);
  //     inorder_traversal(head);
  //   }
  // } while(choice != 4);
}
