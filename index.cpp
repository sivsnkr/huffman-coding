#include<iostream>
using namespace std;
struct node{
    char a;
    int freq;
    struct node *rptr;
    struct node *lptr;
};

struct decoded{
    char a;
    char decode[100];
};

void makeTree(struct node letters[],struct node Memory[],int n){
    int memorySize = 0;
    int i,j;//simple counter
    for(i = 0; i < n-1; i++){
        //find 1st min
        int firstMin = 100000;//letting infinity
        int firstMinIndex;
        for(j = 0; j < n-i; j++){
            if(letters[j].freq < firstMin){
                firstMin = letters[j].freq;
                firstMinIndex = j;
            }
        }
        //finding second Min
        int secondMin = 100000;//letting infinity
        int secondMinIndex;
        for(j = 0; j < n-i; j++){
            if(letters[j].freq < secondMin && j != firstMinIndex){
                secondMin = letters[j].freq;
                secondMinIndex = j;
            }
        }


        Memory[memorySize] = letters[firstMinIndex];
        letters[firstMinIndex].a = '&';
        letters[firstMinIndex].freq = secondMin+firstMin;
        letters[firstMinIndex].lptr = &Memory[memorySize];
        memorySize++;

        Memory[memorySize] = letters[secondMinIndex];
        letters[firstMinIndex].rptr = &Memory[memorySize];
        memorySize++;

        letters[secondMinIndex] = letters[n-i-1];
    }
}


int isLeaf(struct node* root)  
{
    return !(root->lptr) && !(root->rptr); 
} 

void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 

void printCodes(struct node* root, int arr[], int top) 
{
    // Assign 0 to left edge and recur 
    if(root->lptr){ 
        arr[top] = 0; 
        printCodes(root->lptr, arr, top + 1); 
    } 
  
    // Assign 1 to right edge and recur 
    if(root->rptr){
        arr[top] = 1; 
        printCodes(root->rptr, arr, top + 1); 
    } 
  
    // If this is a leaf node, then 
    // it contains one of the input 
    // characters, print the character 
    // and its code from arr[] 
    if(isLeaf(root)){
        printf("%c: ", root->a); 
        printArr(arr, top); 
    } 
} 

int main(void){
    int n;
    cout<<"Enter the number of input:";
    cin>>n;
    struct node mainMemorry[2*n-1];
    struct node letters[n];
    int i,j;//simple counter
    for(i = 0; i < n; i++){
        cin>>letters[i].a>>letters[i].freq;
        letters[i].lptr = NULL;letters[i].rptr=NULL;
    }
    makeTree(letters,mainMemorry,n);
    int decodedLetters[n];
    printCodes(&letters[0],decodedLetters,0);
}


