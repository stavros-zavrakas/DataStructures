#include "binaryTree.h"

// Binary tree
//
// 1. Insert
// 2. Delete
// 3. Travers
//   i. Preorder
//   ii. Inorder
//   iii. Postorder

int main() {
  ptr head = NULL;
  int a;
  int choice;

  BT_Insert_node(&head, 20);
  BT_Insert_node(&head, 30);
  BT_Insert_node(&head, 10);
  BT_Insert_node(&head, 40);
  BT_Insert_node(&head, 51);
  BT_Insert_node(&head, 18);

  printf("\nPreOrder binary tree printing:\n");
  BT_Preorder_traversal(head);
  printf("\nPostOrder binary tree printing:\n");
  BT_Postorder_traversal(head);
  printf("\nInOrder binary tree printing:\n");
  BT_Inorder_traversal(head);
  printf("\n");

  // @todo: fix it
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
