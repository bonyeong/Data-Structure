/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("------소프트웨어학과 2019038021 구본영------");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	{
		freeBST(*h);

	}
	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)	//중위 순회 함수
{

	if (ptr != NULL)		//멈추기 위한 조건을 걸어줌
	{
		inorderTraversal(ptr->left);		//왼쪽 방향으로 내려가기 위해 함수 호출
		printf(" [%d] ", ptr->key);			//ptr->key 출력
		inorderTraversal(ptr->right);		//오른쪽 방향으로 내려가기 위해 함수 호출
	}

}

void preorderTraversal(Node* ptr)		//전위 순회 함수
{
	if (ptr != NULL)		//멈추기 위한 조건을 걸어줌
	{
		printf(" [%d] ", ptr->key);		//ptr->key 출력
		preorderTraversal(ptr->left);	//왼쪽 방향으로 내려가기 위해 함수 호출
		preorderTraversal(ptr->right);	//오른쪽 방향으로 내려가기 위해 함수 호출
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);	//왼쪽 방향으로 내려가기 위해 함수 호출
		postorderTraversal(ptr->right);	//오른쪽 방향으로 내려가기 위해 함수 호출
		printf(" [%d] ", ptr->key);		//ptr->key 출력
	}
}


int insert(Node* head, int key)
{
	Node *node = (Node *)malloc(sizeof(Node));	//node 변수에 동적할당
	Node *temp = head->left;		//임시저장 temp변수에 head->left를 넣는다

	node->key = key;	//node에 key 값을 넣고
	node->left = NULL;	//node의 left에 NULL을 넣는다.
	node->right = NULL;	//node의 right에 NULL을 넣는다.

	if (head->left == NULL)	//head의 left가 비어있다면
	{
		//node를 넣어주고 return
		head->left = node;
		return 0;
	}
	else {
		while (1)
		{
			if (temp->key > node->key)	//temp의 키가 node의 키보다 클 때
			{
				if (temp->left == NULL)		//temp의 left가 비어있으면
				{
					//temp->left에 노드를 넣고 return
					temp->left = node;
					return 0;
				}
				temp = temp->left;	//temp의 값을 temp의 left로 넣는다
			}
			else
			{
				if (temp->right == NULL)	//temp의 right가 비어있으면
				{
					//temp->right에 노드를 넣고 리턴
					temp->right = node;
					return 0;
				}
				temp = temp->right;	//temp의 값을 temp의 right로
			}
		}
	}
	return 0;

}

int deleteLeafNode(Node* head, int key)		//leaf노드 삭제
{
	Node *prev =NULL;	//이전 노드
	Node *temp;			//임시 저장
	temp = head->left;	//head의 left 값을 넣는다.

	int i =2;	//temp가 prev의 left였는지 right 였는지를 구분 가능하게 한다

	while (temp!= NULL)	//temp가 NULL이면 중지
	{
		if ((key == temp->key))	//key의 값을 찾았을 때
		{
			if ((temp->left == NULL) && (temp->right == NULL))	//양쪽이 모두 비어있으면
			{
				free(temp);	//동적할당해제
				//i의 숫자에 따라 NULL값이 들어갈 위치가 달라짐
				if (i == 0)
					prev->left = NULL;
				else if (i == 1)
					prev->right = NULL;
				else
					head->left = NULL;

				return 0;
			}
			else
			{
				//값은 존재하지만 leaf node가 아닐 때
				printf("\nthe node [%d] is not a leaf\n", temp->key);
				return 0;
			}
		}
		else
		{
			if (temp->key > key) //key 값보다 temp의 값이 크면
			{
				prev = temp;	//prev에 temp 값을 넣고
				temp = temp->left;	//temp에 temp의 left 값을 넣는다
				i = 0;	//temp가 prev의 left였다는 것을 알려주는 장치
			}
			else
			{
				prev = temp;	//prev에 temp 값을 넣고
				temp = temp->right;	//temp에 temp의 right 값을 넣는다
				i = 1;	//temp가 prev의 right였다는 것을 알려주는 장치
			}
		}
	}

	printf("\n Cannot find the node [%d]\n", key);	//key를 찾을 수 없을 때

	return 0;
}

Node* searchRecursive(Node* ptr, int key)	//순환탐색
{
	if (ptr != NULL)
	{
		if (ptr->key == key)	//key 값을 찾으면
		{
			return ptr;	//reuturn
		}
		else
		{
			if (ptr->key > key)	//key의 값보다 ptr->key가 크면
				return searchRecursive(ptr->left, key);	//ptr->left를 넣고 searchRecursive함수를 다시 호출
			else		//그렇지 않으면
				return searchRecursive(ptr->right, key);//ptr->를 넣고 searchRecursive함수를 다시 호출
		}
	}

	return NULL;	//NULL 리턴
}

Node* searchIterative(Node* head, int key)
{
	Node *temp = head->left;	//temp에 head->left를 넣는다

	while (temp != NULL)	//temp가 NULL이 아니면
	{
		if (temp->key == key)	//key 값을 찾으면
			return temp;	//temp를 리턴

		else
		{
			if (temp->key > key)	//temp의 값이 key보다 클 때
				temp = temp->left;	//temp에 temp의 left를 넣는다
			else
				temp = temp->right;	//temp에 temp의 right를 넣는다.
		}
	}

	//못 찾으면 NULL리턴
	return NULL;
}


int freeBST(Node* head)
{
	if (head == NULL)	//head가 비어있으면 리턴
		return 0;

	if (head->right == head)	//head의 right가 head를 가리키면
		head = head->left;	//head에 head의 left를 넣어준다

	if (head != NULL)	//head가 널이 아닐 때
	{
		freeBST(head->left);	//freeBST함수 호출 후 head의 left를 동적해제
		freeBST(head->right);	//freeBST함수 호출 후 head의 right를 동적해제
		head->key = 0;	//head의 key 값에 0을 넣어주고
		//left와 right에 NULL을 넣어준다.
		head->left = NULL;
		head->right = NULL;
		free(head);	//마지막으로 head동적 해제
	}

	return 0;
}
