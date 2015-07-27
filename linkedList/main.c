#include "linkedList.h"

int main() {
  struct Subscription *gsub;
  int choice, sId;
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
      printf("Please provide the sId:\n");
      scanf("%d", &sId);

      L_Insert(&gsub, sId);
    } else if(choice == 2) {
      printf("Please provide the sId:\n");
      scanf("%d", &sId);

      L_Remove(&gsub, sId);
    } else if(choice == 3) {
      printf("Please provide the sId that you want to search for: ");
      scanf("%d", &sId);

      L_LookUp(&gsub, sId);
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
