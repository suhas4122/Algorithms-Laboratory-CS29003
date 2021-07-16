#include<bits/stdc++.h>
using namespace std;

typedef struct node{
	string value;
	int	frequency;
	node *next;
	node *left;
	node *right;

	node(char key, int val){
		value = key;
		frequency = val;
		next=left=right=NULL;
	}
}node;

node *head = NULL;

bool compare(node* a,node* b)
{
	if(a->frequency<b->frequency){
		return 1;
	}
	else if(a->frequency>b->frequency){
		return 0;
	}
	else if(a->frequency == b->frequency)
	{
		if(a->value[0]=='N' && b->value[0]=='N'){
			return a->value<b->value;
		}
		else if(a->value[0]=='N' && b->value[0]!='N'){
			return 1;
		}
		else if(a->value[0]!='N' && b->value[0]=='N'){
			return 0;
		}

		if(a->value[0]>='0' && a->value[0]<='9'){
			if(b->value[0]>='0' && b->value[0]<='9')
			{
				return a->value<b->value;
			}
			else
			{
				return 0;
			}
		}
		else if(b->value[0]>='0' && b->value[0]<='9'){
			return 1;
		}
		else
		{
			return a->value<b->value;
		}
	}
	return 1;
}

node* newNode(string key, int val, node* a, node* b)  
{      
    node* new_node =new node('a', val); 
  	
    new_node->value = key;
    new_node->left = a;
    new_node->right = b;  
  
    return new_node;  
} 

void insert(node* new_node){

    if ((head) == NULL || !compare(head,new_node)){
        new_node->next = head;
        head = new_node;
    }
    else{
    	node* current;
		current = head;
        while (current->next!=NULL && compare(current->next,new_node)){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

}

string tostring(int x)
{
	string s;
	if(x==0){
		s+="0";
		return s;
	}
	x*=10;
	while(x/=10)
	{
		s+=('0'+x%10);
	}
	reverse(s.begin(),s.end());
	return s;
}

void Traverse(string &str, node* T, string H[], string C)
{	
	str+=(T->value);
	str+="(";
	str+=tostring(T->frequency);
	str+=")";
	str+=(" ");
	if((T->value[0]>='a'&&T->value[0]<='z')||(T->value[0]>='0'&&T->value[0]<='9'))
	{
		if(T->value[0]>='a'&&T->value[0]<='z')
		{
			H[T->value[0]-'a']=C;
		}
		else
		{
			H[T->value[0]-'0'+26]=C;	
		}
	}
	else
	{	
		if(T->left!=NULL)
		Traverse(str, T->left, H, C+'0');
		
		if(T->right!=NULL)
		Traverse(str, T->right, H, C+'1');
	}
}

int main()
{
	ofstream op ("output.txt");
  	ifstream ip ("log.txt");

  	int n;
	ip>>n;

	int *frequency = new int[36];
	for(int i=0; i<36; i++){
		frequency[i]=0;
	}

	int t = n;

	while(t--)
	{
		string s;
		ip>>s;
		for(int i=0; i<s.size(); i++)
		{
			if(s[i]>='a'&&s[i]<='z')
			{
				int position = s[i]-'a';
				frequency[position]=frequency[position]+1;
			}
			else if(s[i]>='A'&&s[i]<='Z'){
				int position = s[i]-'A';
				frequency[position]=frequency[position]+1;
			}
			else
			{
				int position = 26+s[i]-'0';
				frequency[position]=frequency[position]+1;
			}
		}
	}

	for(int i=0; i<26; i++){
		char c = char('a'+i);
		op<<c<<"="<<frequency[i]<<", ";
		if((i+1)%14==0) op<<"\n";
	}

	for(int i=26; i<35; i++){
		op<<i-26<<"="<<frequency[i]<<", ";
		if((i+1)%14==0) op<<"\n";
	}

	op<<9<<"="<<frequency[35];

	for(int i=0;i<26;i++)
	{
		node* temp = new node('a'+i, frequency[i]);
		//op<<temp.frequency;
		insert(temp);
	}

	for(int i=26; i<36; i++){
		node* temp = new node('0'+i-26, frequency[i]);
		insert(temp);
	}
	node* printer;
	printer = head;

	t = 0;
	op<<endl;
	// while(printer->next != NULL && ++t){
	// 	op<<printer->value<<"="<<printer->frequency<<" ";
	// 	if(t%15==0) op<<"\n";
	// 	printer = printer->next;
	// }

	int counter=1;
	int size=36;
	node* head1 = head;

	while(size>1)
	{
		node *temp = head;
		string x;
		x = "N";
		x+=(tostring(counter));
		node* naya = newNode(x, temp->frequency+temp->next->frequency, temp, temp->next);
		head = head->next->next;
		insert(naya);		
		counter++;
		size--;
	}
	node* temporary = head;
	op<<endl;
	string H[36];
	string C="";
	string str;
	Traverse(str, temporary, H,C);
	op<<str<<endl;
	op<<endl;
	for(int i=0;i<26;i++)
	{
		char c='a'+i;
		op<<c<<" "<<H[i]<<endl;
	}
	for(int i=0; i<10; i++){
		char c='0'+i;
		op<<i<<" "<<H[i+26]<<endl;
	}
}
