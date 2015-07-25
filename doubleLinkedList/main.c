#include "doubleLinkedList.h"

main() {
  struct Info *gFirst;
  struct Info *gLast, *temp;
  int iId, itm;
  int choice;
  gFirst = NULL;
  gLast = NULL;

  printf("Please select one of the following functionalities:\n");
  printf("0. Exit.\n");
  printf("1. Insert a node.\n");
  printf("2. Delete a node.\n");
  printf("3. Searching for a node.\n");
  printf("4. Print the list.\n");
  scanf("%d", &choice);

  while(choice != 0) {
    if(choice == 1) {
      printf("Please provide the iId:\n");
      scanf("%d", &iId);
      printf("Please provide the itm\n");
      scanf("%d", &itm);
      printf("\nAdding the new node with id: %d and time: %d\n", iId, itm);

      DL_Insert(&gFirst, &gLast, itm, iId);
    } else if(choice == 2) {
      printf("Please provide the itm that you want to delete: ");
      scanf("%d", &itm);

      DL_Remove(&gFirst, &gLast, itm);
    } else if(choice == 3) {
      printf("Please provide the itm that you want to search for: ");
      scanf("%d", &itm);

      DL_LookUp(&gFirst, itm);
    } else if(choice == 4) {
      DL_Print(&gFirst);
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

  DL_Free(&gFirst);
}