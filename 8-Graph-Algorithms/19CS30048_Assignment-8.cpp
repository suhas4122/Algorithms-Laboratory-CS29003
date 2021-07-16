/*****
Suhas Jain
19CS30048
Lab-8
Graphs
******/

/********
SOLUTION
In my solution I have done a binary search over the time possible
and then through dfs i have checked if it is possible to reach the
destination at that point of time
And in this way I have calculated the minimum time possible
Then at that time i have made an array and stores 1 if it is
accessible and 0 if it is not, now on this array i have done dfs
and also stored the steps so we can trace the path from the starting
point and then print it in the end
*********/
#include <bits/stdc++.h>
using namespace std;

int n, sx, sy, fx, fy;
int h[4] = {1, -1, 0, 0};
int v[4] = {0, 0, 1, -1};

bool isvalid(int x, int y){
	return (x<n && y<n && x>=0 && y>=0);
}

int helper(int **temp, int**visited, int x, int y){
	if(x==fx && y==fy) return 1;
	for(int i=0; i<4; i++){
		int x1 = x+h[i];
		int y1 = y+v[i];
		int ans = 0;
		if(isvalid(x1, y1) && !visited[x1][y1] && temp[x1][y1]){
			visited[x1][y1]=1;
			ans = helper(temp, visited, x1, y1);
			if(ans == 1){
				return 1;
			}
		}
		if(ans) break;
	}
	return 0;
}

bool dfs(int **temp){
	int ** visited = new int*[n];
	for(int i=0; i<n; i++){
		visited[i] = new int[n];
		for (int j=0; j<n; ++j){
			visited[i][j]=0;
		}
	}
	visited[sx][sy] = 1;
	for(int i=0; i<4; i++){
		int x1 = sx+h[i];
		int y1 = sy+v[i];
		if(isvalid(x1, y1) && temp[x1][y1]){
			int ans = helper(temp, visited, x1, y1);
			visited[x1][y1]=1;
			if(ans == 1){
				return true;
			}
		}
	}
	return false;
}

int path_dfs(int x, int y, int** temp, int** path, int** visited){
	if(x==fx && y==fy) return 1;
	for(int i=0; i<4; i++){
		int x1 = x+h[i];
		int y1 = y+v[i];
		int ans = 0;
		if(isvalid(x1, y1) && !visited[x1][y1] && temp[x1][y1]){
			visited[x1][y1]=1;
			ans = path_dfs(x1, y1, temp, path, visited);
			if(ans == 1){
				path[x][y] = i;
				return 1;
			}
		}
	}
	return 0;
}

int** find_path(int **temp){
	int **visited = new int*[n];
	int **p = new int*[n];
	for(int i=0; i<n; i++){
		visited[i] = new int[n];
		p[i] = new int[n];
		for (int j=0; j<n; ++j){
			visited[i][j]=0;
		}
	}
	path_dfs(sx, sy, temp, p, visited);
	return p;
}

int main(){
	cin>>n;

	int** graph;
	graph = new int*[n];
	for(int i=0; i<n; i++)
		graph[i] = new int[n];

	int max_time = 0;

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>graph[i][j];
			max_time = max(max_time, graph[i][j]);
		}
	}

	cin>>sx>>sy>>fx>>fy;

	int low = 0;
	int high = max_time;
	int mid;
	while(low<high){
		mid = (high+low)/2;
		int **temp = new int*[n];
		for(int i=0; i<n; i++){
			temp[i] = new int[n];
			for(int j=0; j<n; j++){
				if(graph[i][j]<=mid)
					temp[i][j] = 1;
				else
					temp[i][j] = 0;
			}
		}
		if(dfs(temp))
			high = mid;
		else
			low = mid+1;
	}
	int min_time = high;

	int **temp = new int*[n];
	for(int i=0; i<n; i++){
		temp[i] = new int[n];
		for(int j=0; j<n; j++){
			if(graph[i][j]<=min_time)
				temp[i][j] = 1;
			else
				temp[i][j] = 0;
		}
	}
	int **path;
	path = find_path(temp);

	cout<<"Minimum time taken is: "<<min_time<<endl;
	int i = sx;
	int j = sy;
	int count = 2;
	cout<<"The Path to reach from ("<<sx<<","<<sy<<") to ("<<sx<<","<<sy<<") is: \n";
	cout<<"("<<sx<<","<<sy<<")"<<" ";
	while(1){
		int k = path[i][j];
		if(i+h[k] == fx && j+v[k]== fy){
			cout<<"("<<i+h[k]<<","<<j+v[k]<<")"<<" ";
			break;
		}
		else{
			cout<<"("<<i+h[k]<<","<<j+v[k]<<")"<<" ";
		}
		i = i + h[k];
		j = j + v[k];
		count++;
		if((count-1)%6==0) cout<<endl;
	}
	cout<<"\nThe Number of Blocks traversed are: ";
	cout<<count;
	return 0;
}
