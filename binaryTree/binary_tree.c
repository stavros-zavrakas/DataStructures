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
    printf("%d\n", t->data);
    preorder_traversal(t->left);
    preorder_traversal(t->right);
  }
}

void inorder_traversal(PTR t) {
  if(t != NULL) {
    inorder_traversal(t->left);
    printf("%d ", t->data);
    inorder_traversal(t->right);
  }
}

void postorder_traversal(PTR t) {
  if(t != NULL) {
    postorder_traversal(t->left);
    postorder_traversal(t->right);
    printf("%c ", t->data);
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
void delete_node(PTR *pt, int x) {
  PTR t, current, r, prev;
  t = *pt;

  if(t == NULL) {
    printf("The node is not in the tree!\n");
  } else {
    if(x < t->data) {
      delete_node(&(t->left), x);
    } else {
      if(x > t->data) {
        delete_node(&(t->right), x);
      } else {
        current = t;
        if(current->right == NULL) {
          t = current->left;
        } else {
          if(current->left == NULL) {
            t = current->right;
          } else {
            prev = current;
            r = current->left;
            if(r->right == NULL) {
              current->data = r->data;
              current = r;
              prev->left = r->left;
            } else {
              while(r->right != NULL) {
                prev = r;
                r = r->right;
              }

              current->data = r->data;
              current = r;
              prev->right = r->left;
            }
          }
        }
      }
      printf("Node %d has been erased...", x);
      free(current);
    }
  }
  *pt = t;
}

int main() {
  PTR head = NULL;
  int a;
  int choice;

  do {
    printf("Please give choice: \n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Print\n");
    printf("4. Exit\n");
    scanf("%d", &choice);
    while((choice < 1) || (choice > 4)) {
      printf("Error at your choice.. Pleas give again..\n");
      printf("1. Insert\n");
      printf("2. Delete\n");
      printf("3. Print\n");
      printf("4. Exit\n");
      scanf("%d", &choice);
    }

    if(choice == 1) {
      printf("Please give an int\n");
      scanf("%d", &a);
      insert_node(&head, a);
    } else if(choice == 2) {
      printf("Please give an int\n");
      scanf("%d", &a);
      delete_node(&head, a);
    } else if(choice == 3) {
      // printf ("%d\n", head->data);
      inorder_traversal(head);
    }
  } while(choice != 4);
}
