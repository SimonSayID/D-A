# hash

- init

- insert

- delete

- search

- destroy 

- test (hash_test.c)

>碰撞使用分链解决，散列表的大小在初始化时确定。resize的实现取决于具体场景，\
>单线程上简单的新建更大的表一次性rehash移植或者根据后续插入逐步移植在通用情\
>况都显得不够快，故在这里不提供代码。\
>resize的实现逻辑和细节[en_wiki](https://en.wikipedia.org/wiki/Hash_table#Dynamic_resizing)