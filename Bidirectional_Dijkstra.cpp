#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

const int MX = 1e5;
const int MAX = 1e8;

vector<pair<int,int > > g[MX],gr[MX];
int dist[MX],distr[MX], parent[MX],parentr[MX];
bool vis[MX],visr[MX];
vector<int> path;

int BiDirectionalDijkstra(int n, int s, int d) {
	

	priority_queue<pair<int,int> , vector<pair<int,int > > , greater<pair<int,int> > > forward,backward;
	dist[s] = 0;
	distr[d] = 0;
	parent[s]= s;
	parentr[d] = d;

	forward.push({0,s});
	backward.push({0,d});
	int f = 0;
	while(!forward.empty() && !backward.empty()) {
		pair<int,int> tmp = forward.top(); forward.pop();
		if(visr[tmp.S]) {f = 1; break;}

		if(!vis[tmp.S]) {
			vis[tmp.S] = true;
			for(int i = 0; i < g[tmp.S].size(); i++) {
				if(dist[tmp.S]+g[tmp.S][i].S < dist[g[tmp.S][i].F]){
					dist[g[tmp.S][i].F] = dist[tmp.S]+g[tmp.S][i].S;
					forward.push({dist[g[tmp.S][i].F],g[tmp.S][i].F});
					parent[g[tmp.S][i].F] = tmp.S;

				}
			}
		}
		
		tmp = backward.top(); backward.pop();
		if(vis[tmp.S]) {f = 1; break;}
		
		if(!visr[tmp.S]) {
			visr[tmp.S] = true;
			for(int i = 0; i < gr[tmp.S].size(); i++) {
				if(distr[tmp.S]+gr[tmp.S][i].S < distr[gr[tmp.S][i].F]){
					distr[gr[tmp.S][i].F] = distr[tmp.S]+gr[tmp.S][i].S;
					backward.push({dist[gr[tmp.S][i].F],gr[tmp.S][i].F});
					parentr[gr[tmp.S][i].F] = tmp.S;
				}
			}
		}
	}
	if(f == 0) return -1;

	int ans = MAX, ubest = -1;
	for(int i = 1; i <= n; i++){
		if(ans > dist[i] + distr[i]) {
			ans = dist[i] + distr[i];
			ubest = i;
		}
	}
	int last = ubest;
	while(last != s) {
		path.push_back(last);
		last = parent[last];
	}
	path.push_back(s);
	reverse(path.begin(), path.end());
	last = ubest;
	while(last != d) {
		last = parentr[last];
		path.push_back(last);
	}
	return ans;

}
int main()
{
	int u,v,n,m,s,c,d;
	scanf("%d%d", &n,&m);
	for(int i = 0; i <= n; i++) {g[i].clear(); gr[i].clear(); distr[i] = MAX;dist[i] = MAX; vis[i] = false; visr[i] = false;}
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &u,&v,&c);
		g[u].push_back({v,c});
		gr[v].push_back({u,c});
	}
	scanf("%d%d", &s,&d);
	int ans = BiDirectionalDijkstra(n,s,d);
	printf("Distance between (%d,%d) is %d\n", s,d,ans);
	// print path
	cout << "Path is " << endl;
	for(int i = 0; i < path.size()-1; i++)
		cout << path[i] << " -> ";
	cout << path[path.size()-1] << endl;
	
	
return 0;
}