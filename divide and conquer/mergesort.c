#include<stdio.h>

void sort(int *array,int start,int end);
void merge(int *array,int l,int m,int r);
void swap(int *a,int *b);

void sort(int *array,int start,int end)
{
	if(start == end)return;
	else {
		sort(array,start,(end + start)/2);
		sort(array,(end + start)/2 + 1,end);
		merge(array,start,(end + start)/2,end);
	}
}

void merge(int *array,int l,int m,int r)
{
	int i,j,k,ff;
	int llen = m - l + 1;
	int rlen = r - m;
	int la[llen],ra[rlen];
	for(ff = 0;ff < llen;ff++){
		la[ff] = array[ff + l];
	}
	for(ff = 0;ff < rlen;ff++){
		ra[ff] = array[ff + m + 1];
	}
	i = 0;
	j = 0;
	k = l;
	while(i < llen && j < rlen){
		if(la[i] <= ra[j]){
			array[k] = la[i];
			i++;
			k++;
		}
		else{
			array[k] = ra[j];
			j++;
			k++;
		}
	}
	while(i < llen){
		array[k] = la[i];
		i++;
		k++;
	}
	while(j < rlen){
		array[k] = ra[j];
		j++;
		k++;
	}
}

int main(){
	int a[10] = {10,5,7,8,9,3,6,4,2,1};
	sort(a,0,9);
	int ff;
	for(ff = 0;ff < 10;ff ++){
		printf("a[%d] = %d\n",ff,a[ff]);
	}
	return 0;
}
