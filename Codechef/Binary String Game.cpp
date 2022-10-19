#include<bits/stdc++.h>
#ifdef xay5421
#define D(...) fprintf(stderr,__VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ "="),debug_helper::debug(__VA_ARGS__),D("\n")
#include"/home/xay5421/debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define pb push_back
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define each(x,v) for(auto&x:v)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
template<class T>void rd(T&x){int f=0,c;while(!isdigit(c=getchar()))f^=!(c^45);x=(c&15);while(isdigit(c=getchar()))x=x*10+(c&15);if(f)x=-x;}
template<class T>void pt(T x,int c=-1){if(x<0)putchar('-'),x=-x;if(x>9)pt(x/10);putchar(x%10+48);if(c!=-1)putchar(c);}
using namespace std;
using LL=long long;
using ULL=unsigned long long;
const int N=200005;
int T,n;
char s[N];
bool take[N];
int len[N];
vector<int>e[N];
bool ok(int u,int hp){
	if(hp<0)return 0;
	if(e[u].empty())return 1;
	each(x,e[u])if(ok(x,hp+1-(len[u]-len[x]-2)/2))return 1;
	return 0;
}
bool solve(vector<int>v){
	rep(i,0,SZ(v))e[i].clear();
	len[SZ(v)]=SZ(v)+2;
	vector<int>st;
	rep(i,0,SZ(v)-1){
		if(v[i]==0){
			st.pb(i);
		}else{
			if(st.empty())return 0;
			int cur=st.back();
			len[cur]=i-cur+1;
			st.pop_back();
			int u=st.empty()?SZ(v):st.back();
			e[u].pb(cur);
		}
	}
	if(!st.empty())return 0;
	return ok(SZ(v),0);
}
bool check(int mid){
	rep(i,1,n){
		take[i]=0;
	}
	int cnt=0;
	rep(i,1,n){
		if(s[i]=='0'){
			if(++cnt<=mid*2){
				take[i]=1;
			}
		}
	}
	cnt=0;
	per(i,n,1){
		if(s[i]=='1'){
			if(++cnt<=mid*2){
				take[i]=1;
			}
		}
	}
	vector<int>v;
	rep(i,1,n)if(take[i]){
		v.pb(s[i]-'0');
	}
	if(SZ(v)<mid*4)return 0;
	return solve(v);
}
int main(){
#ifdef xay5421
	freopen("a.in","r",stdin);
#endif
	rd(T);
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		int l=1,r=n,ret=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				ret=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		printf("%d\n",ret);
	}
	return 0;
}
