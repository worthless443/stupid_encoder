#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<signal.h>
// NOTE: This is a range based encoding, decoding is ambigious
//TODO make encoding for indiviudal chars

int reverseAscii(int i, int *vec) { 
	int dat; 
	if(!(i>vec[0] && i<vec[1])) dat = i; 
	else if(!(i>vec[2] && i<vec[3])) dat  = i ;  
	else if(!(i>vec[4] && i<vec[5])) dat = i; 
	else if(!(i>vec[6] && i<vec[7])) dat = i; 
	else if(!(i>vec[8] && i<vec[9])) dat = i; 
	return dat;
	} 


char *printAscii(int i, int *vec) { 
	char *dat; 
	if(i>vec[0] && i<vec[1]) dat = "#"; 
	else if(i>vec[2] && i<vec[3]) dat = "$";  
	else if(i>vec[4] && i<vec[5]) dat = "%"; 
	else if(i>vec[6] && i<vec[7]) dat = "&"; 
	else if(i>vec[8] && i<vec[9]) dat = "@`"; 
	else dat =  "."; 
	return dat;
	} 
void print_vec(int *vec) {
	for(int i=0;i<10;i++) {
		if(vec[i]==0) break;
		printf("%d ", vec[i]);
	}
	printf("\n");
}

int *readkey(FILE *f) {
	char *buf = malloc(sizeof(char)*60);
	int skip=6; int *vec = malloc(sizeof(int)*100);
	int ii=0;
	while(fread(buf, skip,1,f)) {
			for(int i=0;i<=skip;i+=1)  if(buf[i]==" "[0] || buf[i] == "\n"[0]) buf[i] = 1;
			for(int i=0;i<skip-2;i+=3) {
				char dat[2];
				dat[0] = buf[i];
				dat[1] = buf[i+1];
				//dat[2] = buf[i+2];
				vec[ii] = atoi(dat);
				dat[0] = 0;
				dat[1] = 0;
				ii++;
				if(ii>10) raise(SIGTERM);
				//dat[2] = 0;
			}
			//strcat(dat, (char*)&buf[i]);
			//strcat(dat, (char*)&buf[i+1]);
		}
	//printf("\n");
	return vec;
}


char *genascii(char *buf, int *vec) {
	char  *buffer = malloc(sizeof(char)*0xfff);
	for(int i=0;*(int*)(buf+i)!=0;i++) {
			strcat(buffer, printAscii(buf[i], vec));
			if(buf[i]==0) break;
		}
	return buffer;
}

void print_range(int a, int b) { for (int i=a;i<=b;i++) printf("%s ", (char*)&i);printf("\n");}
void print_range_filter(int a, int b, int *vec) { for (int i=a;i<=b;i++)  {
	int d = 	reverseAscii(i,vec);
	printf("%s ", (char*)&d);
  	printf("\n");}
}

void decode(int *vec, char *buf) { 
	for(int i=0;*(int*)(buf+i)!=0;i++) {
		if(buf[i]=="#"[0]) print_range(vec[0], vec[1]); 
		else  if(buf[i]=="$"[0]) print_range(vec[2], vec[3]); 
		else if(buf[i]=="%"[0]) print_range(vec[4], vec[5]); 
		else if(buf[i]=="&"[0]) print_range(vec[6], vec[7]); 
		else if(buf[i]=="@"[0]) print_range(vec[8], vec[9]); 
		else print_range_filter(1,125, vec);
}
}

void writeTofile(const char *fname, char *buffer)  {
	FILE *f = fopen(fname, "w");
	int i=1;
	while(fwrite(buffer,i,1,f) && *(int*)buffer!=0) { 
		buffer = buffer + i;
		i++;
	}
}

int incpointer(int *dest, int **src, int size) {
	int i=0;
	for(;i<size;i++) { 
		if((*src)[i]==0) return 0;
		dest[i] = (*src)[i];
	}
	*src = *src + i;
	return 1;
}

int *test(int *vec) {
	int *v  = malloc(1<<12);
	int *vv = v; 
	int size  = 1;
	while(incpointer(vv,&vec,1)) {
			v = realloc(v, size);
			vv = v + size - 1;
			size++;
	}
	//printf("nigger\n");
	//for(int i=1;*vv!=0;i++)  {
	//	vv = vv + 1;
		//v = realloc(v,i);
		//vv = v + (i-1);
	return v;
}

int  *test1(int *vec)  {
	int *v = malloc(1<<12);
	int  *vv = v;
	int  size = 1;	
	while(incpointer(vv,&vec,1))  {
		size+=1;
		v = realloc(v, size + (1<<12));
		vv = v + size - 1;
	}
	return v;

}
int  main(int argc, char **argv) {
	assert(argv[1]!=0);
	assert(argv[2]!=0);
	FILE *f1 = fopen(argv[2], "r");
	int *vec = readkey(f1);
	//print_vec(test(vec));
	const char *fname = argv[1];
	FILE *f = fopen(fname, "r");
	char *buf = malloc(sizeof(char)*4096);
	char *dat = buf;
	int i=1;
	//print_vec(test1(vec));
	//return 0;
	//int *juffer = malloc(1<<12);
	//int *data = buffer;
	 
	//print_vec(test1(vec));
	char buffer[1];
	while(fread(buffer,1,1,f)) {
		strcat(buf, buffer);

	}

	printf("%s\n", genascii(buf,vec));
		
		
	//writeTofile("out.txt",buffer);
	//decode(vec,buffer);
	return 0;
}
