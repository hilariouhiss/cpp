# C++

class 和 struct 具有统一的规则集，class 能干的，struct 也能干。但 struct 一般用于封装数据结构，成为聚合类型，class 用于封装更为复杂的逻辑和行为。

## 聚合与非聚合类型

这是 C++中与类/结构体初始化相关的核心概念，其区别直接影响对象的初始化方式。

### 聚合类型的定义与特性

- 定义 ​​：满足以下所有条件的类或结构体（含数组）：
  - 无用户声明的构造函数（包括 explicit 或继承构造函数）
  - 所有非静态成员均为 public
  - 无虚函数或虚基类
  - 无非公有基类（C++17 起允许公有继承基类）
  - 无成员使用大括号或等号初始化（C++11 限制，C++14 起取消）
- 初始化：
  - 支持大括号列表初始化，按成员声明顺序赋值：

    ```c++
    struct Point { int x; int y; };
    Point p = {1, 2};
    ```

  - C++ 20起，支持指派初始化，指定成员名赋值：

    ```c++
    Point p {.x = 1, .y = 2};
    ```

### 非聚合类型的定义与特性

违反任一条聚合类型定义即为非聚合类型

- 初始化：
  - 必须通过构造函数进行初始化
  - 具有匹配的构造函数才能使用大括号列表初始化

### Constexpr if 语句（C++17）

如果constexpr条件的计算结果为true，则整个if-else将替换为true语句。如果constexpr条件的计算结果为false，则整个if-else将替换为false语句（如果存在else）或直接删除（如果没有else）。

## C++容器

### 顺序容器

#### `vector`（动态数组）

- 特点：连续内存、随机访问高效（`O(1)`），尾部插入/删除高效，中间插入/删除成本高

- 常用成员函数：

  - `push_back()`/`pop_back()`：尾部添加/删除元素。

  - `operator[]`/`at(size_t pos)`：随机访问元素（`at()` 会检查越界）。

  - `reserve(size_t n)`：预分配内存，避免频繁扩容。

  - `capacity()`：返回当前已分配的内存容量。

  - `resize(size_t n)`：调整元素数量，多删少补（默认值填充）。

  - `insert(iterator pos, value)`：指定位置插入（效率低，慎用）。

  - `erase(iterator pos)`：删除指定位置元素（同样效率低）。

- 示例代码：

  ```C++
  #include <vector>
  #include <iostream>
  
  int main() {
      std::vector<int> vec = {1, 2, 3};
  
      // 添加元素
      vec.push_back(4);           // {1,2,3,4}
      vec.insert(vec.begin(), 0);  // {0,1,2,3,4}
  
      // 访问元素
      std::cout << "Element at 2: " << vec[2] << "\n";     // 2
      std::cout << "Front: " << vec.front() << "\n";        // 0
      std::cout << "Back: " << vec.back() << "\n";          // 4
  
      // 删除元素
      vec.pop_back();        // 删除末尾 {0,1,2,3}
      vec.erase(vec.begin()); // 删除头部 {1,2,3}
  
      // 容量操作
      vec.reserve(100);      // 预分配空间
      std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity();
  
      // 遍历
      for(auto& num : vec) {
          std::cout << num << " ";  // 1 2 3
      }
  }
  ```

#### `list`（双向链表）

- 特点：非连续内存，任意位置插入/删除高效（O(1)），不支持随机访问（需遍历）。

- 常用成员函数：
  - `push_front()`/`pop_front()`：头部插入/删除（`vector` 不支持）。
  - `remove(const T& value)`：删除所有匹配的元素。
  - `sort()`：成员函数排序（优于全局 `std::sort`，因链表需特殊处理）。
  - `splice(iterator pos, list& other)`：将其他链表元素移动到当前链表。
  - `unique()`：删除相邻重复元素（需先排序）。

