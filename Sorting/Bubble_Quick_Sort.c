//Quick Sort 
//bubble sort
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
void printStudent(struct Student a[], int n){
    for(int i=0;i<n;i++){
        printf("%s %d %.2f\n",a[i].name,a[i].roll,a[i].marks);
    }

}
int partition(struct Student a[],int low, int high, int *swaps){
    int i=low+1;
    int j=high;
    int pivot=a[low].roll;

    while(i<=j){

        while(i<=high && a[i].roll<pivot){
            i++;
        }
        while(j>=low+1 &&a[j].roll> pivot ){
            j--;
        }
        if(i<j){
            swap(&a[i],&a[j],swaps);
        }
    }
    swap(&a[low],&a[j],swaps);
    return j;
}

void quickSort(struct Student a[],int low, int high, int *swaps){
   if(low<high){
    int loc=partition(a,low,high,swaps);
    quickSort(a,low,loc-1,swaps);
    quickSort(a,loc+1,high,swaps);
   }
}
void bubbleSort(struct Student a[],int n , int *swaps){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j].roll>a[j+1].roll){
                swap(&a[j],&a[j+1],swaps);
            }
        }
    }
}

int main(){
   struct  Student s[100], q[100],b[100];
   int n ;
   printf("Enter number of students:");
   scanf("%d",&n);

   for(int i=0;i<n;i++){
    printf("Enter name, roll no and marks of the student: ");
    scanf("%s %d %f",s[i].name,&s[i].roll,&s[i].marks);
    q[i]=s[i];
    b[i]=s[i];
   }
   int quickSwaps=0;
   int bubbleSwaps=0;
   quickSort(q,0,n-1,&quickSwaps);
   printf("Output of Quick Sort Algorithm on student structure:\n ");
   printStudent(q,n);
   printf("No. of swaps required for Quick Sort: %d",quickSwaps);

   printf("\n");
   printf("Output of Bubble Sort Algorithm on student structure:\n ");
   bubbleSort(b,n, &bubbleSwaps);
   printStudent(b,n);
   printf("No. of swaps required for bubble Sort: %d",bubbleSwaps);
   return 0;
}
