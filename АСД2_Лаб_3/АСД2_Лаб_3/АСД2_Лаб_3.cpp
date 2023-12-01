#include <iostream>
#include <ctime>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <vector>
#include "DynamicArray.h"

using namespace std;

struct BinaryHeap
{
    DynamicArray array;

    int getParent(int index)
    {
        return (index - 1) / 2;
    }

    int getLeftChild(int index)
    {
        return 2 * index + 1;
    }

    int getRightChild(int index)
    {
        return 2 * index + 2;
    }

    void siftUp(int index)
    {
        int parent = getParent(index);

        if (*array.get(index) < *array.get(parent) || *array.get(index) == *array.get(parent))
        {
            return;
        }

        swap(*array.get(index), *array.get(parent));
        siftUp(parent);
    }

    void siftDown(int index)
    {
        int leftChild = getLeftChild(index);
        int rightChild = getRightChild(index);
        int maxChild;

        if (array.get(rightChild) == nullptr)
        {
            if (array.get(leftChild) == nullptr)
            {

                return;
            }

            maxChild = leftChild;
        }
        else
        {
            if (*array.get(leftChild) < *array.get(rightChild))
            {
                maxChild = rightChild;
            }
            else
            {
                maxChild = leftChild;
            }
        }


        if (*array.get(index) > *array.get(maxChild) || *array.get(index) == *array.get(maxChild))
        {
            return;
        }

        swap(*array.get(index), *array.get(maxChild));
        siftDown(maxChild);
    }
};

struct PriorityQueue
{
    BinaryHeap heap;

    void push(Data object)
    {
        heap.array.push_back(&object);

        heap.siftUp(heap.array.size() - 1);
    }

    Data top()
    {
        return *heap.array.get(0);
    }

    void pop()
    {
        swap(*heap.array.get(0), *heap.array.get(heap.array.size() - 1));

        heap.array.pop_back();

        heap.siftDown(0);
    }

    int size()
    {
        return heap.array.size();
    }

    bool empty()
    {
        if (heap.array.size() > 0)
        {
            return false;
        }

        return true;
    }

    void clean()
    {
        heap.array.clear();
    }
};

struct HeapSort
{
    vector<int> array;

    int getParent(int index)
    {
        return (index - 1) / 2;
    }

    int getLeftChild(int index)
    {
        return 2 * index + 1;
    }

    int getRightChild(int index)
    {
        return 2 * index + 2;
    }

    void siftUp(int index)
    {
        int parent = getParent(index);

        if (array[index] <= array[parent])
        {
            return;
        }

        swap(array[index], array[parent]);
        siftUp(parent);
    }

    void siftDown(int index)
    {
        int leftChild = getLeftChild(index);
        int rightChild = getRightChild(index);
        int maxChild;

        if (rightChild >= array.size())
        {
            if (leftChild >= array.size())
            {
                return;
            }

            maxChild = leftChild;
        }
        else
        {
            if (array[leftChild] < array[rightChild])
            {
                maxChild = rightChild;
            }
            else
            {
                maxChild = leftChild;
            }
        }


        if (array[index] >= array[maxChild])
        {
            return;
        }

        swap(array[index], array[maxChild]);
        siftDown(maxChild);

    }

    void buildHeap(int* Arr, int arraySize)
    {
        for (int i = 0; i < arraySize; i++)
        {
            array.push_back(Arr[i]);

            siftUp(array.size() - 1);
        }

        /*cout << "HEAp: " << endl;
        for (int i = 0; i < arraySize; i++)
        {
            cout << array[i] << "\t";
        }
        cout << endl;
        cout << endl;
        cout << endl;*/
    }

    void heapSort(int* Arr, int arraySize)
    {
        buildHeap(Arr, arraySize);

        for (int i = 0, j = arraySize - 1; i < arraySize; i++, j--)
        {
            swap(array[0], array[array.size() - 1]);

            Arr[j] = array.back();
            array.pop_back();

            siftDown(0);
        }
    }

};

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}
bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;

    priority_queue<Data> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime =
        testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}

void generateDataArray(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = rand() % 201;
    }
}

bool compareArrays(int* array1, int* array2, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (!(array1[i] == array2[i]))
        {
            return false;
        }
    }
    return true;
}

void test()
{
    const int ARRAY_SIZE = 20000;
    int data1[ARRAY_SIZE];
    generateDataArray(data1, ARRAY_SIZE);

    int data2[ARRAY_SIZE];
    copy(data1, data1 + ARRAY_SIZE, data2);

    clock_t timeStartMySort = clock();
    HeapSort heapSort;
    heapSort.heapSort(data1, ARRAY_SIZE);
    clock_t timeEndMySort = clock();
    float MySort = (float(timeEndMySort - timeStartMySort)) / CLOCKS_PER_SEC;

    /*priority_queue<int> stl(data1, data1 + ARRAY_SIZE);*/

    /*for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << stl.top() << "\t";
        stl.pop();
    }*/

    clock_t timeStartSTL = clock();
    sort(data2, data2 + ARRAY_SIZE);
    clock_t timeEndSTL = clock();
    float STLSort = (float(timeEndSTL - timeStartSTL)) / CLOCKS_PER_SEC;

    cout << "HashSort: " <<  endl;
    cout << "My time: " << MySort << endl;
    cout << "STL time: " << STLSort << endl;

    if (compareArrays(data1, data2, ARRAY_SIZE))
    {
        cout << "Good!" << endl;
    }
    else
    {
        cout << "Error :(" << endl;
    }

    /*cout << "MySort: " << endl;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << data1[i] << "\t";
    }
    cout << endl;

    cout << "STLSort: " << endl;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << data2[i] << "\t";
    }
    cout << endl;*/
}

int main()
{
    testPriorityQueue();

    test();
}