- 示例代码：

  ```C++
  #include <list>
  #include <algorithm>
  
  int main() {
      std::list<int> lst = {5, 2, 9};
      
      // 双向插入
      lst.push_front(1);    // {1,5,2,9}
      lst.push_back(4);      // {1,5,2,9,4}
      
      // 任意位置插入
      auto it = std::find(lst.begin(), lst.end(), 5);
      if(it != lst.end()) lst.insert(it, 3);  // {1,3,5,2,9,4}
  
      // 删除操作
      lst.remove(2);        // 删除值为2的元素 {1,3,5,9,4}
      lst.unique();          // 删除连续重复值（需先排序）
      
      // 排序
      lst.sort();            // {1,3,4,5,9}
      
      // 链表合并
      std::list<int> lst2 = {2, 6};
      lst.merge(lst2);       // lst: {1,2,3,4,5,6,9}, lst2 为空
  }
  ```

####  `deque`（双端队列）

- 特点：分段连续内存，支持高效头尾插入/删除（O(1)），随机访问效率接近 `vector`。

- 常用成员函数：
  - `push_front()`/`push_back()`：头尾插入元素。
  - `pop_front()`/`pop_back()`：头尾删除元素。
  - `operator[]`：随机访问（无 `capacity()` 和 `reserve()`）。

- 示例代码：

  ```C++
  #include <deque>
  
  int main() {
      std::deque<int> dq;
      
      // 双端操作
      dq.push_back(10);     // {10}
      dq.push_front(5);     // {5,10}
      dq.push_back(15);     // {5,10,15}
      
      // 随机访问
      int mid = dq[1];      // 10
      
      // 删除
      dq.pop_front();       // {10,15}
      dq.pop_back();        // {10}
      
      // 双端插入高效
      for(int i = 0; i < 1000; ++i) {
          dq.push_back(i);
          dq.push_front(i);
      }
  }
  ```

### 关联容器（有序）

#### `map`/`set`（红黑树实现）

- 特点：自动按键排序，查找/插入/删除时间复杂度  `O(log n)`。

- 常用成员函数：
  - `insert({key, value})`/`emplace()`：插入元素（避免拷贝）。
  - `erase(key)`：删除指定键的元素。
  - `find(key)`：返回迭代器（若未找到则返回 `end()`）。
  - `count(key)`：返回键是否存在（0 或 1）。
  - `lower_bound(key)`/`upper_bound(key)`：返回键的边界迭代器。

- 示例代码：

  ```C++
  #include <map>
  #include <set>
  #include <string>
  
  int main() {
      // map 示例 (键值对)
      std::map<std::string, int> scores;
      scores["Alice"] = 90;
      scores.emplace("Bob", 85);  // 避免临时对象
      
      // 查找
      auto it = scores.find("Bob");
      if(it != scores.end()) {
          std::cout << "Bob's score: " << it->second << "\n";
      }
      
      // 有序迭代
      for(const auto& [name, score] : scores) {
          // 自动按键升序排列
      }
      
      // set 示例 (唯一键)
      std::set<int> uniqueNums = {3, 1, 4, 1, 5};
      // {1,3,4,5} 自动排序去重
      
      // 范围查询
      auto start = uniqueNums.lower_bound(3); // 首个>=3的元素
      auto end = uniqueNums.upper_bound(4);   // 首个>4的元素
  }
  ```

#### `unordered_map`/`unordered_set`（哈希表实现）

- 特点：无序存储，平均查找/插入/删除时间复杂度 `O(1)`，最坏情况 `O(n)`。

- 常用成员函数：
  - `insert()`/`emplace()`：插入元素。
  - `erase(key)`：删除元素。
  - `find(key)`：查找元素。
  - `bucket_count()`：返回桶的数量（哈希表大小）。
  - `load_factor()`：返回负载因子（元素数/桶数）。

