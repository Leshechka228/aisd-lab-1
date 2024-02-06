#include <iostream>
#include <random>
#include <chrono>

using namespace std;

class MySet {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    MySet() : root(nullptr) {}

    // ����������� �����������
    MySet(const MySet& other) {
        root = clone(other.root);
    }

    // ����������
    ~MySet() {
        clear(root);
    }

    // �������� ������������
    MySet& operator=(const MySet& other) {
        if (this != &other) {
            clear(root);
            root = clone(other.root);
        }
        return *this;
    }

    // ������ �����������
    void print() {
        printInOrder(root);
    }

    // ������� ��������
    bool insert(int key) {
        return insertValue(root, key);
    }

    // �������� ������� ��������
    bool contains(int key) {
        return containsValue(root, key);
    }

    // �������� ��������
    bool erase(int key) {
        return eraseValue(root, key);
    }

private:
    // ����������� ������� ��� ������������ ������
    Node* clone(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);

        return newNode;
    }

    // ����������� ������� ��� ������� ������
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // ����������� ������� ��� ������ elements � ������� �����������
    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->data << " ";
            printInOrder(node->right);
        }
    }

    // ����������� ������� ��� ������� ��������
    bool insertValue(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }

        if (key == node->data) {
            return false; // ����� ������� ��� ����������
        }

        if (key < node->data) {
            return insertValue(node->left, key); // ���������� ��������� � ����� ���������
        }
        else {
            return insertValue(node->right, key); // ���������� ��������� � ������ ���������
        }
    }

    // ����������� ������� ��� �������� ������� ��������
    bool containsValue(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->data) {
            return true;
        }

        if (key < node->data) {
            return containsValue(node->left, key); // ���������� ��������� � ����� ���������
        }
        else {
            return containsValue(node->right, key); // ���������� ��������� � ������ ���������
        }
    }

    // ����������� ������� ��� �������� ��������
    bool eraseValue(Node*& node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->data) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                eraseValue(node->right, temp->data);
            }
            return true;
        }

        if (key < node->data) {
            return eraseValue(node->left, key); // ���������� ������� � ����� ���������
        }
        else {
            return eraseValue(node->right, key); // ���������� ������� � ������ ���������
        }
    }

    // ������� ��� ������ ������������ �������� � ���������
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

double fillTime(int n) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000000);

    MySet set;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        set.insert(distribution(generator));
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000; // ����� � �������������
}

double searchTime(int n) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000000);

    MySet set;

    for (int i = 0; i < n; ++i) {
        set.insert(distribution(generator));
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        set.contains(distribution(generator));
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000; // ����� � �������������
}

double addRemoveTime(int n) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000000);

    MySet set;

    for (int i = 0; i < n; ++i) {
        set.insert(distribution(generator));
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        int key = distribution(generator);

        if (distribution(generator) % 2 == 0) {
            set.insert(key);
        }
        else {
            set.erase(key);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000; // ����� � �������������
}

int main() {
    // ������������ ������� ����������
    std::cout << "Fill time:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << fillTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << fillTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << fillTime(100000) << " milliseconds" << std::endl;
    std::cout << std::endl;

    // ������������ ������� ������
    std::cout << "search time:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << searchTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << searchTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << searchTime(100000) << " milliseconds" << std::endl;
    std::cout << std::endl;

    // ������������ ������� ���������� � ��������
    std::cout << "Add and remove times:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << addRemoveTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << addRemoveTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << addRemoveTime(100000) << " milliseconds" << std::endl;

    return 0;
}