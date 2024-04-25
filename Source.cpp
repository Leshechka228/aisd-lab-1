#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

class Set {
public:

    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Set() : root(nullptr) {}

    Set(const Set& other) {
        root = clone(other.root);
    }

    ~Set() {
        clear(root);
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            clear(root);
            root = clone(other.root);
        }
        return *this;
    }

    void print() {
        printInOrder(root);
    }

    bool insert(int key) {
        return insertValue(root, key);
    }

    bool contains(int key) {
        return containsValue(root, key);
    }

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

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double searchTime(int n) {
    Set set;

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        set.contains(lcg());
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double addRemoveTime(int n) {
    Set set;

    for (int i = 0; i < n; ++i) {
        set.insert(lcg());
    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        size_t key = lcg();

        if (lcg() % 2 == 0) {
            set.insert(key);
        }
        else {
            set.erase(key);
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double fillTimeVector(int n) {
    vector<int> vec;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        vec.push_back(lcg());
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double searchTimeVector(int n) {
    vector<int> vec;

    for (int i = 0; i < n; ++i) {
        vec.push_back(lcg());
    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        find(vec.begin(), vec.end(), lcg());
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

double addRemoveTimeVector(int n) {
    vector<int> vec;

    for (int i = 0; i < n; ++i) {
        vec.push_back(lcg());
    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        int key = lcg();

        if (lcg() % 2 == 0) {
            vec.push_back(key);
        }
        else {
            vec.erase(remove(vec.begin(), vec.end(), key), vec.end());
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    return time.count() * 1000;
}

void unionSetsHelper(Set& result, Set::Node* node) {
    if (node != nullptr) {
        // Вставляем данные узла в множество result
        result.insert(node->data);

        // Рекурсивно обрабатываем левое и правое поддерево
        unionSetsHelper(result, node->left);
        unionSetsHelper(result, node->right);
    }
}

Set unionOfSets(const Set& set1, const Set& set2) {
    Set result(set1); // Создаем копию первого множества

    // Функция-помощник для выполнения объединения
    unionSetsHelper(result, set2.root);

    return result;
}

void addUniqueElementsToResult(Set::Node* node, Set& result) {
    if (node != nullptr) {
        Set result2 = result;
        if (result.contains(node->data)) {
            result.erase(node->data);
        }

        if (!result2.contains(node->data)) {
            result.insert(node->data);
        }

        // Рекурсивно обходим левое и правое поддеревья
        addUniqueElementsToResult(node->left, result);
        addUniqueElementsToResult(node->right, result);
    }
}
Set symmetricDifference(const Set& set1, const Set& set2) {
    Set result(set1);

    addUniqueElementsToResult(set2.root, result);

    return result;
}

int main() {
    // Тестирование времени заполнения
    cout << "Fill time:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << fillTime(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << fillTime(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << fillTime(100000) << " milliseconds\n" << endl;
    cout << endl;

    // Тестирование времени поиска
    cout << "search time:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << searchTime(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << searchTime(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << searchTime(100000) << " milliseconds\n" << endl;
    cout << endl;

    // Тестирование времени добавления и удаления
    cout << "Add and remove times:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << addRemoveTime(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << addRemoveTime(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << addRemoveTime(100000) << " milliseconds\n" << endl;

    // Тестирование времени заполнения вектора
    cout << "Fill time for vector:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << fillTimeVector(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << fillTimeVector(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << fillTimeVector(100000) << " milliseconds\n" << endl;
    cout << endl;

    // Тестирование времени поиска вектора
    cout << "Search time for vector:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << searchTimeVector(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << searchTimeVector(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << searchTimeVector(100000) << " milliseconds\n" << endl;
    cout << endl;

    // Тестирование времени добавления и удаления вектора
    cout << "Add and remove times for vector:" << endl;
    cout << "------------------" << endl;
    cout << "1000 elements: " << addRemoveTimeVector(1000) << " milliseconds" << endl;
    cout << "10000 elements: " << addRemoveTimeVector(10000) << " milliseconds" << endl;
    cout << "100000 elements: " << addRemoveTimeVector(100000) << " milliseconds\n" << endl;

    Set set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);
    set1.print();
    cout << endl;

    Set set2;
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.insert(6);
    set2.print();
    cout << endl;

    Set unionSet = unionOfSets(set1, set2);
    cout << "Union of sets: ";
    unionSet.print();
    cout << endl;

    Set symmetricDifferenceSet = symmetricDifference(set1, set2);
    cout << "Symmetric difference of sets: ";
    symmetricDifferenceSet.print();
    cout << endl;

    return 0;
}