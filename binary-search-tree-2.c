/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("----------소프트웨어학과 2019038021 구본영 -------------\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)	//반복적 중위 순회
{
	while(1)
	{
		for (; node; node = node->left)		//node가 NULL이 아닐 동안 반복
			push(node);	//push 함수 호출

		node = pop();	//pop 함수 호출해 삭제
		if (!node)	//만약 node가 NULL이면 멈춘다.
			break;

		printf(" [%d] ", node->key);	//node의 key 값을 프린트
		node = node->right;		//node에 node의 오른쪽 자식을 넣는다
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)		//레벨 순서 순회
{
	enQueue(ptr);	//enQueue함수 호출

	while(1)
	{
		ptr = deQueue();	//deQueue함수를 호출해 ptr에 넣어준다.
		if (ptr) {	//ptr이 NULL이 아니면
			printf(" [%d] ", ptr->key);	//ptr의 key값을 프린트 한다.
			if (ptr->left)	//만약 ptr의 왼쪽 자식이 NULL이 아니면
				enQueue(ptr->left);	//enQueue를 호출
			if (ptr->right)	//만약 ptr이 오른쪽 자식이 NULL이 아니면
				enQueue(ptr->right);	//enQueue를 호출
		}
		else	//ptr이 NULL이면 멈춘다.
			break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)	//node를 삭제하는 함수
{
	Node *temp = head->left;	//head->left 값을 지닌 노드
	Node *prev = NULL;		//이전 노드 1
	Node *node = NULL;		//이전 노드 2
	int i = 2;		//temp가 prev의 왼쪽 자식인지 오른쪽 자식인지 구분하기 위한 장치


	while (temp != NULL)	//temp가 NULL이면 중지
	{
		if (temp->key == key)	//temp의 값이 key와 같을 때
		{
			if (temp->left == NULL || temp->right == NULL)	//temp의 왼쪽 자식이 NULL 또는 temp의 오른쪽 자식이 NULL일 때
			{
				if (temp->left == NULL && temp->right == NULL) //그 중 temp의 왼쪽 자식과 오른쪽 자식이 모두 NULL이면
				{
					free(temp);	//temp를 해제하고
					//i의 값에 따라 NULL이 들어갈 위치가 달라진다.
					if (i == 0)
						prev->left = NULL;
					else if (i == 1)
						prev->right = NULL;
					else
						head->left = NULL;

					return 0;
				}
				else	//temp의 자식 중 하나만 NULL일 때
				{
					if (temp->left == NULL)	//temp의 왼쪽 자식이 NULL이면
					{
						//i의 값에 따라 temp의 오른쪽 자식이 들어갈 위치가 달라짐
						if (i == 0)
							prev->left = temp->right;
						else if (i == 1)
							prev->right = temp->right;
						else
							head->left = temp->right;
					}
					else if (temp->right == NULL)	//temp의 오른쪽 자식이 NULL이면
					{	//i의 값에 따라 temp의 왼쪽 자식이 들어갈 위치가 달라짐
						if (i == 0)
							prev->left = temp->left;
						else if (i == 1)
							prev->right = temp->left;
						else
							head->left = temp->left;
					}

					return 0;
				}
			}
			else		//양쪽 자식이 모두 NULL이 아닐 때
			{
				//temp의 오른쪽 서브 트리에서 제일 작은 값을 temp에 넣어준다.

				node = temp;	//node에 temp의 값을 저장
				temp = temp->right;	//temp를 temp의 오른쪽 자식의 값을 넣어준다.


				while (temp->left != NULL || temp->right != NULL)	//오른쪽 자식과 왼쪽 자식이 모두 NULL이면 반복 중지
				{
					prev = temp;	//이전 노드에 temp값을 넣어주고
					temp = temp->left;	//temp에 temp의 왼쪽 자식을 넣는다
				}
				node->key = temp->key;	//node에 temp의 값을 넣어 바꿔준다.
				free(temp);	//temp 해제
				if (prev == NULL)	//이전 노드가 NULL이면
					node->right = NULL;	//node의 오른쪽 자식에 NULL을 넣어준다
				else
				prev->left = NULL;	//아닐 경우 이전 노드의 왼쪾 자식에 NULL을 넣어준다.

				return 0;
			}
		}
		else
		{
			if (temp->key > key)	//temp의 값이 key보다 크면
			{
				prev = temp;	//prev에 temp의 값을 저장해주고
				temp = temp->left;	//temp에 temp의 왼쪽 자식 값을 저장해준다.
				i = 0;	//i를 0으로 초기화.
			}
			else   //temp의 값이 key보다 작으면
			{
				prev = temp;	//prev에 temp의 값을 넣는다.
				temp = temp->right;	//temp에 temp의 오른쪽 자식 값을 넣는다.
				i = 1;	//i=1로 초기화
			}
		}
	}
	printf("\n Cannot find the node [%d]\n", key);	//key를 찾을 수 없을 때

	return 0;

}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}


Node* pop()
{
	if (top == -1)	//stack이 비어있을 때
	return 0;

	return stack[top--];	//stack의 제일 위의 값을 삭제하고 반환한다.
}

void push(Node* aNode)
{
	if (top == (MAX_STACK_SIZE - 1))
		printf("stack이 다 참");
	stack[++top] = aNode;	//stack에 aNode값을 넣는다.
}



Node* deQueue()
{
	if (front == rear)		//queue가 비어있으면 0 반환
		return 0;

	front = (front + 1) % MAX_QUEUE_SIZE;	//queue의 앞 원소를 삭제해주고
	return queue[front];	//현재 front에 있는 원소 return

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;	//rear의 크기를 하나 더 올려준다

	if (front == rear)
		printf("queue가 다 참");

	queue[rear] = aNode;	//queue에 aNode 삽입
}


void printStack()
{
	printf("사용하는 함수가 아님");
}
