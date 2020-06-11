/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int **a);	//초기화
int freeArray(int *a);		//동적할당 해제
void printArray(int *a);	//배열을 프린트

int selectionSort(int *a);	//선택정렬
int insertionSort(int *a);	//삽입 정렬
int bubbleSort(int *a);		//버블 정렬
int shellSort(int *a);		//셸 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n);	//퀵 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;	//입력받은 명령어를 저장할 변수
	int *array = NULL;	//배열을 저장할 포인터 변수
	int *hashtable = NULL;	//hashtable을 저장할 포인터 변수
	int key = -1;		//찾기 위해 입력받은 수를 저장할 변수
	int index = -1;		//반환된 값을 저장하기 위한 변수

	srand(time(NULL));

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);	//초기화
			break;
		case 'q': case 'Q':
			freeArray(array);	//동적메모리 해제하고 종료
			break;
		case 's': case 'S':
			selectionSort(array);	//선택정렬
			break;
		case 'i': case 'I':
			insertionSort(array);	//삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array);	//버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array);		//셸정렬
			break;
		case 'k': case 'K':		//퀵 정렬
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':		//해싱
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);		//해시테이블을 만들기 위해 hashing 함수 호출
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);		//찾기 위한 키 입력
			printArray(hashtable);
			index = search(hashtable, key);		//key의 index를 찾기 위해 search 함수 호출
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');		//q를 누르면 종료

	return 1;
}

int initialize(int** a)		//초기화
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)	//동적메모리 해제
{
	if (a != NULL)	//a가 NUL이 아니면
		free(a);	//a를 동적 해제
	return 0;
}

void printArray(int *a)		//배열 프린트
{
	//배열이 비어있을 때
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);		//배열 번호 프린트
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);	//배열의 값 프린트
	printf("\n");
}


