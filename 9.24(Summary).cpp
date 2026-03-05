#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define uint unsigned long long
using namespace std;
const int mx=1e5+5;
int n,m;
struct fastio{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while(ch<'0'|| ch>'9'){
			if(ch=='-')f=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			x=(x<<1)+(x<<3)+(ch^48);
			ch=getchar();
		}
		return x*f;
	}
	void write(int x)
	{
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10|48);
	}
}fio;
struct bcj{
	int fa[mx];
	inline void init(){
		for(int i=1;i<=n;++i)fa[i]=i;
	}
	inline int find(int x)
	{
		while(x!=fa[x])x=fa[x]=fa[fa[x]];
		return x;
	}
	inline void merge(int x,int y)
	{
		int u=find(x),v=find(y);
		if(u==v)return;
		fa[u]=v;
	}
};
struct fhqtreap{
	int tot,rt,w[mx],v[mx],s[mx],lc[mx],rc[mx];
	inline int new_node(int _v){
		++tot;w[tot]=rand();s[tot]=1;lc[tot]=rc[tot]=0;v[tot]=_v;
		return tot;
	}
	inline void update(int x){s[x]=s[lc[x]]+s[rc[x]]+1;}
	void split_val(int now,int k,int &x,int &y){
		if(!now){x=y=0;return;}
		if(v[now]<=k){
			x=now;
			split_val(rc[now],k,rc[now],y);
		}
		else{
			y=now;
			split_val(lc[now],k,x,lc[now]);
		}
		update(now);
	}
	void split_kth(int now,int k,int &x,int &y){
		if(!now){x=y=0;return;}
		if(k<=s[lc[now]]){
			y=now;split_kth(lc[now],k,x,lc[now]);
		}
		else{
			x=now;split_kth(rc[now],k-s[lc[now]]-1,rc[now],y);
		}
		update(now);
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(w[x]<w[y]){
			rc[x]=merge(rc[x],y);
			update(x);
			return x;
		}
		lc[y]=merge(x,lc[y]);
		update(y);
		return y;
	}
	inline void insert(int &rt,int v){
		int x,y;split_val(rt,v,x,y);
		rt=merge(merge(x,new_node(v)),y);
	}
	inline void del(int &rt,int v){
		int x,y,z;
		split_val(rt,v,x,z);split_val(x,v-1,x,y);
		y=merge(lc[y],rc[y]);
		rt=merge(merge(x,y),z);
	}
	inline int query_kth(int now,int k){
		while(1){
			if(k<=s[lc[now]])now=lc[now];
			else{
				if(k==s[lc[now]]+1)return v[now];
				k-=s[lc[now]]+1;now=rc[now];
			}
		}
		return 0;
	}
	inline int query_rank(int &rt,int v){
		int x,y,rank;
		split_val(rt,v-1,x,y);rank=s[x]+1;
		rt=merge(x,y);
		return rank;
	}
	inline int query_pre(int &rt,int v){
		int x,y,z=0;split_val(rt,v-1,x,y);
		for(z=x;rc[z];z=rc[z]);
		rt=merge(x,y);
		return z;
	}
	inline int query_succ(int &rt,int v){
		int x,y,z=0;split_val(rt,v,x,y);
		for(z=y;lc[z];z=lc[z]);
		rt=merge(x,y);
		return z;
	}
	void print(int rt,int dep=0)
    {
        if(lc[rt])print(lc[rt],dep+1);
        for(int i=1;i<=dep;++i)printf("  ");printf("rt=%d,v=%d,s=%d\n",rt,v[rt],s[rt]);
        if(rc[rt])print(rc[rt],dep+1);
    }
}treap;
struct segtree{
	#define lson rt<<1
	#define rson rt<<1|1
	#define mid ((l+r)>>1)
	int init[mx],val[mx<<2],lazy[mx<<2];
	inline void init(int n){
		for(int i=1;i<=n;++i)init[i]=fio.read();
	}
	inline void pushup(int rt){val[rt]=val[lson]+val[rson]];}
	inline void pushdown(int rt){
		val[lson]+=lazy[rt];val[rson]+=lazy[rt];lazy[lson]+=lazy[rt];lazy[rson]+=lazy[rt];
		lazy[rt]=0;
	}
	inline void build(int rt,int l,int r)
	{
		if(l==r){
			val[rt]=init[l];return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushup(rt);
	}
	inline void update(int rt,int l,int r,int ul,int ur,int add)
	{
		if(ul>r || ur<l)return;
		if(ul<=l && ur>=r){
			val[rt]+=add;lazy[rt]+=add;
			return;
		}
		pushdown(rt);
		update(lson,l,mid,ul,ur,add);update(rson,mid+1,r,ul,ur,add);
		pushup(rt);
	}
	inline int query(int rt,int l,int r,int ql,int qr)
	{
		if(ql>r || qr<l)return 0;
		if(ql<=l && qr>=r)return val[rt];
		pushdown(rt);
		return query(lson,l,mid,ql,qr)+query(rson,mid+1,r,ql,qr);
	}
	#undef mid 
};
struct st{
	Log2[1]=0;
	for(int i=2;i<=n;++i)Log2[i]=Log2[i/2]+1;
	for(int j=1;j<=Log2[n];++j)
	{
	    for(int i=1;i+(1<<j)-1<=n;++i)
	    {
	        f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	        //printf("f[%d][%d]=max(f[%d][%d],f[%d][%d])=%d\n",i,j,i,j-1,i+(1<<(j-1)),j-1,f[i][j]);
	    }
	}
	
