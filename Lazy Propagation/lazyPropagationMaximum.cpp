#include<iostream>
#include<stdio.h>

#define maxsize 10000

using namespace std;

int treeNode[4*maxsize];
int lazy[4*maxsize];
int arr[maxsize];

void initializeTreeNode(int nodeNumber,int start,int end){

    int mid,left,right;
    if(start==end){
        treeNode[nodeNumber] = arr[start]; // intialize leaf treeNode to the array value.
        return ;
    }

    mid = (start + end) / 2;
    left = 2*nodeNumber;
    right = 2*nodeNumber + 1;

    initializeTreeNode(left,start,mid);
    initializeTreeNode(right,mid+1,end);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding minimum value

    return ;
}

void update(int nodeNumber, int start, int end, int l, int r, int value){

    int mid,left,right;
    if(lazy[nodeNumber]!=0){
        treeNode[nodeNumber] += value;
        if(start!=end){
            lazy[nodeNumber*2] += value;
            lazy[nodeNumber*2 + 1] += value;
        }
        lazy[nodeNumber] = 0;
    }
    if(end<l || start > r)
        return ;
    if( start >=l && end <= r ){
        treeNode[nodeNumber] += value;
        if(start!=end){
            lazy[nodeNumber*2] += value;
            lazy[nodeNumber*2 + 1] += value;
        }
        return;
    }

    mid = (start + end) / 2;
    left = nodeNumber*2;
    right = nodeNumber*2 + 1;

    update(left,start,mid,l,r,value);
    update(right,mid+1,end,l,r,value);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );
    return;
}

int query(int nodeNumber, int start, int end, int l, int r){

    int mid,left,right,q1,q2;
    if(end<l || start > r)
        return INT_MIN;
    if(lazy[nodeNumber]!=0){

        treeNode[nodeNumber] +=  lazy[nodeNumber];

        if(start!=end){
            lazy[nodeNumber*2] += lazy[nodeNumber];
            lazy[nodeNumber *2 +1] += lazy[nodeNumber];
        }
        lazy[nodeNumber] = 0;
    }
    if( start >=l && end <= r )
        return treeNode[nodeNumber];

    mid = (start + end) / 2;
    left = nodeNumber*2;
    right = nodeNumber*2 + 1;

    q1 = query(left,start,mid,l,r);
    q2 = query(right,mid+1,end,l,r);
    return max(q1,q2);
}

int main ()
{
    freopen("input.c","r",stdin);

    int n;
    cin >> n;
    for(int i=1;i<=4*maxsize;i++) treeNode[i]=INT_MIN;

    for(int i=1;i<=n;i++) cin >> arr[i];

    initializeTreeNode(1,1,n);

    update(1,1,n,1,4,2);

    cout << query(1,1,n,1,6);

    return 0;
}
