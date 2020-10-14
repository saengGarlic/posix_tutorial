/*
1. 라즈베리파이와 컴퓨터를 연결하여 ssh 구동 가능
2. 첨부의 파일을 읽어서 다음의 프로그램을 구현하시오.

나이별, 이름별, 지역별(zip code) 분포를 구하시오.

순서는 숫자, 알파벳 오름차순으로 정리

나이 : 10 ~ 89
zip code : 001 ~ 015

---------------------------
파일 내용

24,ABC,KS003

32,BCD,KS005

...

----------------------------

 

결과 출력 예제


전체 데이터 갯수 1,000,000개 중 이름은 xx,xxx개
나이:

10 ~ 19 : 3,423명

20 ~ 29 : 5,333명

..

80 ~ 89 : xxx명

 

Zip code

KS001: xxxxx명

KS002: xxxxx명

...

KS015: xxxxx명
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <pthread.h>


typedef struct Row{
	int age;
	char name[4];
	char ziphead[3];
	int zip;
}Row;

void mergesort(Row *arr, int s, int e);
void mergesort_age(Row *arr, int s, int e);
void mergesort_name(Row *arr, int s, int e);
void mergesort_zip(Row *arr, int s, int e);



int main()
{
	Row *row_arr, *temp;
	
	int lineNum, i;
	char c;
	FILE *fp;
	
	
	fp = fopen("data.txt", "r");
	
	if(fp != NULL) printf(">>file import success\n");
	
	//line 수 확인후 임시 구조체 메모리 동적할당
	lineNum = 0;
	while((c = fgetc(fp))!=EOF){
		if(c=='\n') lineNum++;
	}
	printf("total line:%d\n",lineNum);
	
	row_arr = (Row *)malloc(sizeof(Row)*lineNum);
	temp = row_arr;
	if(row_arr != NULL) printf(">>memory allocation success\n");
	
	rewind(fp);
	
	//temp 
	i = 0;
	while(i<lineNum){
		fscanf(fp, "%2d,%3s,%2s%3d", &(temp+i)->age, &(temp+i)->name, &(temp+i)->ziphead, &(temp+i)->zip);
		i++;
	}
	fclose(fp);	
	
	//mergesort_age(temp, 0, lineNum-1);
	mergesort_name(temp, 0, lineNum-1);
	//mergesort_zip(temp, 0, lineNum-1);
	//mergesort(temp, 0, lineNum-1);
	
	//output.txt에 write
	fp = fopen("output.txt", "w");
	i = 0;
	while(i < lineNum){
		fprintf(fp, "%2d,%3s,%2s%3d\n", (temp+i)->age, (temp+i)->name, (temp+i)->ziphead, (temp+i)->zip);
		i++;
	}
	fclose(fp);
	free(row_arr);
	
}

void getminmax(

void rowinsert(Row* target, Row* source, int tn, int sn){
	
	(target + tn)->age = (source + sn)->age;
	strcpy((target + tn)->name, (source + sn)->name);
	strcpy((target + tn)->ziphead, (source + sn)->ziphead);
	(target + tn)->zip = (source + sn)->zip;
}

//s: start e:end 
void merge(Row *arr, int s, int e, int m){
	
	int i = s;
	int j = m + 1;
	int n = 0;
	int size = e - s + 1;
	Row *temp_arr, *temp;
	
	temp_arr = (Row*)malloc(sizeof(Row)*size);
	temp = temp_arr;
	
	printf("merge called from %d to %d of size:%d\n", s, e, size);
	while((i <= m) || (j <= e)){
		if(i > m){
			rowinsert(temp, arr, n, j);
			n++;
			j++;
		}
		else if(j > e){
			rowinsert(temp, arr, n, i);
			n++;
			i++;
		}
		else{
			if((arr+i)->age == (arr+j)->age){
				if(strcmp((arr+i)->name, (arr+j)->name) == 0){								
					if((arr+i)->zip < (arr+j)->zip){
						rowinsert(temp, arr, n, i);
						n++;
						i++;
					}
					else{
						rowinsert(temp, arr, n, j);
						n++;
						j++;
					}
				}
				else if(strcmp((arr+i)->name, (arr+j)->name) < 0){
					rowinsert(temp, arr, n, i);
					n++;
					i++;
				}
				else{
					rowinsert(temp, arr, n, j);
					n++;
					j++;
				}
			}
				
			else if((arr+i)->age < (arr+j)->age){
				rowinsert(temp, arr, n, i);
				n++;
				i++;
			}
			else{
				rowinsert(temp, arr, n, j);
				n++;
				j++;
			}
		}
	}
	
	//원래배열에 집어넣기
	n = 0;
	for(i = s; i <= e; i++){
		rowinsert(arr, temp, i, n);
		n++;
	}
	
	free(temp);
		
}

void merge_age(Row *arr, int s, int e, int m){
	
	int i = s;
	int j = m + 1;
	int n = 0;
	int size = e - s + 1;
	Row *temp_arr, *temp;
	
	temp_arr = (Row*)malloc(sizeof(Row)*size);
	temp = temp_arr;
	
	printf("merge called from %d to %d of size:%d\n", s, e, size);
	while((i <= m) || (j <= e)){
		if(i > m){
			rowinsert(temp, arr, n, j);
			n++;
			j++;
		}
		else if(j > e){
			rowinsert(temp, arr, n, i);
			n++;
			i++;
		}
		else{
			if((arr+i)->age == (arr+j)->age)
			
			else if((arr+i)->age < (arr+j)->age){
				rowinsert(temp, arr, n, i);
				n++;
				i++;
			}
			else{
				rowinsert(temp, arr, n, j);
				n++;
				j++;
			}
		}
	}
	
	//원래배열에 집어넣기
	n = 0;
	for(i = s; i <= e; i++){
		rowinsert(arr, temp, i, n);
		n++;
	}
	
	free(temp);
		
}

void merge_name(Row *arr, int s, int e, int m){
	
	int i = s;
	int j = m + 1;
	int n = 0;
	int size = e - s + 1;
	Row *temp_arr, *temp;
	
	temp_arr = (Row*)malloc(sizeof(Row)*size);
	temp = temp_arr;
	
	printf("merge called from %d to %d of size:%d\n", s, e, size);
	while((i <= m) || (j <= e)){
		if(i > m){
			rowinsert(temp, arr, n, j);
			n++;
			j++;
		}
		else if(j > e){
			rowinsert(temp, arr, n, i);
			n++;
			i++;
		}
		else{			
			if(strcmp((arr+i)->name, (arr+j)->name) == 0)
			
			else if(strcmp((arr+i)->name, (arr+j)->name) < 0){
				rowinsert(temp, arr, n, i);
				n++;
				i++;
			}
			else{
				rowinsert(temp, arr, n, j);
				n++;
				j++;
			}
			
		}
	}
	
	//원래배열에 집어넣기
	n = 0;
	for(i = s; i <= e; i++){
		rowinsert(arr, temp, i, n);
		n++;
	}
	
	free(temp);
		
}

void merge_zip(Row *arr, int s, int e, int m){
	
	int i = s;
	int j = m + 1;
	int n = 0;
	int size = e - s + 1;
	Row *temp_arr, *temp;
	
	temp_arr = (Row*)malloc(sizeof(Row)*size);
	temp = temp_arr;
	
	printf("merge called from %d to %d of size:%d\n", s, e, size);
	while((i <= m) || (j <= e)){
		if(i > m){
			rowinsert(temp, arr, n, j);
			n++;
			j++;
		}
		else if(j > e){
			rowinsert(temp, arr, n, i);
			n++;
			i++;
		}
		else{										
			if((arr+i)->zip == (arr+j)->zip){
				
			else if((arr+i)->zip < (arr+j)->zip){
				rowinsert(temp, arr, n, i);
				n++;
				i++;
			}
			else{
				rowinsert(temp, arr, n, j);
				n++;
				j++;
			}
		}
	}
	
	//원래배열에 집어넣기
	n = 0;
	for(i = s; i <= e; i++){
		rowinsert(arr, temp, i, n);
		n++;
	}
	
	free(temp);
		
}


void mergesort(Row *arr, int s, int e){
	if(s<e){
		int m = (s+e)/2;
		
		mergesort(arr, s, m);
		mergesort(arr, m+1, e);
		
		merge(arr, s, e, m);
	}
}

void mergesort_age(Row *arr, int s, int e){
	if(s<e){
		int m = (s+e)/2;
		
		mergesort_age(arr, s, m);
		mergesort_age(arr, m+1, e);
		
		merge_age(arr, s, e, m);
	}
}

void mergesort_name(Row *arr, int s, int e){
	if(s<e){
		int m = (s+e)/2;
		
		mergesort_name(arr, s, m);
		mergesort_name(arr, m+1, e);
		
		merge_name(arr, s, e, m);
	}
}

void mergesort_zip(Row *arr, int s, int e){
	if(s<e){
		int m = (s+e)/2;
		
		mergesort_zip(arr, s, m);
		mergesort_zip(arr, m+1, e);
		
		merge_zip(arr, s, e, m);
	}
}