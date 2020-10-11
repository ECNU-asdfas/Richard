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

标准写法：

```c++
int n;
__gnu_pbds::tree<int,int,greater<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> T1;//map
//splay_tree_tag ov_tree_tag
__gnu_pbds::tree<LL,__gnu_pbds::null_type,less<LL>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> T2;//set old->null_mapped_type
int main()
{
	read(n);
	rep(i,1,n)
	{
		int op;LL x;
		read(op);read(x);
		LL ans=-inf;//LL存左移20是相当于开pair
		switch(op)
		{
			case 1:
				T2.insert((x<<20)+i);
			break;
			case 2:
				T2.erase(T2.lower_bound(x<<20));
			break;
			case 3:
				cout<<T2.order_of_key(x<<20)+1<<endl;//查询x的排名
			break;
			case 4:
				ans=*T2.find_by_order(x-1);//查询排名为x的是多少
			break;
			case 5:
				ans=*--T2.lower_bound(x<<20);//x的前驱
			break;
			case 6:
				ans=*T2.lower_bound((x+1)<<20);//x的后继
			break;
			//T2.join(T3) 在两棵树的值域不重合的情况下把T3合并入T2
			//T2.split(v,T3) 小于等于v的被留着，剩下的被丢到T3中
		}
		if (ans!=-inf) cout<<(ans>>20)<<endl;
	}
```

自定义维护的写法(由于修改只能在插入删除的时候操作，所以其实有很大限制)(也就是没法区间修改)

```c++
using namespace __gnu_pbds;
template<class Node_CItr,class Node_Itr,class Cmp_Fn,class _Alloc>
struct my_node_update
{
	typedef int metadata_type;
	int order_of_key(pairs x)
	{
		int ans=0;
		Node_CItr it=node_begin();
		while(it!=node_end())
		{
			Node_CItr l=it.get_l_child();//返回迭代器
			Node_CItr r=it.get_r_child();
			if (Cmp_Fn()(x,**it))//**it获取it的信息
				it=l;
			else
			{
				ans++;
				if (l!=node_end()) ans+=l.get_metadata();//返回维护的数据
				it=r;
			}
		}
		return ans;
	}
	void operator()(Node_Itr it,Node_CItr end_it)
	{
		Node_Itr l=it.get_l_child();
		Node_Itr r=it.get_r_child();
		int left=0,right=0;
		if (l!=end_it) left=l.get_metadata();
		if (r!=end_it) right=r.get_metadata();
		const_cast<int&>(it.get_metadata())=left+right+1;
	}
	virtual Node_CItr node_begin() const=0;
	virtual Node_CItr node_end() const=0;
};
tree<pairs,null_type,less<pairs>,rb_tree_tag,my_node_update> rbt;
```

## 可持久化数据结构

### 线段树

经典的区间第k大(权值线段树)

```c++
const int maxn=100001,maxvalue=1e9+2;
int n,m,a[maxn],x,y,k;
struct node
{
	node *l,*r;
	int value;
	node():l(0),r(0),value(0){}
	node(node *ll,node *rr):l(ll),r(rr),value((ll?ll->value:0)+(rr?rr->value:0)){}
	node(int vv):l(0),r(0),value(vv){}
};
node *root[maxn];
char memorypool[maxn*sizeof(node)*60];//1 char=1 byte
char *memorypoolptr=memorypool;
inline void* myalloc(size_t size)
{
	return (memorypoolptr+=size)-size;
}
inline int down(double x) 
{
	if(x >= 0) return x;
	x -= 0.999999;
	return x;
}
#define newnode new (myalloc(sizeof(node))) node
node* insert(node *x,int k,int L=-maxvalue,int R=maxvalue)
{
	if (L==R) return newnode(x?x->value+1:1);
	int mid=down((L+R)/2.0);
	if (k<=mid) return newnode(insert(x?x->l:0,k,L,mid),x?x->r:0);
	else return newnode(x?x->l:0,insert(x?x->r:0,k,mid+1,R));
}
int kth(node *x,int k,int L=-maxvalue,int R=maxvalue)
{
	if (L==R) return L;
	int mid=down((L+R)/2.0);
	if (k<=(x->l?x->l->value:0)) return kth(x->l,k,L,mid);
	else return kth(x->r,k-(x->l?x->l->value:0),mid+1,R);
}
int kth(node *x,node *y,int k,int L=-maxvalue,int R=maxvalue)
{
	if (L==R) return L;
	if (!x) return kth(y,k,L,R);
	int mid=down((L+R)/2.0),temp=(y->l?y->l->value:0)-(x->l?x->l->value:0);
	if (k<=temp) return kth(x->l,y->l,k,L,mid);
	else return kth(x->r,y->r,k-temp,mid+1,R);
}
int main()
{
	scanf("%d%d",&n,&m);
	root[0]=newnode();
	rep(i,1,n) 
	{
		scanf("%d",&a[i]);
		root[i]=insert(root[i-1],a[i]);
	}
	rep(i,1,m)
	{
		scanf("%d%d%d",&x,&y,&k);
		printf("%d\n",kth(root[x-1],root[y],k));
	}
	return 0;
}
```

