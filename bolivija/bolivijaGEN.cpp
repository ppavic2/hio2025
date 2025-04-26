#include "testlib.h"
#include <iostream>
#include <cassert>
#define pb push_back
#define all(a) begin(a),end(a)

using namespace std;
using vi=vector<int>;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    string typ=opt<string>("typ");
    if (typ=="random")
    {
    	int t=opt<int>("t");
    	int n=opt<int>("n");
    	assert(n%2==1);
    	int q=opt<int>("q");
    	int maxa=opt<int>("maxa");
    	bool ch1=opt<bool>("ch1");
    	vi ns=rnd.partition(t,n/2,1);
    	vi as=rnd.partition(t,maxa,1);
    	vi pra={0};
    	for (auto x: as) pra.pb(pra.back()+x);
    	vi prn={0};
    	for (auto x: ns) prn.pb(prn.back()+x);
    	vi perm=rnd.distinct(n/2,0,n/2-1);
    	vi v(n);
    	v[n/2]=maxa;
    	for (int i=0;i<n/2;++i)
    	{
    		int ind=perm[i],test=upper_bound(all(prn),i)-prn.begin()-1;
    		v[ind]=rnd.next(pra[test],pra[test+1]);
    		v[n-ind-1]=rnd.next(pra[test],pra[test+1]);
		}
		cout<<n<<' '<<q<<endl;
		for (int i=0;i<n-1;++i) cout<<v[i]<<' ';
		cout<<v.back()<<endl;
		for (int z=0;z<q;++z)
		{
			int i=rnd.next(0,n/2-1);
			int ind=perm[i],test=upper_bound(all(prn),i)-prn.begin()-1;
			if (rnd.next(0,1)) ind=n-ind-1;
			if (ch1) v[ind]=rnd.next(max(pra[test],v[ind]-1),min(pra[test+1],v[ind]+1));
			else v[ind]=rnd.next(pra[test],pra[test+1]);
			cout<<ind+1<<' '<<v[ind]<<'\n';
		}
	}
	if (typ=="smalllen")
	{
		int n=opt<int>("n");
    	assert(n%2==1);
    	int q=opt<int>("q");
    	assert(q%2==0);
    	int maxa=opt<int>("maxa");
    	int maxlen=opt<int>("maxlen");
    	bool ch1=opt<bool>("ch1");
    	cout<<n<<' '<<q<<endl;
    	vi l(n/2),r(n/2);
    	for (int i=0;i<n/2;++i)
    	{
    		l[i]=rnd.next(0,maxa);
    		r[i]=rnd.next(max(0,l[i]-maxlen),min(maxa,l[i]+maxlen));
		}
		
		for (int i=0;i<n/2;++i) cout<<l[i]<<' ';
		cout<<maxa<<' ';
		for (int i=0;i<n/2-1;++i) cout<<r[n/2-i-1]<<' ';
		cout<<r[0]<<endl;
		for (int z=0;z<q/2;++z)
		{
			int i=rnd.next(0,n/2-1);
			int j=n-i-1;
			if (ch1)
			{
				l[i]=rnd.next(max(0,l[i]-1),min(maxa,l[i]+1));
				r[i]=rnd.next(max(0,r[i]-1),min(maxa,r[i]+1));
			}
			else
			{
				l[i]=rnd.next(0,maxa);
	    		r[i]=rnd.next(max(0,l[i]-maxlen),min(maxa,l[i]+maxlen));
	    	}
    		cout<<i+1<<' '<<l[i]<<'\n';
    		cout<<j+1<<' '<<r[i]<<'\n';
		}
	}
	if (typ=="manychanges")
	{
		int n=opt<int>("n");
    	assert(n%2==1);
    	int q=opt<int>("q");
		int maxa=opt<int>("maxa");
		set<int> s;
		s.insert(0);
		s.insert(maxa);
		while ((int)s.size()<n-1) s.insert(rnd.next(0,maxa));
		vi vv(all(s));
		vi perm=rnd.distinct(n/2,0,n/2-1);
		vi v(n);
		v[perm.back()]=rnd.next(0,maxa);
		v[n/2]=maxa;
		v[n-perm.back()-1]=rnd.next(0,maxa);
		for (int i=0;i<n/2-1;++i)
		{
			if (rnd.next(0,1))
			{
				v[perm[i]]=vv[i*2+1];
				v[n-perm[i]-1]=vv[i*2+2];
			}
			else
			{
				v[perm[i]]=vv[i*2+2];
				v[n-perm[i]-1]=vv[i*2+1];
			}
		}
		cout<<n<<' '<<q<<endl;
		for (int i=0;i<n-1;++i) cout<<v[i]<<' ';
		cout<<v.back()<<endl;
		for (int z=0;z<q;++z)
		{
			int i;
			if (rnd.next(0,1)) i=perm.back();
			else i=n-perm.back()-1;
			int x=rnd.next(0,maxa);
			cout<<i<<' '<<x<<'\n';
		}
	}
}
