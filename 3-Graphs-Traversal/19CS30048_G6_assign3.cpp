#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct{
	int x, y;
}POINT;

//***STACK IMPLEMENTATION***
struct stack{
    POINT* val;
    stack* next;
    stack(int a, int b) {
        val = new POINT;
        val->x = a;
        val->y = b;
        next = NULL;
    }
};

stack* head;

void insert_stack(POINT p) {
    stack* s = new stack(p.x, p.y);
    s->next = head;
    head = s;
}

void pop_stack() {
    head = head->next;
}

POINT* top_stack() {
    if (head != NULL) {
        return head->val;
    }
    return NULL;
}

bool empty_stack() {
    if (head == NULL) {
        return true;
    }
    return false;
}

//***QUEUE IMPLEMENTATION***
struct QUEUE{
	POINT* myqueue;
	int front, rear;

    void init(int size){
		front = -1;
		rear = -1;
		myqueue = new POINT[size];
    }

	int isempty(){
		if(front == -1) return 1;
		else return 0;
    }

	void enqueue(POINT p){
		if(front == -1) front = 0;
		rear++;
		myqueue[rear].x = p.x;
		myqueue[rear].y = p.y;
    }

	POINT dequeue(){
		POINT p;
		p.x = myqueue[front].x;
		p.y = myqueue[front].y;
		if(front >= rear){
			front = -1;
			rear = -1;
        }
		else
			front++;
   		return p;
    }
};

//Function to print the intitial grid in terms of * and -
void print_grid(int** maze, int a, int b){
	cout<<"Grid of stones is:\n";
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			if(maze[i][j]==1) cout<<'*';
			else cout<<'-';
		}
		cout<<endl;
	}
	cout<<endl;
}

//function to check if the cell can be accessed or not
bool is_valid(int** maze, int a, int b, POINT temp){
	int x = temp.x;
	int y = temp.y;
	if((x>=0) && (y>=0) && (x<a) && (y<b) && maze[x][y]==1)
		return true;
	return false;
}

//Function to implement the first strategy
int strategy1(int** maze, int a, int b, POINT starting, POINT ending){
	QUEUE q;
	q.init(100000);
	q.enqueue(starting);
	int visited[a][b];
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			visited[i][j]=0;
		}
	}
	visited[starting.x][starting.y]=1;
	int x_move[4] = {1, 0, -1, 0};
	int y_move[4] = {0, 1, 0, -1};
	while(!q.isempty()){
		POINT t = q.dequeue();
		for(int i=0; i<4; i++){
			POINT temp;
			temp.x = t.x + x_move[i];
			temp.y = t.y + y_move[i];
			if(is_valid(maze, a, b, temp) && visited[temp.x][temp.y]==0){
				visited[temp.x][temp.y]=1;
				q.enqueue(temp);
			}
		}
	}
	if(visited[ending.x][ending.y]==1) return 1;
	else return 0;
}

void print_answer(POINT starting){
	POINT answer[1000];
	int count = 0;
	while(!empty_stack()){
        POINT* p = top_stack();
        answer[count].x = p->x;
        answer[count].y = p->y;
        pop_stack();
        count++;
    }
    cout<<"("<<starting.x<<","<<starting.y<<")";
    while(count--){
        POINT q = answer[count];
        cout << " -> (" << q.x << ',' << q.y << ')';
    }
}

void dfs(int** maze, int** visited, POINT p, POINT starting, POINT ending, int a, int b) {
    visited[p.x][p.y] = 1;

    int x_move[4] = {1, 0, -1, 0};
	int y_move[4] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++){
    	POINT temp;
        temp.x = p.x + x_move[i];
        temp.y = p.y + y_move[i];
        if (temp.x == ending.x and temp.y == ending.y){
        	insert_stack(temp);
        	print_answer(starting);
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                    visited[i][j] = 1;
                }
            }
        }
        if (is_valid(maze, a, b, temp) && visited[temp.x][temp.y]==0){
            insert_stack(temp);
            visited[temp.x][temp.y] = 1;
            dfs(maze, visited, temp, starting, ending, a, b);
        }
    }
    pop_stack();
}

void strategy2(int** maze, int a, int b, POINT starting, POINT ending){
	int** visited = new int*[a];
	for(int i=0; i<a; i++) visited[i] = new int[b];
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			visited[i][j]=0;
		}
	}
    dfs(maze, visited, starting, starting, ending, a, b);
}

int main(){
	int** maze;
	int a, b, n;
	cin>>a>>b>>n;
	maze = new int*[a];
	for(int i=0; i<a; i++) maze[i] = new int[b];
	int* x_unstable = new int[n];
	int* y_unstable = new int[n];
	for(int i=0; i<n; i++) cin>>x_unstable[i];
	for(int i=0; i<n; i++) cin>>y_unstable[i];
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			maze[i][j]=1;
		}
	}
	for(int i=0; i<n; i++){
		maze[x_unstable[i]][y_unstable[i]]=0;
	}
	print_grid(maze, a, b);
	POINT starting, ending;
	cin>>starting.x>>starting.y>>ending.x>>ending.y;

	int ans = strategy1(maze, a, b, starting, ending);

	if(ans==1){
		cout<<"Path exists\n";
	}
	else cout<<"Path does not exist\n";
	if(ans) strategy2(maze, a, b, starting, ending);
	return 1;
}
