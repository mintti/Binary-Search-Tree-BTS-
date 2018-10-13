#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<malloc.h>
#include<string.h>

typedef int element;

typedef struct QueueNode {
	element item;
	struct QueueNode *link;
}QueueNode;

typedef struct {
	QueueNode *front, *rear;
}QueueType;

void init(); //초기화함수
int is_empty(); //공백 상태 검출 함수
void enqueue();//삽입함수
element dequeue(); //삭제함수

int eval();

typedef struct TreeNode	//노드의 구조
{
	int data;
	struct TreeNode *left, *right;
}node;

int scanf_int(int *a);
void Insert();
void Delete();
int Count();
int Height();
int get_Height();
void Level_order();
int Ancestor();
int get_Ancestor();
int Terminal();
int Number();
int Find();
int Near();
void Quit();

main(void) {
	int i, j, n;
	node *root = NULL;

	printf("Binary Search Tree(BTS)를 이용한 data 관리프로그램 입니다. \n(활동 목록 호출은 0번입니다.)\n\n");
	while (1) {
		printf("원하는 활동의 번호를 입력해주세요. > ");
		scanf("%d", &i);
		printf("-----------------------------------------------------------\n");
		switch (i)
		{
		case 0:
			printf(" 0. 목록 호출\n 1. BST 삽입\n 2. BST 삭제\n 3. 원소의 개수 출력\n");
			printf(" 4. BST 높이 출력\n 5. 레벨순회 방식으로 방문한 원소 출력\n 6. 원소의 조상 노드 출력\n");
			printf(" 7. 단말 노드의 개수 출력\n 8. 입력된 원소의 값이 몇 번째로 작은지 출력\n");
			printf(" 9. BST에 없는 값을 입력받아 가장 차이가 적은 원소를 출력\n10. 프로그램 종료\n");
			break;
		case 1:
			n = eval();
			while (n <= 0 || n > 100) {
				printf("조건에 맞는 수를 입력해주세요.\n");
				n = eval();
			};
			Insert(&root, n);
			break;
		case 2:
			printf("BTS에서 삭제할 값을 입력하세요 > ");
			scanf("%d", &n);
			Delete(&root, n);
			break;
		case 3:
			printf("BTS의 원소는 %d 개입니다.\n", Count(&root, 0));
			break;
		case 4:
			printf("BTS의 높이는 %d 입니다.\n", Height(root));
			break;
		case 5:
			if (Count(&root, 0) == 0)		printf("원소가 없습니다.\n");
			else {
				Level_order(root);
				printf("\n");
			}
			break;
		case 6:
			printf("조상 노드 출력을 원하는 원소를 입력하세요. > ");
			scanf("%d", &n);
			printf("%d의 조상 노드는 ", n);
			if (Ancestor(root, n) == -1) 	printf("존재하지 않습니다.\n");
			else	printf("입니다.\n");
			break;
		case 7:
			printf("단말 노드는 %d 개입니다.\n", Terminal(&root, 0));
			break;
		case 8:
			printf("몇 번째로 작은지 알고 싶은 원소를 입력하세요. > ");
			scanf("%d", &n);
			i = Count(&root, 0);
			j = 0;
			if(i!=0)
				j = Find(root, n);
			if (i == 0 ||  j == 0)		printf("원소가 없습니다.\n");
			else
				printf("%d는 %d 번째로 작은 수입니다.\n", n, Number(root, n, i));
			break;
		case 9:
			printf("가장 차이가 적은 원소를 찾을 값을 입력하세요. > ");
			scanf("%d", &n);
			if (Count(&root, 0) == 0)	printf("원소가 없습니다.\n");
			else
				printf("%d와 가장 차이가 적은 값은 %d 입니다.\n", n, Near(root, n));
			break;
		case 10:
			Quit();
			return 0;
		default:
			printf("잘못된 번호입니다. 재입력 부탁드립니다.\n");
			break;
		}
		printf("\n");
	}
	system("PAUSE");
}

