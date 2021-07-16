#include <bits/stdc++.h>
using namespace std;

/*****************************
Suhas Jain 19CS30048
We have made 2 2-d arrays named as dp and counter
++Sub-problem: (i, j) element of our dp array stores the
	maximum probability of success if there were only initial i
	reactions and we hat total j amount of catalyst.
	Then we compute the ith row using already known values
	(i-1)th row.
++How do we find values in ith row?
	Ans: If we have j catalyst in total then the maximum probability
	is calculated by taking the maximum of probability of all the
	cases, the cases will taken by changing no of catalyst used in the
	last step and then calculating the probability by multiplying probability
	of last step by dp[i-1][no of catalyst left apart from last step
	(SEE LINES 76-82)
++Base case: We store values in the 1st row(0th index) as the probabilities
	of success in the 1st row of the input array, as we have only one step,
	both will be same
++How de we calculate the no. of catalyst in each step?
	Ans: In array counter at (i, j) element we store the no of catalyst
	being used in the ith step if the reaction in case when we get the
	maximum probability with i steps and j number of catalysts
++Time complexity
	O(n*c^2)
	n: no. of steps in the reaction
	c: given number of catalysts
******************************/

int main(){
	FILE* input1 = fopen("input.txt", "r");

  	int n;
  	fscanf(input1, "%d", &n);

  	int c;
  	fscanf(input1, "%d", &c);

  	double** prob = new double*[n];
  	for(int i=0; i<n; i++){
  		prob[i] = new double[c];
  	}
  	for(int i=0; i<n; i++){
  		for(int j=0; j<c; j++){
  			fscanf(input1, "%lf", &prob[i][j]);
  		}
  	}

  	double** dp = new double*[n];
  	for(int i=0; i<n; i++){
  		dp[i] = new double[c];
  	}

  	int** counter = new int*[n];
  	for(int i=0; i<n; i++){
  		counter[i] = new int[c];
  	}

	for(int i=0; i<c; i++){
		dp[0][i] = prob[0][i];
		counter[0][i] = i+1;
	}

	for(int i=1; i<n; i++){
		for(int j=0; j<c; j++){
			if(j<i){
				dp[i][j] = 0;
				counter[i][j] = 0;
				continue;
			}
			double max_prob;
			int number;
			max_prob = 0;
			for(int k=0; k<j; k++){
				double temp = dp[i-1][k]*prob[i][j-k-1];
				if(temp>max_prob){
					max_prob = temp;
					number = j-k;
				}
			}
			dp[i][j] = max_prob;
			counter[i][j] = number;
		}
	}

	fclose(input1);
	FILE*output1 = fopen("output.txt", "w");

	fprintf(output1, "%lf\n", dp[n-1][c-1]);

	int k = c-1;
	double* react = new double[n];
	for(int i=n-1; i>=0; i--){
		react[i] = counter[i][k];
		k = k-counter[i][k];
	}
	/**
	Here we have used react array to reverse the order of
	counts of catalyst used in each step
	As we have to print in ascending order of no. of steps
	reversing is necessary
	**/
	for(int i=0; i<n; i++){
		fprintf(output1, "reaction %d : ", i+1);
		fprintf(output1, "%.lf\n", react[i]);		
	}

	return 0;
}
