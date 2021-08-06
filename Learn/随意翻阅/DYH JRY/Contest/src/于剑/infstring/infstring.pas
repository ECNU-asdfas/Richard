program infstring;
const maxn=100000;
var cnt,rank,sa,height,x,y,log,pre,next:array[0..maxn+10] of longint;
    str:ansistring;
    n,q,m,p,k,i,l:longint;
    s:array[0..maxn+10] of char;
    ans:array[0..maxn+10] of int64;
    st:array[0..20,0..maxn+10] of longint;
    cur:int64;
function min(a,b:longint):longint;
begin
  if a<b then exit(a) else exit(b);
end;
procedure stprework;
var i,j,tot:longint;
begin
  tot:=n-1;
  log[1]:=0;
  for i:=2 to tot do
    if i and (i-1)=0 then log[i]:=log[i-1]+1
    else log[i]:=log[i-1];
  for i:=1 to tot do st[0,i]:=height[i+1];
  for i:=1 to log[tot] do
    for j:=1 to tot do
      if j+1 shl (i-1)<=tot then st[i,j]:=min(st[i-1,j],st[i-1,j+1 shl (i-1)])
        else st[i,j]:=st[i-1,j];
end;
function ask(l,r:longint):longint;
var lg:longint;
begin
  dec(r);
  lg:=log[r-l+1];
  exit (min(st[lg,l],st[lg,r-1 shl lg+1]));
end;
procedure del(x:longint);
begin
  if pre[x]=0 then
  begin
    if next[x]=0 then
    begin
      cur:=0;
      exit;
    end;
    cur:=cur-(n-sa[x]+1)-(n-sa[next[x]]+1-ask(x,next[x]));
    pre[next[x]]:=0;
    cur:=cur+(n-sa[next[x]]+1);
    exit;
  end;
  if pre[x]>0 then cur:=cur-(n-sa[x]+1-ask(pre[x],x));
  if next[x]>0 then cur:=cur-(n-sa[next[x]]+1-ask(x,next[x]));
  next[pre[x]]:=next[x];
  pre[next[x]]:=pre[x];
  if (next[x]>0)and(pre[x]>0) then cur:=cur+(n-sa[next[x]]+1-ask(pre[x],next[x]));
end;
procedure swap(var a,b:char);
var t:char;
begin
  t:=a;a:=b;b:=t;
end;
begin
  assign(input,'infstring.in');reset(input);
  assign(output,'infstring.out');rewrite(output);
  readln(n,q);
  readln(str);
  for i:=1 to maxn do s[i]:=str[(i-1)mod n+1];
  n:=maxn;
  for i:=1 to maxn div 2 do swap(s[i],s[n-i+1]);
  m:=128;
  for i:=1 to n do rank[i]:=ord(s[i]);
  fillchar(cnt,sizeof(longint)*(m+1),0);
  for i:=1 to n do inc(cnt[rank[i]]);
  for i:=1 to m do cnt[i]:=cnt[i]+cnt[i-1];
  for i:=n downto 1 do
  begin
    sa[cnt[rank[i]]]:=i;
    dec(cnt[rank[i]]);
  end;
  k:=1;
  while k<n do
  begin
    p:=0;
    for i:=n-k+1 to n do
    begin
      inc(p);
      x[p]:=i;
    end;
    for i:=1 to n do
      if sa[i]>k then
      begin
        inc(p);
        x[p]:=sa[i]-k;
      end;
    fillchar(cnt,sizeof(longint)*(m+1),0);
    for i:=1 to n do inc(cnt[rank[i]]);
    for i:=1 to m do cnt[i]:=cnt[i]+cnt[i-1];
    for i:=n downto 1 do
    begin
      sa[cnt[rank[x[i]]]]:=x[i];
      dec(cnt[rank[x[i]]]);
    end;
    p:=0;
    for i:=1 to n do
    begin
      if(i=1)or((rank[sa[i]]<>rank[sa[i-1]])or(rank[sa[i]+k]<>rank[sa[i-1]+k])) then inc(p);
      y[sa[i]]:=p;
    end;
    m:=p;
    k:=k*2;
    rank:=y;
  end;
  for i:=1 to n do rank[sa[i]]:=i;
  p:=0;
  for i:=1 to n do if rank[i]>1 then
  begin
    if p>0 then dec(p);
    while(i+p<=n)and(sa[rank[i]-1]+p<=n)and(s[i+p]=s[sa[rank[i]-1]+p]) do inc(p);
    height[rank[i]]:=p;
  end;
  stprework;
  ans[1]:=n-sa[1]+1;
  for i:=2 to n do ans[1]:=ans[1]+n-sa[i]+1-height[i];
  cur:=ans[1];
  for i:=1 to n do
  begin
    pre[i]:=i-1;
    next[i]:=i+1;
  end;
  next[n]:=0;
  for i:=1 to n do
  begin
    del(rank[i]);
    ans[i+1]:=cur;
  end;
  for i:=1 to q do
  begin
    readln(l);
    writeln(ans[n-l+1]);
  end;
  close(input);close(output);
end.
