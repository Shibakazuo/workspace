#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

typedef struct node *link;
struct node{
	int v;
	link next;
};

int loop[MAX];
link adj[MAX];

link NEW(int v,link n){
	link x = malloc(sizeof(*x));
	x->v = v; x->next=n;
	return x;
}

void search(int n,int cnt){
	if(loop[n]==-1){
		link t;
		loop[n]=cnt;
		for(t=adj[n];t!=NULL;t=t->next)search(t->v,cnt);
	}
}

int main(void){
	int n,m,s,t;
	int i;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++){
		adj[i]=NULL;
		loop[i]=-1;
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&s,&t);
		adj[s]=NEW(t,adj[s]);
		adj[t]=NEW(s,adj[t]);
	}
	
	scanf("%d %d",&s,&t);
	search(s,s);
	
	if(loop[s]==loop[t])printf("true\n");
	else printf("false\n");

	return 0;
}