#include <bits/stdc++.h>
#define int long long
#define ll long long
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
inline int read()
{
	int x=0;char ch=getchar();
	while(ch>'9' || ch<'0')ch=getchar();
	while(ch>='0' && ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
const int mx=2e5+3;
int N,M,rt,mod;
int u,v,w;
int head[mx],nxt[mx<<1],to[mx<<1],cnt;

inline void add(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

int dep[mx],son[mx],sz[mx],fa[mx],top[mx],rnd[mx],seg[mx],ctr=0;

void dfs1(int u,int f)
{
	int maxx=0;
	fa[u]=f;dep[u]=dep[f]+1;sz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		if(to[i]==f)continue;
		dfs1(to[i],u);
		sz[u]+=sz[to[i]];
		if(sz[to[i]]>maxx)
		{
			maxx=sz[to[i]];
			son[u]=to[i];
		}
	}
}
void dfs2(int u,int f)
{
	top[u]=f;
	seg[u]=++cnt;
	rnd[cnt]=u;
	if(!son[u])return;
	dfs2(son[u],f);
	for(int i=head[u];i;i=nxt[i])
	{
		if(to[i]==fa[u] || to[i]==son[u])continue;
		dfs2(to[i],to[i]);
	}
}

struct Segtree{
	ll val[mx<<2],lazy[mx<<2],init[mx];
	inline void pushup(int rt)
	{
		val[rt]=(val[lson]+val[rson])%mod;
	}
	inline void pushdown(int rt,int l,int r)
	{
		int mid=l+r>>1;
		if(lazy[rt])
		{
			(lazy[lson]+=lazy[rt])%=mod;
			(lazy[rson]+=lazy[rt])%=mod;
			(val[lson]+=lazy[rt]*(mid-l+1))%=mod;
			(val[rson]+=lazy[rt]*(r-mid))%=mod;
			lazy[rt]=0;
		}
	}
	
	void build(int rt,int l,int r)
	{
		if(l==r){
			val[rt]=init[rnd[l]]%mod;
			return;
		}
		int mid=(l+r)>>1;
		build(lson,l,mid);build(rson,mid+1,r);
		pushup(rt);
	}
	void update(int rt,int l,int r,int ul,int ur,int add)
	{
		if(ul>r || ur<l)return;
		if(ul<=l && ur>=r)
		{
			(val[rt]+=(r-l+1)*add)%=mod;
			(lazy[rt]+=add)%=mod;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt,l,r);
		update(lson,l,mid,ul,ur,add);
		update(rson,mid+1,r,ul,ur,add);
		pushup(rt);
	}
	ll query(int rt,int l,int r,int ql,int qr)
	{
		if(ql<=l && qr>=r)return val[rt];
		pushdown(rt,l,r);
		int mid=(l+r)>>1,ret=0;
		if(ql<=mid)(ret+=(query(lson,l,mid,ql,qr)))%=mod;
		if(qr>mid)(ret+=query(rson,mid+1,r,ql,qr))%=mod;
		return ret;
	}
	void print(int rt,int l,int r,int dep=0)
	{
		int mid=(l+r)>>1;
		if(val[lson])print(lson,l,mid,dep+1);
		for(int i=1;i<=dep;++i)printf("  ");
		printf("rt=%d,val=%d,l=%d,r=%d\n",rt,val[rt],l,r);
		if(val[rson])print(rson,mid+1,r,dep+1);
	}
}Seg;

inline void update_chain(int x,int y,int w)
{
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Seg.update(1,1,N,seg[top[x]],seg[x],w);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Seg.update(1,1,N,seg[x],seg[y],w);
}
inline int query_chain(int x,int y)
{
	ll ret=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		(ret+=Seg.query(1,1,N,seg[top[x]],seg[x]))%=mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	(ret+=Seg.query(1,1,N,seg[x],seg[y]))%=mod;
	return ret;
}

signed main()
{
	//freopen("P3384_2.in","r",stdin);
	N=read();M=read();rt=read();mod=read();
	for(int i=1;i<=N;++i)Seg.init[i]=read()%mod;
	for(int i=1;i<N;++i)u=read(),v=read(),add(u,v),add(v,u);
	cnt=0;
	dfs1(rt,0);
	dfs2(rt,rt);
	Seg.build(1,1,N);
	
//	Seg.print(1,1,N);
	while(M--)
	{
		int op=read();
		if(op==1)
		{
			u=read();v=read();w=read();	
			update_chain(u,v,w%mod);
		}	
		else if(op==2)
		{
			u=read();v=read();
			printf("%d\n",query_chain(u,v));
		}
		else if(op==3)
		{
			u=read();w=read();
			Seg.update(1,1,N,seg[u],seg[u]+sz[u]-1,w%mod);
		}
		else 
		{
			u=read();
			printf("%d\n",(int)Seg.query(1,1,N,seg[u],seg[u]+sz[u]-1));
		}
	}
	return 0;
}