	for(int i=1;i<=m;++i)
	{
	    scanf("%d%d",&S,&E);
	    int k=Log2[E-S+1];
	    printf("%d\n",max(f[S][k],f[E-(1<<k)+1][k]));
	}
};
struct mergesort{
	void mergesort(int l,int r)
	{
    	if(l==r)return;
    	int mid=(l+r)>>1;
    	mergesort(l,mid);mergesort(mid+1,r);
    	int i=l,j=mid+1,t=l;
   		while(i<=mid || j<=r)
   		{
        	if(i>mid ||(j<=r && a[i]>a[j]))
            	b[t++]=a[j++];
        	else{
            	ans+=j-mid-1;
            	b[t++]=a[i++];
        	}
    	}
    	for(int i=l;i<=r;++i)a[i]=b[i];
    }

};
struct lca{
	void dfs(int x,int fa,int l)
	{
	    dep[x]=dep[fa]+1;
	    dfn[x]=++id;s[id]=x;dis[x]=dis[fa]+l;anc[x][0]=fa;
	    for(int i=1;i<MAXLOG;++i)anc[x][i]=anc[anc[x][i-1]][i-1];
	    for(int i=head[x];i;i=nxt[i])
	        if(to[i]!=fa)dfs(to[i],x,dist[i]);
	}
	
