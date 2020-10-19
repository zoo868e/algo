#include<stdio.h>
#include<string.h>

int findmax(int *array,int start,int end)
{
	if(start == end)return array[start];
	else if(start == (end-1))return array[start] > array[end] ? array[start]:array[end];
	int l = findmax(array,start,(end + start)/2);
	int r = findmax(array,(end + start)/2 + 1,end);
	return l > r ? l:r;
}


int main (){
	int len,ff;
	scanf("%d",&len);
	ff = 0;
	int array[len];
	memset(array,0,sizeof(array));
	while(ff < len){
		scanf("%d",&array[ff]);
		ff++;
	}
	printf("max = %d",findmax(array,0,len-1));
}
