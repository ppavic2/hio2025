#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pii=pair<int,int>;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
#define pb push_back
#define all(a) begin(a),end(a)

const int N=200010,MOD=1e9+7,M=1<<20;
const char en='\n';
const ll LLINF=1ll<<61;

int n,q,h[N];
array<ll,6> seg[M*2+10],id={0,0,LLINF,0,0,0}; //sum, length, min prefix sum, how many prefix min prefix sums, how many suffix min prefix sums, how many min prefix sum subarrays

array<ll,6> mer(array<ll,6> a,array<ll,6> b)
{
	array<ll,6> c;
	c[0]=a[0]+b[0];
	c[1]=a[1]+b[1];
	c[2]=min(a[2],a[0]+b[2]);
	if (a[1]==0 || a[2]==c[2]) c[3]=((a[3]==a[1] && a[0]+b[2]==c[2]) ? a[3]+b[3] : a[3]);
	else c[3]=0;
	if (b[1]==0 || a[0]+b[2]==c[2]) c[4]=((b[4]==b[1] && a[2]==c[2]) ? a[4]+b[4] : b[4]);
	else c[4]=0;
	c[5]=0;
	if (a[2]==c[2]) c[5]+=a[5];
	if (a[0]+b[2]==c[2]) c[5]+=b[5];
	if (a[2]==c[2] && a[0]+b[2]==c[2]) c[5]+=a[4]*b[3];
	return c;
}

void upd(int i,int x)
{
	seg[i+=M][0]+=x;
	seg[i][1]=1;
	seg[i][2]=seg[i][0];
	seg[i][3]=1;
	seg[i][4]=1;
	seg[i][5]=1;
	for (i/=2;i;i/=2) seg[i]=mer(seg[i*2],seg[i*2+1]);
}

array<ll,6> ge(int l,int r)
{
	l+=M;
	r+=M;
	array<ll,6> le=id,ri=id;
	while (l<r)
	{
		if (l&1) le=mer(le,seg[l]),++l;
		if (r&1) ri=mer(seg[r-1],ri),--r;
		l/=2;
		r/=2;
	}
	return mer(le,ri);
}

ll getAns()
{
	auto re=ge(0,h[n/2]);
	if (re[2]==0) return re[5];
	else return 0;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	for (int i=0;i<n;++i) cin>>h[i];
	for (int i=0;i<h[n/2];++i) seg[i+M]={0,1,0,1,1,1};
	for (int i=h[n/2];i<M;++i) seg[i+M]=id;
	for (int i=M-1;i;--i) seg[i]=mer(seg[i*2],seg[i*2+1]);
	for (int i=0;i<n/2;++i)
	{
		int mi=min(h[i],h[n-i-1]),ma=max(h[i],h[n-i-1]);
		upd(mi,1);
		upd(ma,-1);
	}
	cout<<getAns()<<en;
	while (q--)
	{
		int i,x;
		cin>>i>>x;
		--i;
		int mi=min(h[i],h[n-i-1]),ma=max(h[i],h[n-i-1]);
		upd(mi,-1);
		upd(ma,1);
		h[i]=x;
		mi=min(h[i],h[n-i-1]),ma=max(h[i],h[n-i-1]);
		upd(mi,1);
		upd(ma,-1);
		cout<<getAns()<<en;
	}
}