	ll getlca(int x,int y){
	    ll ans=dis[x]+dis[y];if(dep[x]<dep[y])swap(x,y);
	    for(int i=MAXLOG-1;i>=0;i--)
	        if(dep[anc[x][i]]>=dep[y])x=anc[x][i];
	    if(x==y)return ans-2*dis[y];
	    for(int i=MAXLOG-1;i>=0;i--)
	        if(anc[x][i]!=anc[y][i]){
	            x=anc[x][i];y=anc[y][i];
	        }
	    return ans-2*dis[anc[x][0]];
	}
};
struct dij{
	int head[mx],dis[mx];bool vis[mx];
	struct edge{
	    int dis,to,next;
	}e[mx];
	struct node{
	    int dis,pos;
	    bool operator <(const node &x)const{
	        return x.dis<dis;
	    }
	};
	priority_queue <node> q;
	void build(int u,int v,int w)
	{
	    e[++cnt].dis=w;
	    e[cnt].to=v;
	    e[cnt].next=head[u];
	    head[u]=cnt;
	}
	void dijkstra()
	{
	    dis[S]=0;q.push(node{0,S});
	    while(!q.empty())
	    {
	        int x=q.top().pos;q.pop();
	        if(vis[x])continue;
	        vis[x]=1;       
	        for(int i=head[x];i;i=e[i].next)
	        {
	            int y=e[i].to;
	            if(dis[x]+e[i].dis<dis[y])
	            {
	                dis[y]=dis[x]+e[i].dis;
	                if(!vis[y])q.push(node{dis[y],y});
	            }
	        }
	    }
	}
};
struct floyd{
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(i!=j && i!=k && j!=k)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
};
struct spfa{
	struct edge{
	    int to,dis,from,nxt;
	}e[mx<<2];
	int head[mx],dis[mx],cnt[mx],inq[mx],n,m;
	queue <int> q;
	inline int SPFA(int s)
	{
	    while(!q.empty())q.pop();
	    q.push(s);
	    inq[s]=1;dis[s]=0;
	    while(!q.empty())
	    {
	        int x=q.front();q.pop();
	        inq[x]=0;
	        for(int i=head[x];i;i=e[i].nxt){
	            int y=e[i].to;
	            if(dis[y]>dis[x]+e[i].dis){
	                dis[y]=dis[x]+e[i].dis;
	                if(!inq[y]){
	                    inq[y]=1;
	                    q.push(y);
	                    if(++cnt[y]>=n)return 1;
	                }
	            }
	        }
	    }
	    return 0;
	}
};
struct kruskal{
	struct edge{
	    int start,to,val;
	}e[km<<1];
	
	inline int find(int x)
	{
	    while(x!=fa[x])x=fa[x]=fa[fa[x]];
	    return x;
	}
	
	inline bool cmp(edge x,edge y)
	{
	    return x.val<y.val;//ÏÈsort
	}
	
	inline void kruskal()
	{
	    for(int i=1;i<=M;++i)
	    {
	        int u=find(e[i].start),v=find(e[i].to);
	        if(u==v)continue;
	        ans+=e[i].val;
	        fa[u]=v;
	        cnt++;//cout<<cnt<<endl;
	        if(cnt==N-1){ok=1;break;}
	    }
	}
};
struct bignum{
	
};
struct hashi{
	HASH[0][1]=HASH[0][0]=(uint)s[0];
    for(int i=1;i<len;++i)
        for(int w=0;w<=1;++w)
            HASH[i][w]=HASH[i-1][w]*mod[w]+(uint)s[i];
};
struct mathematics{
	struct exgcd{
		//EXGCD ax=1 mod b
		void exgcd(ll a,ll b,ll &x,ll &y)
		{
		    if(!b){
		        x=1;y=0;
		    }
		    else{
		        exgcd(b,a%b,y,x);
		        y-=(a/b)*x;
		    }
		}
	};
	struct getprimes{
		const int mx=1e5+5;
		int v[mx],primes[mx],cnt,n;
		for(int i=2;i<=n;++i)
		{
			if(!v[i]){
				v[i]=i;primes[++cnt]=i;
			}
			for(int j=1;j<=cnt;++j)
			{
				if(primes[j]>v[i] || primes[j]>n/i)break;
				v[i*primes[j]]=i;
			}
		}
	};
	struct C{//yanghuisanjiao
		for(int i=0;i<mx;++i)C[i][0]=C[i][i]=1;
		for(int i=1;i<mx;++i)
			for(int j=1;j<mx;++j)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	};
	struct niyuan{
		const int mx=3e6+5;
	    ll inv[mx];
		inv[1]=1;
    	for(int i=2;i<=n;++i)
        	inv[i]=(p-p/i)*inv[p%i]%p;
	};
};
struct matrix{
	struct node{
		ll mat[mx][mx];
	    inline void print()
	    {
	        for(int i=1;i<=n;++i,printf("\n"))
	            for(int j=1;j<=n;++j)
	                printf("%lld ",mat[i][j]);
	    }
	    inline void input()
	    {
	        for(int i=1;i<=n;++i)
	            for(int j=1;j<=n;++j)
	                scanf("%lld",&mat[i][j]);
	    }
	    inline void build()
	    {
	        for(int i=1;i<=n;++i)mat[i][i]=1;
	    }
	}a,ans;
	node mul(node &a,node &b)
	{
	    node c;
	    for(int k=1;k<=n;++k)
	        for(int i=1;i<=n;++i)
	            for(int j=1;j<=n;++j)
	                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j]%mod)%mod;
	    return c;
	}
};
struct scc{
	const int mx=1e5+5;
	stack<int> sta;
	bool instack[mx],vis[mx];
	int dfn[mx],low[mx],idx=0,scc_cnt=0,in_scc[mx],in[mx],val[mx];
	vector <int> G[mx],scc[mx];
	void tarjan(int u)
	{
	    dfn[u]=low[u]=++idx;
	    instack[u]=1;
	    sta.push(u);
	    for(int e=0;e<G[u].size();++e)
	    {
	        int v=G[u][e];
	        if(!dfn[v]){//tree edge
	            tarjan(v);
	            low[u]=min(low[u],low[v]);
	        }
	        else if(instack[v])low[u]=min(low[u],dfn[v]);//not tree, v need to be popped
	    }
	    if(dfn[u]==low[u]){
	        ++scc_cnt;
	        int v;
	        do{
	            v=sta.top();sta.pop();
	            instack[v]=0;scc[scc_cnt].push_back(v);
	            in_scc[v]=scc_cnt;
	        }while(v!=u);
	    }
	}
	void solve()
	{
	    for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	}
};
struct ae_ap{
	void ae_tarjan(int u)
	{
	    dfn[u]=low[u]=++idx;
	    for(int e=0;e<G[u].size();++e)
	    {
	        int v=G[u][e];
	        if(!dfn[v]){
	            fa[v]=u;
	            ae_tarjan(v);
	            low[u]=min(low[u],low[v]);
	            if(low[v]>dfn[u]){
	                ce[cec][0]=u;ce[cec++][1]=v;
	            }
	        }
	        else if(v!=fa[u])low[u]=min(low[u],dfn[v]);
	    }
	}
	
