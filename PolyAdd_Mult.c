//多项式的乘法和加法
//来源于网易mooc浙江大学 
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode* Polynomial;
struct PolyNode{
	int coef;
	int expon;
	Polynomial link;
}; 

Polynomial ReadPoly();
void Attach(int, int, Polynomial*);
Polynomial Mult(Polynomial, Polynomial);
Polynomial Add(Polynomial, Polynomial);
void PrintPoly(Polynomial);
int compare(int, int);

int main()
{
	Polynomial P1, P2, PP, PS;
	
	P1 = ReadPoly();
	P2 = ReadPoly();
	PP = Mult(P1, P2);
	PrintPoly(PP);
	PS = Add(P1, P2);
	PrintPoly(PS);
	
	return 0;
}
//读入多项式 
Polynomial ReadPoly()
{
	Polynomial P, Rear, Temp;
	int N, c, e;
	
	scanf("%d", &N);
	P = (Polynomial)malloc(sizeof(struct PolyNode));	//空的首节点 
	P->link =  NULL;
	Rear = P;		//做为尾节点 用来插入新结点 
	while(N--){
		scanf("%d %d", &c, &e);
		Attach(c, e, &Rear);
	}
	Temp = P;
	P = P->link;
	free(Temp);
	
	return P;
}
//串联链表 
void Attach(int c, int e, Polynomial *pRear)
{
	Polynomial fresh = (Polynomial)malloc(sizeof(struct PolyNode));
	fresh->coef = c;
	fresh->expon = e;
	(*pRear)->link = fresh;		//尾指针每次都作为链表的最后一个指针 
	*pRear = fresh;
}
//多项式的乘法
Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;
	int c, e;
	
	if(!P1 || !P2)
		return NULL;
	
	t1 = P1;
	t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	
	while(t2){
		//先用t1的第一项乘以t2的每一项 
		Attach(t1->coef*t2->coef, t1->expon+t2->expon, &Rear);
		t2 = t2->link;
	}		
	t1 = t1->link;
	while(t1){
		t2 = P2;
		Rear = P;
		while(t2){
			c = t1->coef * t2->coef;
			e = t1->expon + t2->expon;
			while(Rear->link && Rear->link->expon > e)
				Rear = Rear->link;
			if(Rear->link && Rear->link->expon == e){
				if(Rear->link->coef + c)
					Rear->link->coef += c;
				else{
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}	
			}
			else{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;
			}	
		}
		t1 = t1->link;
	}
	t2 = P;
	P = P->link;
	free(t2);
	
	return P;
} 
//多项式的输出
void PrintPoly(Polynomial P)
{
	int flag = 0;
	
	if(!P){
		printf("0 0\n");
		return ;
	}
	
	while(P){
		if(!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d",P->coef, P->expon);
		P = P->link;	
	}	
	printf("\n");
} 
//多项式的加法
 Polynomial Add(Polynomial P1, Polynomial P2)
 {
	Polynomial front, Rear, temp;
	int sum;
	front = (Polynomial)malloc(sizeof(struct PolyNode));
	Rear = front;
	while(P1 && P2)
		switch(compare(P1->expon, P2->expon)){
			case 1:
					Attach(P1->coef, P1->expon, &Rear);
					P1 = P1->link;
					break;
			case -1:
					Attach(P2->coef, P2->expon, &Rear);
					P2 = P2->link;
					break;
			case 0:
					sum = P1->coef + P2->coef;
					if(sum)
						Attach(sum, P1->expon, &Rear);
					P1 = P1->link;
					P2 = P2->link;
					break;				   
		}
	while(P1){
		Attach(P1->coef, P1->expon, &Rear);
		P1 = P1->link;
	}
	while(P2){
		Attach(P2->coef, P2->expon, &Rear);
		P2 = P2->link;
	}
	Rear->link = NULL;
	temp = front;
	front = front->link;
	free(temp);
	
	return front;	
 }
 
 int compare(int x, int y)
 {
	if(x > y)
		return 1;
	else if(y < x)
		return -1;
	else
		return 0;		
 }
