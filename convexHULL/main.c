#include<stdio.h>
#include<stdlib.h>
#include<float.h>

/*Define the data structure*/
typedef struct _node{
	int x;
	int y;
	float slope;
	struct _node *next;
}node;

/*Declare the operation of node*/
node *initnode(int x,int y);
void dnode(node *x);
void sortnodebyx(node *array,int size);
void insertnode(node *array,node *newnode,int position);
void swapnode(node *a,node *b);
node popnode(node *array,int len);
int nodelen(node *array);
node nodeminy(node *array,int start,int end);
float slope(node *start,node *end);
void insertnodebyslope(node *array,node *newnode,int position);
node popnodebyslope(node *array,int len);
int dire(node *a,node *b,node *c);
/*Declare the operation of convex hull*/
void convexhull(node *array,int len);
/*Implement the operation of node*/
node *initnode(int x,int y)
{
	node *newnode = (node*) malloc(sizeof(node));
	newnode->x = x;
	newnode->y = y;
	newnode->slope = 0;
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
	(array + position)->next = newnode->next;
	(array + position)->slope = newnode->slope;
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
	temp->slope = a->slope;
	a->x = b->x;
	a->y = b->y;
	a->slope = b->slope;
	b->x = temp->x;
	b->y = temp->y;
	b->slope = temp->slope;
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
node nodeminy(node *array,int start,int end)
{		
	node templ;
	node tempr;
	if(start == end)return *array;
	templ = nodeminy(array,start,end/2);
	tempr = nodeminy(array,end/2+1,end);
	if(templ.y == tempr.y);
	else templ = templ.y < tempr.y ? templ:tempr;
	return templ;
}
float slope(node *start,node *end)
{
	if(start->y == end->y)return 0;
	else if(start->x == end->x) return FLT_MAX;
	return ((float)end->y - (float)start->y)/((float)end->x - (float)start->x);
}
void insertnodebyslope(node *array,node *newnode,int position)
{
	(array + position)->x = newnode->x;
	(array + position)->y = newnode->y;
	(array + position)->next = newnode->next;
	(array + position)->slope = newnode->slope;
	while(position > 0 && (array + position)->slope < (array + position/2)->slope){
		swapnode(array + position,array + position/2);
		position /= 2;
	}
}
node popnodebyslope(node *array,int len)
{
	node temp = *array;
	int position = 1;
	int max = -1;
	if(len == 1)return temp;
	len --;
	*array = *(array + len);
	while(2*position <= len){
		if((2*position + 1) > len){
			if(array->slope > (array + position)->slope)swapnode(array,array + position);
			array = array + position;
		}
		else{
			max = (array + position)->slope < (array + position + 1)->slope ? position:position + 1;
			if(array->slope > (array + max)->slope){
				swapnode(array, array + max);
				array = array + max;
			}
		}
		position *= 2;
	}
	return temp;
}
/*calculate the three points in left turn or right turn*/
int dire(node *a,node *b,node *c)
{
	return (b->x - a->x)*(c->y - a->y) - (b->y - a->y)*(c->x - a->x);
}
/*convex hull*/
void convexhull(node *array,int len)
{
	node *root = (node*) malloc(sizeof(node));
	printf("arraylen = %d\n",len);
	int wp,fp,fi,flag = 0,a,b,c,tc,ptc;
	root = array;
	/*step 1*/
	/*step 2*/
	/*step 3*/
	/*step 4*/
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
	/*sortnodebyx(input,nodenum);
	printf("after sort node by x\n");
	while(wp < nodenum){
		printf("input[%d] = (%d,%d)\n",wp,input[wp].x,input[wp].y);
		wp++;
	}*/
	convexhull(input,nodenum);
	printf("before sort node by x\n");
	while(wp < nodenum){
		printf("input[%d] = (%d,%d)\n",wp,input[wp].x,input[wp].y);
		wp++;
	}

	return 0;
}
