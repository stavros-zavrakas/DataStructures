#include "linkedList.h"

int main() {
  struct Subscription *gsub;
  int choice;
  gsub = NULL;

  printf("Please select one of the following functionalities:\n");
  printf("0. Exit.\n");
  printf("1. Insert a node.\n");
  printf("2. Delete a node.\n");
  printf("3. Searching for a node.\n");
  printf("4. Print the list.\n");
  scanf("%d", &choice);

  while(choice != 0) {
    if(choice == 1) {
      L_Insert(&gsub);
    } else if(choice == 2) {
      L_Remove(&gsub);
    } else if(choice == 3) {
      L_LookUp(&gsub);
    } else if(choice == 4) {
      L_Print(&gsub);
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

  L_Free(&gsub);
  return 0;
}
