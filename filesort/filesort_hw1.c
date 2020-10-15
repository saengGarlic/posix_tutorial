#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Row{
	int age;
	char name[4];
	char ziphead[3];
	int zip;
}Row;

void mergesort_age(Row *arr, int s, int e);
void mergesort_name(Row *arr, int s, int e);
void mergesort_zip(Row *arr, int s, int e);


int main()
{
	Row *row_arr, *temp;
	Row tmp;
	int lineNum, i;
	char c;
	FILE *fp;
	
	int ageMax, ageMin, zipMax, zipMin;
	int ageInterval, zipInterval, ageDistNum, zipDistNum;
	int nameNum;
	int *ageDist, *zipDist, *nameList;
	
	
	fp = fopen("data.txt", "r");
	
	//line 수 확인
	lineNum = 0;
	while((c = fgetc(fp))!=EOF){
		if(c=='\n') lineNum++;
	}
	printf("total line:%d\n",lineNum);
		
	ageInterval = 10;
	zipInterval = 1;
	nameNum = 0;
	ageMin = 100;
	zipMin = 20;
	ageMax = 0;
	zipMax = 0;
	
	
	row_arr = (Row *)malloc(sizeof(Row)*lineNum);
	temp = row_arr;
	if(row_arr != NULL) printf(">>memory allocation success\n");
	
	rewind(fp);
	for(i = 0; i<lineNum; i++){
		fscanf(fp, "%2d,%3s,%2s%3d", &(temp+i)->age, &(temp+i)->name, &(temp+i)->ziphead, &(temp+i)->zip);
	}
	
	//분포 초기화할 패러미터들 세팅
	rewind(fp);
	for(i = 0; i<=lineNum; i++){
		fscanf(fp, "%2d,%3s,%2s%3d", &tmp.age, &tmp.name, &tmp.ziphead, &tmp.zip);
		if(tmp.age < ageMin) ageMin = tmp.age - tmp.age%ageInterval;
		if(tmp.zip < zipMin) zipMin = tmp.zip;
	}
	rewind(fp);
	for(i = 0; i<=lineNum; i++){
		fscanf(fp, "%2d,%3s,%2s%3d", &tmp.age, &tmp.name, &tmp.ziphead, &tmp.zip);
		if(tmp.age > ageMax) ageMax = tmp.age/ageInterval * ageInterval;
		if(tmp.zip > zipMax) zipMax = tmp.zip;
	}
	
	ageDistNum = (ageMax - ageMin)/ageInterval + 1;
	zipDistNum = (zipMax - zipMin)/zipInterval + 1;
	ageDist = (int*)malloc(sizeof(int)*ageDistNum);
	zipDist = (int*)malloc(sizeof(int)*zipDistNum);
	
	//분포 배열 초기화
	for(i = 0; i < ageDistNum; i++){
		*(ageDist + i) = 0;
	}
	for(i = 0; i < zipDistNum; i++){
		*(zipDist + i) = 0;
	}
	printf("age %d/%d, ageDistNum %d, zip %d/%d, zipDistNum %d\n\n", ageMin, ageMax, ageDistNum, zipMin, zipMax, zipDistNum);
	
	
	//이름기준 오름차순 정렬
	mergesort_name(temp, 0, lineNum-1);
	
	fp = fopen("sorted_byname.txt", "w");
	for(i = 0; i < lineNum; i++){
		fprintf(fp, "%2d,%3s,%2s%03d\n", (temp+i)->age, (temp+i)->name, (temp+i)->ziphead, (temp+i)->zip);	
		if(i == 0) nameNum++;
		else if(strcmp((temp+i-1)->name, (temp+i)->name) != 0) nameNum++;
	}
	printf("전체 데이터 갯수 %d개 중 이름은 %d개\n\n", lineNum, nameNum);
	fclose(fp);
	
	
	//나이기준 오름차순 정렬
	mergesort_age(temp, 0, lineNum-1);
	
	fp = fopen("sorted_byage.txt", "w");
	for(i = 0; i < lineNum; i++){
		fprintf(fp, "%2d,%3s,%2s%03d\n", (temp+i)->age, (temp+i)->name, (temp+i)->ziphead, (temp+i)->zip);			
		*(ageDist + ((temp+i)->age - (temp+i)->age%ageInterval)/ageInterval - 1) += 1;
	}
	fclose(fp);
	
	//주소기준 오름차순 정렬
	mergesort_zip(temp, 0, lineNum-1);
	
	fp = fopen("sorted_byzip.txt", "w");
	for(i = 0; i < lineNum; i++){
		fprintf(fp, "%2d,%3s,%2s%03d\n", (temp+i)->age, (temp+i)->name, (temp+i)->ziphead, (temp+i)->zip);			
		*(zipDist + (temp+i)->zip - 1) += 1;
	}
	fclose(fp);
	
	//output.txt 출력
	fp = fopen("output.txt", "w");
	
	fprintf(fp, "전체 데이터 갯수 %d개 중 이름은 %d개\n\n", lineNum, nameNum);
	fprintf(fp, "나이\n\n");
	printf("나이:\n\n");
	for(i = 1; i < ageDistNum+1; i++){
		fprintf(fp, "%d ~ %d : %d 명\n\n", i*ageInterval, (i+1)*ageInterval, *(ageDist+i-1));
		printf("%d ~ %d세: %d명\n\n", i*ageInterval, (i+1)*ageInterval, *(ageDist+i-1));
	}
	fprintf(fp, "Zip code\n\n");
	printf("Zip code\n\n");
	for(i = 1; i < zipDistNum+1; i++){
		fprintf(fp, "%s%03d : %d 명\n\n", tmp.ziphead, i*zipInterval, *(zipDist+i-1));
		printf("%s%03d : %d명\n\n", tmp.ziphead, i*zipInterval, *(zipDist+i-1));
	}
	fclose(fp);
	
	free(row_arr);
	free(ageDist);
	free(zipDist);
	
	
}


void rowinsert(Row* target, Row* source, int tn, int sn){
	
	(target + tn)->age = (source + sn)->age;
	strcpy((target + tn)->name, (source + sn)->name);
	strcpy((target + tn)->ziphead, (source + sn)->ziphead);
	(target + tn)->zip = (source + sn)->zip;
}

void merge_age(Row *arr, int s, int e, int m){
	
	int i = s;
	int j = m + 1;
	int n = 0;
	int size = e - s + 1;
	Row *temp_arr, *temp;
	
	temp_arr = (Row*)malloc(sizeof(Row)*size);
	temp = temp_arr;
	
	//printf("merge_age called from %d to %d of size:%d\n", s, e, size);
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
			if((arr+i)->age < (arr+j)->age){
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
	
	//printf("merge_name called from %d to %d of size:%d\n", s, e, size);
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
			if(strcmp((arr+i)->name, (arr+j)->name) > 0){
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
	
	//printf("merge_zip called from %d to %d of size:%d\n", s, e, size);
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
	}
	
	//원래배열에 집어넣기
	n = 0;
	for(i = s; i <= e; i++){
		rowinsert(arr, temp, i, n);
		n++;
	}
	
	free(temp);
		
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