#include <iostream>
#include <random>
#include <chrono>

using namespace std;

class Set {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    Set() : root(nullptr) {}

    Set(const Set& other) {
        root = clone(other.root);
    }

    ~Set() {
        clear(root);
    }

    // Оператор присваивания
    Set& operator=(const Set& other) {
        if (this != &other) {
            clear(root);
            root = clone(other.root);
        }
        return *this;
    }

    // Печать содержимого
    void print() {
        printInOrder(root);
    }

    // Вставка элемента
    bool insert(int key) {
        return insertValue(root, key);
    }

    // Проверка наличия элемента
    bool contains(int key) {
        return containsValue(root, key);
    }

    // Удаление элемента
    bool erase(int key) {
        return eraseValue(root, key);
    }

private:
    // Рекурсивная функция для клонирования дерева
    Node* clone(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);

        return newNode;
    }

    // Рекурсивная функция для очистки памяти
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Рекурсивная функция для печати elements в порядке возрастания
    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->data << " ";
            printInOrder(node->right);
        }
    }

    // Рекурсивная функция для вставки элемента
    bool insertValue(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }

        if (key == node->data) {
            return false; // Такой элемент уже существует
        }

        if (key < node->data) {
            return insertValue(node->left, key); // Рекурсивно вставляем в левое поддерево
        }
        else {
            return insertValue(node->right, key); // Рекурсивно вставляем в правое поддерево
        }
    }

    // Рекурсивная функция для проверки наличия элемента
    bool containsValue(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->data) {
            return true;
        }

        if (key < node->data) {
            return containsValue(node->left, key); // Рекурсивно проверяем в левом поддереве
        }
        else {
            return containsValue(node->right, key); // Рекурсивно проверяем в правом поддереве
        }
    }

    // Рекурсивная функция для удаления элемента
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
            return eraseValue(node->left, key); // Рекурсивно удаляем в левом поддереве
        }
        else {
            return eraseValue(node->right, key); // Рекурсивно удаляем в правом поддереве
        }
    }

    // Функция для поиска минимального элемента в поддереве
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

double fillTime(int n) {
    Set set;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double searchTime(int n) {
    Set set;

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        set.contains(lcg());
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double addRemoveTime(int n) {
    Set set;

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        size_t key = lcg();

        if (lcg() % 2 == 0) {
            set.insert(key);
        }
        else {
            set.erase(key);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

int main() {
    // Тестирование времени заполнения
    std::cout << "Fill time:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << fillTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << fillTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << fillTime(100000) << " milliseconds" << std::endl;
    std::cout << std::endl;

    // Тестирование времени поиска
    std::cout << "search time:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << searchTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << searchTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << searchTime(100000) << " milliseconds" << std::endl;
    std::cout << std::endl;

    // Тестирование времени добавления и удаления
    std::cout << "Add and remove times:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "1000 elements: " << addRemoveTime(1000) << " milliseconds" << std::endl;
    std::cout << "10000 elements: " << addRemoveTime(10000) << " milliseconds" << std::endl;
    std::cout << "100000 elements: " << addRemoveTime(100000) << " milliseconds" << std::endl;

    return 0;
}