





##### 例1

有 k 种不同的优惠券,  问

(1) 直到第 n 次才取到全部k 种优惠券的概率

(2) 取了 n 次后, 包含了 j 种优惠券的概率

**解**

(1) 要求 $P(X=n)$, 考虑求出 $P(X>n) - P(X>n-1) = P(X = n)$. 

$P(X>n)$ 表示第 n 次有某个优惠券没有取到, 其为 $P(A_1\cup A_2 \cup A_3 \dots A_k)$, 其中$A_i $ 表示取完 n 次后, 还没有第 i 种优惠券.

然后用容斥公式算一下就行了.

(2) 要求的事件为, A = 前 n 张中都是这 j 种优惠券, B = 这 j 张优惠券至少出现了一次.

$P(AB) = P(A)P(B|A)$. 

$P(A) = (\frac{j}{k})^n$.  , $P(B|A) = 1- P(取了n次没有取到全部j种优惠券)$ , 后面的这个概率即为上一题算的$P(X>n)$

 



## 离散型随机变量

### 二项分布

#### 定义

 对参数为 (n ,p) 的二项分布, X表示成功的次数
$$
P(X = i) = \binom{n}{i}p^i(1-p)^{n-i}
$$


#### 性质

首先考虑期望和方差
$$
E[X^k] = \sum_{i=1}^{n}i^{k}\binom{n}{i}p^{i}(1-p)^{n-i}
$$
因为
$$
i\binom{n}{i} = i\frac{n!}{i!(n-i)!} = n\frac{(n-1)!}{(i-1)!(n-i)!} = n\binom{n-1}{i-1}
$$
所以
$$
E[X^k] = \sum_{i=1}^{n}i^{k-1}n\binom{n-1}{i-1}p^{i}(1-p)^{n-i}
\\= np\sum_{i=1}^{n}i^{k-1}\binom{n-1}{i-1}p^{i-1}(1-p)^{n-i}
\\ = np\sum_{j=0}^{n-1}(j+1)^{k-1}\binom{n-1}{j}p^{j}(1-p)^{n-1-j}
$$
可以看到
$$
\binom{n-1}{j}p^{j}(1-p)^{n-1-j}
$$
这一项就是一个参数为 (n-1,p) 的二项分布.

所以上面这个式子相当于
$$
E[X^{k}] = npE[(Y+1)^{k-1}], Y\sim(n-1,p)
$$
k = 1时, $E[X] = np$

k = 2时,$E[X^2] = npE[Y+1] = np((n-1)p+1) = np(np-p+1)$, 得到方差
$$
Var[x] = E[X^2] - (E[X])^2 = np(np-p+1) - (np)^2= np(1-p )
$$


##### 单调性

考虑二项分布的概率的变换情况
$$
\frac{P(X=k)}{P(X=k-1)} = \frac{\frac{n!}{k!(n-k)!}p^{k}(1-p)^{n-k}}{\frac{n!}{(k-1)!(n+1-k)!}p^{k-1}(1-p)^{n-k+1}} = \frac{(n+1-k)p}{k(1-p)}
\\ 令他大于1得到
\\ \frac{(n+1-k)p}{k(1-p)} \ge 1
\\ np+p-kp \ge k-kp
\\ k \le (n+1)p
$$
也就是说二项分布的最大值出现在
$$
\lfloor (n+1)p \rfloor 
$$
同样的用上面推导的 $k $ 和 $k-1$ 的关系可以递推算出来二项分布的分布函数



### 泊松分布

随机变量的取值为 $X = 0,1,2,\dots$, 只有一个参数$\lambda$ ,
$$
P(X = i) = e^{-\lambda}\frac{\lambda^i}{i!}
$$
可以看成进行很多很多次的二项分布, $\lambda = np$, n要足够大, p要足够小. 

正则性:
$$
\sum_{i=0}^{\infty}\frac{\lambda^i}{i!} = e^{\lambda}
$$


#### 性质

1. 均值

   可以猜测均值为$\lambda$, 证明如下
   $$
   \sum_{i=1}i\frac{\lambda^i}{i!} = \lambda\sum_{i=1} \frac{\lambda^{i-1}}{(i-1)!} = \lambda e^{\lambda}
   $$
   故均值为$\lambda = np$.

2. 方差
   $$
   E[X^2] = \sum_{i=1}i^2 \frac{\lambda^i}{i!} = \lambda + \sum_{i=2}{}\frac{\lambda^i}{(i-2)!} = \lambda + \lambda^2
   $$
    故方差为
   $$
   E[X^2] - (E[X])^2 = \lambda
   $$
   

#### 泊松范例

一般情况下, 泊松分布要求每个事件发生是互相独立的. 但实际上事件之间是弱相依的, 仍然可以使用泊松分布来算近似.



### 几何分布

