#include <bits/stdc++.h>
using namespace std;

/*******
Suhas Jain
19CS30048
Assignment-6 (Greedy algorithms)
******/

int n, series[8];

double max1(double a, double b){
	if(a>b)
		return a;
	else 
		return b; 
}

double absolute(double x){
	if(x>=0) return x;
	else return ((-1)*x);
}

/***
This is the main scheduling function 
For a given order of customers and time gap
It returns how much time before the ending time of 
last customer is our schedule ending
***/
double schedule_visits(double* a, double* b, double gap){
	double lastCustomer = a[series[0]];
	int k = n-1, i=1;
	while(k--){
		double target = lastCustomer + gap;
		if (target <= b[series[i]])
			lastCustomer = max1(a[series[i]], target);
		else
			return 1;
		i++;
	}
	return lastCustomer - b[series[n - 1]];
}

//function to reverse the array
void reverse_array(int arr[], int start, int end){
    while (start < end)
    {
        int temp = arr[start]; 
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    } 
}   

/***
This function changes to the array a to the next laxicographic order
It returns false if the array is sorted in decending order and true otherwise 
****/
bool next_permutation1(int a[]){ 
    int li = -1;
    int flag = 1;
	int next_candidate_index = li + 1; 

  	for (int i = 0; i < n; ++i) { 
	    if ((i + 1 < n) && a[i + 1] > a[i]) {
	    	flag = 0; 
	      	li = i; 
	      	next_candidate_index = li + 1; 
	    } 
	    if (li >= 0 && a[i] > a[li] && a[i] < a[next_candidate_index]) { 
	      	next_candidate_index = i; 
	    } 
  	} 
 
  	if (flag) { 
    	return false; 
  	} 

  	int temp;
  	temp = a[li];
  	a[li] = a[next_candidate_index];
  	a[next_candidate_index] = temp; 
  	reverse_array(a, li+1, n-1); 
  	return true; 
} 

int main(){
	FILE* inp = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
			
	double a[8], b[8], gap, max_gap;

	fscanf(inp, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(inp, "%lf%lf", &a[i], &b[i]);
	}

	for (int i = 0; i < n; i++) {
		a[i] *= 60; 
		b[i] *= 60;
		series[i] = i;
	}

	max_gap = -1; 
	int answer[n];

	/****
	What we're doing here is a binary search over all the possible 
	values of time gap to find the maximum value possible 
	We're varing the order of customers lexicographically and then
	determining which order gives us the best possible answer
	The best possible order of customers is stored in array "answers"
	*****/
	do{
		double low = 0, high = 86400;
		gap = (low + high) / 2.0; 
		while(absolute(low - high) >= 0.01) { 
			double returnV = schedule_visits(a, b, gap); 
			if (returnV <= 0.1) 
				low = gap;
			else
				high = gap;
			gap = (low + high) / 2.0; 
		}
		if(gap > max_gap){
			max_gap = gap;
			for(int j=0; j<n; j++){
				answer[j] = series[j];
			}
		} 
	}
	while (next_permutation1(series));

	max_gap = max_gap + 0.5;
	int time = (int)max_gap;
	int ans = (int)(time / 60);
	fprintf(out, "%d", ans);
	fprintf(out, ":%0.2d\n", (int)time % 60);
	for(int i=0; i<n; i++){
		fprintf(out, "%d ", answer[i]);
	}

	return 0;
}