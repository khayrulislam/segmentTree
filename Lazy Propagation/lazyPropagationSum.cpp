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

    treeNode[nodeNumber] = treeNode[left] + treeNode[right] ;
   // treeNode[nodeNumber] = min(treeNode[left], treeNode[right] );  // for finding minimum value
   // treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding maximum value
    return ;
}

void update(int nodeNumber, int start, int end, int l, int r, int value){

    int mid,left,right;
    if(lazy[nodeNumber]!=0){
        treeNode[nodeNumber] += (end-start+1)*value;
        //treeNode[nodeNumber] += value;   // for finding min and max
        if(start!=end){
            lazy[nodeNumber*2] += value;
            lazy[nodeNumber*2 + 1] += value;
        }
        lazy[nodeNumber] = 0;
    }
    if(end<l || start > r)
        return ;
    if( start >=l && end <= r ){
        treeNode[nodeNumber] += (end-start+1)*value;
        //treeNode[nodeNumber] += value;     // for finding min and max
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

    treeNode[nodeNumber] = treeNode[left] + treeNode[right];
   // treeNode[nodeNumber] = min(treeNode[left], treeNode[right] );  // for finding minimum value
   // treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding maximum value
    return;
}

int query(int nodeNumber, int start, int end, int l, int r){

    int mid,left,right,q1,q2;
    if(end<l || start > r)
        return 0;
        // return INT_MAX;      // for finding min
        // return INT_MIN;      // for finding max
    if(lazy[nodeNumber]!=0){

        treeNode[nodeNumber] += (end-start+1) * lazy[nodeNumber];
        //treeNode[nodeNumber] +=  lazy[nodeNumber];    // for finding min and max
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
    return q1+q2;
    //return min(q1,q2);       // for finding min
    //return max(q1,q2);       // for finding max
}

int main ()
{
    freopen("input.c","r",stdin);

    int n;
    cin >> n;
    //  for(int i=1;i<=4*maxsize;i++) treeNode[i]=INT_MAX;     // for finding min
    //for(int i=1;i<=4*maxsize;i++) treeNode[i]=INT_MIN;       // for finding max
    for(int i=1;i<=n;i++) cin >> arr[i];

    initializeTreeNode(1,1,n);

    update(1,1,n,1,5,10);

    cout << query(1,1,n,1,6);

    return 0;
}
