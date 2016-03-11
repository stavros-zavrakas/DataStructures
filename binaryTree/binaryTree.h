#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
  int data;
  struct treenode * left;
  struct treenode * right;
};

typedef struct treenode * ptr;

// Function: BT_Preorder_traversal
// --------------------
// @todo: add the description
// returns: (void)
void BT_Preorder_traversal(ptr t);

// Function: BT_Postorder_traversal
// --------------------
// @todo: add the description
// returns: (void)
void BT_Postorder_traversal(ptr t);

// Function: BT_Preorder_traversal
// --------------------
// @todo: add the description
// returns: (void)
void BT_Inorder_traversal(ptr t);

// Function: BT_Preorder_traversal
// --------------------
// @todo: add the description
// returns: (void)
void BT_Insert_node(ptr *pt, int x);

// Function: BT_Preorder_traversal
// --------------------
// @todo: add the description
// returns: (void)
void BT_Delete_node(ptr *pt, int x);