//입력 조건
int eval() {
	char x[100] = "0";	//배열초기화
	int n;

	printf("BTS에 삽입할 원소를 입력해주세요. (1~100사이의 정수)> ");
	scanf("%s", x);

	for (int i = 0; i < strlen(x); i++)	//0~9 이외의 값이 있는지
		if (x[i] < '0' || x[i] > '9')	// 배열의 길이만큼 검사
			return 0;
	n = atoi(x);	//문자열을 정수(int로 변환)

	return n;
}

//1. 노드 삽입
void Insert(node **root, int id) {	//(node *)malloc(sizeof(node))
	node *p, *t;
	node *n;

	t = *root;
	p = NULL;

	//탐색을 먼저 수행
	while (t != NULL) {
		if (id == t->data) return;
		p = t;
		if (id < p->data) t = p->left;
		else t = p->right;
	}

	//data가 트리 안에 없으므로 삽입가능
	//트리노드 구성
	n = (node *)malloc(sizeof(node));
	if (n == NULL) return;
	//테이터 복사
	n->data = id;
	n->left = n->right = NULL;
	//부모노드 연결
	if (p != NULL)
		if (id < p->data)
			p->left = n;
		else p->right = n;
	else *root = n; //원소가 1개 밖에 없을 경우

}

//2. 노드 삭제
void Delete(node **root, int id) {
	node *p, *child, *succ, *succ_p, *t; //p는 부모노드, t는 현재노드, succ는 후계자노드, succ_p는 후계자노드의 부모 
										 //id를 갖는 노드 t를 탐색, p는 t의 부모 노드
	p = NULL;
	t = *root;
	//id를 갖는 노드 t를 탐색한다.
	while (t != NULL && t->data != id) {
		p = t;
		t = (id < t->data) ? t->left : t->right;
	}
	//탐색이 종료된 시점에 t가 NULL이면 트리안에 id가 없음
	if (t == NULL) {
		printf("입력하신 값이 트리 안에 없습니다.\n\n");
		return;
	}
	//첫 번째 경우: 단말 노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			//부모 노드의 자식 필드를 NULL로 만든다.
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = NULL;
	}
	//두 번째 경우: 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) //부모를 자시과 연결
				p->left = child;
			else p->right = child;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}
	//세 번째 경우: 두개의 자식을 가지는 경우
	else {
		//왼쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->left;
		//후계자를 찾아서 계속 오른쪽으로 이동한다.
		while (succ->right != NULL) {
			succ_p = succ;
			succ = succ->right;
		}
		//후속자의 부모와 자식을 연결
		if (succ_p->right == succ)
			succ_p->right = succ->left;
		else
			succ_p->left = succ->left;
		//후속자가 가진 키값을 현재 노드에 복사
		t->data = succ->data;
		//원래의 후속자 삭제
		t = succ;
	}
	free(t);
}

//3. 노드 개수
int Count(node **root, int count) {
	node *t;
	t = *root;

	if (t != NULL)//원소가 있는지 확인
		count++;
	else
		return 0;

	//왼쪽 오른쪽 탐색하며 카운트
	if (t->right != NULL)
		count = Count(&t->right, count);
	if (t->left != NULL)
		count = Count(&t->left, count);

	//순회 후 카운트 값 리턴
	return count;
}

//4. BTS 높이
int Height(node *root) {

	if (root != NULL)
		return 1 + max(get_height(root->left), get_height(root->right));
	else
		return 0;
}
int get_height(node *root) {
	int height = 0;

	if (root != NULL)
		height = 1 + max(get_height(root->left), get_height(root->right));
	return height;
}