- 示例代码：

  ```C++
  #include <unordered_map>
  #include <unordered_set>
  
  int main() {
      // unordered_map 示例
      std::unordered_map<std::string, int> phonebook;
      phonebook.reserve(100);  // 预分配桶
      
      phonebook["Alice"] = 123456;
      phonebook["Bob"] = 987654;
      
      // O(1)平均查找
      if(phonebook.find("Bob") != phonebook.end()) {
          std::cout << "Found Bob\n";
      }
      
      // unordered_set 示例
      std::unordered_set<int> ids = {101, 102, 103};
      ids.insert(102);  // 重复值不会插入
      
      // 负载因子管理
      if(ids.load_factor() > 0.7) {
          ids.rehash(ids.bucket_count() * 2);
      }
  }
  ```

### 容器适配器

####  `queue`（队列，默认基于 `deque`）

- 特点：FIFO（先进先出），不支持遍历。

- 常用成员函数：
  - `push()`：队尾插入元素。
  - `pop()`：队头删除元素（不返回值）。
  - `front()`/`back()`：访问队头/队尾元素。

- 示例代码：

  ```C++
  #include <queue>
  
  int main() {
      std::queue<int> q;
      
      q.push(10);  // 队尾入队
      q.push(20);
      q.push(30);
      
      while(!q.empty()) {
          std::cout << q.front() << " ";  // 访问队首：10 20 30
          q.pop();                        // 队头出队
      }
  }
  ```

#### `stack`（栈，默认基于 `deque`）

- 特点：LIFO（后进先出），不支持遍历。

- 常用成员函数：
  - `push()`：栈顶插入元素。
  - `pop()`：删除栈顶元素（不返回值）。
  - `top()`：访问栈顶元素。

- 示例代码：

  ```C++
  #include <stack>
  
  int main() {
      std::stack<int> st;
      
      st.push(10);  // 入栈
      st.push(20);
      st.push(30);
      
      while(!st.empty()) {
          std::cout << st.top() << " ";  // 访问栈顶：30 20 10
          st.pop();                       // 出栈
      }
  }
  ```

#### 通用成员函数（所有容器支持）

- `size()`：返回元素数量。
- `empty()`：判断是否为空。
- `clear()`：清空容器。
- `begin()`/`end()`：返回正向迭代器。
- `rbegin()`/`rend()`：返回反向迭代器。

### 容器选择建议

|         **场景**         |          **推荐容器**           |           **原因**            |
| :----------------------: | :-----------------------------: | :---------------------------: |
|       随机访问频繁       |            `vector`             |      连续内存，访问 O(1)      |
|  频繁任意位置插入/删除   |             `list`              |   链表结构，插入/删除 O(1)    |
|       高频头尾操作       |             `deque`             |    双端队列，头尾操作 O(1)    |
|   需有序存储与范围查询   |           `map`/`set`           | 红黑树保证有序，查找 O(log n) |
| 需快速查找（不要求有序） | `unordered_map`/`unordered_set` |  哈希表实现，平均 O(1) 查找   |
|        FIFO 需求         |             `queue`             |          队列适配器           |
|        LIFO 需求         |             `stack`             |           栈适配器            |

## switch 

case标签之前和之后声明或定义（但不能初始化）switch语句内的变量：

```
switch (1)
{
    int a; // okay: case标签之前可以声明变量
    int b{ 5 }; // 不合法: case 标签之前，不可以初始化变量

    case 1:
        int y; // okay 但不推荐
        y = 4; // okay: 赋值语句可以
        break;

    case 2:
        int z{ 4 }; // 不合法: 后面还有case标签，不允许初始化变量
        y = 5; // okay: y 在上面声明，所以这里可以赋值
        break;

    case 3:
        break;
}
```

switch内的所有语句都被视为同一作用域的一部分。因此，在 case 1 内声明或定义的变量可以在以后使用。
	因为变量的初始化，需要在运行时执行（因为需要将初始值设置给变量）。如果后续还有case标签，则不允许初始化变量（因为初始化可能被跳过，这将使变量未初始化）。在第一个case标签之前不允许初始化，因为这些语句永远不会执行，switch语句无法指定到它们。
