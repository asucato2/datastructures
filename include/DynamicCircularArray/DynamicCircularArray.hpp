#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

template <class T>
class DynamicCircularArray
{
protected:
    T *_store; // pointer to array
    unsigned int _startIndex; // index of first element
    unsigned int _endIndex; // index of next available index
    unsigned int _size; // number of elements in store
    unsigned int _capacity; // number of elements store can hold

    T _errorDump;

    /**
     * @brief Determine corrected index (if you go above or below limits)
     *
     * This is the heart of increment and decrement index functions
     */
    int correctIndex(int index)
    {
        return (index + _capacity) % _capacity;
    }

    int decrementIndex(int index)
    {
        return correctIndex(index - 1);
    }

    int incrementIndex(int index)
    {
        return correctIndex(index + 1);
    }

    int findMedian5(int arr[], int left, int right)
    {
        insertionSort(arr, left, right);
        return (left + right) / 2;
    }

    void insertionSort(int arr[], const int left, const int right)
    {
        int len = right - left + 1;

        for (int i = left; i <= right; i++)
        {
            int t = arr[i];
            int j = i - 1;

            while (j >= left && t < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = t;
        }
    }

    int selectPivot(int arr[], int left, int right)
    {
        // Base case
        if (right - left < 5)
            return findMedian5(arr, left, right);

        int numMedians = 0;
        for (int i = left; i < right; i += 5)
        {
            int subRight = i + 4;
            // check to make sure subarray index isn't past right bound
            if (subRight > right)
                subRight = right;

            int subMedian = findMedian5(arr, i, subRight);
            swap(arr, subMedian, left + (i / 5));

            numMedians++;
        }

        return selectPivot(arr, left, left + numMedians);
    }

    void swap(int arr[], int a, int b)
    {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    int partition(int arr[], int l, int r, int pivot)
    {
        int pivotVal = arr[l];
        int firstGreaterIndex = r;

        for (int i = r; i > l; i--)
        {
            if (arr[i] > pivotVal)
            {
                swap(arr, firstGreaterIndex, i);
                firstGreaterIndex--;
            }
        }

        swap(arr, l, firstGreaterIndex); // Plop the pivot val where it belongs
        return firstGreaterIndex;
    }

    int findKthSmallest(int arr[], const int k, int l, int r, bool medianOfMedians = 0)
    {
        const int desiredIndex = k - 1; // ex. 2nd smallest is in 1st index

        while (l <= r)
        {
            int pivotIndex = l;
            if (medianOfMedians)
                pivotIndex = selectPivot(arr, l, r);

            int finalIndexOfChosenPivot = partition(arr, l, r, pivotIndex);

            if (finalIndexOfChosenPivot == desiredIndex)
            {
                // bingo
                return arr[finalIndexOfChosenPivot];
            }
            else if (finalIndexOfChosenPivot > desiredIndex)
            {
                // overshot - need to do a partition on left
                r = finalIndexOfChosenPivot - 1;
            }
            else
            {
                // undershot - need to do a partition on right
                l = finalIndexOfChosenPivot + 1;
            }
        }
        return -1;
    }

    void merge(int arr[], const int start, const int mid, const int end)
    {
        int sortedArr[end - start + 1];
        int leftIndex = start;
        int rightIndex = mid + 1;
        int sortedIndex = 0;

        // While neither half is empty
        while (leftIndex <= mid && rightIndex <= end)
        {
            if (arr[leftIndex] < arr[rightIndex])
            {
                sortedArr[sortedIndex] = arr[leftIndex];
                leftIndex++;
                sortedIndex++;
            }
            else if (arr[leftIndex] > arr[rightIndex])
            {
                sortedArr[sortedIndex] = arr[rightIndex];
                rightIndex++;
                sortedIndex++;
            }
            else
            {
                sortedArr[sortedIndex] = arr[leftIndex];
                sortedIndex++;
                leftIndex++;
            }
        }

        // fill in the remaining items left at the end
        while (leftIndex <= mid)
        {
            sortedArr[sortedIndex] = arr[leftIndex];
            sortedIndex++;
            leftIndex++;
        }

        while (rightIndex <= end)
        {
            sortedArr[sortedIndex] = arr[rightIndex];
            sortedIndex++;
            rightIndex++;
        }

        // copy the array back into the original array
        for (int i = 0; i <= end - start; i++)
        {
            arr[i + start] = sortedArr[i];
        }
    }

    void mergeSort(int arr[], const int start, const int end)
    {
        if(start < end) // if size > 1
        {
            int mid = (start + end) / 2;
            mergeSort(arr, start, mid);     // recurse on left half
            mergeSort(arr, mid + 1, end);   // recurse on right half
            merge(arr, start, mid, end);    // merge sorted halves
        }
    }

    int getBit(const int a, const unsigned int bit)
    {
        unsigned int mask = 0x01u;

        int val = mask & (a >> bit);
        return mask & (a >> bit);
    }


    void countingSortBitwise(int arr[], int sorted[], const int len, const int bit)
    {
        int count[2] = {0};

        for (int i = 0; i < len; i++)
        {
            int test = getBit(arr[i], bit);
            count[getBit(arr[i], bit)]++;
        }

        count[1] = count[1] + count[0];

        for (int i = len - 1; i >= 0; i--)
        {
            sorted[count[getBit(arr[i], bit)] - 1] = arr[i];
            count[getBit(arr[i], bit)]--;
        }
    }


    /// Copy store to new array, with length = _size
    void copyStore(T *dest)
    {
        for (int i = 0; i < _size; i++)
        {
            dest[i] = get(i);
        }
    }

    void expandStore()
    {
        T *newStore = new T[_capacity * 2];
        copyStore(newStore);

        delete[] _store;
        _store = newStore;

        _startIndex = 0;
        _endIndex = _size;
        _capacity *= 2;
    }

    void reduceStore()
    {
        if ((_capacity / 2) < 2)
            return;

        T *newStore = new T[_capacity / 2];
        copyStore(newStore);

        delete[] _store;
        _store = newStore;

        _startIndex = 0;
        _endIndex = _size - 1;
        _capacity /= 2;
    }

public:
    /// Default Constructor
    explicit DynamicCircularArray() :
            _startIndex(0),
            _endIndex(0),
            _size(0),
            _capacity(2)
    {
        _store = new T[_capacity];
    }
    explicit DynamicCircularArray(int capacity) :
            _startIndex(0),
            _endIndex(0),
            _size(capacity),
            _capacity(capacity)
    {
        _store = new T[_capacity];
    }

    /// Copy Constructor
    DynamicCircularArray(DynamicCircularArray &copy) :
            _capacity(copy.capacity()),
            _startIndex(0),
            _endIndex(0),
            _size(0)
    {
        _store = new T[_capacity];
        for (int i = 0; i < copy._size; i++)
        {
            addEnd(copy[i]);
        }
    }

    /// Destructor
    ~DynamicCircularArray()
    {
        delete[] _store;
    }


    /// Returns element at logical index
    T& get(int index)
    {
        return _store[correctIndex(index + _startIndex)];
    }

    /// Access operator
    T& operator[](int index)
    {
        if(index >= _size)
        {
            std::cout << "Error: Attempted access outside of bounds" << std::endl;
            return _errorDump;
        }
        return get(index);
    }


    void set(int index, T& value)
    {
        _store[correctIndex(index + _startIndex)] = value;
    }

    /// Assignment operator
    DynamicCircularArray& operator= (DynamicCircularArray array)
    {
        // Self assignment guard
        if (this == &array)
            return *this;

        delete[] _store;
        _size = 0;
        _startIndex = 0;
        _endIndex = 0;
        _capacity = array._capacity;
        _store = new T[_capacity];

        for (int i = 0; i < array._size; i++)
        {
            addEnd(array[i]);
        }
    }

    /// Returns number of elements contained
    int length()
    {
        return _size;
    }

    /// Returns capacity of array
    int capacity()
    {
        return _capacity;
    }

    /// Add element to back of array
    void addEnd(T val)
    {
        if (_size + 1 > _capacity)
            expandStore();

        _store[_endIndex] = val;
        _endIndex = incrementIndex(_endIndex);
        _size++;
    }

    /// Add element to front of array
    void addFront(T val)
    {
        // Edge case where there are no elements
        if (_size == 0)
            addEnd(val);

        else
        {
            if (_size + 1 > _capacity)
                expandStore();

            _startIndex = decrementIndex(_startIndex);
            _store[_startIndex] = val;
            _size++;
        }
    }

    /// Deletes item at front of array
    void delFront()
    {
        // Guard against case where there are no elements
        if (_size <= 0)
            return;

        _startIndex = incrementIndex(_startIndex);
        _size--;

        if (_size <= _capacity / 4)
            reduceStore();
    }

    /// Deletes item at back of array
    void delEnd()
    {
        // Guard against case where there are no elements
        if (_size <= 0)
            return;

        _endIndex = decrementIndex(_endIndex);
        _size--;

        if (_size <= _capacity / 4)
            reduceStore();
    }

    void clear()
    {
        delete[] _store;

        _store = new T[2];
        _startIndex = 0;
        _endIndex = 0;
        _capacity = 2;
        _size = 0;
    }

    /**
     * Search linearly through array for element
     *
     * @param val - value searching for
     * @return index of first val found, if none found -1 returned
     */
    int linearSearch(T val)
    {
        for (int i = 0; i < _size; i++)
        {
            if (get(i) == val)
                return i;
        }
        return -1; // If not found return -1
    }

    /**
     * Returns the kth smallest element in the array using the quickselect alg.
     *
     * @param k - kth smallest element
     * @return element
     */
    T quickSelect(int k)
    {
        T copy[_size];
        copyStore(copy);

        findKthSmallest(copy, k, 0, _size-1);
    }

    T WCSelect(int k)
    {
        T copy[_size];
        copyStore(copy);

        findKthSmallest(copy, k, 0, _size - 1, 1);
    }

    /// Sorts the store
    void stableSort()
    {
        T copy[_size];
        copyStore(copy);

        mergeSort(copy, 0, _size-1);

        for(int i = 0; i < _size; i++)
            set(i, copy[i]);
    }

    void radixSort(int bits)
    {
        T copy[_size], sorted[_size] = {0};
        copyStore(copy);

        for (int i = 0; i < bits; i++)
        {
            countingSortBitwise(copy, sorted, _size, i);
            for (int j = 0; j < _size; j++)
                copy[j] = sorted[j];
        }

        for (int i = 0; i < _size; i++)
            set(i, sorted[i]);
    }

    /**
     * Binary search on sorted array
     *
     * @param val - value you want to find
     * @return integer of index or -1 if not found
     */
    int binSearch(T val)
    {
        int l = 0;
        int r = _size;
        int m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (val > get(m))
                l = m + 1;
            else if (val < get(m))
                r = m - 1;
            else
                return m;
        }

        return -1;
    }

};

#endif //DYNAMICARRAY_H