int selectionSort(int *a)		//선택 정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);			//비교를 위해 정렬되지 않은 배열을 프린트

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		//0~MAX_ARRAY_SIZE까지 비교하여 최솟값을 찾는다.
		minindex = i;		//최소 인덱스를 i로 지정
		min = a[i];			//최솟값에는 a[i]값을 넣는다.
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)	//주어진 최솟값과 비교하여 최솟값을 찾는 장치
		{
			if (min > a[j])	//현재 최솟값이 a[j]보다 크면 현재 최솟값과 최소 인덱스를 바꿔준다.
			{
				min = a[j];	//최솟값이 a[j]가 된다.
				minindex = j;	//최소 인덱스를 j로 바꿔준다.
			}
		}
		//최솟값을 찾게되면 위치를 바꿔준다.
		a[minindex] = a[i];	//a[i]의 값을 최솟값이 있는 인덱스에 넣어주고
		a[i] = min;	//a[i]의 위치에 최솟값을 바꿔준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬된 배열을 프린트
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//정렬되기 전 배열을 프린트

	for (i = 1; i < MAX_ARRAY_SIZE; i++)	//a[0]은 정렬되어있다고 가정하기 때문에 i=1부터 시작해서 돌린다
	{
		t = a[i];	//a[i]의 값을 미리 t에 저장
		j = i;		//j에  i의 값을 넣는다.

		/*a[j-1]이 t의 값보다 크고 j가 0보다 크면
		정렬된 부분에서 정렬을 해준다.*/
		while (a[j - 1] > t && j > 0)
		{
			a[j] = a[j - 1];	//a[j]에 a[j-1]의 값을 넣고
			j--;	//j에서 값을 하나 빼준다.
		}
		a[j] = t;	//a[j]에 t의 값을 넣는다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬된 배열 프린트

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//비교를 위해 정렬되지 않은 배열을 프린트

	for (i = 0; i < MAX_ARRAY_SIZE; i++)	//0~MAX_ARRAY_SIZE까지 돌리면서 최댓값을 마지막 번호로 보낸다.
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)	//j=0 부터 돌리면서 자리를 교환한다.
		{
			if (a[j - 1] > a[j])	//배열 앞 번호의 값이 뒷번호의 값보다 크면 앞 번호의 값을 뒤로 보내주기 위한 조건
			{
				t = a[j - 1];	//t에 a[j-1] 값을 먼저 저장을 해주고

				//a[j-1]값과 a[j]의 위치를 바꿔준다.
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬된 배열을 프린트

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//정렬 전 배열 프린트

	/* h에 부분집합 기준이 되는 간격을 넣기 위해 1/2씩 감소시킨다,
		h만큼 거리에 있는 배열의 값을 비교하여 정렬한다.*/
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)	//정렬을 한단계 끝낼 동안 전체적으로 돌기 위한 조건
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)	//한개의 배열과 한개의 배열을 비교하기 위한 조건
			{
				v = a[j];	//v에 a[j]의 값을 저장
				k = j;		//k에 j의 값을 넣는다.

				/*k의 값이 h-1보다 크고 a[k-h]의 값이 v보다 크면
					a[k]와 a[k-h]의 값을 바꿔준다.*/
				while (k > h - 1 && a[k - h] > v)
				{

					a[k] = a[k - h];	//a[k]에 a[k-h]의 값을 넣어놓고
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬된 배열을 프린트

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n - 1];		//pivot이 된다. 맨 처음에 제일 끝 원소를 선택한다
		i = -1;				//첫번째 원소부터 돌리기 위해 지정
		j = n - 1;			//마지막 번째 원소부터 돌리기 위해 지정


		while (1)
		{

			while (a[++i] < v);	//pivot보다 값이 작을 동안
			while (a[--j] > v);	//pivot보다 값이 클 동안

			//i>가 j보다 크거나 같으면 while문을 빠져 나온다.
			if (i >= j) break;

			//pivot을 기준으로 왼쪽이 작게, 오른쪽이 크도록 정렬하기 위해 a[i]와 a[j]의 값을 바꿔준다.
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		//pivot의 위치를 바꿔준다
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i);	//pivot의 왼쪽 부분을 재귀를 통해 정렬
		quickSort(a + i + 1, n - i - 1);	//pivot의 오른쪽 부분을 재귀를 통해 정렬
		//printArray(a, MAX_ARRAY_SIZE);
	}


	return 0;
}

int hashCode(int key) {
	return key % MAX_HASH_TABLE_SIZE;	//key값을 MAX_HASH_TABLE_SIZE로 나눴을 때 나온 나머지 값을 반환한다.
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;		//hashtable의 값들을 -1로 초기화한다

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];		//a[i]의 값을 key에 저장
		hashcode = hashCode(key);	//hashCode함수를 호출해 받은 값을 hashcode에 저장한다.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)		//hashtable의 버킷이 비어있을 때
		{
			hashtable[hashcode] = key;		//hashtable[hashcode]에 key 값을 넣는다.
		}
		else {

			index = hashcode;		//index에 hashcode 값을 저장한다.

			while (hashtable[index] != -1)	//hashtable[index]가 비어있지 않는 동안 반복
			{
				//hashtable에 비어있는 부분을 찾기 위해 index에 나머지 값을 새로 대입해서 찾는다.
				index = (++index) % MAX_HASH_TABLE_SIZE;

				/*
				printf("index = %d\n", index);
				*/
			}
			//hashtable[index]에 key값을 저장한다.
			hashtable[index] = key;

		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);		//hashCode함수를 호출해서 받은 값을 index에 저장

	if (ht[index] == key)	//hash table에 index위치에 있는 값이 key 값과 같으면
		return index;		//index를 반환한다.

	while (ht[++index] != key)		//hash table에서 key 값이 같지 않는 동안 반복한다.
	{
		//index의 나머지값을 구해 index에 새로 저장해 key 값을 찾는다.
		index = index % MAX_HASH_TABLE_SIZE;
	}
	//key 값과 같은 index 위치를 찾으면 index 반환
	return index;
}
