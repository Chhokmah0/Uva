//Uva 297 超时代码（意料之中）
#include <cstdio>
#include <cstring>

int num[10];//储存2^2x，防止过多计算
const int cnt = 5;//长宽为2^5

struct Node
{
    bool have_tree;
    bool color;
    struct Node *node1, *node2, *node3, *node4;
    Node():have_tree(false),color(0),node1(NULL),node2(NULL),node3(NULL),node4(NULL){}
};

Node* newnode() 
{
    return new Node();
}

Node* buildtree(char* s,int &p)
{
    Node* root = newnode();
    if (s[p] == 'p')
    {
        p++;
        root->have_tree = true;
        root->node1 = buildtree(s,p);
        root->node2 = buildtree(s,p);
        root->node3 = buildtree(s,p);
        root->node4 = buildtree(s,p);
    }else if(s[p] == 'e'){
        p++;
        root->color = 0;
    }else if(s[p] == 'f'){
        p++;
        root->color = 1;
    }
    return root;
}

void deltree(Node * root)
{
    if(!root->node1) deltree(root->node1);
    if(!root->node2) deltree(root->node2);
    if(!root->node3) deltree(root->node3);
    if(!root->node4) deltree(root->node4);
    delete root;
}



Node* addtree(Node* t1, Node* t2)
{
    Node* root = newnode();
    if (t1->color || t2->color)
    {
        root->color = 1;
    }else if(t1->have_tree && t2->have_tree){
        root->have_tree = true;
        root->node1 = addtree(t1->node1,t2->node1);
        root->node2 = addtree(t1->node2,t2->node2);
        root->node3 = addtree(t1->node3,t2->node3);
        root->node4 = addtree(t1->node4,t2->node4);
    }else if(t1->have_tree){
        root = t1;
    }else if(t2->have_tree){
        root = t2;
    }
    return root;
}

//cnt为32（2的5次方）中的5
int number(Node* root, int cnt)
{
    int sum = 0;
    if (root->color)
        sum += num[cnt];
    if (root->have_tree)
    {
        sum += number(root->node1,cnt-1);
        sum += number(root->node2,cnt-1);
        sum += number(root->node3,cnt-1);
        sum += number(root->node4,cnt-1);
    }
    return sum;
}


int main()
{
    for (int i = 0; i <= cnt; i++)
    {
        num[i] = 1<<(2*i);
    }
    
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        Node *root1, *root2;
        char s1[1024+10],s2[1024+10];
        int p1 = 0, p2 = 0;
        scanf("%s%s",s1,s2);
        root1 = buildtree(s1, p1);
        root2 = buildtree(s2, p2);
        Node *root = addtree(root1,root2);
        printf("There are %d black pixels.\n",number(root,cnt));
    }
}
