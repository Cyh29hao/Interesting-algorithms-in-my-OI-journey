#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mx=5e4+5,col=225;
int n,m,k,a[mx];
ll ans[mx],now=0,cnt[mx];
inline int bel(int x){
	return (x-1)/col+1;
}
struct query{
	int l,r,id;
	inline bool operator < (const query &x)const{
		return bel(l)!=bel(x.l)?bel(l)<bel(x.l):(bel(l)&1?r<x.r:r>x.r);
	}
}q[mx];
inline void add(int pos){
	now-=cnt[a[pos]]*cnt[a[pos]];cnt[a[pos]]++;
	now+=cnt[a[pos]]*cnt[a[pos]];
}
inline void del(int pos){
	now-=cnt[a[pos]]*cnt[a[pos]];cnt[a[pos]]--;
	now+=cnt[a[pos]]*cnt[a[pos]];
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=m;++i)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(int i=1;i<=m;++i){
		int ql=q[i].l,qr=q[i].r;
		while(l<ql)del(l++);
		while(l>ql)add(--l);
		while(r<qr)add(++r);
		while(r>qr)del(r--);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;++i)printf("%lld\n",ans[i]);
	return 0;
}