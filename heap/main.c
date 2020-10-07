#include <stdio.h>
#include <string.h>
#include <limits.h>

void insert();
int deletemax();
void printarray();
void swap();
void heapsort();

int main(){
	int heap[10],x,len = 0,result[10];
	memset(heap,INT_MIN,sizeof(heap));
	memset(result,INT_MIN,sizeof(result));
	while(len < 10){
		scanf("%d",&x);
		insert(heap,x,len);
		len++;
		printarray(heap,len);

	}
	printf("\n");
	heapsort(heap,result,len);
	printarray(result,len);


	return 0;
}


void insert(int *heap,int x,int position)
{
	*(heap + position) = x;
	while(position > 0 &&  *(heap + position) > *(heap + position/2)){
		swap((heap + position),(heap + position/2));
		position /= 2;
	}
}

void printarray(int *heap, int len)
{
	while(len>0){
		printf("%d,",*heap);
		heap++;
		len--;
	}
}

int deletemax(int *heap,int len)
{
	int temp = *heap,position = 1,max = INT_MIN;
	if(len == 1)return *heap;
	len--;
	*heap = *(heap + len);
	while(2*position <= len){
		if((2*position + 1) > len){
			if(*heap < *(heap + position))swap(heap,heap + position);
			heap = heap + position;
		}
		else{
			max = *(heap + position) > *(heap + position + 1) ? position:position+1;
			if(*heap < *(heap + max)){
				swap(heap,heap + max);
				heap = heap + max;
			}
		}
		position = position * 2;
	}
	return temp;
}


void swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


void heapsort(int *heap,int *solution,int len)
{
	int x,count = len;
	while(count > 0){
		x = deletemax(heap,count);
		*(solution + (len - count)) = x;
		count--;
	}
}
