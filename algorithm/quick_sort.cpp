#include <iostream>
using namespace std;

unsigned int bit_reverse(unsigned int n)
{
    n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
    n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
    n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
    n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
    n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
    return n;
}


void QuickSort(int a[], int left, int right)
{
  // 停止条件：当a只剩下1个元素就返回（不用继续排了）
  if (left >= right)
  {
    return;
  }

  int p = right; // 为简单起见，这里p设为最右边的
  int key = a[p], l=left, r=right-1; // l-左标记，r-右标记

  while(l<=r)
  { // 若l>r，表示一趟排完了
    if (a[l]>key)
    { // 找到后就停下来
      if (a[r]<key)
      { // 找到后就停下来
        swap(a[l], a[r]); // 交换
      }
      else
      {
        r--; // 没找到r就继续往前找
      }
    }
    else
    {
      l++; // 没找到l就继续往后找
    }
  }
  swap(a[l], a[p]); // 将基准元素a[p]插入到中间正确位置

  // 这样下来，以a[p]为界，左边的全是小于a[p]的，右边的全是大于a[p]的
  QuickSort(a, left, l-1);
  QuickSort(a, r+1, right);
}

bool test()
{
    printf("test %d", __LINE__ );
    return true;
}

int main()
{
    unsigned int redata = bit_reverse(0xAAAA);
    printf("%d\n", redata);
    test();
  int n = 1005;
  int a[1005]; // 假设最多1005个元素

  // 输入数据
  for (int i=0; i<n; i++)
  {
    a[i] = rand() % 1005;
  }

  QuickSort(a, 0, n-1);

  // 输出结果
  for (int i=0; i<n; i++)
  {
    if( (i % 10) == 0 )
    {
      cout << endl;
    }
    cout << a[i] << " ";
  }

  return 0;
}



