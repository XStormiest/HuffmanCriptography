#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include <iostream>
#include <string.h>
using namespace std;
char** codes; int codes_idx = 0;

struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode* left, *right;
};

struct MinHeap {
    int size;
    int capacity;
    MinHeapNode** array;
};

MinHeapNode* newNode(char data, unsigned freq)
{
    MinHeapNode* temp = new MinHeapNode[ sizeof(MinHeapNode) ];
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap = new MinHeap[ sizeof(MinHeap) ];
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new MinHeapNode*[capacity];
    return minHeap;
}

void swapMinHeapNode( MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int index)
{
    int smallest = index;
    int left =  2 * index + 1;
    int right = 2 * index + 2;
    if( left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if( right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if(smallest != index)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

bool isSizeOne(MinHeap* minHeap)
{
    return minHeap->size == 1;
}

MinHeapNode* extractMin(MinHeap* minHeap)
{
    MinHeapNode * temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size-1];

    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while( i && minHeapNode->freq < minHeap->array[ (i-1)/2 ]->freq) {
        minHeap->array[i] = minHeap->array[ (i-1)/2 ];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for( i = (n-1) / 2; i >=0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for(i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

bool isLeaf(MinHeapNode* root)
{
    return !(root->left) && !(root->right);
}

MinHeap* buildMinHeap(char data[],  int freq[], int size)
{
    MinHeap* minHeap = createMinHeap(size);

    for(int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    return minHeap;
}

MinHeapNode* buildHuffman(char data[], int freq[], int size)
{
    MinHeapNode* left, *right, *top;;
    MinHeap* minHeap = buildMinHeap(data, freq, size);
    while(!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void getCodes(MinHeapNode* root, char arr[], int top)
{
    if(root->left) {
        arr[top] = '0';
        getCodes(root->left, arr, top+1);
    }

    if(root->right) {
        arr[top] = '1';
        getCodes(root->right, arr, top + 1);
    }

    if(isLeaf(root)) {
        arr[top] = '\0';

        strcpy(codes[codes_idx++], arr);
    }
}

void HuffmanCodes(char* data, int freq[], int size)
{
    MinHeapNode * root = buildHuffman(data, freq, size);

    char arr[100]; int top = 0;
    getCodes(root, arr, top);
}


#endif // HUFFMAN_H_INCLUDED
