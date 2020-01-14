#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
struct go{
	int r;
	int c;
	int num;
};
int map[51][51];
int n,m,k;
int play[7];
int visit[7];
vector<go> magic;
int dr[4] ={-1,0,1,0};
int dc[4] = {0,-1,0,1};
int ans=987654321;
void show(int data[][51])
{
	cout<<"S"<<endl;
	for(int i=0 ; i < n ; i++)
	{
		for(int j=0 ; j < m ; j++)
		{
			cout<<map[i][j]<<" ";
		}
		cout<<endl;
	}
}
int getdir(int d)
{
	if(d==3)
		return d=2;
	else if(d==2)
	return d=1;
	else if(d==1)
	return d=0;
	else if(d==0)
	return d=1;
}
void rotate(int sr, int sc, int num)
{
	for(int i=num; i>=1 ; i--)
	{
		int ssr = sr + i*dr[0];
		int ssc = sc + i*dc[1];
		int rr,cc;
		int dir=3;
		int nexttemp=map[ssr][ssc];
		int nowtemp=map[ssr][ssc];
		rr= ssr;
		cc =ssc;
		int cnt=0;
		while(true)
		{
			cnt++;
			nexttemp=nowtemp;
			int nr = rr +dr[dir];
			int nc = cc +dc[dir];
	//		cout<<"nr"<<nr<<"nc"<<nc<<endl;
			if(nr==ssr && nc==ssc)
			{
	//			cout<<"ASDF"<<endl;
				map[nr][nc]=nexttemp;
				break;
			}
			if( nr <ssr || nc <ssc || nr >ssr+i*2 || nc >ssc +i*2)
			{
	//			cout<<"AA"<<endl;
				dir=getdir(dir);
				continue;
			}
			nowtemp=map[nr][nc];
			map[nr][nc]=nexttemp;
			rr=nr;
			cc=nc;
		}
	}
}
void dfs(int now,int num)
{
	if(num==k)
	{
		int mapc[51][51];
		memcpy(mapc,map,sizeof(map));
		for(int i=1 ; i<=num ; i++)
		{
			int r = magic.at(play[i]-1).r;
			int c = magic.at(play[i]-1).c;
			int nu = magic.at(play[i]-1).num;
	//		cout<<"nu"<<nu<<endl;
			rotate(r,c,nu);
		}
		for(int i=0 ; i < n ; i++)
		{
			int sum=0;
			for(int j =0 ; j<m ; j++)
			{
				sum+=map[i][j];
		}
			if(ans>sum)
			{
				ans=sum;
			}
			
		}
		memcpy(map,mapc,sizeof(map));
		return;
	}
	if(num==k || num>k)
		return;
	for(int i=1;i<=k;i++)
	{
		if(visit[i]==1)
			continue;
		play[num+1]=i;
		visit[i]=1;
		dfs(i,num+1);
		visit[i]=0;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0 ; i < n ; i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	for(int i=0 ; i < k ; i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		magic.push_back({x-1,y-1,z});
	}
	for(int i=1 ; i <=k ; i++)
	{
		memset(visit,0,sizeof(visit));
		memset(play,0,sizeof(play));
		visit[i]=1;
		play[1]=i;
		dfs(i,1);
	}
	
	cout<<ans<<endl;
}