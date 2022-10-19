#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
#define rep(i,n) for(int i=0;i<int(n);i++)
#define rep1(i,n) for(int i=1;i<=int(n);i++)
#define per(i,n) for(int i=int(n)-1;i>=0;i--)
#define per1(i,n) for(int i=int(n);i>0;i--)
#define all(c) c.begin(),c.end()
#define si(x) int(x.size())
#define pb push_back
#define eb emplace_back
#define fs first
#define sc second
template<class T> using V = vector<T>;
template<class T> using VV = vector<vector<T>>;
template<class T,class U> bool chmax(T& x, U y){
	if(x<y){ x=y; return true; }
	return false;
}
template<class T,class U> bool chmin(T& x, U y){
	if(y<x){ x=y; return true; }
	return false;
}
template<class T> void mkuni(V<T>& v){sort(all(v));v.erase(unique(all(v)),v.end());}
template<class T> int lwb(const V<T>& v, const T& a){return lower_bound(all(v),a) - v.begin();}
template<class T>
V<T> Vec(size_t a) {
    return V<T>(a);
}
template<class T, class... Ts>
auto Vec(size_t a, Ts... ts) {
  return V<decltype(Vec<T>(ts...))>(a, Vec<T>(ts...));
}
template<class S,class T> ostream& operator<<(ostream& o,const pair<S,T> &p){
	return o<<"("<<p.fs<<","<<p.sc<<")";
}
template<class T> ostream& operator<<(ostream& o,const vector<T> &vc){
	o<<"{";
	for(const T& v:vc) o<<v<<",";
	o<<"}";
	return o;
}
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n-1); }

#ifdef LOCAL
#define show(x) cerr << "LINE" << __LINE__ << " : " << #x << " = " << (x) << endl
void dmpr(ostream& os){os<<endl;}
template<class T,class... Args>
void dmpr(ostream&os,const T&t,const Args&... args){
	os<<t<<" ~ ";
	dmpr(os,args...);
}
#define shows(...) cerr << "LINE" << __LINE__ << " : ";dmpr(cerr,##__VA_ARGS__)
#define dump(x) cerr << "LINE" << __LINE__ << " : " << #x << " = {";  \
	for(auto v: x) cerr << v << ","; cerr << "}" << endl;
#else
#define show(x) void(0)
#define dump(x) void(0)
#define shows(...) void(0)
#endif

template<class D> D divFloor(D a, D b){
	return a / b - (((a ^ b) < 0 && a % b != 0) ? 1 : 0);
}
template<class D> D divCeil(D a, D b) {
	return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

map<pair<V<int>,V<int>>,V<int>> mp;
bool god(V<int> a, V<int> b){
	return mp.count(make_pair(a,b));
}

bool esp(V<int> a, V<int> b){
	int n = si(a);
	if(a[0] != 1) return false;
	if(b[n-1] != 1) return false;
	if(a[n-1] != b[0]) return false;
	rep(i,n-1) if(a[i] > a[i+1] || a[i]+1 < a[i+1]) return false;
	rep(i,n-1) if(b[i] < b[i+1] || b[i] > b[i+1]+1) return false;
	int L = b[0];
	// rep1(l,n-1) if(a[l-1] + b[l] < L) return false;
	rep1(i,n-2){
		if(a[i]+b[i] <= L) return false;
		if(a[i-1] < a[i] && b[i] > b[i+1] && a[i]+b[i] != L+1) return false;
	}
	return true;
}
int LIS(V<int> a){
	int n = si(a);
	V<int> dp(n,1);
	rep1(i,n-1){
		rep(j,i) if(a[j]<a[i]) chmax(dp[i],dp[j]+1);
	}
	return *max_element(all(dp));
}
void god_pre(int N){
	V<int> p(N); iota(all(p),0);
	do{
		V<int> A(N),B(N);
		rep(i,N){
			A[i] = LIS(V<int>(p.begin(),p.begin()+i+1));
			B[i] = LIS(V<int>(p.begin()+i, p.end()));
		}
		mp[make_pair(A,B)] = p;
	}while(next_permutation(all(p)));
}
void test(int N){
	god_pre(N);
	V<int> a(N),b(N);
	auto dfs2 = [&](auto& self,int i,int from)->void{
		if(i == -1){
			if(god(a,b) != esp(a,b)){
				// show(a);show(b);
				// show(god(a,b));
				// show(esp(a,b));
				// show(mp[make_pair(a,b)]);
				// assert(0);
				cout << a << " " << b << endl;
				show(god(a,b));
				show(esp(a,b));
				show(mp[make_pair(a,b)]);
			}
			return;
		}
		for(int v=from;v<=N-i;v++){
			b[i] = v;
			self(self,i-1,v);
		}
	};
	auto dfs = [&](auto& self,int i,int from)->void{
		if(i == N){
			dfs2(dfs2,N-1,1);
			return;
		}
		for(int v=from;v<=i+1;v++){
			a[i] = v;
			self(self,i+1,v);
		}
	};
	dfs(dfs,0,1);
}

void solve(){
	int N; cin >> N;
	V<int> a(N),b(N);
	rep(i,N) cin >> a[i];
	rep(i,N) cin >> b[i];
	if(!esp(a,b)){
		cout << "No" << endl;
		return;
	}
	V<bool> inc(N),dec(N);
	inc[0] = 1;
	rep1(i,N-1) inc[i] = a[i-1]<a[i];
	dec[N-1] = 1;
	rep(i,N-1) dec[i] = b[i]>b[i+1];
	V<int> sep; sep.pb(-1);
	rep(i,N){
		if(inc[i] && dec[i]) sep.pb(i);
	}
	sep.pb(N);
	V<int> p(N,-1);
	for(int i: sep) if(i != -1 && i != N) p[i] = i;
	rep(_,si(sep)-1){
		int l = sep[_]+1, r = sep[_+1]-1;	//[l,r]
		if(l>r) continue;
		int v = l;
		for(int i=l;i<=r;i++) if(!inc[i] && dec[i]) p[i] = v++;
		for(int i=r;i>=l;i--) if(!inc[i] && !dec[i]) p[i] = v++;
		for(int i=l;i<=r;i++) if(inc[i] && !dec[i]) p[i] = v++;
		assert(v == r+1);
	}
	cout << "Yes" << endl;
	for(int v: p) cout << v+1 << " ";
	cout << endl;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);		//DON'T USE scanf/printf/puts !!
	cout << fixed << setprecision(20);

	// int N; cin >> N;
	// test(N);

	int T; cin >> T;
	while(T--) solve();
}
