#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 20
#define FALSE 0
#define TRUE 1

typedef struct Vertex{
	int num;
	struct Vertex* link;
}Vertex;

typedef struct VertexHead {
	Vertex* Head;
}VertexHead;

typedef struct Graph {
	VertexHead* vlist;
}Graph;

void createGraph(VertexHead** v);			//그래프 생성
int destroyGraph(VertexHead* v);			//그래프 삭제
int insertVertex(VertexHead *v, int key);	//정점 삽입
int deleteVertex(VertexHead *v, int key);	//정점 삭제
int insertEdge(VertexHead *v, int key1, int key2);//간선 삽입
int DeleteEdge(VertexHead *v, int key1, int key2);//간선 삭제
void depthFS(VertexHead *v, int key);			//깊이 우선 탐색
void breadthFS(int key, VertexHead *v);		//너비 우선 탐색
void printGraph(VertexHead *v);		//그래프
void push(Vertex* st);		//stack 값을 넣는 함수
void addq(int i, int item);	//queue 값을 넣는 함수
Vertex *pop();		//stack 값을 비우는 함수
int deleteq(int i);	//queue 값을 비우는 함수
/*stack*/
Vertex* stack[MAX_VERTEX];
int top = -1;

/*queue*/
Vertex* front[MAX_VERTEX];
Vertex* rear[MAX_VERTEX];