独立重复实验中, 每次实验成功的概率为p, 用X表示直到第一次成功做了几次实验,那么
$$
P(X = n) = (1-p)^{n-1}p
$$

##### 期望

$$
\sum_{i=1}i(1-p)^{i-1} = \sum_{i=1}(i-1+1)(1-p)^{i-1} = \sum_{i=1}(i-1)(1-p)^{i-1} + \sum_{i=1}(1-p)^{i-1}
\\ = (1-p)\sum_{i=2}(i-1)(1-p)^{i-2} + \frac{1}{p}
\\ x =(1-p)x + \frac{1}{p}
\\ px = \frac{1}{p}
\\ x = \frac{1}{p^2}
$$

故几何分布的期望为
$$
\frac{1}{p}
$$
比如投骰子, 平均要仍几次才能出现1, 显然是$6$. 

##### 无记忆性

几何分布具有无记忆性, 即
$$
P(X > m+n| X > m) = P(X > n)
$$
已知失败m次的情况下, 接下来的n次实验仍然都未成功的概率和前面失败的次数无关

**证明**
$$
P(X > m + n| X > m) = \frac{P(X > m + n, X > m)}{P(X > m)} = \frac{P(X > m + n)}{P(X > m)}
$$
而
$$
P(X > m) = p\sum_{i=m + 1}^{\infty}(1-p)^{i-1} = p \frac{(1-p)^{m}}{p} = (1-p)^{m}
$$
所以得到
$$
\frac{P(X > m + n)}{P(X > m)} = \frac{(1-p)^{m + n}}{(1-p)^{m}} = (1-p)^{n} = P(X > n)
$$



### 负二项分布



### 负超几何分布

- 引出:

  总共有$N$ 个球, 里面有$k$ 个白球,$N - k$个黑球.  每次取一个球不返回. 问当取到 $r$ 个白球时, 取到黑球数的期望.

这个东西和负二项分布很像, 相当于不放回的负二项分布.用$X$ 代表黑球数.
$$
P(X = x) = \frac{\binom{N-k}{x}\binom{k}{r-1}}{\binom{N}{x+r-1}}\times \frac{k-r+1}{N-x-r+1}
\\ = \frac{\binom{x+r-1}{x}\binom{N-x-r}{k-r}}{\binom{N}{k}}
$$
后面这个是化简来的, 他也有组合意义. 

在$N$ 个未知中选$K$ 个放白球, 前$x + r - 1$ 个位置有$r-1$ 个白球, 第$x+r$ 个位置是白球, 后$N - x - r$个位置有$k-r$个白球.

接下来计算期望

- 期望:
  $$
  \sum_{x = 0}^{\infty}x \frac{\binom{x+r-1}{x}\binom{N-x-r}{k-r}}{\binom{N}{k}}
  \\ =  \frac{1}{\binom{N}{k}}\sum_{x=0}^{\infty}x\binom{x+r-1}{r-1}\binom{N-x-r}{k-r}
  \\ = \frac{1}{\binom{N}{k}}(\sum_{x=0}^{\infty}(x+r)\binom{x+r-1}{r-1}\binom{N-x-r}{k-r} - \sum_{x=0}^{\infty}r\binom{x+r-1}{r-1}\binom{N-x-r}{k-r})
  $$
  注意到
  $$
  \sum_{x=0}^{\infty}\frac{\binom{x+r-1}{x}\binom{N-x-r}{k-r}}{\binom{N}{k}} = 1
  $$
  于是原来后面那项就是$r$. 计算前面那项
  $$
  \sum_{x=0}^{\infty}(x+r)\binom{x+r-1}{r-1}\binom{N-x-r}{k-r}
  \\ = \sum_{x=0}^{\infty}r\binom{x+r}{r}\binom{N-x-r}{N-x-k}
  \\ = \sum_{x=0}^{\infty}r\binom{x+r}{x}\binom{-N+x+r+N-x-k-1}{N-x-k}(-1)^{N-x-k}
  \\ = \sum_{x=0}^{\infty}r\binom{-r-1}{x}\binom{r-k-1}{N-x-k}(-1)^{N-x-k}(-1)^{x}
  \\ = r(-1)^{N-k}\sum_{x=0}^{\infty}\binom{-r-1}{x}\binom{r-k-1}{N-x-k}
  \\ = r(-1)^{N-k}\binom{-k-2}{N-k}
  \\ = r\binom{N+1}{N-k}
  $$
  再把分母除进去得到
  $$
  E[X] = r\frac{\binom{N+1}{N-k}}{\binom{N}{k}} - r= r\frac{(N+1)!k!(N-k)!}{N!(N-k)!(k+1)!} - r 
  \\ = \frac{(N+1)r}{k+1} - r = \frac{(N+1)r - rk - r}{k+1} = \frac{(N-k)r}{k+1}
  $$
  可以把这个式子理解成, 每增加一个白球, 所取出的黑球的期望就增加$\frac{黑}{白+1}$. 

  





