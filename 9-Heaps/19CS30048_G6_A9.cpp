/*******
Suhas Jain 
19CS30048
********/
#include<bits/stdc++.h>
using namespace std;

#define MAX_SIZE 100

typedef struct _job {
	int jobId;
	int startTime;
	int jobLength;
	int remLength;
}job;

typedef struct _heap {
	job list[MAX_SIZE];
	int numJobs;
}heap;

void initHeap(heap *H){
	H->numJobs = 0;
}

bool compare(job a,job b)
{
	if(a.remLength!=b.remLength)
	{
		return (a.remLength<b.remLength);
	}
	return (a.jobId<b.jobId);
}

void heapify(int i, heap *h)
{
	int size = h->numJobs;
	int temp = i;	
	int left = (2*i);
	int right = 2*i+1;

	if(left<size && compare(h->list[temp], h->list[left])==0)
	{
		temp = left;
	}
	if(right<size && compare(h->list[temp], h->list[right])==0)
	{
		temp = right;
	}
	if(temp != i)
	{	
		swap(h->list[i], h->list[temp]);
		heapify(temp, h);
	}
}

void insertJob(heap *H, job j)
{	
	if(H->numJobs == 0){
		H->numJobs++;
		H->list[1] = j;
		return; 
	}
	H->numJobs++;
	int index;
	index = H->numJobs;
	H->list[index] = j;
	int parent = index/2;
	while(parent!=0 && compare(H->list[index], H->list[parent]))
	{
		swap(H->list[index], H->list[parent]);
		index = index/2;
		parent = index/2;
	}
}

job getMinJob(heap *H)
{
	return H->list[1];
}

job extractMinJob(heap *H)
{
	job minimum = H->list[1];
	int last = H->numJobs;
	swap(H->list[last], H->list[1]);
	H->numJobs--;
	heapify(1, H);
	return minimum;
}

void counting_sort(job* J, int n)
{
	int count[500];
	for(int i=0; i<500; i++){
		count[i] = 0;
	}
	for(int i=1; i<n+1; i++){
		count[J[i].startTime]++;
	}
	for(int i=1; i<500; i++){
		count[i] += count[i-1];
	}
	job output[n+1];
	for (int i = 1; i<n+1; ++i) { 
        output[count[J[i].startTime]] = J[i]; 
        count[J[i].startTime]--; 
    } 
    for (int i = 1; i<n+1; ++i) 
        J[i] = output[i];
}

void scheduler(job *J, int n)
{
	heap* H;
	H = new heap;

	int started = 1;
	int now_job = -1;
	int start[n+1];
	int end[n+1];

	int min_start = 100000;
	for(int i=1;i<=n;i++)
	{
		min_start = min(min_start, J[i].startTime);
	}

	for(int i = 0; i<n+1; i++){
		end[i] = start[i] = -1;
	}
	cout<<"Jobs scheduled at each timestep are:\n";
	for(int i=0; i<min_start; i++){
		cout<<-1<<" ";
	}
	for(int t=0;;t++)
	{	
		if(now_job!=-1 && J[now_job].remLength==0)
		{	
			end[now_job] = t;
			now_job = -1;
		}

		while(started <=n && J[started].startTime == t)
		{
			insertJob(H, J[started]);
			started ++;
		}

		if(now_job==-1)
		{	
			if(H->numJobs != 0)
			{
				job job_found = extractMinJob(H);
				//cout<<job_found.jobId;
				now_job = job_found.jobId;
				if(start[now_job] == -1)
					start[now_job] = t;
			}
		}
		else
		{
			job k = getMinJob(H);
			if(J[now_job].remLength > k.remLength)
			{
				insertJob(H, J[now_job]);
				job k = extractMinJob(H);
				now_job = k.jobId;
				if(start[now_job] == -1)
					start[now_job] = t;
			}
		}

		if(now_job!=-1)
		{
			J[now_job].remLength--;
		}

		if(started == n+1 && now_job==-1)
		{
			break;
		}
		if(now_job != -1)
			cout<<now_job<<" ";
	}
	int sum1 = 0;
	int sum2 = 0;
	for(int i=1; i<=n; i++){
		sum1 += start[i];
		sum2 += J[i].startTime;
	}
	cout<<"\nAverage Turnaround Time is ";
	double av = (double)(sum1-sum2)/n;
	cout<<av;
}

int main()
{	
	#ifndef ONLINE_JUDG
      freopen("input.txt", "r", stdin);
      //freopen("output.txt", "w", stdout);
    #endif

	int n;
	cout<<"Enter no. of jobs (n): ";
	cin>>n;

	job *J = new job[n+1];

	cout<<"Enter the jobs:\n";
	for(int i=1;i<=n;i++)
	{
		cin>>J[i].jobId;
		cin>>J[i].startTime;
		cin>>J[i].jobLength;
		J[i].remLength = J[i].jobLength;
	}

	job *J_sorted = new job[n+1];
	counting_sort(J, n);
	scheduler(J, n);
}