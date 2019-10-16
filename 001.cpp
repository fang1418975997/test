#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const int mx=1e5+10;
int sum[mx*40],L[mx*40],R[mx*40],T[mx],a[mx],b[mx];
int n,m,l,r,k,cnt;
void build(int& rt,int l,int r)
{
    rt=++cnt;
    sum[rt]=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(L[rt],l,mid);
    build(R[rt],mid+1,r);
}
void update(int& rt,int pre,int l,int r,int k)
{
    rt=++cnt;
    L[rt]=L[pre];
    R[rt]=R[pre];
    cout<<rt<<"---"<<pre<<endl;
    cout<<L[rt]<<" "<<L[pre]<<endl;
    cout<<R[rt]<<" "<<R[pre]<<endl;
    sum[rt]=sum[pre]+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(k<=mid) update(L[rt],L[pre],l,mid,k);
    else   update(R[rt],R[pre],mid+1,r,k);
}
int query(int a,int b,int l,int r,int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    int ans=sum[L[b]]-sum[L[a]];
    if(k<=ans) return query(L[a],L[b],l,mid,k);
    else return query(R[a],R[b],mid+1,r,k-ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(a+1,a+1+n);
    int len=unique(a+1,a+1+n)-a-1;
    cnt=0;
    build(T[0],1,len);
    for(int i=1;i<=cnt;i++)
        cout<<i<<" "<<L[i]<<endl;
    for(int i=1;i<=cnt;i++)
        cout<<i<<" "<<R[i]<<endl;

    for(int i=1;i<=n;i++)
    {
        update(T[i],T[i-1],1,len,lower_bound(a+1,a+1+len,b[i])-a);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&l,&r,&k);
        int ans=query(T[l-1],T[r],1,len,k);
        printf("%d\n",a[ans]);
    }
    return 0;
}
