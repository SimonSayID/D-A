# D-A
Data structure &amp; Algorithm （数据结构与算法）

>all the implement in here just for practice\
>这里所有的实现只是用于练习

## list（链表） 

- init 初始化

- insert 插入 (duplicate node won't merge)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- test 测试 (detail see list_test.c)

## stack（栈） (avl_tree version)

- init 初始化

- push 进栈

- top 顶部

- pop 出栈

## queue（队列）

- init 初始化

- enqueue 进队

- dequeue 出队

- is_empty 是否为空

- destroy_queue 销毁队列

- test (detail see queue_test.c)

## avl tree （AVL 树） (non-recursive 非递归)

- init 初始化

- insert 插入 (duplicate node won't insert)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- test 测试 (detail see avl_tree_test.c)

>AVL树的数据结构没有使用父节点，另外测试代码基本涵盖所有情况

## red black tree （红黑树） (non-recursive 非递归)

- init 初始化

- insert 插入 (duplicate node won't insert)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- test 测试 (detail see rb_tree_test.c)


>红黑树使用了父节点，但是没有用哨兵节点（sentinel），另外测试代码基本涵盖所有情况

## hash（散列表）

- init 初始化

- insert 插入 (duplicate node won't insert)

- delete 删除 (remain unchanged if the node want to delete does not exist)

- search 搜索 (return NULL if the node does not exist)

- destroy 销毁

- test 测试 (detail see hash_test.c)

>碰撞使用分链解决，散列表的大小在初始化时确定，目前没有实现resize

## sorting (排序)

- bubble sort 冒泡排序

- select sort 挑选排序

- insert sort 插入排序

- quick sort 快速排序

- merge sort 归并排序

- test 测试 (detail see sort_test.c)
