# D-A
Data structure and Algorithm 

- list [#](list/LIST.MD)

- stack [#](stack/STACK.MD)

- queue [#](queue/QUEUE.MD)

- binomial heap [#](heap/binomial/BINOMIAL.MD)

- avl tree (non-recursive) [#](tree/avl/AVL.MD)

- red black tree (non-recursive) [#](tree/rb/RB.MD)

- splay tree (non-recursive) [#](tree/splay/SPLAY.MD)

- hash [#](hash/HASH.MD)

- graph [#](graph/GRAPH.MD)

- sorting [#](sort/SORT.MD)

>操作函数形式为fun(DataStructure h, ElementType data)，
>而不是fun(DataStructure h, DataStructureNode node)。
>这两者在实现和内存管理上是有很大的区别。
>因为优先队列的实现并没有使用函数指针来兼容泛型，所以这里的图形
>算法将放在C++里面实现。[项目地址](https://github.com/SimonSayID/D_A_graph_algo)