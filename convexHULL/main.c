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
node *nodeminy(node *array,int start,int end);
float slope(node *start,node *end);
void insertnodebyslope(node *array,node *newnode,int position);
node popnodebyslope(node *array,int len);
int dire(node *a,node *b,node *c);
void sortnodebyslopeminheap(node *array,int size);
void insertnodebyslopeminheap(node *array,node *newnode,int position);								//initialize the node array to node heap by insert
node popnodebyslopeminheap(node *array,int len);
void sortnodebyslopemaxheap(node *array,int size);
void insertnodebyslopemaxheap(node *array,node *newnode,int position);								//initialize the node array to node heap by insert
node popnodebyslopemaxheap(node *array,int len);

/*Declare the operation of convex hull*/
void convexhull(node *array,int len);
node *convexhulll5(node *array,int len);
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
		array[wp].slope = temp.slope;
		array[wp].next = temp.next;
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
node *nodeminy(node *array,int start,int end)
{		
	node *templ = (node*) malloc(sizeof(node));
	node *tempr = (node*) malloc(sizeof(node));
	if(start == end)return array;
	if((end - start) == 1){
		templ = &array[start];
		tempr = &array[end];
	}
	else{
		templ = nodeminy(array,start,end/2);
		tempr = nodeminy(array,end/2+1,end);
	}
	if(templ->y == tempr->y);
	else templ = templ->y < tempr->y ? templ:tempr;
	return templ;
}
float slope(node *start,node *end)
{
	if(start->y == end->y)return 0;
	else if(start->x == end->x) return FLT_MAX;
	return ((float)end->y - (float)start->y)/((float)end->x - (float)start->x);
}
/*sort the node by slope from small to big*/
void sortnodebyslopeminheap(node *array,int size)
{
	node heap[size];
	int wp = 0;
	while(wp < size){
		insertnodebyslopeminheap(heap,&array[wp],wp);
		wp++;

	}
	wp = 0;
	while(wp <= size){
		node temp;
		temp = popnodebyslopeminheap(heap,size-wp);
		array[wp].x = temp.x;
		array[wp].y = temp.y;
		array[wp].slope = temp.slope;
		array[wp].next = temp.next;
		wp++;
	}
}
void insertnodebyslopeminheap(node *array,node *newnode,int position)								//initialize the node array to node heap by insert
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
node popnodebyslopeminheap(node *array,int len)
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
			max = (array + position)->slope > (array + position + 1)->slope ? position:position + 1;
			if(array->slope < (array + max)->slope){
				swapnode(array, array + max);
				array = array + max;
			}
		}
		position *= 2;
	}
	return temp;
}
/*sort the node by slope from big to small*/
void sortnodebyslopemaxheap(node *array,int size)
{
	node heap[size];
	int wp = 0;
	while(wp < size){
		insertnodebyslopemaxheap(heap,&array[wp],wp);
		wp++;

	}
	wp = 0;
	while(wp <= size){
		node temp;
		temp = popnodebyslopemaxheap(heap,size-wp);
		array[wp].x = temp.x;
		array[wp].y = temp.y;
		array[wp].slope = temp.slope;
		array[wp].next = temp.next;
		wp++;
	}
}
void insertnodebyslopemaxheap(node *array,node *newnode,int position)								//initialize the node array to node heap by insert
{
	(array + position)->x = newnode->x;
	(array + position)->y = newnode->y;
	(array + position)->next = newnode->next;
	(array + position)->slope = newnode->slope;
	while(position > 0 && (array + position)->slope > (array + position/2)->slope){
		swapnode(array + position,array + position/2);
		position /= 2;
	}
}
node popnodebyslopemaxheap(node *array,int len)
{
	node temp = *array;
	int position = 1;
	int max = -1;
	if(len == 1)return temp;
	len --;
	*array = *(array + len);
	while(2*position <= len){
		if((2*position + 1) > len){
			if(array->slope < (array + position)->slope)swapnode(array,array + position);
			array = array + position;
		}
		else{
			max = (array + position)->slope > (array + position + 1)->slope ? position:position + 1;
			if(array->slope < (array + max)->slope){
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
/*convex hull*//*The input array is sort by x*/
void convexhull(node *array,int len)
{
	node *root = convexhulll5(array,len);
	//printf("arraylen = %d\n",len);
	//int wp,fp,fi,flag = 0,a,b,c,tc,ptc;
	//root = convexhulll5(array,len);
	/*printf("we got convexhull!\n");
	node *temp = root;
	printf("convex root : (%d,%d)\n",temp->x,temp->y);
	temp = temp->next;*/
	/*while(temp != root){
		printf("next node : (%d,%d)\n",temp->x,temp->y);
		temp = temp->next;
	}*/
	/*step 1*/
	/*step 2*/
	/*step 3*/
	/*step 4*/
}
node *convexhulll5(node *array,int len)
{
	if(len > 3){
		node *miny = (node*) malloc(sizeof(node));
		miny = nodeminy(array,0,len-1);
		int left = 0,right = 0,ff,minypos;
		/*find the position of miny over array*/
		for(ff = 0;ff < len;ff++){
			if(array[ff].x == miny->x && array[ff].y == miny->y)break;
		}
		minypos = ff;
		printf("minypos : %d\n",minypos);
		right = len - minypos - 1;
		left = minypos;
		node r[right],l[left];
		for(ff = 0;ff < len;ff++){
			if(ff == minypos) continue;
			array[ff].slope = slope(miny,&array[ff]);
		}
		/*calculate the slope of node which on the right of miny*/
		for(ff = 0;ff < left;ff++){
			printf("-----------------------------------------------\n");
			l[ff].x = array[ff].x;
			printf("l[%d].x = %d\n",ff,l[ff].x);
			printf("array[%d].x = %d\n",ff,array[ff].x);

			l[ff].y = array[ff].y;
			printf("l[%d].y = %d\n",ff,l[ff].y);
			printf("array[%d].y = %d\n",ff,array[ff].y);

			l[ff].slope = array[ff].slope;
			printf("l[%d].slope = %f\n",ff,l[ff].slope);
			printf("array[%d].slope = %f\n",ff,array[ff].slope);

			l[ff].next = array[ff].next;
			printf("l[%d].next = %p\n",ff,l[ff].next);
			printf("array[%d].next = %p\n",ff,array[ff].next);
			printf("-----------------------------------------------\n");

		}
		for(ff = 0;ff < right;ff++){
			r[ff].x = array[ff + minypos + 1].x;
			printf("r[%d].x = %d\n",ff,r[ff].x);
			printf("array[%d].x = %d\n",ff + minypos + 1,array[ff + minypos + 1].x);

			r[ff].y = array[ff + minypos + 1].y;
			printf("r[%d].y = %d\n",ff,r[ff].y);
			printf("array[%d].y = %d\n",ff + minypos + 1,array[ff + minypos + 1].y);

			r[ff].slope = array[ff + minypos + 1].slope;
			printf("r[%d].slope = %f\n",ff,r[ff].slope);
			printf("array[%d].slope = %f\n",ff + minypos + 1,array[ff + minypos + 1].slope);

			r[ff].next = array[ff + minypos + 1].next;
			printf("r[%d].next = %p\n",ff,r[ff].next);
			printf("array[%d].next = %p\n",ff + minypos + 1,array[ff + minypos + 1].next);
			printf("-----------------------------------------------\n");


		}
		sortnodebyslopeminheap(r,right);
		sortnodebyslopeminheap(l,left);
		printf("After sort by slope:\n");
		for(ff = 0;ff < right;ff++){
			printf("r[%d] : (%d,%d) slope = %f\n",ff,r[ff].x,r[ff].y,r[ff].slope);
		}
		for(ff = 0;ff < left;ff++){
			printf("l[%d] : (%d,%d) slope = %f\n",ff,l[ff].x,l[ff].y,l[ff].slope);
		}
		node *temp = miny;
		temp->next = &r[0];
		for(ff = 1;ff < right;ff++){
			int k = dire(temp,temp->next,&r[ff]);
			if(k >= 0){
				temp->next->next = &r[ff];
				temp = temp->next;
			}
			else {
				temp->next = &r[ff];
			}
		}
		for(ff = 0;ff < left;ff++){
			int k = dire(temp,temp->next,&l[ff]);
			if(k >= 0){
				temp->next->next = &l[ff];
				temp = temp->next;
			}
			else{
				temp->next = &l[ff];
			}
		}
		if(dire(temp,temp->next,miny) > 1){
			temp->next->next = miny;
		}
		else temp->next = miny;
		return miny;
	}
	else if(len == 3){
		if(dire(array,array+1,array+2) > 0){
			array->next = (array + 1);
			(array + 1)->next = (array + 2);
			(array + 2)-> next = array;
			return nodeminy(array,0,2);
		}
		else if(dire(array,array+1,array+2) < 0){
			array->next = (array + 2);
			(array + 2)->next = (array + 1);
			(array + 1)->next = array;
			return nodeminy(array,0,2);
		}
		else{
			array->next = (array + 2);
			return array;
		}
	}
	else if(len == 2){
		if(array->y > (array + 1)->y){
			(array + 1)->next = array;
			return (array + 1);
		}
		array->next = (array + 1);
		return array;
	}

	return array;
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

	return 0;
}
