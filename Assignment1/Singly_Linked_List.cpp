#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class SinglyLL {
private:
    Node* head;
    int size;

public:
    SinglyLL() : head(nullptr), size(0) {}

    ~SinglyLL() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(int index, int value) 
    {
        if (index < 0 || index > size) 
        {
            cout << "Index out of bounds\n";
            return;
        }
        Node* newNode = new Node();
        newNode->data = value;
        if (index == 0) 
        {
            newNode->next = head;
            head = newNode;
        } 
        else 
        {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) 
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    void deleteAt(int index) 
    {
        if (index < 0 || index >= size) 
        {
            cout << "Index out of bounds\n";
            return;
        }
        Node* tDelete;
        if (index == 0) 
        {
            tDelete = head;
            head = head->next;
        } 
        else 
        {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) 
            {
                current = current->next;
            }
            tDelete = current->next;
            current->next = tDelete->next;
        }
        delete tDelete;
        size--;
    }


    int Sizee() 
    const 
    {
        return size;
    }

    bool isEmpty() 
    const 
    {
        return head == nullptr;
    }

    void rotate(int k) 
    {
        if (head == nullptr || k == 0) return;
        k = k % size;
        if (k == 0) return;
        Node* current = head;
        int count = 1;
        while (count < size - k && current != nullptr)
        {
            current = current->next;
            count++;
        }
        Node* kthNode = current;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = head;
        head = kthNode->next;
        kthNode->next = nullptr;
    }

    void reverse() 
    {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) 
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void append(int value) 
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr)
         {
            head = newNode;
        } 
        else 
        {
            Node* current = head;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void prepend(int value) 
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void merge(SinglyLL& other) 
    {
        if (other.head == nullptr) return;
        if (head == nullptr) 
        {
            head = other.head;
        } 
        else 
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = other.head;
        }
        size += other.size;
        other.head = nullptr;
        other.size = 0;
    }
    int Middlee() 
    const 
    {
        if (head == nullptr) 
        {
            cout << "List is empty\n";
            return -1;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) 
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    int indexOf(int value) 
    const 
    {
        Node* current = head;
        int index = 0;
        while (current != nullptr) 
        {
            if (current->data == value) 
            {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1;
    }

    void display()
    const 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }
};

int main() 
{
    SinglyLL slist;

    slist.insert(0, 10);
    slist.insert(1, 20);
    slist.insert(2, 30);
    slist.display();

    slist.insert(1, 15);
    slist.display();

    slist.deleteAt(2);
    slist.display();

    slist.append(40);
    slist.display();

    slist.prepend(5);
    slist.display();

    slist.rotate(2);
    slist.display();


    slist.reverse();
    slist.display();

    cout << "Size of the list: " << slist.Sizee() << "\n";

    cout << "Is the list empty? " << (slist.isEmpty()) << "\n";

    cout << "Middle element: " << slist.Middlee() << "\n";

    cout << "Index of 10: " << slist.indexOf(10) << "\n";
    cout << "Index of 100: " << slist.indexOf(100) << "\n";
}