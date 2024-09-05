# include<iostream>
# include<vector>
# include<deque>
# include<list>
# include<set>
# include<map>
# include<unordered_set>
# include<unordered_map>
# include<stack>
# include<queue>
# include<algorithm>

using namespace std;

// 迭代器
// vector deque 随机访问迭代器
// list set map 双向迭代器 不支持迭代器的+-i操作（但支持自增自减操作），不支持随机访问（不支持[]操作），不支持迭代器的大小比较操作
// stack queue priority_queue 不支持迭代器
void iterator_example(){
    vector<int> v = {1, 2, 3, 4, 5};
    // 迭代器是一个指向容器元素的指针
    vector<int>::iterator it = v.begin(); // 指向第一个元素
    cout << *it << endl; // 输出第一个元素
    it++; // 移动到下一个元素
    cout << *it << endl; // 输出第二个元素
    it = v.end(); // 指向最后一个元素的下一个位置
    it--; // 移动到最后一个元素
    cout << *it << endl; // 输出最后一个元素

    // 通过随机迭代器遍历容器的三种方法
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << *it << " ";
    }
    for (vector<int>::iterator it = v.begin(); it < v.end(); it++){ // 对于list之类的双向迭代器，不支持it < v.end()这样的大小比较
        cout << *it << " ";
    }   
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;

    // find
    vector<int>::iterator it2 = find(v.begin() + 1, v.end(), 3); // 查找元素3
}


// 顺序容器：vector, deque, list
/* 
顺序容器: 小结
vector: 强调通过随机访问进行快速访问
• 插入/删除：非尾处O(n)或结尾处O(1) 
list: 强调元素的快速插入和删除, 不支持随机访问迭
代器
• 插入/删除为O(1)
deque: 类似vector容器, 但强调在两端处的快速插入
和删除
• 均为O(1)
 */
