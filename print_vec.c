#include<stdio.h>
#include<stdlib.h>

int incpointer(int *dest, int **src, int size) {
	int i=0;
	for(;i<size;i++) { 
		dest[i] = (*src)[i];
		if((*src)[i]==0) return 0;
		//dest[i+1] = (*src)[i+1];
	}
	*src = *src + i;
	return 1;
	
}

int  *test1(int *vec)  {
	int *v = malloc(1<<12);
	int  *vv = v;
	int  size = 1;	
	while(incpointer(vv,&vec,1))  {
		size+=1;
		printf("reallocing\n");
		v = realloc(v, (1<<12) + size);
		vv = v + size - 1; //(size-1);
	}
	return v;
}
void print_vec(int *vec, int size) {
	for(int i=0;i<size;i++) {
		if(vec[i]==0) break;
		printf("%d ", vec[i]);
	}
	printf("\n");
}

int main() {
	int *v = malloc(4*20);
	for(int i=0;i<20;i++) v[i] = i+1;
	int *vec = test1(v);
	print_vec(vec,20);
	
}
