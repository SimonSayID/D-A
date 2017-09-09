# D-A
Data structure &amp; Algorithm （数据结构与算法）

stack（栈） (avl_tree version)

- init 初始化

- push 进栈

- top 顶部

- pop 出栈

queue（队列）

- init 初始化

- enqueue 进队

- dequeue 出队

- is_empty 是否为空

- destroy_queue 销毁队列

avl tree （AVL 树） (non-recursive 非递归)

- init 初始化

- insert 插入 (duplicate node won't insert)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- test 测试 (detail see avl_tree_test.c)

red black tree （红黑树） (non-recursive 非递归)

- init 初始化

- insert 插入 (duplicate node won't insert)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- test 测试 (detail see rb_tree_test.c)


AVL树的数据结构没有使用父节点，红黑树则使用了父节点，但是没有用哨兵（sentinel）
另外测试代码基本涵盖所有情况

sorting (排序)

- bubble sort 冒泡排序

- select sort 挑选排序

- insert sort 插入排序

- quick sort 快速排序

- merge sort 归并排序

- test 测试 (detail see sort_test.c)