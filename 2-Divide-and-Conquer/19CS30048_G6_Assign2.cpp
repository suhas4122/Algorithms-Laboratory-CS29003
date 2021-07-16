#include <iostream>
using namespace std;
/**
Suhas Jain
19CS30048
Group - G6
Assignment - 2 : Divide and conquer
**/

typedef struct  {
	// x coordinate of left side
	int left;
	// height
	int ht;
	// x coordinate of right side
	int right;
}Box;

struct point {
    int left;
    int ht;

    point(int l = 0, int h = 0)
    {
        left = l;
        ht = h;
    }
};

/***
we keep an array of points in this struct which make out boundary
A function add_new helps to add a new point to the boundary
**/
struct boundary {
	int max_size;
    int size;
    point* array;

    boundary(int length)
    {
        max_size = length;
        array = new point[length];
        size = 0;
    }

    void add_new(point* str)
    {
        if (size > 0 && array[size - 1].ht == str->ht)
            return;
        if (size > 0 && array[size - 1].left == str->left) {
            array[size - 1].ht = max(array[size - 1].ht, str->ht);
            return;
        }
        array[size] = *str;
        size++;
    }
};

/***
Given boundaries of 2 different set of ractangles this function helps us
to merge these 2 boundaries and return a new one
**/
boundary* merge_boundaries(boundary* b1, boundary* b2)
{
    int size1 = b1->size;
    int size2 = b2->size;

   	boundary* answer = new boundary(size1+size2);

    int height1 = 0;
    int height2 = 0;

    int i = 0, j = 0;

    while (i < size1 && j < size2) {
    	int left1 = b1->array[i].left;
    	int left2 = b2->array[j].left;

        if (left1 < left2) {
        	height1 = b1->array[i].ht;
            int bigger = max(height1, height2);
            point* st = new point(left1, bigger);
            answer->add_new(st);
            delete st;
            i++;
        }

        else {
            height2 = b2->array[j].ht;
            int bigger = max(height1, height2);
            point* st = new point(left2, bigger);
            answer->add_new(st);
            delete st;
            j++;
        }
    }

    while (i < size1) {
        int x1 = b1->array[i].left;
        int x2 = b1->array[i].ht;
        point* st = new point(x1, x2);
        answer->add_new(st);
        i++;
    }

    while (j < size2) {
        int x1 = b2->array[i].left;
        int x2 = b2->array[i].ht;
        point* st = new point(x1, x2);
        answer->add_new(st);
        j++;
    }

    return answer;
}

/**
this works just like merge sort where we divide the points into two parts
and then calculate the boundary of both and then merge the boundaries
In base case when there is only one element boundary is made up of top left and bottom right point
**/
boundary* solve(Box boxes[], int l, int r)
{
    if (l == r) {
        boundary* answer = new boundary(2);

        point* s1 = new point(boxes[l].left, boxes[l].ht);
        point* s2 = new point(boxes[l].right, 0);

        answer->add_new(s1);
        answer->add_new(s2);

        return answer;
    }

    int mid = (l + r) / 2;

    boundary* b1 = solve(boxes, l, mid);
    boundary* b2 = solve(boxes, mid + 1, r);

    boundary* answer = merge_boundaries(b1, b2);

    delete b1;
    delete b2;
    return answer;
}

point* findOutLine(Box boxes[], int n, int &outputsize){
	point* answer;
	boundary* temp;
	temp = solve(boxes, 0, n-1);
	answer = temp->array;
	outputsize=temp->size;;
	return answer;
}

void prettyPrint(point* points, int outputsize) {
	int i;
	printf(" OutLine for given Boxes is \n[");
	for (i = 0; i < outputsize; i++) {

		printf(" (%d, %d), ", points[i].left, points[i].ht);

	}
	printf("\b\b ]\n");
}

void process() {
	int n;
	scanf("%d", &n);
	Box boxes[n];
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &boxes[i].left , &boxes[i].right , &boxes[i].ht);
	}
	int outputsize;
	point* ptr = findOutLine(boxes, n, outputsize);

	prettyPrint(ptr, outputsize);
}

int main(){
	process();
	return 0;
}