可持久化数组

```c++
#define newnode new PA::node
namespace PA
{
	struct node
	{
		node *l,*r;
		int value;
		node():l(0),r(0),value(0){}
		node(node *ll,node *rr):l(ll),r(rr),value((ll?ll->value:0)+(rr?rr->value:0)){}
		node(int vv):l(0),r(0),value(vv){}
		node(node *y):l(y->l),r(y->r),value(y->value){}
	};
	node *build(int *a,int L=1,int R=n)
	{
		if (L==R) return newnode(a[L]);
		int mid=(L+R)/2;
		return newnode(build(a,L,mid),build(a,mid+1,R));
	}
	node *replace(node *x,const int &pos,const int &val,int L=1,int R=n)
	{
		if (L==R) {return newnode(val);}
		int mid=(L+R)/2;
		if (pos<=mid) return newnode(replace(x?x->l:0,pos,val,L,mid),x?x->r:0);
		else return newnode(x?x->l:0,replace(x?x->r:0,pos,val,mid+1,R));
	}
	int query(node *x,const int &pos,int L=1,int R=n)
	{
		if (L==R) return x->value;
		int mid=(L+R)/2;
		if (pos<=mid) return query(x->l,pos,L,mid);
		else return query(x->r,pos,mid+1,R);
	}
};
PA::node *root[maxn];
int main()
{
	read(n,m);
	root[0]=newnode();
	rep(i,1,n) read(a[i]);
	root[0]=PA::build(a);
	rep(i,1,m)
	{
		int op,pos,vir,val;
		read(vir,op,pos);
		root[i]=newnode(root[vir]);
		if (op==1)
		{
			read(val);
			root[i]=PA::replace(root[i],pos,val);
		}
		else
		{
			printf("%d\n",PA::query(root[i],pos));
		}
	}
	return 0;
}
```

[POI2014]KUR-Couriers

题意:给一个数列，每次询问一个区间内有没有一个数出现次数超过一半

```c++
int query(node *x,node *y,const int &k,int L=0,int R=maxvalue)
{
	if (L==R) return L;
	if (!x) return query(y,k,L,R);
	int mid=(L+R)/2,suml=(y->l?y->l->value:0)-(x->l?x->l->value:0),sumr=(y->r?y->r->value:0)-(x->r?x->r->value:0);
	if (k<suml) return query(x->l,y->l,k,L,mid);//若左子树所有元素出现次数总和>(y-x+1)/2
	if (k<sumr) return query(x->r,y->r,k,mid+1,R);
	return 0;
}
query(root[x-1],root[y],(y-x+1)/2)
其余部分和k大值几乎一样
```



### Rope

```c++
#include <ext/rope>
int n,now,len;
__gnu_cxx::rope <char> a,b,c;//b is reversed
char s[2000000],rs[2000000];//1234567 654321
int main()
{
	scanf("%d",&n);
	int x;
	while (n--)
	{
		scanf("%s",s);
		switch(s[0])
		{
			case 'M':scanf("%d",&now);break;//move
			case 'P':now--;break;//previous
			case 'N':now++;break;//next
			case 'G':{putchar(a[now]);if (a[now]!='\n') putchar('\n');}break;//get
			case 'I'://insert
			{
				scanf("%d",&x);len=a.length();getchar();
				rep(i,0,x-1)
				{
					s[i]=getchar();
					rs[x-i-1]=s[i];
				}
				rs[x]=s[x]='\0';
				a.insert(now,s);
				b.insert(len-now,rs);
				break;
			}
			case 'D'://delete
			{
				scanf("%d",&x);len=a.length();
				a.erase(now,x);
				b.erase(len-now-x,x);
				break;
			}
			case 'R'://reverse
			{
				scanf("%d",&x);len=a.length();
				c=a.substr(now,x);//从now开始提取x个
				a=a.substr(0,now)+b.substr(len-now-x,x)+a.substr(now+x,len-now-x);
				b=b.substr(0,len-now-x)+c+b.substr(len-now,now);
				break;
			}
			//a.push_back()=a.append()
			//a.push_front()
            //a.insert(pos,a+1,n) a数组第一位开始的n位插入到pos去
			//a.copy(pos,len,s)把a中pos开始长为len的串复制到s中(s可以是数组)
			//a.replace(pos,len,x)把pos开始的len个用一个x替换
			//a.replace(pos,len1,s,len2) 删除a从pos开始的len1位并在那里插入s的前len2位
            /*
            	rope<type>* R[1000];
				R[i] = new rope<type>(*R[v]);
				存下根即可可持久化（调用函数时都需要R[1]->append(xxx)）
				可以直接对R[i]修改 效果相当于对第i个版本的rope进行修改
			*/
		}
	}
	return 0;
}
```

### 平衡树

### Trie

### 可并堆

## 划分树

(这是啥)

## 各种树套树

## KD-Tree

## (珂朵莉树)

OI-Wiki上的...好像是个方便写的次暴力算法

## LCT

## ~~NTT/TopTree~~

## pb_ds通用头

```c++
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
```

# 离线算法

## 带修改莫队

## 整体二分

## cdq分治