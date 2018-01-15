#include<iostream>
#include<stdio.h>
#include<algorithm>  // for finding gcd

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

    treeNode[nodeNumber] = treeNode[left] + treeNode[right] ;
   // treeNode[nodeNumber] = min(treeNode[left], treeNode[right] );  // for finding minimum value
   // treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding maximum value
   // treeNode[nodeNumber] = __gcd(treeNode[left], treeNode[right]);  // for finding gcd value

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

    treeNode[nodeNumber] = treeNode[left] + treeNode[right] ;
    // treeNode[nodeNumber] = min(treeNode[left], treeNode[right] );  // for finding minimum value
   // treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding maximum value
   // treeNode[nodeNumber] = __gcd(treeNode[left], treeNode[right]);  // for finding gcd value

    return ;
}

int query(int nodeNumber,int start,int end,int posStart,int posEnd){

    int mid,left,right,q1,q2;
    if(posEnd < start || posStart > end)
        return 0;
       // return INT_MAX;   // for finding minimum value
       // return INT_MIN;   // for finding maximum value
       // return 0;     // for finding gcd value

    if (posStart <= start && posEnd >= end)
        return treeNode[nodeNumber];

    mid = (start + end) / 2;
    left = 2*nodeNumber;
    right = 2*nodeNumber + 1;

    q1 = query(left,start,mid,posStart,posEnd);
    q2 = query(right,mid+1,end,posStart,posEnd);

    return q1 + q2;
   // return min(q1,q2);    // for finding minimum value
   // return max(q1,q2);    // for finding maximum value
   // return __gcd(q1,q2);   // for finding gcd value
}



int main (){

    freopen("input.c","r",stdin);

    int n;
    cin >> n;

    //for (int i=0;i<=4*maxsize;i++) treeNode[i] = INT_MAX;  // initialize treeNode as a max value for finding the minimum value
    //for (int i=0;i<=4*maxsize;i++) treeNode[i] = INT_MIN;  // initialize treeNode as a min value for finding the maximum value

    for(int i=1;i<=n;i++) cin >> arr[i];

    initializeTreeNode(1,1,n);

    update(1,1,n,5,50);

    cout << query(1,1,n,5,6)<<endl;


return 0;
}
