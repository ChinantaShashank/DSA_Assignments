#include<iostream>
#include<algorithm>
using namespace std;

class DynamicArray
{
private:
    int* array;
    int capacity;
    int size;
    double resizeFactor;

    void resize() 
    {
        int newCapacity = static_cast<int>(capacity * resizeFactor);
        int* newArray = new int[newCapacity];
        for (int i = 0; i < size; ++i) 
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    DynamicArray(int initialCapacity = 2, double factor = 1.5) : capacity(initialCapacity), size(0), resizeFactor(factor) 
    {
        array = new int[capacity];
    }

    ~DynamicArray() 
    {
        delete[] array;
    }

    void insert(int index, int value) 
    {
        if (index < 0 || index > size) 
        {
            cout << "Index out of bounds\n";
            return;
        }
        if (size == capacity) 
        {
            resize();
        }
        for (int i = size; i > index; --i) 
        {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
    }

    void deleteAt(int index) 
    {
        if (index < 0 || index >= size) 
        {
            cout << "Index out of bounds\n";
            return;
        }
        for (int i = index; i < size - 1; ++i) 
        {
            array[i] = array[i + 1];
        }
        --size;
    }

    int getSize() const 
    {
        return size;
    }

    bool isEmpty() const 
    {
        return size == 0;
    }

    void rotate(int k) 
    {
        if (size == 0 || k % size == 0) return;
        k = k % size;
        std::reverse(array, array + size);
        std::reverse(array, array + k);
        std::reverse(array + k, array + size);
    }

    void reverseArray() 
    {
        std::reverse(array, array + size);
    }

    void append(int value) 
    {
        if (size == capacity) 
        {
            resize();
        }
        array[size++] = value;
    }

    void prepend(int value) 
    {
        insert(0, value);
    }

    void merge(const DynamicArray& other) 
    {
        for (int i = 0; i < other.size; ++i) 
        {
            append(other.array[i]);
        }
    }

    void interleave(const DynamicArray& other) 
    {
        int newSize = size + other.size;
        int* newArray = new int[newSize];
        int i = 0, j = 0, k = 0;

        while (i < size && j < other.size) 
        {
            newArray[k++] = array[i++];
            newArray[k++] = other.array[j++];
        }

        while (i < size) 
        {
            newArray[k++] = array[i++];
        }

        while (j < other.size) 
        {
            newArray[k++] = other.array[j++];
        }

        delete[] array;
        array = newArray;
        size = newSize;
        capacity = newSize;
    }

    int getMiddle() const 
    {
        if (size == 0) 
        {
            cout << "Array is empty\n";
            return -1;
        }
        return array[size / 2];
    }

    int indexOf(int value) const 
    {
        for (int i = 0; i < size; ++i) 
        {
            if (array[i] == value) 
            {
                return i;
            }
        }
        return -1;
    }

    void split(int index, DynamicArray& array1, DynamicArray& array2) const 
    {
        if (index < 0 || index > size) 
        {
            cout << "Index out of bounds\n";
            return;
        }

        for (int i = 0; i < index; ++i) 
        {
            array1.append(array[i]);
        }

        for (int i = index; i < size; ++i) 
        {
            array2.append(array[i]);
        }
    }

    void display() const 
    {
        for (int i = 0; i < size; ++i) 
        {
            cout << array[i] << " ";
        }
        cout << "\n";
    }
};

int main() 
{
    DynamicArray array1;

    array1.append(10);
    array1.append(20);
    array1.append(30);
    array1.display(); 

    array1.insert(1, 15);
    array1.display(); 

    array1.deleteAt(2);
    array1.display(); 
    array1.append(40);
    array1.display(); 

    array1.prepend(5);
    array1.display();

    array1.rotate(2);
    array1.display();

    array1.reverseArray();
    array1.display(); 

    cout << "Size of the array: " << array1.getSize() << "\n"; // Output: 5
    cout << "Is the array empty? " << (array1.isEmpty() ? "Yes" : "No") << "\n"; // Output: No
    cout << "Middle element: " << array1.getMiddle() << "\n"; // Output: 5
    cout << "Index of 10: " << array1.indexOf(10) << "\n"; // Output: 1
    cout << "Index of 100: " << array1.indexOf(100) << "\n"; // Output: -1

    DynamicArray array2, array3;
    array1.split(2, array2, array3);
    array2.display();
    array3.display(); 

    DynamicArray array4;
    array4.append(50);
    array4.append(60);
    array1.merge(array4);
    array1.display(); 

    DynamicArray array5;
    array5.append(70);
    array5.append(80);
    array5.append(90);
    array1.interleave(array5);
    array1.display(); 

    return 0;
}
