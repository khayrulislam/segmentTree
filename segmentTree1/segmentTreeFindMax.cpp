#include<iostream>
#include<stdio.h>

using namespace std;
#define maxsize 10000

int treeNode[4*maxsize];
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

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );

    return ;
}

void update(int nodeNumber,int start,int end,int index,int newValue){

    int mid,left,right;
    if(index < start || index > end)
        return ;

    if(index == start && index == end){         // if(index =< start && index >= end
        treeNode[nodeNumber] = newValue;
        return ;
    }
    mid = (start + end) / 2;
    left = 2*nodeNumber;
    right = 2*nodeNumber + 1;

    update(left,start,mid,index,newValue);
    update(right,mid+1,end,index,newValue);

    treeNode[nodeNumber] = max(treeNode[left] , treeNode[right]) ;

    return ;
}

int query(int nodeNumber,int start,int end,int posStart,int posEnd){

    int mid,left,right,q1,q2;
    if(posEnd < start || posStart > end)
        return INT_MIN;

    if (posStart <= start && posEnd >= end)
        return treeNode[nodeNumber];

    mid = (start + end) / 2;
    left = 2*nodeNumber;
    right = 2*nodeNumber + 1;

    q1 = query(left,start,mid,posStart,posEnd);
    q2 = query(right,mid+1,end,posStart,posEnd);

    return max(q1,q2);
}



int main (){

    freopen("input.c","r",stdin);

    int n;
    cin >> n;
    for (int i=0;i<=4*maxsize;i++) treeNode[i] = INT_MIN;
    for(int i=1;i<=n;i++) cin >> arr[i];

    initializeTreeNode(1,1,n);

    update(1,1,n,5,INT_MAX);

    cout << query(1,1,n,1,6)<<endl;


return 0;
}


