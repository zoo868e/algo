#include<stdio.h>
#include<stdlib.h>


/*Define the struct of node*/
typedef struct _node {
	int key;
	struct _node *rightchild;
	struct _node *leftchild;
	struct _node *previous;
}node;

typedef struct _BST {
	int size;
	struct _node *root;
}BST;
/*operation of node*/
node *initnode(int key);																	/*Initialize the node*/
void deletenode(node *node);

/*operation of BST*/
void initBST(BST *BST);																		/*Initialize the BST*/
int BSTisEmpty(BST *BST);																	/*Return 1 if BST is empty,else return 0*/
int BSTLength(BST *BST);																	/*Return the BST size*/
void printBST(BST *BST,node *currentnode);													/*PRINT the BST in INORDER traversal*/
void insertBST(BST *BST,node *currentnode,node *previousnode,int key);						/*INSERT node to BST*/
void deleteBST(BST *BST,node *root,int key);												/*DELETE a BST node*/
int searchBST(BST *BST,node *root,int key);													/*SEARCH the number, if exist return 1 else return 0*/

int main(){
	BST a;
	initBST(&a);
	printf("BSTisEmpty : %d\n",BSTisEmpty(&a));
	printf("BSTLength : %d\n",BSTLength(&a));
	printf("Insert 10 to BST\n");
	insertBST(&a,a.root,NULL,10);
	printf("BSTisEmpty : %d\n",BSTisEmpty(&a));
	printf("BSTLength : %d\n",BSTLength(&a));

	printf("Insert 20 to BST\n");
	insertBST(&a,a.root,NULL,20);
	printf("BSTisEmpty : %d\n",BSTisEmpty(&a));
	printf("BSTLength : %d\n",BSTLength(&a));

	printf("Insert -1 to BST\n");
	insertBST(&a,a.root,NULL,-1);
	printf("BSTisEmpty : %d\n",BSTisEmpty(&a));
	printf("BSTLength : %d\n",BSTLength(&a));

	printBST(&a,a.root);
	printf("\nSearch -1 is in BST or not : %d\n",searchBST(&a,a.root,-1));
	printf("\nDelete -1 from BST and PRINTBST:\n");
	deleteBST(&a,a.root,-1);
	printBST(&a,a.root);
	printf("\nDelete 100 from BST and PRINTBST:\n");
	deleteBST(&a,a.root,100);
	printBST(&a,a.root);
	printf("\nDelete 10 from BST and PRINTBST:\n");
	deleteBST(&a,a.root,10);
	printBST(&a,a.root);



	

	return 0;
}

/*Implement the operation of node*/
node *initnode(int key)
{
	node *newnode = (node*) malloc(sizeof(node));
	newnode->key = key;
	newnode->leftchild = NULL;
	newnode->previous = NULL;
	newnode->rightchild = NULL;
	return newnode;
}

void deletenode(node *node)
{
	free(node);
}

/*Implement the operaion of BST*/
void initBST(BST *BST)
{
	BST->size = 0;
	BST->root = NULL;
}

int BSTisEmpty(BST *BST)
{
	if(BST->size)return 0;
	else return 1;
}

int BSTLength(BST *BST)
{
	return BST->size;
}

void printBST(BST *BST,node *currentnode)
{
	if(currentnode != NULL){
		printBST(BST,currentnode->leftchild);
		printf("%d\n",currentnode->key);
		printBST(BST,currentnode->rightchild);
	}
}

void insertBST(BST *BST,node *currentnode,node *previousnode,int key)
{
	node *temp = initnode(key);
	if(BST->size < 1){
		BST->root = temp;
		BST->size++;
	}
	else if(!currentnode){
		currentnode = temp;
		currentnode->previous = previousnode;
		if(previousnode->key < currentnode->key)previousnode->rightchild = currentnode;
		else previousnode->leftchild = currentnode;
		BST->size++;
	}
	else if(temp->key < currentnode->key)insertBST(BST,currentnode->leftchild,currentnode,key);
	else insertBST(BST,currentnode->rightchild,currentnode,key);
}

void deleteBST(BST *BST,node *root,int key)			//	i=0 means replace by leftchild,i=1 means replace by rightchild
{
	if(!root){
		printf("There is no %d in this BST.\n",key);
		return;
	}
	if(key == root->key){
		if(!root->leftchild && !root->rightchild){
			if(root->previous){
				if(key < root->previous->key)root->previous->leftchild = NULL;
				else root->previous->rightchild = NULL;
			}
			BST->size--;
			deletenode(root);
			return;
		}
		if(root->leftchild){
			root->key = root->leftchild->key;
			deleteBST(BST,root->leftchild,root->leftchild->key);
		}
		else {
			root->key = root->rightchild->key;
			deleteBST(BST,root->rightchild,root->rightchild->key);
		}
	}
	else if(key < root->key)deleteBST(BST,root->leftchild,key);
	else deleteBST(BST,root->rightchild,key);
}

int searchBST(BST *BST,node *root,int key)
{
	if(!root)return 0;
	else if(key == root->key)return 1;
	else if(key < root->key)return searchBST(BST,root->leftchild,key);
	else return searchBST(BST,root->rightchild,key);
	return 0;
}
