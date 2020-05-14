/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;


	printf("--------소프트웨어학과 2019038021 구본영---------");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	listNode *prev = NULL;	//이전값
	listNode *node = h->rlink;	//헤드 노드의 다음 노드

	while (node->rlink != h)	//노드의 다음 링크가 헤드 노드라면 반복 중지
	{
		//노드 값을 따로 저장하고 다음 노드로 옮겨 저장한 노드를 해제
		prev = node;
		node = node->rlink;
		free(prev);
	}


	free(h);	//마지막으로 헤드노드를 해제한다
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode *node = (listNode *)malloc(sizeof(listNode));	//노드 동적할당
	listNode *temp;	//임시저장할 노드를 선언
	node->key = key;	//	node의 키 값에 키를 넣는다
	temp = h;	//temp에는 헤드노드를 넣는다.

	while (temp->rlink != h)	//temp의 다음값이 헤드노드면 반복 중지
	{
		temp = temp->rlink;	//temp에 temp의 다음 노드를 넣는다
	}

	node->rlink = temp->rlink;	//node의 다음 값이 temp의 다음 값이 되도록하고
	temp->rlink = node;	//temp의 다음값에 node를 넣어준다
	node->llink = temp;	//node의 이전 노드가 temp임을 명시
	h->llink = node;	//헤드 노드의 이전 노드가 마지막 노드를 가리키게 한다.



	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode *node;
	listNode *prev = NULL;

	node = h->rlink;	//node에 헤드 노드의 다음 노드를 넣음

	if (node->rlink == h)	//노드의 다음 노드가 헤드노드일 때
	{
		//노드를 해제하고 초기화가 필요함을 알림
		free(node);
		printf("초기화 필요\n");
		return 0;
	}

	while (node->rlink != h)	//노드의 다음 노드가 헤드 노드가 되면 중지
	{
		prev = node;	//node 값을 저장하고
		node = node->rlink;	//node에는 node의 다음 노드를 저장한다
	}

	prev->rlink = h;	//이전 노드의 다음 노드가 헤드 노드가 되도록한다.
	h->llink = prev;	//헤드 노드의 왼쪽 노드가 이전노드를 향한다.
	free(node);	//node 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));

	node->key = key;	//node의 key 값에 key를 저장

	if(h->llink == h)	//만약 헤드노드가 자기 자신을 가리키면
	{
		h->rlink = node;	//헤드노드의 오른쪽 노드에 node를 넣고
		h->llink = node;	//헤드노드의 왼쪽 노드에 node를 넣는다/
		node->llink = h;	//node의 왼쪽에 헤드노드를 넣고
		node->rlink = h;	//node의 오른쪽에 헤드노드를 넣는다
	}
	else	//헤드 노드가 자신을 안 가리킬 때
	{
		node->rlink = h->rlink;	//노드의 오른쪽 노드에 헤드 노드의
		h->rlink->llink = node;	//헤드 노드의 오른쪽 노드의 왼쪽에 node를 넣는다
		node->llink = h;	//노드의 왼쪽 노드에 헤드를 넣고
		h->rlink = node;	//헤드노드의 오른쪽에 노드를 넣어 연결
	}
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode *node;
	node = h->rlink;

	h->rlink = node->rlink;	//헤드 노드에 노드의 오른쪽 노드를 넣는다
	node->rlink->llink = h;	//노드의 오른쪽 노드의 왼쪽 노드에 헤드노드를 넣는다
	free(node);	//노드 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode *node = h->rlink;
	listNode *prev = NULL;	//노드의 이전노드 저장
	listNode *temp = h;	//임시 저장

	h->llink = h->rlink;	//순서를 바꾸니 헤드노드의 왼쪽노드가 헤드 노드의 오른쪽 노드가 가리키는 것으로 바꿈

	while (node != h)	//node가 헤드노드면 중지
	{
		prev = temp;	//이전 노드 값에 temp를 넣는다
		temp = node;	//temp에 node를 넣는다
		node = node->rlink;	//노드에 노드의 다음 노드를 넣는다
		temp->rlink = prev;	//temp의 다음 노드에 이전 노드를 넣는다
		temp->llink = node;	//temp의 이전 노드는 node가 되게 한다
	}

	h->rlink = temp;	//헤드 노드의 다음 노드는 temp가 되게 한다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->llink == h)	//헤드 노드가 자기 자신을 가리킬 때
	{
		insertFirst(h, key);	//insertFirst함수 호출
		return 0;
	}

	listNode *prev = NULL;	//이전 노드 저장
	listNode *temp = h->rlink;// 임시 저장

	while (1)
	{
		if (temp->key >= key)	//temp의 key 값이 key보다 크거나 같을 때
		{
			if (temp->llink == h)	//temp의 이전 노드가 헤드 노드일 때
			{
				node->llink = h;	//node의 이전 노드에 헤드노드를 넣고
				node->rlink = temp;	//노드의 다음 노드에 temp를연결				h->rlink = node;
				temp->llink = node;	//temp의 이전 노드에 node를 연결
			}
			else
			{
				prev = temp->llink;	//prev에 temp의 이전 노드 값을 저장
				temp->llink = node;	//temp의 이전 노드에 node를 연결
				node->rlink = temp;	//node의 다음 노드에 temp 연결
				node->llink = prev;	//node의 이전 노드에 prev연결
				prev->rlink = node;	//prev의 다음 노드에 node 연결
			}
			break;//멈춘다
		}
		else
		{
			if (temp->rlink == h)	//temp의 다음 노드가 헤드노드이면
			{
				node->rlink = h;	//node의 다음 노드에 헤드노드를연결
				node->llink = temp;	//node의 이전 노드가 temp이면
				temp->rlink = node;	//node의 다음 노드에 node를 연결
				h->llink = node;	//헤드 노드의 이전 노드에 node를 넣는다
				break;	//멈춘다
			}
		temp = temp->rlink;	//temp에 temp의 다음 노드를 연결
		}
	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode *node;
	listNode *prev = NULL;

	node = h->rlink;	//node에 헤드 노드의 다음 노드 연결

	if (node->key == key)	//node의 값이 key와 같으면
	{
		deleteFirst(h);	//deleteFirst함수 호출
		return 0;
	}
	else
	{
		while (node != h)	//node의 다음값이 헤드노드면 중지
		{
			if (node->key == key)	//node의 값이 key와 같을 때
			{
				prev->rlink = node->rlink;	//prev의 다음 노드에 node의 다음 노드를 넣는다
				node->rlink->llink = prev;	//node의 다음 노드의 이전 노드가 prev가 되게 한다
				free(node);	//node 해제
				return 0;
			}
			else if (node->rlink == h && node->key == key) //node의 다음 노드가 헤드노드이면서 node의 key 값이 key와 같을 때
			{
				prev->rlink = h;	//이전 노드의 다음 노드를 헤드노드로 연결
				h->llink = prev;	//헤드노드의 이전 노드가 prev를 가리키도록 한다
				free(node);	//node 해제
				return 0;
			}
			else
			{
				prev = node;	//node값을 prev에 저장
				node = node->rlink;	//node에 다음 노드를 넣는다
			}
		}
	}

	printf("잘못 입력하셨습니다.\n");	//잘못 입력한 경우


	return 0;
}


