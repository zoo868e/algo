#include<stdio.h>

void sort(int *array,int start,int end);
void merge(int *array,int startl,int endl,int startr,int endr);
void swap(int *a,int *b);

void sort(int *array,int start,int end)
{
	if(start == end)return;
	else {
		sort(array,start,(end + start)/2);
		sort(array,(end + start)/2 + 1,end);
		merge(array,start,(end + start)/2,(end + start)/2 + 1,end);
	}
}

void merge(int *array,int startl,int endl,int startr,int endr)
{
	while(startl != endl || startr != endr){
		if(array[startl] > array[startr){
			swap(&array[startl],&array[startr]);
		}
	}
}

void swap(int *a,int *b)
{
	*a = *b ^ *a;
	*b = *b ^ *a;
	*a = *b ^ *a;
}

int main(){
	return 0;
}
