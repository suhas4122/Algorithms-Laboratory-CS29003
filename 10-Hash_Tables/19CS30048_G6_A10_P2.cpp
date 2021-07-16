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
    int data;
    _hashing *next;
}_hash; 

void init(_hash** chain, int size)
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert(int value, _hash** chain, int size)
{
    _hash *newNode = (_hash*)malloc(sizeof(_hash));
    newNode->data = value;
    newNode->next = NULL;

    int key = value % size;

    if(chain[key] == NULL)
        chain[key] = newNode;
    else
    {
        _hash *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

int del(int value, _hash** chain, int size)
{
    int key = value % size;
    _hash *temp = chain[key], *dealloc;
    if(temp != NULL)
    {
        if(temp->data == value)
        {
            dealloc = temp;
            chain[key] = temp->next;
            free(dealloc);
            return 1;
        }
        else
        {
            while(temp->next)
            {
                if(temp->next->data == value)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return 1;
                }
                temp = temp->next;
            }
        }
    }
    return 0;
}

void print(_hash** chain, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        _hash *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%d -->",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

bool isEmpty(_hash** chain, int size)
{
    int i;
    for(i = 0; i < size; i++)
        if(chain[i] != NULL)
            return false;
    return true;
}

typedef struct _hashing_adv
{
    int key;
    _hash **table;
}_hash_adv; 

void init_adv(_hash_adv *chain, int size)
{
    int i;
    for(i = 0; i < size; i++){
        chain[i].key = -1;
        chain[i].table = new _hash*[size];
        init(chain[i].table, size);
    }
}

void insert_adv(int a, int b, _hash_adv *chain, int size)
{
    int index = a % size;
    chain[index].key = a;
    insert(b, chain[index].table, size);
}

void delete_hash_adv(int a, _hash_adv *hash1, _hash_adv *hash2, int size)
{
    int index = a % size;
    init(hash2[index].table, size);

    for(int i=0; i<size; i++)
    {
        del(a, hash1[i].table, size);
    }
}

int main()
{
    ifstream ip ("input.txt");
    ofstream op ("output.txt");

    int size;
    ip>>size;

    int n;
    ip>>n;

    _hash_adv hash1[size];
    _hash_adv hash2[size];
    init_adv(hash1, size);
    init_adv(hash2, size);

    for (int i=0; i<n; ++i)
    {
        char c;
        ip>>c;
        if(c=='+')
        {
            int a, b;
            ip>>a>>b;
            insert_adv(b, a, hash1, size);
            insert_adv(a, b, hash2, size);
        }
        else
        {
            int a;
            ip>>a;
            delete_hash_adv(a, hash1, hash2, size);
        }
    }

    for(int j = 0; j < size; j++)
    {
        _hash **temp1 = hash1[j].table;

        if(!isEmpty(temp1, size))
        {
            for(int i = 0; i < size; i++)
            {
                _hash *temp = temp1[i];
                if(temp)
                {
                    while(temp)
                    {
                        op<<"p"<<" "<<j<<" "<<hash1[j].key<<" "<<temp->data<<endl;
                        temp = temp->next;
                    }
                }
            }
        }
        else
        {
            op<<"p"<<" "<<j<<" "<<-1<<" "<<-1<<endl;
        }
    }

    for(int j = 0; j < size; j++)
    {
        _hash **temp1 = hash2[j].table;

        if(!isEmpty(temp1, size))
        {
            for(int i = 0; i < size; i++)
            {
                _hash *temp = temp1[i];
                if(temp)
                {
                    while(temp)
                    {
                        op<<"c"<<" "<<j<<" "<<hash2[j].key<<" "<<temp->data<<endl;
                        temp = temp->next;
                    }
                }
            }
        }
        else
        {
            op<<"c"<<" "<<j<<" "<<-1<<" "<<-1<<endl;
        }
    }
}