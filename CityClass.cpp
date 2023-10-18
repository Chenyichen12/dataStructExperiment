//
// Created by 陈鹏宇 on 2023/10/18.
//

#include "CityClass.h"

// 构造函数
CityDataBase::CityDataBase() {
    root = nullptr;
}

// 构造函数
CityDataBase::CityDataBase(CityNode *root) {
    this->root = root;
}

// 析构函数
CityDataBase::~CityDataBase() {
    delete root;
}

// 查询记录 name
CityNode *CityDataBase::search(string const& name) {
    CityNode *p = root;
    while (p != nullptr) {
        if (p->cityName == name)
            return p;
        else if (p->cityName > name)
            p = p->left;
        else
            p = p->right;
    }
    return nullptr;
}

// 查询记录 x，y
CityNode *CityDataBase::search(int x, int y, CityNode *Node) { // NOLINT(*-no-recursion)
    CityNode *p = Node;
    // 检索所有节点
    if (Node->x == x && Node->y == y)
        return Node;
    if (p->left != nullptr) {
        CityNode *left = search(x, y, p->left);
        if (left != nullptr)
            return left;
    }
    if (p->right != nullptr) {
        CityNode *right = search(x, y, p->right);
        if (right != nullptr)
            return right;
    }
    return nullptr;
}

// 插入记录
bool CityDataBase::insert(string const& name, int x, int y) {
    CityNode *p = root;
    CityNode *pre = nullptr;
    while (p != nullptr) {
        if (p->cityName == name)
            return false;
        else if (p->cityName > name) {
            pre = p;
            p = p->left;
        } else {
            pre = p;
            p = p->right;
        }
    }
    auto *newNode = new CityNode(name, x, y);
    newNode->parent = pre;
    if (pre == nullptr)
        root = newNode;
    else if (pre->cityName > name)
        pre->left = newNode;
    else
        pre->right = newNode;
    return true;
}

// 删除记录
bool CityDataBase::remove(const string& name) {
    CityNode *p = search(name);
    if (p == nullptr)
        return false;
    remove(p);
    return true;
}

// 删除记录,x,y
bool CityDataBase::remove(int x, int y) {
    CityNode *p = search(x, y, root);
    if (p == nullptr)
        return false;
    remove(p);
    return true;
}

// 删除节点
void CityDataBase::remove(CityNode *Node) {
    CityNode *p = Node;
    CityNode *pre = p->parent;
    if (p == nullptr)
        return;
    if (p->left == nullptr && p->right == nullptr) {
        // 删除没有叶子节点的根节点
        if (pre == nullptr) {
            root = nullptr;
            delete p;
        }
            // 是父节点的左指针
        else if (pre->left == p) {
            pre->left = nullptr;
            delete p;
        }
            // 是父节点的右指针
        else {
            pre->right = nullptr;
            delete p;
        }
    }
        // 删除没有左子树的节点
    else if (p->left == nullptr) {
        if (pre == nullptr)
            root = p->right;
        else if (pre->left == p)
            pre->left = p->right;
        else
            pre->right = p->right;
        p->right->parent = pre;
        // 避免链式删除
        p->right = nullptr;
        delete p;
    } else if (p->right == nullptr) {
        if (pre == nullptr)
            root = p->left;
        else if (pre->left == p)
            pre->left = p->left;
        else
            pre->right = p->left;
        p->left->parent = pre;
        // 避免链式删除
        p->left = nullptr;
        delete p;
    }
        // 删除健全的节点
    else {
        CityNode *min = findMin(p->right);
        p->cityName = min->cityName;
        p->x = min->x;
        p->y = min->y;
        if (min->parent->left == min) {
            min->parent->left = min->right;
            if (min->right != nullptr) {
                min->right->parent = min->parent;
            }
        } else {
            min->parent->right = min->right;
            if (min->right != nullptr) {
                min->right->parent = min->parent;
            }
        }

        // 避免链式删除
        min->right = nullptr;
        min->left = nullptr;
        delete min;
    }
}

// 找到最小的节点
CityNode *CityDataBase::findMin(CityNode *Node) {
    CityNode *p = Node;
    while (p->left != nullptr)
        p = p->left;
    return p;
}

// 打印出与指定点给定距离在一定范围内的所有记录。枚举全部节点
void CityDataBase::print(int x, int y, int distance, CityNode *Node) { // NOLINT(*-no-recursion)
    CityNode *p = Node;
    if (p == nullptr)
        return;
    if ((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y) <= distance * distance)
        cout << p->cityName << " " << p->x << " " << p->y << endl;
    print(x, y, distance, p->left);
    print(x, y, distance, p->right);
}
