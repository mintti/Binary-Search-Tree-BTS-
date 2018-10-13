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

void init(); //�ʱ�ȭ�Լ�
int is_empty(); //���� ���� ���� �Լ�
void enqueue();//�����Լ�
element dequeue(); //�����Լ�

int eval();

typedef struct TreeNode	//����� ����
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

	printf("Binary Search Tree(BTS)�� �̿��� data �������α׷� �Դϴ�. \n(Ȱ�� ��� ȣ���� 0���Դϴ�.)\n\n");
	while (1) {
		printf("���ϴ� Ȱ���� ��ȣ�� �Է����ּ���. > ");
		scanf("%d", &i);
		printf("-----------------------------------------------------------\n");
		switch (i)
		{
		case 0:
			printf(" 0. ��� ȣ��\n 1. BST ����\n 2. BST ����\n 3. ������ ���� ���\n");
			printf(" 4. BST ���� ���\n 5. ������ȸ ������� �湮�� ���� ���\n 6. ������ ���� ��� ���\n");
			printf(" 7. �ܸ� ����� ���� ���\n 8. �Էµ� ������ ���� �� ��°�� ������ ���\n");
			printf(" 9. BST�� ���� ���� �Է¹޾� ���� ���̰� ���� ���Ҹ� ���\n10. ���α׷� ����\n");
			break;
		case 1:
			n = eval();
			while (n <= 0 || n > 100) {
				printf("���ǿ� �´� ���� �Է����ּ���.\n");
				n = eval();
			};
			Insert(&root, n);
			break;
		case 2:
			printf("BTS���� ������ ���� �Է��ϼ��� > ");
			scanf("%d", &n);
			Delete(&root, n);
			break;
		case 3:
			printf("BTS�� ���Ҵ� %d ���Դϴ�.\n", Count(&root, 0));
			break;
		case 4:
			printf("BTS�� ���̴� %d �Դϴ�.\n", Height(root));
			break;
		case 5:
			if (Count(&root, 0) == 0)		printf("���Ұ� �����ϴ�.\n");
			else {
				Level_order(root);
				printf("\n");
			}
			break;
		case 6:
			printf("���� ��� ����� ���ϴ� ���Ҹ� �Է��ϼ���. > ");
			scanf("%d", &n);
			printf("%d�� ���� ���� ", n);
			if (Ancestor(root, n) == -1) 	printf("�������� �ʽ��ϴ�.\n");
			else	printf("�Դϴ�.\n");
			break;
		case 7:
			printf("�ܸ� ���� %d ���Դϴ�.\n", Terminal(&root, 0));
			break;
		case 8:
			printf("�� ��°�� ������ �˰� ���� ���Ҹ� �Է��ϼ���. > ");
			scanf("%d", &n);
			i = Count(&root, 0);
			j = 0;
			if(i!=0)
				j = Find(root, n);
			if (i == 0 ||  j == 0)		printf("���Ұ� �����ϴ�.\n");
			else
				printf("%d�� %d ��°�� ���� ���Դϴ�.\n", n, Number(root, n, i));
			break;
		case 9:
			printf("���� ���̰� ���� ���Ҹ� ã�� ���� �Է��ϼ���. > ");
			scanf("%d", &n);
			if (Count(&root, 0) == 0)	printf("���Ұ� �����ϴ�.\n");
			else
				printf("%d�� ���� ���̰� ���� ���� %d �Դϴ�.\n", n, Near(root, n));
			break;
		case 10:
			Quit();
			return 0;
		default:
			printf("�߸��� ��ȣ�Դϴ�. ���Է� ��Ź�帳�ϴ�.\n");
			break;
		}
		printf("\n");
	}
	system("PAUSE");
}

//�Է� ����
int eval() {
	char x[100] = "0";	//�迭�ʱ�ȭ
	int n;

	printf("BTS�� ������ ���Ҹ� �Է����ּ���. (1~100������ ����)> ");
	scanf("%s", x);

	for (int i = 0; i < strlen(x); i++)	//0~9 �̿��� ���� �ִ���
		if (x[i] < '0' || x[i] > '9')	// �迭�� ���̸�ŭ �˻�
			return 0;
	n = atoi(x);	//���ڿ��� ����(int�� ��ȯ)

	return n;
}

//1. ��� ����
void Insert(node **root, int id) {	//(node *)malloc(sizeof(node))
	node *p, *t;
	node *n;

	t = *root;
	p = NULL;

	//Ž���� ���� ����
	while (t != NULL) {
		if (id == t->data) return;
		p = t;
		if (id < p->data) t = p->left;
		else t = p->right;
	}

	//data�� Ʈ�� �ȿ� �����Ƿ� ���԰���
	//Ʈ����� ����
	n = (node *)malloc(sizeof(node));
	if (n == NULL) return;
	//������ ����
	n->data = id;
	n->left = n->right = NULL;
	//�θ��� ����
	if (p != NULL)
		if (id < p->data)
			p->left = n;
		else p->right = n;
	else *root = n; //���Ұ� 1�� �ۿ� ���� ���

}