	void ap_tarjan(int u)
	{
	    int children=0;
	    dfn[u]=low[u]=++idx;
	    for(int e=0;e<G[u].size();++e)
	    {
	        int v=G[u][e];
	        if(!dfn[v]){
	            ++children;
	            fa[v]=u;
	            ap_tarjan(v);
	            low[u]=min(low[u],low[v]);
	            if(!fa[u] && children>1)ap[u]=1;
	            else if(fa[u] && low[v]>=dfn[u])ap[u]=1;
	        }
	        else if(v!=fa[u])low[u]=min(low[u],dfn[v]);
	    }
	
	}
};
struct timer{
	clock_t beg;
	inline void start(){beg=clock();}
	inline void end(){printf("%lf\n",double(clock()-beg)/CLOCKS_PER_SEC);}
}runtime;
struct ksm{
	ull solve1()//Quickpower
	{
	    ull ans=1,base=a;
	    while(b>0)
	    {
	        if(b&1)ans=ans*base%p;
	        base=base*base%p;
	        b>>=1;
	    }
	    return ans;
	}
};
struct toposort(){
	void topo()
	{
	    for(int i=1;i<=N;++i)
	        if(!in[i])q.push(i);
	    while(!q.empty())
	    {
	        int x=q.front();q.pop();
	        if(vis[x])return;
	        vis[x]=1;ans[++ctr]=x;
	        for(int i=head[x];i;i=e[i].nxt)
	        {
	            int y=e[i].to;
	            if(vis[y])return;
	            if(!--in[y])q.push(y);
	        }
	    }
	    if(ctr<N)return;
	}
}

inline void init()
{
	n=fio.read();m=fio.read();
	runtime.start();
}

inline void solve()
{
	
}

inline void print()
{
	
	runtime.end();
}

int main()
{
	init();
	solve();
	print();
	return 0;
}
