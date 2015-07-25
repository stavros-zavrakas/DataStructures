#include "sortedLinkedList.h"

int main() {
  struct SubInfo *head;
  int choice;
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
      SL_Insert(&head);
    } else if(choice == 2) {
      SL_Remove(&head);
    } else if(choice == 3) {
      SL_LookUp(&head);
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
