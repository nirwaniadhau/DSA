//insertion and merge sort
#include<stdio.h>
struct Student{
    char name[50];
    int roll;
    float marks;
};

void swap(struct Student *a, struct Student *b, int *swap){
    struct Student temp= *a;
    *a=*b;
    *b=temp;
    (*swap)++;


}
void insertionSort(struct Student a[], int n , int *swaps){
    
    for(int i=1;i<n;i++ ){
        struct Student key =a[i];
        int j=i-1;
        while(j>=0 && a[j].roll >key.roll){
            a[j+1]=a[j];
            (*swaps)++;
            j--;
        }
        a[j+1]=key;
        if(j+1!=i){
            (*swaps)++;
        }
    }
}
void printStudent(struct Student a[], int n){
    for(int i=0;i<n;i++){
        printf("%s %d %.2f\n",a[i].name,a[i].roll,a[i].marks);
    }

}

void merge(struct Student a[],int low ,int mid , int high , int *mergeSwaps){
    int n1=mid-low+1;
    int n2=high-mid;

    int i,j,k;
    struct Student L[n1], R[n2];

    for( i=0;i<n1;i++){
        L[i]=a[low+i];
    }
    for(j=0;j<n2;j++){
        R[j]=a[mid+j+1];
    }

    i=j=0;
    k=low;
    while(i<n1 && j<n2){

        if(L[i].roll<=R[i].roll){
            a[k++]=L[i++];
        }else{
            a[k++]=R[j++];
            (*mergeSwaps)++;
        }
        
    }

    while(i<n1){
        a[k++]=L[i++];
    }
    while(j<n2){
        a[k++]=R[j++];
    }

}
void mergeSort(struct Student a[],int low, int high, int *mergeSwaps){
    int mid=low+(high-low)/2;

    if(low<high){ 
    mergeSort(a,low,mid,mergeSwaps);
    mergeSort(a,mid+1,high,mergeSwaps);
    merge(a,low,mid,high,mergeSwaps);
    }
}


int main(){
   struct  Student s[100], insertion[100],merge[100];
   int n ;
   printf("Enter number of students:");
   scanf("%d",&n);

   for(int i=0;i<n;i++){
    printf("Enter name, roll no and marks of the student: ");
    scanf("%s %d %f",s[i].name,&s[i].roll,&s[i].marks);
    insertion[i]=s[i];
    merge[i]=s[i];
   }
   int insertionSwaps=0;
   int mergeSwaps=0;

   insertionSort(insertion, n ,&insertionSwaps);
   printf("Output of Insertion Sort Algorithm on student structure:\n ");
   printStudent(insertion,n);
   printf("No. of swaps required for Insertion Sort: %d",insertionSwaps);

   printf("\n");
   printf("Output of merge Sort Algorithm on student structure:\n ");
   mergeSort(merge,0,n-1, &mergeSwaps);
   printStudent(merge,n);
   printf("No. of swaps required for merge Sort: %d",mergeSwaps);
   return 0;
}
