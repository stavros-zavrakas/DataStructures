#include "sortedLinkedList.h"

int main() {
  struct SubInfo *head;
  int sId, stm, choice;
  head = NULL;

  printf("Please select one of the following functionalities:\n");
  printf("0. Exit.\n");
  printf("1. Insert a node.\n");
  printf("2. Delete a node.\n");
  printf("3. Searching for a node.\n");
  printf("4. Print the list.\n");
  scanf("%d", &choice);

  while(choice != 0) {
    if(choice == 1) {
      printf("Please provide the sId:\n");
      scanf("%d", &sId);
      printf("Please provide the stm:\n");
      scanf("%d", &stm);
      printf("\nAdding the new node with id: %d and time: %d.\n", sId, stm);

      SL_Insert(&head, sId, stm);
    } else if(choice == 2) {
      printf("Please provide the stm that you want to delete:\n");
      scanf("%d", &stm);

      SL_Remove(&head, stm);
    } else if(choice == 3) {
      printf("Please provide the stm that you want to search for: ");
      scanf("%d", &stm);

      SL_LookUp(&head, stm);
    } else if(choice == 4) {
      SL_Print(&head);
    } else {
      printf("The functionality is not supported. Please another option.\n");
    }

    printf("Please select one of the following functionalities:\n");
    printf("0. Exit.\n");
    printf("1. Insert a node.\n");
    printf("2. Delete a node.\n");
    printf("3. Searching for a node.\n");
    printf("4. Print the list.\n");
    scanf("%d", &choice);
  }

  SL_Free(&head);
  return 0;
}
