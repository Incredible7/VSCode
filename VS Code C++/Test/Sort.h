#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//ð������
void Bubble_Sort(int A[], int m) {
    int x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (A[j] > A[j + 1]) {
                x = A[j];
                A[j] = A[j + 1];
                A[j + 1] = x;
            }
        }
    }
}

void bubble_sort(vector<int> &nums, int n) {
    bool swapped;
    for (int i = 1; i < n; ++i) {
        swapped = false;
        for (int j = 1; j < n - i + 1; ++j) {
            if (nums[j] < nums[j - 1]) {
                swap(nums[j], nums[j - 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

//ѡ������
void Selection_Sort(int A[], int m) {
    int x = 0;
    for (int i = 0; i < m; i++) {
        int min = i;
        for (int j = i + 1; j < m; j++) {
            if (A[j] < A[min])
                min = j;
        }
        x = A[i];
        A[i] = A[min];
        A[min] = x;
    }
}

void selection_sort(vector<int> &nums, int n) {
    int mid;
    for (int i = 0; i < n - 1; ++i) {
        mid = i;
        for (int j = i + 1; j < n; j++)
            if (nums[j] < nums[mid])
                mid = j;
        swap(nums[mid], nums[i]);
    }
}

//��������
void Insertion_Sort(int A[], int m) {
    int current, pre;
    for (int i = 1; i < m; i++) {
        pre = i - 1;
        current = A[i];
        while (pre >= 0 && A[pre] > current) {
            A[pre + 1] = A[pre];
            pre--;
        }
        A[pre + 1] = current;
    }
    return;
}

void insertion_sort(vector<int> &nums, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; j--)
            swap(nums[i], nums[j - 1]);
    }
}

//ϣ������
void ShellSort(int A[], int len) // m==length
{
    for (int gap = len >> 1; gap > 0; gap = gap >> 1) {
        for (int i = gap; i < len; i++) {
            for (int j = i; j > gap - 1; j -= gap) {
                if (A[j - gap] > A[j])
                    swap(A[j], A[j - gap]);
            }
        }
    }
}

//�鲢����
int *B = (int *)malloc(9 * sizeof(int)); //��������

void Merge(int A[], int low, int mid, int high) {
    int i, j, k;
    for (k = low; k <= high; k++) //�������ռ丳ֵ
        B[k] = A[k];
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high;
         k++) //������������������
    {
        if (B[i] <= B[j])
            A[k] = B[i++];
        else
            A[k] = B[j++];
    }
    //�����϶���Ǹ����������ֵ
    while (i <= mid)
        A[k++] = B[i++];
    while (j <= high)
        A[k++] = B[j++];
}

void Merge_Sort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        Merge_Sort(A, low, mid);
        Merge_Sort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}

void merge_sort(vector<int> &nums, int l, int r, vector<int> &temp) {
    if (l + 1 >= r)
        return;
    // devide
    int m = l + (r - l) / 2;
    merge_sort(nums, l, m, temp);
    merge_sort(nums, m, r, temp);
    // conquer
    int p = l, q = m, i = l;
    while (p < m || q < r) {
        if (q >= r || (p < m && nums[p] <= nums[q]))
            temp[i++] = nums[p++];
        else
            temp[i++] = nums[q++];
    }
    for (i = l; i < r; ++i)
        nums[i] = temp[i];
}

//��������
int Partrition(int A[], int low, int high) //ÿִ��һ��ȷ��pivot��λ��
{
    int pivot = A[low];
    while (low < high) {
        while (low < high && A[high] >= pivot) //��������С�ںſ��Ըı�������
            high--;
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void Quick_Sort(int A[], int low, int high) {
    if (low < high) {
        int partrition = Partrition(A, low, high);
        Quick_Sort(A, low, partrition);
        Quick_Sort(A, partrition + 1, high);
        return;
    }
}

void quick_sort(vector<int> &nums, int l, int r) {
    if (l + 1 >= r)
        return;
    int first = l, last = r - 1, key = nums[first];
    while (first < last) {
        while (first < last && nums[last] >= key)
            --last;
        nums[first] = nums[last];
        while (first < last && nums[first] <= key)
            ++first;
        nums[last] = nums[first];
    }
    nums[first] = key;
    quick_sort(nums, l, first);
    quick_sort(nums, first + 1, r);
}

//�ѵ��㷨
//�������ϵĶ����򻯣��ϸ�����ʵ��
void swim(int A[], int k) {
    while (k > 1 && A[k / 2] < A[k]) {
        swap(A[k / 2], A[k]);
        k = k / 2;
    }
}
//�������µĶ����򻯣��³�����ʵ��
void sink(int A[], int k, int len) {
    while (2 * k + 1 < len) {
        int j = 2 * k + 1;
        if (A[j] <= A[j + 1])
            j++;
        if (A[k] > A[j])
            break;
        swap(A[k], A[j]);
        k = j;
    }
}

//������
void HeapSort(int A[], int len) {
    int N = len - 1;
    for (int k = N / 2 - 1; k >= 0; k--)
        sink(A, k, N);
    while (N > 0) {
        swap(A[0], A[N--]);
        sink(A, 0, N);
    }
}

//堆排序通俗易懂版
void Heapify(vector<int> &nums, int len, int k) {
    if (k >= len)
        return;
    int lc = 2 * k + 1, rc = 2 * k + 2;
    int max = k;
    if (lc < len && nums[lc] > nums[max])
        max = lc;
    if (rc < len && nums[rc] > nums[max])
        max = rc;
    if (max != k) {
        swap(nums[max], nums[k]);
        Heapify(nums, len, max);
    }
}

void BuildHeap(vector<int> &nums, int len) {
    int last_node = len - 1;
    int parent = (last_node - 1) / 2;
    for (int i = parent; i >= 0; i--)
        Heapify(nums, len, i);
}

void HeapSort01(vector<int> &nums, int len) {
    BuildHeap(nums, len);
    for (int i = len - 1; i >= 0; i--) {
        swap(nums[i], nums[0]);
        Heapify(nums, i, 0);
    }
}

//��������
//Ͱ����
//��������
int maxbit(int data[], int len) //�������飬����������λ��
{
    int maxData = data[0]; //�����
    for (int i = 1; i < len; i++) {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p) {
        // p*=10  Maybe OverFlow
        maxData /= 10;
        ++d;
    }
    return d;
}

void RadixSort(int A[], int len) {
    int d = maxbit(A, len);
    int *tmp = new int[len];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for (i = 0; i <= d; i++) //����d������
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for (j = 0; j < len; j++) {
            k = (A[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for (j = len - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (A[j] / radix) % 10;
            tmp[count[k] - 1] = A[j];
            count[k]--;
        }
        for (j = 0; j < len; j++)
            A[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}