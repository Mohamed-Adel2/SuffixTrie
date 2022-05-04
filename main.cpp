#include <iostream>

using namespace std;

class LinkedList;

class TrieNode
{
public:
    LinkedList* lst;
    TrieNode();
};

class ListNode
{
public:
    ListNode* next;
    char c;
    TrieNode* n;
    int num;
    ListNode(char c)
    {
        next=NULL;
        this->c=c;
        n=new TrieNode();
        num=-1;
    }
    void setNext(ListNode* n)
    {
        next=n;
    }
    ListNode* getNext()
    {
        return next;
    }
};

class LinkedList
{

private:
    ListNode* head;
    ListNode* tail;
public:
    int len;
    LinkedList()
    {
        head=NULL;
        tail=NULL;
        len=0;
    }
    void AddTail(int n)
    {
        ListNode* tmp=new ListNode(n);
        if(head==NULL && tail==NULL) head=tail=tmp;
        else
        {
            tail->next=tmp;
            tail=tmp;
        }
        len+=1;
    }

    ListNode* getHead()
    {
        return head;
    }

    ListNode* getTail()
    {
        return tail;
    }

    ListNode* SearchNode(char ch)
    {
        ListNode* temp=head;
        while(temp!=NULL)
        {
            if(temp->c==ch) return temp;
            temp=temp->next;
        }
        return NULL;
    }

};

class SuffixTrie
{
public:
    TrieNode* root;
    int len;
    SuffixTrie(char s[])
    {
        len=WordLen(s);
        root=new TrieNode();
        buildTrie(s);
    }
    int WordLen(char s[])
    {
        int x=0;
        while(s[x]!='\0'){
            x++;
        }
        return x;
    }
    void buildTrie(char s[])
    {
        TrieNode* tmp;
        for(int i=0;i<len;i++)
        {
            tmp=root;
            if(tmp->lst->SearchNode(s[i])==NULL) Addsub(tmp,s,i,i);
            else
            {
                tmp=tmp->lst->SearchNode(s[i])->n;
                int j=i+1;
                while(tmp->lst->SearchNode(s[j])!=NULL&&j<len)
                {
                    tmp=tmp->lst->SearchNode(s[j])->n;
                    j++;
                }
                if(j<len) Addsub(tmp,s,j,i);
            }
        }
    }
    void Addsub(TrieNode* n,char s[],int x,int y)
    {
        TrieNode* tmp=n;
        for(int i=x;i<len;i++)
        {
            tmp->lst->AddTail(s[i]);
            if(s[i]=='$') tmp->lst->getTail()->num=y;
            tmp=tmp->lst->SearchNode(s[i])->n;
        }
    }
    void Search(char s[])
    {
        TrieNode* tmp=root;
        for(int i=0;i<WordLen(s);i++)
        {
            if(tmp->lst->SearchNode(s[i])==NULL){cout<<"No Such Substring.!"<<endl;return;}
            else tmp=tmp->lst->SearchNode(s[i])->n;
        }
        getLeafs(tmp);
        cout<<endl;
    }
    void getLeafs(TrieNode* n)
    {
        ListNode* tmp=n->lst->getHead();
        for(int i=0;i<n->lst->len;i++)
        {
            if(tmp->c=='$') cout<<tmp->num<<" ";
            else getLeafs(tmp->n);
            tmp=tmp->next;
        }
    }
};

TrieNode::TrieNode()
{
     lst=new LinkedList();
}

