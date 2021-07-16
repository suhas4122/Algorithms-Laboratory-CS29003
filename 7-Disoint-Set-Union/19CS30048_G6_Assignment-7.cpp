/*****
Suhas Jain
19CS30048
Lab-7
Disjoint sets
******/

#include<iostream>
using namespace std ;

int i, j;
char **H;
char **V;
int m;
int n;

typedef struct _node  //declaration of node of DSU
{
   int rank;
   struct _node *parent;
}node;

node makeset(node &N)
{
   N.rank = 1;
   N.parent = &N;
   return N;
}

node* findset( node **R, int i, int j)
{
   node *x = &(R[i][j]);
      while (x -> parent != x) x = x -> parent;
   return x;
}

void mergeset ( node **R, int i1, int j1, int i2, int j2)
{
   node* x = findset(R, i1, j1); 
   node* y = findset(R, i2, j2);

      if (x == y) return;

      if (x -> rank > y -> rank) {  //using union by rank to do union of 2 sets
      y -> parent = x;
      }else if(x -> rank < y -> rank) {
         x -> parent = y;
      }
      else{
         x -> parent = y;
         y -> rank += 1;
      }
}

void init_chambers (node** &X) //initialising the 2d array of nodes as 
{                              //seperate disjoint sets 
   node **R = new node*[m];

   for (i=0; i<m; ++i) {
      R[i] = new node[n];
      for (j=0; j<n; ++j) {
         R[i][j] = makeset(R[i][j]);
      }
   }
   X = R;
}

void printgrid() //function to print the grid at particular point of time 
{
   cout<<"    +   +";

      for (j=1; j<n; ++j)
         cout<<"---+";
      cout<<endl;

      for (i=0; i<m; ++i) {
      cout<<"    |";
         for (j=0; j<=n-2; ++j){
            if(V[i][j] == 0)
               cout<<"   |";
            else
               cout<<"    ";
         }

         if(i!=m-1){
            cout<<"   |";
            cout<<endl;
         }
         else cout<<endl;

         if (i != m-1) {
            cout<<"    ";
            for (j=0; j<n; ++j){
               if(H[i][j] == 0)
                  cout<<"+---";
               else
                  cout<<"+   ";
            }
            cout<<"+";
            cout<<endl;
         }
      }
      cout<<"    +";
      for (j=0; j<n; ++j)
         cout<<"---+";
      cout<<endl;
}

void findtreasure(node** R)
{
   int a, b;
   i = 0;
   while(i<m*n-1){
      if(rand()%2){ //randomly choosing if to eliminate horizontal or vertical wall
         a = rand()%(m-1);
         b = rand()%(n);
         if(H[a][b] == 0){
            node* root1 = findset(R, a, b);
            node* root2 = findset(R, a+1, b);
            if(root1 != root2){
               mergeset(R, a, b, a+1, b);
               H[a][b] = 1; //merging 2 sets and removing the wall in between them
               i++;
            }
         }
      }
      else{
         a = rand()%(m);
         b = rand()%(n-1);
         if(V[a][b] == 0){
            node* root1 = findset(R, a, b);
            node* root2 = findset(R, a, b+1);
            if(root1 != root2){
               mergeset(R, a, b, a, b+1) ;
               V[a][b] = 1; //merging 2 sets and removing the wall in between them
               i++;
            }
         }
      }
   }
}


int main ( int argc, char *argv[] )
{
   if (argc >= 3){
      m = atoi(argv[1]);
      n = atoi(argv[2]);
   }
   else{
      m=n=10;
   }

   node **R;

   H = new char*[m];
   for (i=0; i<=m; ++i){
      H[i] = new char[n];
   } //dynamically allocating the 2d array storing horizontal walls

   V = new char*[m];
   for (i=0; i<=m; ++i){
      V[i] = new char[n];
   }//dynamically allocating a 2d array storing vertical walls

   init_chambers(R);

   for(i=0; i<m; i++)
      for(j=0; j<n; j++)
         H[i][j] = 0; //initialising all horizontal walls as present 


   for(i=0; i<m; i++)
      for(j=0; j<n; j++)
         V[i][j] = 0; //initialising all vertical walls as present 

   cout<<"\nInitial Grid\n";
   printgrid(); //printing the initial grid 

   findtreasure(R); //solving and removing m*n-1 walls 

   if(findset(R, 0, 0) == findset(R, n-1, m-1)){  //checking if initial and final chambers are in the same set 
      cout<<"\nThe final chamber can be reached from the start chamber\n"; //as mentioned in part 2
   }
   else 
      cout<<"Not Possible";

   cout<<"\nFinal grid\n";
   printgrid(); //printing the final grid

   return 0;
}
