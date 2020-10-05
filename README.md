# 数据结构

## 线段树

### "小清新线段树"

​																----------_(from 《小清新线段树》 jiry_2)_

可以说是个加了剪枝的线段树，均摊复杂度比较优秀但是比较难说清楚想清楚，个人理解是某些题目中区间修改操作会导致数据趋于相同的时候适合使用

#### 例题1:区间取模区间覆盖询问区间和

考虑发现取模过程当中数据要么不变，要么数据变得小于等于原本的二分之一，所以执行次数不会很多

维护区间max并不断进行单点修改解决

当 $区间max\le x$ 时不向下递归(显然的剪枝)

当区间max=min时直接处理

#### 例题2:花神游历各国

题意 0~1e9范围1e5个数的数列，区间取int(sqrt)，询问区间和

发现sqrt取整最多5次后就会变1(或者本来是0)

所以区间修改时就暴力下放，除非区间max<=1(显然的剪枝)

#### 例题3:Gorgeous Sequence(区间开根询问区间和)

题意 0~$2^{31}$范围1e6个数的数列，区间取max、区间与输入的t取min、区间求和

区间取max和区间求和与一般线段树相同

但是与t取min搞不了普通lazy标记，怎么办呢？

jiry_2的方法是对线段树每个节点维护三个值

* 最大值

* 严格次大值

* 最大值个数

当 $t\ge 最大值$ 时，显然不用管

当 $严格次大值< t<最大值$ 时，显然只会影响到所有的最大值，所以可以直接更新区间和与最大值，增添lazy标记

当 $t\le 次大值$ 时，暴力下放

某个地方题解说运行效率可以被证明是$O(m\log{n})$的，另一个说是$O(m\log^2{n})$，在随机数据条件下飞快。感受一下可以发现，其实暴力下放的情况是比较少的，如果不断满足条件进行暴力下放的操作，那么其实数据会很快趋于相同且变小，程序速度是有保证的。

#### 例题4 区间and区间or询问区间max

考虑区间and和or多搞几遍区间内就会有很多位一样了。维护区间内所有位置都相同的集合，如果and/or操作影响到的只是这个集合里面的位，那么就可以直接打标记走人。

## 哈希表

不多说，unordered_map走起

自定义hash函数:

```c++
struct my_hash {
  size_t operator()(int x) const { return x; }
};
unordered_map<int,int,my_hash> mp;
```

### pb_ds 哈希

```c++
#include <bits/extc++.h>
using namespace __gnu_pbds;
cc_hash_table <int,int> a;//拉链
gp_hash_table <int,int> b;//查探 (更快)
//当普通unordered_map用可以卡常
```

大概没大用

## 左偏树

废话不说 直接上板子

```c++
struct LeftistTree//注意initialize!!!!!!!!!merge之类的操作都必须先find根再操作
{
	struct Node
	{
		int l,r,v,fa;//Left Son,Right Son,Value,Father
	}T[maxn];
	int dist[maxn];
	void init(int n){rep(i,1,n) T[i].fa=i;}//////////important
	int find(int x){while (T[x].fa!=x) x=T[x].fa;return x;}///find ancestor
	int merge(int x,int y)//merge x and y and return the new root
	{
		if (!x) return y;
		if (!y) return x;
		if (T[x].v<T[y].v) swap(x,y);//默认是大根堆 
		int rrt;//new right root
		if (T[x].r) rrt=merge(T[x].r,y);else rrt=y;
		T[x].r=rrt;T[rrt].fa=x;
		if (dist[T[x].l]<dist[T[x].r]||!T[x].l) swap(T[x].l,T[x].r);
		if (!T[x].r) dist[x]=0;else dist[x]=dist[T[x].r]+1;
		return x;
	}
	int pop(int x)
	{
		T[x].fa=x;T[T[x].l].fa=T[x].l;T[T[x].r].fa=T[x].r;
		int nrt=merge(T[x].l,T[x].r);
		T[x].l=0;T[x].r=0;dist[x]=0;
		return nrt;
	}
}lt;
```

## pb_ds 配对堆

```c++
#include <bits/extc++.h>
//using namespace __gnu_pbds;//容易冲突 最好不加
__gnu_pbds::priority_queue<pairs,greater<pairs>,__gnu_pbds::pairing_heap_tag>h[5];
int main()
{
	h[1].join(h[2]);//把h[2]合并进h[1],并清空h[2]
	pairs p=h[1].top();
	h[1].pop();
	priority_queue <int> p;
	priority_queue <int>::point_iterator it=p.push(0);
	p.push(1);p.push(2);
	p.modify(it,3);//修改it迭代器所指数据的值，结束后p.top()==3
	p.erase(it);//删除it迭代器所指数据，结束后p.top()==2
	return 0;
}
```

## 块状链表

(好像是差不多的东西)

## 树上分块算法&莫队

From OIWiki

## ST表

## 区间树状数组

## 划分树

(这是啥)

## 替罪羊树

要研究什么它是干不了的 找替代（treap之类的)

## pb_ds tree

## 跳表

## 可持久化数据结构

### 线段树

### 块状数组

### 平衡树

### Trie

### 可并堆

(研究pb_ds可不可干)

## 各种树套树

## KD-Tree

## (珂朵莉树)

OI-Wiki上的...好像是个方便写的次暴力算法

## LCT

## ~~NTT/TopTree~~