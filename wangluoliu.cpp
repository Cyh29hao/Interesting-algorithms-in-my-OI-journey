#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mx=1e4+5,INF=2147483647;
int n,m,s,t,u,v,w;
int head[mx],nxt[mx],dist[mx],to[mx],cnt=1,cur[mx];
ll ans=0;

inline void add_edge(int u,int v,int w){
	to[++cnt]=v;dist[cnt]=w;nxt[cnt]=head[u];head[u]=cnt;
}

int lv[mx];
queue <int> q;

inline bool bfs(){
	memset(lv,-1,sizeof lv);memcpy(cur,head,sizeof head);while(!q.empty())q.pop();
	
	lv[s]=0;q.push(s);
	
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i],w=dist[i];
			if(w>0 && lv[v]==-1)
				lv[v]=lv[u]+1,q.push(v);
		}
	}
	return lv[t]!=-1;
}

inline int dfs(int u=s,int flow=INF){
	if(u==t)return flow;
	int ret=flow;
	for(int i=cur[u];i && ret;i=nxt[i]){
		cur[u]=i;
		int v=to[i],w=dist[i];
		if(w>0 && lv[v]==lv[u]+1){
			int c=dfs(v,min(ret,w));
			ret-=c;
			dist[i]-=c;dist[i^1]+=c;
		}
	}
	return flow-ret;
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--)scanf("%d%d%d",&u,&v,&w),add_edge(u,v,w),add_edge(v,u,0);
	while(bfs())
		ans+=dfs();
	printf("%lld\n",ans);
	return 0;
}