//
// Created by 陈鹏宇 on 2023/10/18.
//

#ifndef DATASTRUCTEXPERIMENT_CITYCLASS_H
#define DATASTRUCTEXPERIMENT_CITYCLASS_H

#include "iostream"

using namespace std;

// 城市节点 包含城市名，城市坐标
struct CityNode {
    string cityName;
    int x;
    int y;
    CityNode *left;
    CityNode *right;
    CityNode *parent;

    CityNode(string name, int x, int y) {
        this->cityName = name;
        this->x = x;
        this->y = y;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    // 析构函数
    ~CityNode() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};

// 城市数据库，根据城市名组织城市节点
class CityDataBase {
private:
    CityNode *root;

    static CityNode *findMin(CityNode *Node);

    void remove(CityNode *Node);

public:
    CityDataBase();

    CityDataBase(CityNode *root);

    ~CityDataBase();

    // 数据库应该允许插入记录、按照名字或者坐标删除或检索记录
    bool insert(const string &name, int x, int y); // 失败返回false，成功返回true
    bool remove(const string &name);

    bool remove(int x, int y);

    CityNode *search(const string &name);

    CityNode *search(int x, int y, CityNode *Node);

    // 还应该支持打印出与指定点给定距离在一定范围内的所有记录。
    void print(int x, int y, int distance, CityNode *Node);

    CityNode *getRoot() { return root; };
};

#endif //DATASTRUCTEXPERIMENT_CITYCLASS_H
