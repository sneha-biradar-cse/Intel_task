
#include <stdio.h>
#include <stdlib.h>

/*BST IMPLEMENTATION*/

struct BSTNode {
int data;
struct BSTNode* left;
struct BSTNode* right;
};

/* Create BST Node */

struct BSTNode* createBSTNode(int val) {
struct BSTNode* node =
(struct BSTNode*)malloc(sizeof(struct BSTNode));
node->data = val;
node->left = NULL;
node->right = NULL;
return node;
}

/* Insert in BST */

struct BSTNode* insertBST(struct BSTNode* root, int val) {
if (root == NULL) {
return createBSTNode(val);
}
if (val < root->data)
root->left = insertBST(root->left, val);
else if (val > root->data)
root->right = insertBST(root->right, val);
return root;
}

/* Inorder BST */

void inorderBST(struct BSTNode* root) {
if (root == NULL)
return;
inorderBST(root->left);
printf("%d ", root->data);
inorderBST(root->right);
}

/*RED BLACK TREE*/

enum Color { RED, BLACK };
struct RBNode {
int data;
enum Color color;
struct RBNode *left, *right, *parent;
};
struct RBTree {
struct RBNode* root;
};

/* Create RB Node */
struct RBNode* createRBNode(int val) {
struct RBNode* node =
(struct RBNode*)malloc(sizeof(struct RBNode));
node->data = val;
node->color = RED;
node->left = NULL;
node->right = NULL;
node->parent = NULL;
return node;
}

/* Left Rotate */
void leftRotate(struct RBTree* tree, struct RBNode* x) {
struct RBNode* y = x->right;
x->right = y->left;
if (y->left != NULL)
y->left->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
tree->root = y;
else if (x == x->parent->left)
x->parent->left = y;
else
x->parent->right = y;
y->left = x;
x->parent = y;
}

/* Right Rotate */
void rightRotate(struct RBTree* tree, struct RBNode* y) {
struct RBNode* x = y->left;
y->left = x->right;
if (x->right != NULL)
x->right->parent = y;
x->parent = y->parent;
if (y->parent == NULL)
tree->root = x;
else if (y == y->parent->left)
y->parent->left = x;
else
y->parent->right = x;
x->right = y;
y->parent = x;
}

/* Fix Violations */
void fixViolation(struct RBTree* tree, struct RBNode* z) {
while (z != tree->root && z->parent->color == RED) {
struct RBNode* parent = z->parent;
struct RBNode* grandparent = parent->parent;
/* Parent is left child */
if (parent == grandparent->left) {
struct RBNode* uncle = grandparent->right;

/* Case 1 */
if (uncle != NULL && uncle->color == RED) {
parent->color = BLACK;
uncle->color = BLACK;
grandparent->color = RED;
z = grandparent;
}
else {
/* Case 2 */
if (z == parent->right) {
z = parent;
leftRotate(tree, z);
}
/* Case 3 */
parent->color = BLACK;
grandparent->color = RED;
rightRotate(tree, grandparent);
}
}

/* Parent is right child */
else {
struct RBNode* uncle = grandparent->left;
/* Case 1 */
if (uncle != NULL && uncle->color == RED) {
parent->color = BLACK;
uncle->color = BLACK;
grandparent->color = RED;
z = grandparent;
}
else {
/* Case 2 */
if (z == parent->left) {
z = parent;
rightRotate(tree, z);
}
/* Case 3 */
parent->color = BLACK;
grandparent->color = RED;
leftRotate(tree, grandparent);
}
}
}
tree->root->color = BLACK;
}

/* Insert RB Node */
void insertRB(struct RBTree* tree, int val) {
struct RBNode* node = createRBNode(val);
struct RBNode* y = NULL;
struct RBNode* x = tree->root;
while (x != NULL) {
y = x;
if (node->data < x->data)
x = x->left;
else
x = x->right;
}
node->parent = y;
if (y == NULL)
tree->root = node;
else if (node->data < y->data)
y->left = node;
else
y->right = node;
fixViolation(tree, node);
}

/* Inorder RB Tree */
void inorderRB(struct RBNode* root) {
if (root == NULL)
return;
inorderRB(root->left);
printf("%d(%c) ",
root->data,
root->color == RED ? 'R' : 'B');
inorderRB(root->right);
}

int main() {
printf("BST Example:\n");
struct BSTNode* bstRoot = NULL;
int arr[] = {10, 5, 20, 3, 7, 15};
int n = 6;
for (int i = 0; i < n; i++) {
bstRoot = insertBST(bstRoot, arr[i]);
}
printf("Inorder BST: ");
inorderBST(bstRoot);
printf("\n\n");
printf("Red Black Tree Example:\n");
struct RBTree tree;
tree.root = NULL;
for (int i = 0; i < n; i++) {
insertRB(&tree, arr[i]);
}
printf("Inorder RBT: ");
inorderRB(tree.root);
printf("\n");
return 0;
}
