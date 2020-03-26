#include"insertion.h"
void insertion(int arr[], int n)
{
    n = n / sizeof(arr[0]);
    for(int i = 1; i < n; ++i )
    {
        for(int j = i; j > 0; --j)
        {
            if(arr[j-1] > arr[j])
            {
                swapTwo(arr,j-1,j);
            }
            else
            {
                break;
            }
        }
    }
}

void swapTwo(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void binaryInsertion(int arr[], int n)
{
    n = n / sizeof(arr[0]);
    for(int i = 0; i < n-1; ++i)
    {
        int low = 0;
        int high = i+1;
        int middle = 0;
        while(high >= low)
        {
            middle = (low + high)/2;
            if(arr[middle] > arr[i+1])
            {
                high = middle - 1;
            }
            else
            {
                low = middle + 1;
            }
        }
        for(int j = i+1; j > middle;--j)
        {
            swapTwo(arr,j,j-1);
        }
    }
}
void shellsort(int v[],int n)
{
    n = n/sizeof(v[0]);
    int gap,i,j,temp;
    for (gap = n/2; gap > 0; gap /= 2)
    {
        for(i = gap; i < n; i++)

            for(j = i-gap; j>=0 && v[j]>v[j+gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }

    }
}

void shellInsertion(int arr[], int n)
{
    n = n/sizeof(arr[0]);
    for(int batch = n/2;batch >= 1;batch=batch/2)
    {
        for(int i = batch; i < n; i += batch)
        {
            for(int j = i; j >=batch ; j -= batch)
            {
                if(arr[j]<arr[j-batch])
                {
                    swapTwo(arr,j,j-batch);
                }
            }
        }
    }
}


 void heerSort(int a[],int n) {
//    System.out.println();
     int length = n/sizeof(a[0]);
    int d = length/2;//默认增量
    while (true) {
        for (int i = 0; i < d; i++) {
            for (int j = i; j + d < length; j += d) {//i开始，d为增量分组比较(eg:d=3; i=0; j=0、3，3、6，6、9，9、12，12、15)
                int temp;
                if (a[j] > a[j + d]) {//互换位置
                    temp = a[j];
                    a[j] = a[j + d];
                    a[j + d] = temp;
                }
            }
        }
        cout<<"\nd: "<<d<<endl;
        for (int x = 0; x < length; ++x)
        {
            cout<<a[x]<<" ";
        }
        cout<<endl;
        if (d == 1) {
            break;
        }
        d--;//增量-1继续比较
    }

}

void heerBubbleSort(int a[],int n) {
    //    System.out.println();
      int length = n/sizeof(a[0]);
      int d = length / 2;
      while (true) {
//          d = d/2;
          for (int i = 0; i < d; i++) {
              for (int j = i; j + d < length; j += d) {//i开始，d为增量分组比较并组内排序(eg:d=3; i=0; j=0、3、6、9、12、15)
                  for (int n = i; n + d < length; n += d) {//冒泡排序（组内排序）
                      int temp;
                      if (a[n] > a[n + d]) {//互换位置
                          temp = a[n];
                          a[n] = a[n + d];
                          a[n + d] = temp;
                      }
                  }
              }
          }
          if (d == 1) {
              break;
          }
          cout<<d<<endl;
          d--;//增量-1继续比较/
      }
}

void bubbleSortTest(int a[],int n) {
    //    System.out.println();
      int length = n/sizeof(a[0]);

      for(int i = 0;i < length ;i++)
      {
          for(int j = length -1; j > i; j--)
          {
              cout<<a[j]<<endl;
              int temp;
              if (a[j] < a[j - 1]) {//互换位置
                  temp = a[j];
                  a[j] = a[j - 1];
                  a[j - 1] = temp;

              }
          }

          }
      }