// ==================== vector ====================
void print_vector(vector<int>& v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
// vector 是一个动态数组，可以在尾部快速插入或删除元素
void vector_example(){
    vector<int> v;
    v = {1, 2, 3, 4, 5};
    v.push_back(6); // 在末尾添加元素
    v.pop_back(); // 删除末尾元素
    v.at(2) = 4; // 修改第3个元素
    v.insert(v.begin() + 2, 7); // 在第3个元素前插入7
    // print v
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    v.erase(v.begin() + 3); // 删除第4个元素
    // v.clear(); // 清空
}

// ==================== deque ====================
// deque 是一个双端队列，可以在头尾快速插入或删除元素
void deque_example(){
    deque<int> d;
    d.push_back(1); // 在末尾添加元素
    d.push_front(2); // 在开头添加元素
    d.pop_back(); // 删除末尾元素
    d.pop_front(); // 删除开头元素
    d.insert(d.begin() + 2, 3); // 在第3个元素前插入3
    d.erase(d.begin() + 3); // 删除第4个元素
    // d.clear(); // 清空
}

// ==================== list ====================
// list 是一个双向链表，可以在任意位置快速插入或删除元素
void list_example(){
    list<int> l = {1, 2, 3, 4, 5};
    l.push_back(1); // 在末尾添加元素 l = {1, 2, 3, 4, 5, 1}
    l.push_front(2); // 在开头添加元素 l = {2, 1, 2, 3, 4, 5, 1}
    l.pop_back(); // 删除末尾元素 l = {2, 1, 2, 3, 4, 5}
    l.pop_front(); // 删除开头元素 l = {1, 2, 3, 4, 5}
    // 获取指向第三个元素的迭代器
    auto it = std::next(l.begin(), 3); // 指向第四个元素
    l.insert(it, 99); // 在第三个元素后插入99
    // 寻找迭代器指向的2的位置，在其后插入5
    auto it2 = find(l.begin(), l.end(), 2);
    l.insert(it2, 5);
    // print l
    for(int i:l){
        cout << i << " ";
    }
    // merge
    list<int> l2 = {6, 7, 8};
    l.merge(l2); // 合并两个有序链表 并清空被合并的那个
    // list容器的迭代器不支持完全随机访问, 所以不能用标准库中sort函数对它进行排序
    l.sort(); // 排序
    // unique 删除相邻重复元素
    l.unique();
    // remove 删除所有等于某个值的元素
    l.remove(5);
    // l.clear(); // 清空
}

// 关联容器：set, map, multiset, multimap
// ==================== set ====================
// set 是一个集合，元素是唯一的，可以快速查找元素
void set_example(){
    set<int> s= {3, 4, 5, 2};
    s.insert(1); // 插入元素
    s.erase(5); // 删除元素
    set<int>::iterator it = s.find(1); // 查找元素
    if (it != s.end()){
        cout << "Found" << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    for(int i:s){
        cout << i << " "; // 输出顺序是排序后的顺序 1,2,3,4
    }
    cout << endl;
}
// ==================== multiset ====================
// multiset 是一个集合，元素可以重复，可以快速查找元素
void multiset_example(){
    multiset<int> ms = {1, 3, 4, 5, 2, 3};
    ms.insert(1); // 插入元素
    ms.erase(3); // 删除元素，删掉所有的3

    multiset<int>::iterator it = ms.find(1); // 查找元素
    if (it != ms.end()){
        cout << "Found" << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    for(int i:ms){
        cout << i << " "; // 输出顺序是排序后的顺序 1,1,2,4,5
    }
    cout << endl;
}
// ==================== map ====================
// map 是一个键值对集合，键是唯一的，可以快速查找元素
void map_example(){
    map<string, int> m;
    m["Alice"] = 1; // 插入元素
    m["Bob"] = 2;
    m["Alice"] = 3; // 更新元素
    m.erase("Bob"); // 删除元素
    map<string, int>::iterator it = m.find("Alice"); // 查找元素
    if (it != m.end()){
        cout << "Found" << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    for(pair<string, int> p:m){
        cout << p.first << " " << p.second << endl;
    }
}
// ==================== multimap ====================
// multimap 是一个键值对集合，键可以重复，可以快速查找元素
void multimap_example(){
    multimap<string, int> mm;
    mm.insert({"Alice", 1}); // 插入元素
    mm.insert({"Bob", 2});
    mm.insert({"Alice", 3});
    mm.erase("Bob"); // 删除元素
    multimap<string, int>::iterator it = mm.find("Alice"); // 查找元素
    if (it != mm.end()){
        cout << "Found" << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    for(pair<string, int> p:mm){
        cout << p.first << " " << p.second << endl;
    }
    // 输出Alice对应的值
    pair<multimap<string, int>::iterator, multimap<string, int>::iterator> range = mm.equal_range("Alice");
    for(multimap<string, int>::iterator it = range.first; it != range.second; it++){
        cout << it->second << " ";
    }
}

// 容器适配器：stack, queue, priority_queue 
// ==================== stack ====================
// stack 是一个后进先出（LIFO）的容器
void stack_example(){
    stack<int> s;
    s.push(1); // 入栈
    s.push(2);
    s.pop(); // 出栈
    cout << s.top() << endl; // 访问栈顶元素
}
// ==================== queue ====================
// queue 是一个先进先出（FIFO）的容器
void queue_example(){
    queue<int> q;
    q.push(1); // 入队
    q.push(2);
    q.pop(); // 出队
    cout << q.front() << endl; // 访问队首元素
}
// ==================== priority_queue ====================
// priority_queue 是一个优先级队列，元素按照优先级排序（通常是大顶堆）
void priority_queue_example(){
    priority_queue<int> pq;
    pq.push(3); // 入队
    pq.push(1); // 入队
    pq.push(5);
    cout << pq.top() << endl; // 访问队首元素 5
    pq.pop(); // 出队
}

int main(){
    //vector_example();
    //deque_example();
    list_example();
    //set_example();
    //multiset_example();
    // multimap_example();
    //priority_queue_example();
    return 0;
}