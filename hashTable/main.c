#include "hashTable.h"

int main() {
  struct SubInfo *temp;
  int hashSize = 67;
  int hashNum;
  int i, sId;

  table = malloc(hashSize * sizeof(struct SubInfo*));
  for(i = 0; i < hashSize; i++) {
    table[i] = NULL;
  }

  do {
    temp = (struct SubInfo *) malloc(sizeof(struct SubInfo));

    printf("Please provide sId to insert (type 0 to stop inserting): ");
    scanf("%d", &temp->sId);

    // printf("Please provide the stm: ");
    // scanf("%d", &temp->stm);
    temp->stm = 0;

    hashNum = HT_HashFunction(temp->sId, hashSize);

    HT_Insert(&temp, hashNum, hashSize);
  } while(temp->sId != 0);

  HT_Print(hashSize);

  printf("Please provide sId to remove: ");
  scanf("%d", &sId);

  HT_Remove(sId, hashSize);

  HT_Print(hashSize);

  HT_Free(hashSize);
}