## 连续型随机变量



### 正态分布

$$
f(x) = \frac{1}{\sqrt{2\pi} \sigma}e^{-\frac{(x-\mu)^{2}}{2\sigma^2}}
$$





#### 性质

1. 若X是正态分布$N(\mu, \sigma^2 )$, 那么$aX + b$ 也是正态分布, 且参数为$(a\mu + b, a^{2}\sigma^2)$

   **证明**

   令$Y = aX + b$, 那么
   $$
   F_Y(x) = P(Y \le x) = P(aX+b \le x) = P(X \le \frac{x-b}{a}) = F_X(\frac{x-b}{a})
   $$
   求导的
   $$
   f_Y(x) = F_Y(x)' = F_X(\frac{x-b}{a})' = \frac{1}{a}f_X(\frac{x-b}{a}) 
   \\ = \frac{1}{a}\frac{1}{\sqrt{2\pi}\sigma}e^{-\frac{(x-b-a\mu)^{2}}{2\sigma^2a^{2}}}
   $$
   即满足$N(b+a\mu, a^2\sigma^2)$

   可以看出对$X$ 加一个常数只改变对称轴, 不改变$\sigma$. 也就是$\sigma$代表正态分布的形状.

   **应用**

   对于正态分布$X \sim N(\mu, \sigma^2) $, $\frac{X - \mu}{\sigma}$ 满足标准正态分布$N(0,1) $

2. 期望和方差

   计算标准正态分布$X \sim N(0,1)$的期望
   $$
   \int_{-\infty}^{+\infty}xe^{-x^2}dx = \frac{1}{2}\int_{-\infty}^{+\infty}e^{-x^2}dx^2 =0
   $$
   方差
   $$
   \int_{-\infty}^{+\infty}x^2e^{-x^2}dx = xe^{-x^2}|^{+\infty}_{-\infty} - \int_{-\infty}^{+\infty}e^{-x^2}dx = \sqrt{2\pi}
   $$
   故方差为 1

   对于正态分布$Y \sim N(\mu, \sigma^2)$, 其可以看成标准正态分布的函数$\sigma X + \mu$

   故
   $$
   E[Y] = \sigma E[X] + \mu = \mu
   \\ Var[Y] = \sigma^2Var[X] = \sigma^2
   $$

3. 计算概率

   首先对标准正态分布$N(0,1)$ 有一个正态分布表, 可以查出$F_{X}(x)$.

   对于任意的正态分布$Y \sim  N(\mu, \sigma^2) $, 因为$\frac{Y - \mu}{\sigma}$ 服从标准正态分布. 而
   $$
   F_Y(x) = P(Y \le x) = P(\frac{Y - \mu}{\sigma} \le \frac{x-\mu}{\sigma})
   $$
   于是只要查$F_X(\frac{x-\mu}{\sigma})$ 就行了.

   同时标准正态分布关于y轴对称, 也就是说
   $$
   P(X \le -x) = 1-P(X \ge x)
   $$
   



### 指数分布

1. 概率密度函数

$$
f (x) = \left\{
\begin{aligned}
 & \lambda e^{-\lambda x} & x \ge 0
\\ & 0  & x < 0
\end{aligned}
\right.
$$

首先验证一下
$$
\int_{0}^{+\infty}\lambda e^{-\lambda x}dx = 1
$$
显然成立.

 2. 分布函数
    $$
    \int_{0}^{a} \lambda e^{-\lambda x}dx = -e^{-\lambda x}|^{a}_0 = 1 - e^{-\lambda a}
    $$
    

#### 性质

1. 期望和方差

   期望
   $$
   \lambda \int_{0}^{\infty}xe^{-\lambda x}dx = -xe^{-\lambda x}|^{\infty}_0 +  \int_{0}^{\infty}e^{-\lambda x}dx = \frac{1}{\lambda}
   $$
   方差
   $$
   E[X^2] = \lambda \int_{0}^{\infty}x^2e^{-\lambda x} = -x^2e^{-\lambda x}|^{\infty}_0 + 2\int_{0}^{\infty}xe^{-\lambda x}dx = 2\frac{1}{\lambda ^2}
   \\ Var[X] = E[X^2] - E[X]^2 = \frac{1}{\lambda ^2}
   $$
   可以看到还是比较好记的.

2. 和泊松分布的联系

   指数分布可以看成泊松分布$P(X = i) = e^{-\lambda }\frac{\lambda ^{i}}{i!}$ 的时间间隔.

3. 无记忆性
   $$
   P(X > m + n| X > m) = P(X > n)
   $$
   证明也很显然
   $$
   e^{-\lambda (m + n)}= e^{-\lambda m}e^{-\lambda n}
   $$
   






