//2. ��� ����
void Delete(node **root, int id) {
	node *p, *child, *succ, *succ_p, *t; //p�� �θ���, t�� ������, succ�� �İ��ڳ��, succ_p�� �İ��ڳ���� �θ� 
										 //id�� ���� ��� t�� Ž��, p�� t�� �θ� ���
	p = NULL;
	t = *root;
	//id�� ���� ��� t�� Ž���Ѵ�.
	while (t != NULL && t->data != id) {
		p = t;
		t = (id < t->data) ? t->left : t->right;
	}
	//Ž���� ����� ������ t�� NULL�̸� Ʈ���ȿ� id�� ����
	if (t == NULL) {
		printf("�Է��Ͻ� ���� Ʈ�� �ȿ� �����ϴ�.\n\n");
		return;
	}
	//ù ��° ���: �ܸ� ����� ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			//�θ� ����� �ڽ� �ʵ带 NULL�� �����.
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}
	//�� ��° ���: �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) //�θ� �ڽð� ����
				p->left = child;
			else p->right = child;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}
	//�� ��° ���: �ΰ��� �ڽ��� ������ ���
	else {
		//���� ����Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->left;
		//�İ��ڸ� ã�Ƽ� ��� ���������� �̵��Ѵ�.
		while (succ->right != NULL) {
			succ_p = succ;
			succ = succ->right;
		}
		//�ļ����� �θ�� �ڽ��� ����
		if (succ_p->right == succ)
			succ_p->right = succ->left;
		else
			succ_p->left = succ->left;
		//�ļ��ڰ� ���� Ű���� ���� ��忡 ����
		t->data = succ->data;
		//������ �ļ��� ����
		t = succ;
	}
	free(t);
}

//3. ��� ����
int Count(node **root, int count) {
	node *t;
	t = *root;

	if (t != NULL)//���Ұ� �ִ��� Ȯ��
		count++;
	else
		return 0;

	//���� ������ Ž���ϸ� ī��Ʈ
	if (t->right != NULL)
		count = Count(&t->right, count);
	if (t->left != NULL)
		count = Count(&t->left, count);

	//��ȸ �� ī��Ʈ �� ����
	return count;
}

//4. BTS ����
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

//5. ������ȸ
void init(QueueType *q) {
	q->front = q->rear = NULL;
}
int is_empty(QueueType *q) {
	return (q->front == NULL);
}
void enqueue(QueueType *q, element item) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL)
		perror("�޸𸮸� �Ҵ��� �� �����ϴ�.\n\n");
	else {
		temp->item = item; //������ ����
		temp->link = NULL; //��ũ �ʵ带 NULL
		if (is_empty(q)) { //ť�� �����̸�
			q->front = temp;
			q->rear = temp;
		}
		else { //ť�� ������ �ƴϸ�
			q->rear->link = temp; //������ �߿�
			q->rear = temp;
		}
	}
}
element dequeue(QueueType *q) {
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q)) //�������
		perror("ť�� ��� �ֽ��ϴ�.\n\n");
	else {
		item = temp->item; //�����͸� ������.
		q->front = q->front->link; //front�� ������带 ����Ű���� �Ѵ�.
		if (q->front == NULL) //���� ����
			q->rear = NULL;
		free(temp); //�����޸� ����
		return item; //������ ��ȯ
	}
}
void Level_order(node *ptr) {
	QueueType q;

	printf("���� ��ȸ : ");
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

//6. ���� ��� ���
int Ancestor(node *root, int id) {
	int x[100], i = 0;	//���� ��带 �����ϴ� x�� �ε��� i
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
	else if (id == root->data) { //id���� ã�����Ƿ� ������ ���
		for (int j = 0; j<i; j++)
			printf("%d ", x[j]);
		return 0;
	}
	else {	//�ٽ� Ž��
		x[i++] = root->data;

		if (id < root->data)
			return get_Ancestor(root->left, id, x, i);
		else
			return get_Ancestor(root->right, id, x, i);
	}
}

//7. �ܸ� ��� ����
int Terminal(node **root, int count) {
	node *t;
	t = *root;

	if (t == NULL) return 0; // ���Ұ� ������ ����
	if (t->right == NULL && t->left == NULL)  //�ܸ� ����̸� ī��Ʈ
		count++;

	//���� ������ Ž��
	if (t->right != NULL)
		count = Terminal(&t->right, count);
	if (t->left != NULL)
		count = Terminal(&t->left, count);

	//��ȸ �� ī��Ʈ �� ����
	return count;
}

//8. �Է¹��� ���Ұ� �� ��°�� ������ ���
int Number(node *root, int id, int count) {
	if (id < root->data)	//id���� ���� ��� count ����
		count--;

	//���� ������ Ž��
	if (root->left != NULL)
		count = Number(root->left, id, count);
	if (root->right != NULL)
		count = Number(root->right, id, count);

	//��ȸ �� ī��Ʈ �� ����
	return count;
}
int Find(node *root, int id) { //Ʈ���� id�� �����ϸ� 1����
	if (id == root->data)
			return 1;

		
	if (root->left != NULL)
		Find(root->left, id);
	if (root->right != NULL)
		Find(root->right, id);
}

//9. BTS���� id���� ���� ���̰� ���� �������
int Near(node *root, int id) {
	int min = 0, gap = 100;	//min���� ���̰� ���� ��
							//gap�� min�� id�� ���̰��� ����.
	return get_Near(root, id, min, gap);
}
int get_Near(node *root, int id, int min, int gap) {
	int tm; //���̰��� �ӽ÷� ����

			//���� ���̰��� �����ϰ�� �ݴ�� ����.
	tm = root->data - id < 0 ? id - root->data : root->data - id;

	if (tm <= gap)
		if (tm == gap) {//���� ���� ���� ���
			if (root->data < min)//data���� min���� ���Ͽ�
				min = root->data;//�� ���� ���� min�� ����
		}
		else {
			min = root->data;
			gap = tm;
		}
		//���� �������� Ž��
		if (root->left != NULL)
			min = get_Near(root->left, id, min, gap);
		if (root->right != NULL)
			min = get_Near(root->right, id, min, gap);

		//���������� ���̰� ���� ���� ����
		return min;
}

//10. ���α׷� ����
void Quit() {
	printf("BST data���� ���α׷��� �����մϴ�.\n");
}