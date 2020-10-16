#include<stdio.h>
#include<stdlib.h>

/*Define the data structure*/
typedef struct _node{
	int x;
	int y;
	struct _node *next;
}node;

typedef struct _edge{
	struct _node *start;
	struct _node *end;
}edge;
/*Declare the operation of node*/
node *initnode(int x,int y);
void dnode(node *x);
void sortnodebyx(node *array,int size);
void insertnode(node *array,node *newnode,int position);
void swapnode(node *a,node *b);
node popnode(node *array,int len);
int nodelen(node *array);
/*Declare the operation of edge*/
void initedge(edge *newedge,node *a,node *b);
void dedge(edge *x);
/*Declare the operation of convex hull*/
node *convexhull(node *array,int start,int end);
node *mergehull(node *array1,node *array2);
node *graham(node *array1,node *array2,int x,int y);

/*Implement the operation of node*/
node *initnode(int x,int y)
{
	node *newnode = (node*) malloc(sizeof(node));
	newnode->x = x;
	newnode->y = y;
	newnode->next = NULL;
	return newnode;
}
void dnode(node *x)
{
	free(x);
}
void sortnodebyx(node *array,int size)
{
	node heap[size];
	int wp = 0;
	while(wp < size){
		insertnode(heap,&array[wp],wp);
		wp++;

	}

	wp = 0;
	while(wp <= size){
		node temp;
		temp = popnode(heap,size-wp);
		array[wp].x = temp.x;
		array[wp].y = temp.y;
		wp++;
	}
}
void insertnode(node *array,node *newnode,int position)								//initialize the node array to node heap by insert
{
	(array + position)->x = newnode->x;
	(array + position)->y = newnode->y;
	while(position > 0 && (array + position)->x > (array + position/2)->x){
		swapnode(array + position,array + position/2);
		position /= 2;
	}
}
void swapnode(node *a,node *b)
{
	node *temp = (node*) malloc(sizeof(node));
	temp->x = a->x;
	temp->y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = temp->x;
	b->y = temp->y;
	free(temp);
}
node popnode(node *array,int len)
{
	node temp = *array;
	int position = 1;
	int max = -1;
	if(len == 1)return temp;
	len --;
	*array = *(array + len);
	while(2*position <= len){
		if((2*position + 1) > len){
			if(array->x < (array + position)->x)swapnode(array,array + position);
			array = array + position;
		}
		else{
			max = (array + position)->x > (array + position + 1)->x ? position:position + 1;
			if(array->x < (array + max)->x){
				swapnode(array, array + max);
				array = array + max;
			}
		}
		position *= 2;
	}
	return temp;
}
int nodelen(node *array)
{
	return (sizeof(&array)/sizeof(node));
}
/*Implement the operation of edge*/
void initedge(edge *newedge,node *a,node *b)
{
	newedge->start = a;
	newedge->end = b;
}
void dedge(edge *x)
{
	free(x);
}

/*convex hull*/
node *convexhull(node *array,int start,int end)
{
	node *tempr = (node*) malloc(sizeof(node));
	node *templ = (node*) malloc(sizeof(node));
	node *root = (node*) malloc(sizeof(node));
	if(start == end){
		root = array + start;
	}
	else if((start - end) > 0){
		templ = convexhull(array,start,end/2);
		tempr = convexhull(array,end/2+1,end);
		root = mergehull(templ,tempr);
	}
	dnode(templ);
	dnode(tempr);
	return root;
}

node *mergehull(node *array1,node *array2)
{
	node *root = (node*) malloc(sizeof(node));
	int lenarray1 = nodelen(array1);
	int lenarray2 = nodelen(array2);
	if(lenarray1 == 1 && lenarray2 == 1){
		array1->next = array2;
		root = array1;
	}
	else{
		int wp = 0,x=0,y=0;
		while(wp < lenarray1){
			x += array1[wp].x;
			y += array2[wp].y;
			wp++;
		}
		/*Centroid of the node which in array1*/
		x = x / lenarray1;
		y = y / lenarray1;
		root = graham(array1,array2,x,y);
	}
	return root;
}
node *graham(node *array1,node *array2,int x,int y)
{
	node *root = (node*) malloc(sizeof(node));
	return root;
}

int main(){
	/*nodenum = number of nodes; wp,fp = loop conditions; tx,ty = temporary of coordinates*/
	int nodenum,wp,tx,ty;
	scanf("%d",&nodenum);
	node input[nodenum];
	wp = 0;
	while(wp < nodenum){
		scanf("%d %d",&tx,&ty);
		input[wp].x = tx;
		input[wp].y = ty;
		wp++;
	}
	wp = 0;
	printf("before sort node by x\n");
	while(wp < nodenum){
		printf("input[%d] = (%d,%d)\n",wp,input[wp].x,input[wp].y);
		wp++;
	}
	wp = 0;
	sortnodebyx(input,nodenum);
	printf("after sort node by x\n");
	while(wp < nodenum){
		printf("input[%d] = (%d,%d)\n",wp,input[wp].x,input[wp].y);
		wp++;
	}
	return 0;
}
