/*************
Suhas Jain
19CS30048
Lab assignment - 10
Hash Tables 
*************/
#include<bits/stdc++.h>
using namespace std;

typedef struct _hashing
{
	int key;
	int value;
	_hashing *next;
}_hash;	

void init(_hash **chain, int size)
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert(int a, int b, _hash **chain, int size)
{
    _hash *newNode = (_hash*)malloc(sizeof(_hash));
    newNode->key = a;
    newNode->value = b;
    newNode->next = NULL;

    int i = a % size;

    if(chain[i] == NULL)
        chain[i] = newNode;
    else
    {
        _hash *temp = chain[i];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

int del(int a, int b, _hash **chain, int size)
{
    int index = a % size;
    _hash *temp = chain[index], *dealloc;

    if(temp != NULL)
    {
        if(temp->key == a && temp->value == b)
        {
            dealloc = temp;
            chain[index] = temp->next;
            free(dealloc);
        }
        else
        {
            while(temp->next)
            {
                if(temp->next->key == a && temp->next->value == b)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                }
                temp = temp->next;
            }
        }
    }

    return 0;
}

void delete__hash(int a, _hash **hash1, _hash **hash2, int size)
{
	int index1 = a % size;
	_hash *temp1 = hash2[index1];

	while(temp1 != NULL)
	{
		if(temp1->key == a)
		{
			int value1 = temp1->value;
			//if(a==45) op<<value1<<endl;
			del(value1, a, hash1, size);
			temp1 = temp1->next;
		}
	}

	hash2[index1] = NULL;
}

int main()
{	
	ifstream ip ("input.txt");
	ofstream op ("output.txt");

	int size;
	ip>>size;

	int n;
	ip>>n;

	_hash** _hash1 = new _hash*[size];
	_hash** _hash2 = new _hash*[size];

	init(_hash1, size);
	init(_hash2, size);

	for (int i=0; i<n; ++i)
	{
		char c;
		ip>>c;
		if(c=='+'){
			int a, b;
			ip>>a>>b;
			insert(b, a, _hash1, size);
			insert(a, b, _hash2, size);
		}
		else{
			int a;
			ip>>a;
			delete__hash(a, _hash1, _hash2, size);
		}
	}

	int i;

    for(i = 0; i < size; i++)
    {
       	_hash *temp = _hash1[i];

        if(!temp)
        {
        	op<<"p"<<" "<<i<<" "<<-1<<" "<<-1<<endl;
        }
        else{
	        while(temp)
	        {
	            op<<"p"<<" "<<i<<" "<<temp->key<<" "<<temp->value<<endl;
	            temp = temp->next;
	        }
	    }
    }

    for(i = 0; i < size; i++)
    {
       	_hash *temp = _hash2[i];

        if(!temp)
        {
        	op<<"c"<<" "<<i<<" "<<-1<<" "<<-1<<endl;
        }
        else{
	        while(temp)
	        {
	            op<<"c"<<" "<<i<<" "<<temp->key<<" "<<temp->value<<endl;
	            temp = temp->next;
	        }
	    }
    }

}