//5. 레벨순회
void init(QueueType *q) {
	q->front = q->rear = NULL;
}
int is_empty(QueueType *q) {
	return (q->front == NULL);
}
void enqueue(QueueType *q, element item) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL)
		perror("메모리를 할당할 수 없습니다.\n\n");
	else {
		temp->item = item; //데이터 저장
		temp->link = NULL; //링크 필드를 NULL
		if (is_empty(q)) { //큐가 공백이면
			q->front = temp;
			q->rear = temp;
		}
		else { //큐가 공백이 아니면
			q->rear->link = temp; //순서가 중요
			q->rear = temp;
		}
	}
}
element dequeue(QueueType *q) {
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q)) //공백상태
		perror("큐가 비어 있습니다.\n\n");
	else {
		item = temp->item; //데이터를 꺼낸다.
		q->front = q->front->link; //front를 다음노드를 가리키도록 한다.
		if (q->front == NULL) //공백 상태
			q->rear = NULL;
		free(temp); //동적메모리 해제
		return item; //데이터 반환
	}
}
void Level_order(node *ptr) {
	QueueType q;

	printf("레벨 순회 : ");
	init(&q);
	if (!ptr) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("%d ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

//6. 조상 노드 출력
int Ancestor(node *root, int id) {
	int x[100], i = 0;	//조상 노드를 보관하는 x와 인덱스 i
	if (root == NULL || id == root->data) return -1;
	x[i++] = root->data;

	if (id < root->data)
		return get_Ancestor(root->left, id, x, i);
	else
		return get_Ancestor(root->right, id, x, i);
}
int get_Ancestor(node *root, int id, char *x, int i) {

	if (root == NULL)
		return -1;
	else if (id == root->data) { //id값을 찾았으므로 조상노드 출력
		for (int j = 0; j<i; j++)
			printf("%d ", x[j]);
		return 0;
	}
	else {	//다시 탐색
		x[i++] = root->data;

		if (id < root->data)
			return get_Ancestor(root->left, id, x, i);
		else
			return get_Ancestor(root->right, id, x, i);
	}
}

//7. 단말 노드 개수
int Terminal(node **root, int count) {
	node *t;
	t = *root;

	if (t == NULL) return 0; // 원소가 없으면 종료
	if (t->right == NULL && t->left == NULL)  //단말 노드이면 카운트
		count++;

	//왼쪽 오른쪽 탐색
	if (t->right != NULL)
		count = Terminal(&t->right, count);
	if (t->left != NULL)
		count = Terminal(&t->left, count);

	//순회 후 카운트 값 리턴
	return count;
}

//8. 입력받은 원소가 몇 번째로 작은지 출력
int Number(node *root, int id, int count) {
	if (id < root->data)	//id값이 작을 경우 count 감소
		count--;

	//왼쪽 오른쪽 탐색
	if (root->left != NULL)
		count = Number(root->left, id, count);
	if (root->right != NULL)
		count = Number(root->right, id, count);

	//순회 후 카운트 값 리턴
	return count;
}
int Find(node *root, int id) { //트리에 id가 존재하면 1리턴
	if (id == root->data)
			return 1;

		
	if (root->left != NULL)
		Find(root->left, id);
	if (root->right != NULL)
		Find(root->right, id);
}

//9. BTS에서 id값과 가장 차이가 적은 원소출력
int Near(node *root, int id) {
	int min = 0, gap = 100;	//min에는 차이가 작은 값
							//gap는 min과 id의 차이값을 넣음.
	return get_Near(root, id, min, gap);
}
int get_Near(node *root, int id, int min, int gap) {
	int tm; //차이값을 임시로 저장

			//만약 차이값이 음수일경우 반대로 셈함.
	tm = root->data - id < 0 ? id - root->data : root->data - id;

	if (tm <= gap)
		if (tm == gap) {//차이 값이 같을 경우
			if (root->data < min)//data값과 min값을 비교하여
				min = root->data;//더 작은 값을 min에 저장
		}
		else {
			min = root->data;
			gap = tm;
		}
		//왼쪽 오른쪽을 탐색
		if (root->left != NULL)
			min = get_Near(root->left, id, min, gap);
		if (root->right != NULL)
			min = get_Near(root->right, id, min, gap);

		//최종적으로 차이가 적은 값을 리턴
		return min;
}

//10. 프로그램 종료
void Quit() {
	printf("BST data관리 프로그램을 종료합니다.\n");
}