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

### pb_ds 哈希//卡常

```c++
#include <bits/extc++.h>
using namespace __gnu_pbds;
cc_hash_table <int,int> a;//拉链
gp_hash_table <int,int> b;//查探 (更快)
//当普通unordered_map用可以卡常
```

## 左偏树

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

就是外层链表内层数组，走$O(\sqrt{n})$次一定能查到，同时可以每个块打标记，这个看起来挺好写，用到可能性也比较小，功能基本被几种平衡树覆盖，所以不贴板子了

## ST表

```c++
#define log2(x) (31-__builtin_clz(x))
const int maxn=111111,logn=log2(maxn);
int n,m,st[maxn][logn+1];
int main()
{
	read(n,m);
	rep(i,1,n) read(st[i][0]);
	rep(i,1,logn)
			for (int j=1;j+(1<<i)-1<=n;j++)
				st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	while (m--)
	{
		int l,r;
		read(l,r);
		int s=log2(r-l+1);
		printf("%d\n",max(st[l][s],st[r-(1<<s)+1][s]));
	}
	return 0;
}
```

## 区间树状数组&二维区间树状数组

区间树状数组(初始值的前缀和需要预处理存在sum中)

```c++
#define lowbit(x) (x&(-x))
struct interval_BIT
{
	struct BIT
	{
		LL c[maxn];
		void cg(int x,LL v){while (x<=n) {c[x]+=v;x+=lowbit(x);}}
		LL qr(LL x){LL res=0;while (x){res+=c[x];x-=lowbit(x);}return res;}
	}b,c;
	LL sum[maxn];
	void change(int l,int r,LL v)
    {
        b.cg(l,v);b.cg(r+1,-v);
        c.cg(l,v*l);c.cg(r+1,-v*(r+1));
    }
	LL query(int l,int r)
	{
		LL suml=sum[l-1]+(LL)l*b.qr(l-1)-c.qr(l-1);
		LL sumr=sum[r]+(LL)(r+1)*b.qr(r)-c.qr(r);
		return sumr-suml;
	}
}ibit;
```

```c++
#define lowbit(x) (x&(-x))
struct interval_d2BIT
{
	struct d2BIT
	{
		LL t[maxn][maxn];
		void cg(int a,int b,LL v)
		{
			for (int i=a;i<=n;i+=lowbit(i))
				for (int j=b;j<=m;j+=lowbit(j))
					t[i][j]+=v;
		}
		LL qr(int a,int b)
		{
			LL res=0;
			for (int i=a;i;i-=lowbit(i))
				for (int j=b;j;j-=lowbit(j))
					res+=t[i][j];
			return res;
		}
	}t[5];
	void cg(int a,int b,LL v)
	{
		t[1].cg(a,b,v);t[2].cg(a,b,v*a);
		t[3].cg(a,b,v*b);t[4].cg(a,b,v*a*b);
	}
	void change(int a,int b,int c,int d,LL v)
	{
		cg(a,b,v);cg(c+1,d+1,v);
		cg(a,d+1,-v);cg(c+1,b,-v);
	}
	LL qr(int a,int b)
	{
		return t[1].qr(a,b)*(a+1)*(b+1)-t[2].qr(a,b)*(b+1)-t[3].qr(a,b)*(a+1)+t[4].qr(a,b);
	}
	LL query(int a,int b,int c,int d){return qr(c,d)+qr(a-1,b-1)-qr(c,b-1)-qr(a-1,d);}
}i2dbit;
```

## 替罪羊树

```c++
const double alpha=0.75;
struct node
{
	node *ch[2];
	int key,size,cover,exist;//cover:actual size+empty size
	void pushup()
	{
		size=ch[0]->size+ch[1]->size+exist;
		cover=ch[0]->cover+ch[1]->cover+1;
	}
	bool isbad()
	{
		return ((ch[0]->cover>cover*alpha)||(ch[1]->cover>cover*alpha));
	}
};
struct sgt
{
	node mem[maxn],*tail,*root,*null,*bc[maxn];
	int top;
	node *newnode(int key)
	{
		node *p=top?bc[top--]:tail++;
		p->ch[0]=p->ch[1]=null;
		p->size=p->cover=p->exist=1;
		p->key=key;
		return p;
	}
	void travel(node *p,vector<node *> &v)
	{
		if (p==null) return;
		travel(p->ch[0],v);
		if (p->exist) v.push_back(p);
		else bc[++top]=p;
		travel(p->ch[1],v);
	}
	node *divide(vector<node *> &v,int l,int r)
	{
		if (l>=r) return null;
		int mid=(l+r)>>1;
		node *p=v[mid];
		p->ch[0]=divide(v,l,mid);
		p->ch[1]=divide(v,mid+1,r);
		p->pushup();
		return p;
	}
	void rebuild(node *&p)
	{
		static vector<node*>v;
		v.clear();
		travel(p,v);
		p=divide(v,0,v.size());
	}
	node **insert(node *&p,int key)
	{
		if (p==null)
		{
			p=newnode(key);
			return&null;
		}
		p->size++,p->cover++;
		node **res=insert(p->ch[key>=p->key],key);
		if (p->isbad()) res=&p;
		return res;
	}
	void erase(node *p,int id)
	{
		p->size--;
		int offset=p->ch[0]->size+p->exist;
		if (p->exist&&id==offset)
		{
			p->exist=0;
			return;
		}
		if (id<=offset) erase(p->ch[0],id);
		else erase(p->ch[1],id-offset);
	}
	void init()
	{
		tail=mem;
		null=tail++;
		null->ch[0]=null->ch[1]=null;
		null->cover=null->size=null->key=0;
		root=null;
		top=0;
	}
	sgt()
	{
		init();
	}
	void insert(int key)
	{
		node **p=insert(root,key);
		if (*p!=null) rebuild(*p);
	}
	int rank(int key)
	{
		node *now=root;
		int ans=1;
		while (now!=null)
		{
			if (now->key>=key)now=now->ch[0];
			else
			{
				ans+=now->ch[0]->size+now->exist;
				now=now->ch[1];
			}
		}
		return ans;
	}
	int kth(int k)
	{
		node *now=root;
		while (now!=null)
		{
			if (now->exist&&now->ch[0]->size+1==k) return now->key;
			if (now->ch[0]->size>=k) now=now->ch[0];
			else k-=now->ch[0]->size+now->exist,now=now->ch[1];
		}
		return -1;
	}
	void erase(int k)
	{
		erase(root,rank(k));
		if (root->size<alpha*root->cover) rebuild(root);
	}
};
sgt t;
```

区间操作想了想是可以做的，只要拍扁时候把所有标记下放，再在建树的时候一个一个统计上来即可

对于随机数据应该是常数最小的平衡树了

## pb_ds tree

## 跳表

## 可持久化数据结构

### 线段树

### 块状数组

### 平衡树

### Trie

### 可并堆

## 划分树

(这是啥)各种树套树

## KD-Tree

## (珂朵莉树)

OI-Wiki上的...好像是个方便写的次暴力算法

## LCT

## ~~NTT/TopTree~~