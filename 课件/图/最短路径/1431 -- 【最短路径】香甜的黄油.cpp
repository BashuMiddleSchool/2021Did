//堆+Dij 
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1000,maxm=5100;
struct edge { int v,to,next; } a[maxm]= {0};
struct Heap {
	int d,num;
	bool operator < (const Heap& T)const {
		return d>T.d;
		//由于 priority_queue 默认大根堆，所以要实现d值最小的在堆顶，需反着来 
	}
};
int dis[maxn]= {0};
int cn,n,m,cnt,s,t,h[maxn]= {0},INF=9999999,cow[700],vst[maxn];
void AddEdge(int x,int y,int z) {
	cnt++;
	a[cnt].to=y;
	a[cnt].v=z;
	a[cnt].next=h[x];
	h[x]=cnt;
}
void Read() {
	int i,x,y,z;
	cin>>cn>>n>>m;
	for(i=1; i<=cn; i++)cin>>cow[i];
	cnt=0;
	for(i=1; i<=m; i++) {
		cin>>x>>y>>z;
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
}
int Dijkstra(int s) {
	int i,j,k,x,y,ans;
	priority_queue<Heap> Q;  //由大到小 
	memset(vst,0,sizeof(vst));
	for(i=1; i<=n; i++)dis[i]=INF;
	dis[s]=0;
	Q.push((Heap){ dis[s],s }); 
	while(!Q.empty()) {
		Heap u=Q.top();
		Q.pop();
		int x=u.num;
		if(vst[x])continue;
		vst[x]=1;
		for(k=h[x]; k; k=a[k].next) {
			y=a[k].to;
			if(!vst[y]&&dis[x]+a[k].v<dis[y]) { //松弛操作
				dis[y]=dis[x]+a[k].v;
				Q.push((Heap){ dis[y],y });
			}
		}
	}
	ans=0;
	for(i=1; i<=cn; i++)ans+=dis[cow[i]];
	return ans;
}
int main() {
	int i,k;
	Read();
	k=INF;
	for(i=1; i<=n; i++)k=min(k,Dijkstra(i));
	cout<<k<<endl;
}