int main()
{

	char command;	//사용자에게 입력받은 명령어를 구분
	int key1;		//사용자가 입력할 값1
	int key2;		//사용자가 입력할 값2
	int result;		//함수로부터 반환받은 값 저장할 변수
	VertexHead* vlist = NULL;		//vlist

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                            Graph                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph	          = c                                       \n");
		printf(" print Graph		  = p      Delete Edge             = x \n");
		printf(" Insert Vertex		  = i      depth First Search	   = f \n");
		printf(" delete Vertex		  = d      breadth Firsth Search   = b \n");
		printf(" inseert Edge		  = e      Quit                    = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'c': case 'C':		//그래프 생성
			createGraph(&vlist);
			break;
		case 'i': case 'I':			//정점 삽입
			printf("Your Key = ");
			scanf("%d", &key1);
			insertVertex(vlist, key1);
			break;
		case 'd': case 'D':			//정점 삭제
			printf("Your Key = ");
			scanf("%d", &key1);
			deleteVertex(vlist, key1);
			break;
		case 'e': case 'E':			//간선 삽입
			printf("Your Key1 = ");
			scanf("%d", &key1);
			printf("Your Key2 = ");
			scanf("%d", &key2);
			insertEdge(vlist, key1, key2);
			break;
		case 'x': case 'X':		//간선 삭제
			printf("Your Key = ");
			scanf("%d", &key1);
			printf("Your Key = ");
			scanf("%d", &key2);
			result=DeleteEdge(vlist, key1, key2);
			if (result == 1)
				printf("찾을 수가 없습니다.");
		case 'f': case 'F':		//깊이 우선 탐색
			printf("Your Key = ");
			scanf("%d", &key1);
			depthFS(vlist , key1);
			break;
		case 'b': case 'B':		//너비 우선 탐색
			printf("Your Key = ");
			scanf("%d", &key1);
			breadthFS(key1, vlist);
			break;
		case 'p': case 'P':		//그래프 프린트
			printGraph(vlist);
			break;
		case 'q': case 'Q':
			destroyGraph(vlist);	//그래프 삭제 후 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');
}


void createGraph(VertexHead** v)
{
	if (*v != NULL)		//만약 그래프가 비어있지 않다면
	{
		destroyGraph(*v);	//그래프를 삭제해준다.
	}

	*v = (VertexHead*)malloc(sizeof(Vertex));	//vlist에 동적할당


	for (int i = 0; i < MAX_VERTEX; i++)		//MAX_VERTEX만큼 돌린다.
	{
		(*v + i)->Head = (Vertex*)malloc(sizeof(Vertex));	//vlist 각 번호의 head에 동적 할당
		(*v + i)->Head ->link= (Vertex*)malloc(sizeof(Vertex));
		(*v + i)->Head->link = NULL;
		(*v + i)->Head = NULL;	//head를 NULL로 지정해줌

	}
}

int destroyGraph(VertexHead* v)
{
	Vertex *h = v->Head;	//vlist의 head
	Vertex *prev = NULL;
	int i = 0;
	//h가 비어있을 때
	if (h == NULL)
	{
		free(h);
		return 0;
	}

	if (h->link != NULL)
	{
		while (h != NULL)
		{
			while (h->link != NULL)
			{
				prev = h->link;
				h->link = prev->link;
				free(prev);
			}
			i++;
			h = (v + i)->Head;
		}
		return 0;
	}
}

int insertVertex(VertexHead *v, int key)
{
	int i = 0;

	Vertex *h = (Vertex*)malloc(sizeof(Vertex));	//h에 동적할당
	h->num = key; //h의 num값에 key 값을 넣는다.

	if (v == NULL)	//그래프가 안 만들어져 있을 경우 출력
	{
		printf("먼저 그래프를 만드세요.");
		return 0;
	}

	while (1)
	{
		if ((v+i)->Head == NULL)		//(v+i)의 Head가 NULL이라면
		{
			//vlsit에 h를 새로 삽입한다.
			(v+i)->Head= h;
			(v + i)->Head->link = NULL;  //(v+i)->Head->link는 NULL로 초기화해준다.
			return 0;
		}
		//NULL이 아니면 다음 값을 넘어간다.
		i++;
	}
	return 0;
}

int deleteVertex(VertexHead *v , int key)
{
	Vertex *temp = v->Head;		//temp에 v->Head값을 임시 저장
	Vertex *del = v->Head;		//del에 v->Head값을 임시 저장
	VertexHead *p =v;		//p에 v 값을 임시 저장
	int i = 0;	//temp값을 찾을 때
	int j = 0;	//간선을 찾을 때

	while (temp != NULL)	//temp가 NLLL이 되면 중지
	{
		if (temp->num == key)	//temp의 값이 key값과 같으면
		{
			//key값과 간선을 이루는 정점을 찾아 연결을 해제해준다.
			while (del != NULL)
			{
				if (key != del->num)	//key값과 del->num의 값이 같지 않으면
					DeleteEdge(v, key, del->num);	//간선이 있으면 삭제한다.
				j++;
				del = (v + j)->Head;	//vlist의 그 다음값으로 넘어간다.
			}

			//이제 해당 정점을 삭제한다.
				while (1)
				{
					//해당 정점의 위치를 찾는다.
					if (p->Head->num == temp->num)
					{
						//해당 값을 삭제하고 다음 값들을 앞의 위치로 옮겨준다.
						while (p->Head != NULL)
						{
							p->Head = (p + 1)->Head;	//앞으로 옮겨주고
							p = p + 1;	//다음 값으로 넘어가서 반복
						}
						//모든 값의 위치를 옮기면
						free(temp);	//해당 값을 동적 해제
						break;
					}
					else
					{
						//못찾을 경우 다음 값으로 넘어간다.
						p = p + 1;
					}
				}
			return 0;
		}
		else
		{
			//key값을 못찾으면 다음 값으로 넘어간다.
			i++;
			temp = (v + i)->Head;
		}
	}
	//key값을 못찾고 while문을 빠져나왔을 때 명시
	printf("key 값을 찾을 수 없습니다.");
	return 0;
}

int insertEdge(VertexHead *v , int key1, int key2) {

	Vertex *h = v->Head;		//v->Head를 h에 임시 저장
	Vertex *h2 =v->Head;		//v->Head를 h2에 임시 저장
	int i = 0;
	int temp = 0;
	/*
	작은 값을 계산하고 큰 값을 뒤에 계산하기 때문에
	첫번째 값이 더 큰 경우 두번째 값과 위치를 바꿔준다.
	*/
	if (key1 > key2)
	{
		temp = key1;
		key1 = key2;
		key2 = temp;
	}

	//첫번째 값이 있는지를 찾는다.
	while (h != NULL)
	{
		if (h->num == key1)	//찾으면 멈춘다.
		{
			break;
		}
		else
		{
			//못찾으면 다음으로 넘어가 값을 찾는다.
			i++;
			h = (v + i)->Head;
		}
	}

	//값을 찾지 못하고 while문에서 빠져나왔을 경우
	if (h == NULL)
	{
		printf("key 값을 찾을 수 없습니다.");	//값을 찾을 수 없음을 명시하고 리턴
		return 0;
	}

	//두번째 값이 존재하는지 찾는다.
	while (h2 != NULL)
	{
		if (h2->num == key2)	//h2->num이 key값하고 같으면 반복을 멈춘다
		{
			break;
		}
		else
		{
			i++;		//아니면 다음 값으로 넘어가서 반복
			h2 = (v + i)->Head;
		}
	}
	//key값을 찾지 못하고 while문 밖으로 나왔을 때
	if (h2 == NULL)
	{
		printf("key 값을 찾을 수 없습니다.");	//key값을 찾지 못함을 명시
		return 0;
	}

	//h11과 h21에 동적할당을 해 key1, key2값을 넣어준다.
	//간선이 이미 존재하는지를 알아보기 위한 변수다.
	Vertex *h11 = (Vertex*)malloc(sizeof(Vertex));
	Vertex *h21 = (Vertex*)malloc(sizeof(Vertex));
	h11->num = key1;
	h21->num = key2;

	while (h->link != NULL)		//h->link가 NULL이 되면 중지
	{
		h = h->link;
		if (h->num == key2)//key2값이 이미 h->link에 존재한다면
		{
			printf("이미 있습니다.");	//존재함을 명시하고 return
			return 0;
		}
	}

	h->link = h21;	//h->link값에 h21을 넣고
	h21->link = NULL;//h21->link에 NULL값을 넣는다.

	while (h2->link != NULL)		//h2->link가 NULL이 되면 중지
	{
		h2 = h2->link;
		if (h2->num == key1)//key1값이 이미 h2->link에 존재한다면
		{
			printf("이미 있습니다.");	//존재함을 명시하고 return
			return 0;
		}
	}

	h2->link = h11;		//h2->link값에 h21을 넣고
	h11->link = NULL;	//h11->link에 NULL값을 넣는다.

	return 0;
}

int DeleteEdge(VertexHead *v, int key1, int key2)
{

	Vertex *h1 = v->Head;	//key1
	Vertex* h2 = NULL;		//key2
	Vertex* prev1 = NULL;	//이전값1
	Vertex* prev2 = NULL;	//이전값2
	int i = 0;
	int temp;


	if (v == NULL)	//그래프가 안 만들어져 있을 경우 출력
	{
		printf("먼저 그래프를 만드세요.");
		return 0;
	}

	/*
	작은 값을 계산하고 큰 값을 뒤에 계산하기 때문에
	첫번째 값이 더 큰 경우 두번째 값과 위치를 바꿔준다.
	*/
	if (key1 > key2)
	{
		temp = key1;
		key1 = key2;
		key2 = temp;
	}

	while (h1 != NULL)	//h1이 NULL이 되면 반복 중지
	{
		if (h1->num == key1)	//h->num이 key1값과 같으면
		{
			prev1 = h1;		//h1을 prev에 미리 저장하고
			while (h1->num != key2)		//h1->num이 key2값과 같으면 반복 중지
			{
				prev1 = h1;		//prev1에 h1값을 저장하고
				h1 = h1->link;	//h1은 다음으로 넘어간다.

				if (h1 == NULL)	//만약 h1이 NULL이 되면 1을 반환해 간선이 없음을 명시해준다.
					return 1;
			}
			//찾으면 while문을 빠져나온다.
			break;
		}
		else
		{
			//key1값을 찾지 못하면 다음 값으로 넘어간다.
			h1 = (v + i)->Head;
			i++;
		}
	}
	//key1값을 찾지 못하고 while문을 그대로 빠져나오면
	if (h1 == NULL)
	{
		printf("존재하지 않습니다.\n");		//존재하지 않음을 명시하고 반환
		return 0;
	}
	//만약 key1과 key2값을 찾으면 prev1의 link를 h1의 link와 연결한 뒤
	prev1->link = h1->link;
	free(h1);	//h1은 동적해제한다

	h2 = (v + i)->Head;	//h2는 vlist의 마지막 위치를 이어서 찾는다.

	while (h2 != NULL)	//h2가 NULL이되면 중지
	{
		if (h2->num == key2)	//key2값을 찾으면
		{
			prev2 = h2;		//prev2에 h2를 넣고
			while (h2->num != key1)	//h2의 num값과 key1의 값이 같으면 반복 중지
			{
				prev2 = h2;	//prev2에 h2값을 저장하고
				h2 = h2->link;	//h2는 다음 링크로 넘겨줌
				if (h2 == NULL)	//h2가 NULL이되면
					return 1;	//1을 반환해 찾지 못함을 명시
			}
			//찾으면 while문을 빠져나온다.
			break;
		}
		else
		{
			//key2 값을 찾지 못하면 h2의 값을 다음으로 넘겨 찾아준다.
			h2 = (v + i)->Head;
			i++;
		}
	}
	//key값을 찾지 못하고 while 문을 그대로빠져나왔을 경우
	if (h2 == NULL)
	{
		printf("존재하지 않습니다.\n");	//존재하지 않음을 명시하고 return
		return 0;
	}

	prev2->link = h2->link;		//prev2의link에 h2의 link를 연결하고
	free(h2);		//h2는 동적해제한다.

	return 0;
}

void depthFS(VertexHead*v, int key)
{
	Vertex *w;
	w = (Vertex*)malloc(sizeof(Vertex));
	int visited[MAX_VERTEX] = {0};
	int i = 0;

	while ((v + i)->Head != NULL)
	{
		if ((v + i)->Head->num == key)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	if ((v + i)->Head == NULL)
	{
		printf("값을 찾을 수가 없습니다.\n");
		return;
	}

	i = 0;

	visited[key] = TRUE;
	printf("%5d", key);



}
void breadthFS(int key, VertexHead* v) {

	Vertex *w;
	int *visited = (int*)malloc(sizeof(int));
	int i = 0;
	int j = 0;

	while ((v + i)->Head != NULL)
	{
		if ((v + i)->Head->num == key)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	if ((v + i)->Head == NULL)
	{
		printf("값을 찾을 수가 없습니다.\n");
		return 0;
	}

	i = 0;

	printf("%5d", key);
	visited[key] = TRUE;
	addq(j, key);
	while ((v+i)->Head!=NULL)
	{
		key = deleteq(j);
		printf(" c " );
		for (w = (v + i)->Head; w != NULL; w = w->link)
		{
			printf(" c ");
			if (visited[w->num] == NULL)
			{
				j++;
				printf("%5d", w->num);
				addq(j, w->num);
				visited[w->num] = TRUE;
			}
		}
		i++;
	}
}
void push(Vertex* st)
{
	if (top == (MAX_VERTEX - 1))
	{
		printf("stack is full\n");
		return;
	}
	top++;
	stack[top] = st;
}

void addq(int i, int item)
{
	Vertex *temp = (Vertex*)malloc(sizeof(Vertex));
	//MALLOC(temp, sizeof(*temp));
	temp->num = item;
	temp->link = NULL;

	if (front[i])
	{
		rear[i]->link = temp;
	}
	else
	{
		front[i] = temp;
	}
	rear[i] = temp;
}

Vertex *pop()
{
	if(top==-1)
	{
		return NULL;
	}
	return stack[top--];
}

int deleteq(int i)
{
	Vertex* temp = front[i];
	int item;

	if (!temp)
	{
		printf("queue는 비어있음");
		return;
	}

	item = temp->num;
	front[i] = temp->link;
	free(temp);

	return item;

}
void printGraph(VertexHead *v)
{
	int i = 0;
	Vertex *temp;

	if (v == NULL)
	{
		printf("no print\n");	//비어있으면 no print 출력
	}

	while((v+i)->Head != NULL)
	{
		printf("[%d]=%d ",i, (v + i)->Head->num);	//vlist의 head 부분을 인덱스와 함께 출력
		temp = (v + i)->Head->link;		//temp에 vlistd의 헤드의 링크를 저장
		if ((v + i)->Head->link != NULL)	//만약 link가 NULL이 아닐 때
		{
			while (temp != NULL)	//temp가 NULL이 되면 중지
			{
				printf("-> %d ", temp->num);	//link값을 출력해준다.
				temp = temp->link;	//temp는 다음 link로 넘어간다.
			}
		}

		i++;	//vlist의 다음 값을 출력
		printf("\n");

	}

}

