#include<bits/stdc++.h>
using namespace std;
#ifndef N
#define N 10
#endif
#ifndef M
#define M 5
#endif

// Problem 2
void* f(void *p){
    cout<<"Thread created"<<endl;
    return NULL;
} 

// Problem 3
int currIdx=0;

// problem 4
// shared variable to protect currIdx and SLL
pthread_mutex_t idM;
pthread_mutex_t listM;
// Node structure
struct Node{
    int data;
    Node* next;
};

struct required{
    vector<int>* vj;
};
// initially LL is empty
Node* head=NULL;

void insertIntoLL(int val){
    Node* nn=new Node{val,NULL};
    // entry section
    pthread_mutex_lock(&listM);
    // critical section
    nn->next=head;
    head=nn;
    pthread_mutex_unlock(&listM);
}

void* f1(void* a){
    required *args = (required *)a;
    while(true){
        vector<int> &vj=*(args->vj);
        int i;

        // lock index mutex
        pthread_mutex_lock(&idM);
        if(currIdx>=vj.size()){
            pthread_mutex_unlock(&idM);
            break;
        }

        i=currIdx;
        currIdx++;
        pthread_mutex_unlock(&idM);

        int val=vj[i];
        insertIntoLL(val);

        cout<<vj[i]<<" inserted into Linked List"<<endl;
    }
    return NULL;
}

// problem 5-> preserving original order
int curridx=0;
Node* headA=NULL;
Node* currA=NULL;
void insertIntoLLSame(int val){
    Node* nn=new Node{val,NULL};
    // entry section
    pthread_mutex_lock(&listM);
    // critical section
    if(headA==NULL)
        headA=nn;
    else
        currA->next=nn;
    currA=nn;
    pthread_mutex_unlock(&listM);
}

void* f2(void* a){
    required *args = (required *)a;
    while(true){
        int i;
        vector<int> &vj=*(args->vj);
        // lock index mutex
        pthread_mutex_lock(&idM);
        if(curridx>=vj.size()){
            pthread_mutex_unlock(&idM);
            break;
        }

        i=curridx;
        curridx++;
        pthread_mutex_unlock(&idM);

        int val=vj[i];
        insertIntoLLSame(val);

        cout<<vj[i]<<" inserted into Linked List"<<endl;
    }
    return NULL;
}

// Problem 6
struct requirements
{
    Node *head;
    vector<int> *pv;
    int *result;
};

void *checkSeq(void *arg)
{
    // pointer to a structure
    requirements *args = (requirements *)arg;
    Node *start = args->head;
    vector<int> &rv = *(args->pv); // rv is reference to vector v
    int n = rv.size();
    int i = 0;
    while (start && i < n)
    {
        if (start->data != rv[i])
        {
            *(args->result) = 0;
            return NULL;
        }
        start = start->next;
        i++;
    }
    *(args->result) = (start == NULL && i == n);
    return NULL;
}

int main(){
    // Problem 1
    vector<int> jp(N);
    // creating object 
    ifstream jpFile("file1.txt");

    // file can't opened
    if(jpFile.is_open()==0){
        cout<<"Some error in opening"<<endl;
        return 0;
    }
    
    string x;
    int i=0;
    // reading file line by line 
    while(getline(jpFile,x))
        jp[i++]=stoi(x);
    
    jpFile.close();

    // problem 2
    int k;
    pthread_t pj[M];  // collection of m threads
    for(k=0;k<M;k++){
        pthread_create(&pj[k],NULL,f,NULL);
        pthread_join(pj[k],NULL);
    }

    // // problem 4
    // int n=4;
    // pthread_t th[n];

    // //  mutex initialize krdo
    // pthread_mutex_init(&idM,NULL);

    // // create thread and join
    // required r={&jp};
    // for(int i=0;i<n;i++){
    //     pthread_create(&th[i],NULL,f1,&r);
    //     pthread_join(th[i],NULL);
    // }

    // Node* start=head;
    // while(start){
    //     cout<<start->data<<"->";
    //     start=start->next;
    // }
    // cout<<"NULL"<<endl;

    // // destroy the mutex
    // pthread_mutex_destroy(&idM);
    // pthread_mutex_destroy(&listM);

    // problem 5
    int n5=4;
    pthread_t jpj[n5];
    required rA={&jp};
    //  mutex initialize krdo
    pthread_mutex_init(&idM,NULL);

    // create thread and join
    for(int i=0;i<n5;i++){
        pthread_create(&jpj[i],NULL,f2,&rA);
        pthread_join(jpj[i],NULL);
    }

    Node* startA=headA;
    while(startA){
        cout<<startA->data<<"->";
        startA=startA->next;
    }
    cout<<"NULL"<<endl;

    // destroy the mutex
    pthread_mutex_destroy(&idM);
    pthread_mutex_destroy(&listM);

    // Problem 6
    // thread for verify
    pthread_t t;
    int ans = 0;
    // passing actual arguments to structure variable
    requirements r2 = {headA, &jp, &ans};

    pthread_create(&t, NULL, checkSeq, &r2);
    pthread_join(t, NULL);

    if (ans == 1)
        cout << "Both LL and vector are sequentially same"<<endl;
    else
        cout << "Both LL and vector are not sequentially same"<<endl;
}