#include <iostream>
#include <chrono>
#include "CityClass.h"
#include "fstream"
using namespace std;
using namespace std::chrono;

// 测试
void insertTestData(CityDataBase *dataBase) {
    dataBase->insert("Beijing", 1, 1);
    dataBase->insert("Shanghai", 2, 2);
    dataBase->insert("Guangzhou", 3, 3);
    dataBase->insert("Shenzhen", 4, 4);
    dataBase->insert("Hangzhou", 5, 5);
    dataBase->insert("Nanjing", 6, 6);
    dataBase->insert("Chongqing", 7, 7);
    dataBase->insert("Wuhan", 8, 8);
    dataBase->insert("Chengdu", 9, 9);
    dataBase->insert("Tianjin", 10, 10);
    dataBase->insert("Xi'an", 11, 11);
    dataBase->insert("Shenyang", 12, 12);
    dataBase->insert("Dalian", 13, 13);
    dataBase->insert("Qingdao", 14, 14);
    dataBase->insert("Xiamen", 15, 15);
    dataBase->insert("Ningbo", 16, 16);
    dataBase->insert("Changsha", 17, 17);
    dataBase->insert("Zhengzhou", 18, 18);
    dataBase->insert("Changchun", 19, 19);
    dataBase->insert("Jinan", 20, 20);
    dataBase->insert("Taiyuan", 21, 21);
    dataBase->insert("Hefei", 22, 22);
    dataBase->insert("Fuzhou", 23, 23);
    dataBase->insert("Nanchang", 24, 24);
    dataBase->insert("Haikou", 25, 25);
    dataBase->insert("Kunming", 26, 26);
    dataBase->insert("Guiyang", 27, 27);
    dataBase->insert("Lanzhou", 28, 28);
    dataBase->insert("Xining", 29, 29);
    dataBase->insert("Yinchuan", 30, 30);
    dataBase->insert("Wulumuqi", 31, 31);
}

void searchTest(CityDataBase *dataBase, const string &name) {
    CityNode *p = dataBase->search(name);
    if (p != nullptr)
        cout << p->cityName << " " << p->x << " " << p->y << endl;
    else
        cout << "Not Found" << endl;
}

void searchTestData(CityDataBase *dataBase) {
    searchTest(dataBase, "Beijing");  // 1
    searchTest(dataBase, "Kunming");  // 1
    searchTest(dataBase, "Wulumuqi"); // 1
    searchTest(dataBase, "Shenyang"); // 1
    searchTest(dataBase, "Nofind");   // nofind
}

void deleteTest(CityDataBase *dataBase, const string &name) {
    cout << dataBase->remove(name) << endl;
}

void deleteTest(CityDataBase *dataBase, int x, int y) {
    cout << dataBase->remove(x, y) << endl;
}

void deleteTestData(CityDataBase *dataBase) {
    deleteTest(dataBase, "Beijing");  // 1
    deleteTest(dataBase, "Kunming");  // 1
    deleteTest(dataBase, "Wulumuqi"); // 1
    deleteTest(dataBase, "Shenyang"); // 1
    deleteTest(dataBase, "Nofind");   // 0
    deleteTest(dataBase, "Beijing");  // 0

    deleteTest(dataBase, 1, 1);   // 0
    deleteTest(dataBase, 10, 10); // 1
}

// 功能测试
void testFunction() {
    // 测试数据 x,y 应该随机
    auto *dataBase = new CityDataBase();
    insertTestData(dataBase);

    // 测试插入
    cout << dataBase->insert("Beijing", 1, 1) << endl;        // 0
    cout << dataBase->insert("Kunming", 1, 1) << endl;        // 0
    cout << dataBase->insert("TestInsert", 100, 100) << endl; // 1

    // 测试检索
    searchTestData(dataBase);

    // 测试删除 另外准备database
    auto *dataBase2 = new CityDataBase();
    insertTestData(dataBase2);
    deleteTestData(dataBase2);
    dataBase2->print(0, 0, 20, dataBase2->getRoot());
    delete dataBase2;

    // 测试打印
    dataBase->print(0, 0, 20, dataBase->getRoot());
}

// 性能测试
string rand_str(const int len) {
    string str;
    char c;
    int idx;
    for (idx = 0; idx < len; idx++) {
        c = 'a' + rand() % 26; // NOLINT(*-narrowing-conversions)
        str.push_back(c);
    }
    return str;
}

//n 表示数据规模
void testPerformance(int n,vector<vector<string>>& data){
    auto *dataBase = new CityDataBase();
    // 测试插入
    string str[n];
    for (int i = 0; i < n; i++) {
        str[i] = rand_str(10);
    }
    time_point<high_resolution_clock> begin = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        dataBase->insert(str[i], i, i);
    }
    time_point<high_resolution_clock> end = high_resolution_clock::now();
    //cout << "insert " << duration_cast<microseconds>(end - begin).count() << "ms" << endl;
    data[1].push_back(to_string(duration_cast<microseconds>(end - begin).count()));

    // 测试检索
    begin = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        dataBase->search(str[i]);
    }
    end = high_resolution_clock::now();
    //cout << "search name " << duration_cast<microseconds>(end - begin).count() << "ms" << endl;
    data[2].push_back(to_string(duration_cast<microseconds>(end - begin).count()));
    // 测试检索x，y
    begin = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        dataBase->search(i, i, dataBase->getRoot());
    }
    end = high_resolution_clock::now();
    //cout << "search x,y " << duration_cast<microseconds>(end - begin).count() << "ms" << endl;
    data[3].push_back(to_string(duration_cast<microseconds>(end - begin).count()));
    // 测试删除
    begin = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        dataBase->remove(str[i]);
    }
    end = high_resolution_clock::now();
    //cout << "remove name " << duration_cast<microseconds>(end - begin).count() << "ms" << endl;
    data[4].push_back(to_string(duration_cast<microseconds>(end - begin).count()));
    delete dataBase;

    // 测试删除 x，y
    auto *dataBase2 = new CityDataBase();
    for (int i = 0; i < n; i++) {
        dataBase2->insert(str[i], i, i);
    }
    begin = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        dataBase2->remove(i, i);
    }
    end = high_resolution_clock::now();
    //cout << "remove x,y " << duration_cast<microseconds>(end - begin).count() << "ms" << endl;
    data[5].push_back(to_string(duration_cast<microseconds>(end - begin).count()));
    delete dataBase2;
}
void saveToCsv(const vector<vector<string>>& data, const string& name) {
    ofstream mOutFile;
    mOutFile.open(name, ios::out);
    for(const auto &i : data) {
        for(const auto &j : i) {
            mOutFile << j ;
            if(j != i.back())
                mOutFile << ',';
        }
        mOutFile << endl;
    }
    mOutFile.close();
}
int main() {
    vector<vector<string>> data;
    data.push_back({"n"});
    data.push_back({"insert"});
    data.push_back({"search name"});
    data.push_back({"search xy"});
    data.push_back({"remove name"});
    data.push_back({"remove xy"});
    for (int i = 100; i <= 10000; i += 10) {
        cout << "n = " << i << endl;
        data[0].push_back(to_string(i));
        testPerformance(i,data);
    }
    saveToCsv(data, "data.csv");
    return 0;
}

// 时间复杂度分析
// 插入：O(logn)
// 检索：O(logn)
// 检索x，y：O(n)
// 删除：O(logn)
// 删除x，y：O(n)
// 打印：O(n)

