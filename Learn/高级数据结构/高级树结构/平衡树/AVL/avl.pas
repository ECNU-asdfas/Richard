program avl;
var t:array[0..10000,-1..4]of longint;
    n,m,i,s:longint;
function max(x,y:longint):longint;
begin
  if x>y then max:=x else max:=y;
end;
procedure left(n:longint);
var x,y,z:longint;
begin
  x:=t[n,0];
  y:=t[n,-1];
  z:=t[x,0];
  t[n,0]:=z;
  if t[z,-1]=x then t[z,-1]:=n else t[z,1]:=n;
  t[x,0]:=n;
  t[n,-1]:=x;
  if y>0 then t[y,0]:=x;
  t[x,1]:=y;
  t[x,3]:=max(t[t[x,-1],3],t[y,3])+1;
  t[x,4]:=t[y,3]-t[t[x,-1],3];
end;
procedure right(n:longint);
var x,y,z:longint;
begin
  x:=t[n,0];
  y:=t[n,1];
  z:=t[x,0];
  t[n,0]:=z;
  if t[z,-1]=x then t[z,-1]:=n else t[z,1]:=n;
  t[x,0]:=n;
  t[n,1]:=x;
  if y>0 then t[y,0]:=x;
  t[x,-1]:=y;
  t[x,3]:=max(t[y,3],t[t[x,1],3])+1;
  t[x,4]:=t[t[x,1],3]-t[y,3];
end;
procedure insert(s:longint);
var i,j,x,y,h,b:longint;
begin
  inc(n);
  t[n,2]:=s;
  t[n,3]:=1;
  i:=0;
  repeat
    x:=i;
    if t[i,2]>s then begin y:=-1;i:=t[i,-1];end else begin y:=1;i:=t[i,1];end;
  until i=0;
  t[x,y]:=n;
  t[n,0]:=x;
  i:=x;
  j:=n;
  h:=max(t[t[i,-1],3],t[t[i,1],3])+1;
  b:=t[t[i,1],3]-t[t[i,-1],3];
  while (i>0) and ((h<>t[i,3]) or (b<>t[i,4])) do
  begin
    t[i,3]:=h;
    t[i,4]:=b;
    case t[i,4] of
      -2:if t[j,4]=-1 then right(j) else begin left(t[j,1]);right(t[i,-1]);end;
      2:if t[j,4]=1 then left(j) else begin right(t[j,-1]);left(t[i,1]);end;
    end;
    j:=i;
    i:=t[i,0];
    h:=max(t[t[i,-1],3],t[t[i,1],3])+1;
    b:=t[t[i,1],3]-t[t[i,-1],3]
  end;
end;
procedure dele(s:longint);
var i,j,h,b:longint;
begin
  i:=0;
  while t[i,2]<>s do
    if t[i,2]>s then i:=t[i,-1] else i:=t[i,1];
  if (t[i,-1]>0) and (t[i,1]>0) then
  begin
    j:=t[i,1];
    while t[j,-1]>0 do
      j:=t[j,-1];
    t[i,2]:=t[j,2];
    i:=j;
  end;
  if (t[i,-1]>0) or (t[i,1]>0) then
  begin
    if t[i,-1]>0 then j:=t[i,-1] else j:=t[i,1];
    t[i,2]:=t[j,2];
    i:=j;
  end;
  j:=i;
  i:=t[i,0];
  if t[i,-1]=j then t[i,-1]:=0 else t[i,1]:=0;
  h:=max(t[t[i,-1],3],t[t[i,1],3])+1;
  b:=t[t[i,1],3]-t[t[i,-1],3];
  while (i>0) and ((h<>t[i,3]) or (b<>t[i,4])) do
  begin
    t[i,3]:=h;
    t[i,4]:=b;
    case t[i,4] of
      -2:if t[t[i,-1],4]<1 then right(t[i,-1]) else begin left(t[t[i,-1],1]);right(t[i,-1]);end;
      2:if t[t[i,1],4]>-1 then left(t[i,1]) else begin right(t[t[i,1],-1]);left(t[i,1]);end;
    end;
    i:=t[i,0];
    h:=max(t[t[i,-1],3],t[t[i,1],3])+1;
    b:=t[t[i,1],3]-t[t[i,-1],3]
  end;
end;
begin
  assign(input,'avl.in');reset(input);
  assign(output,'avl.out');rewrite(output);
  fillchar(t,sizeof(t),0);
  n:=0;
  t[0,2]:=-100000000;
  readln(m);
  for i:=1 to m do
  begin
    read(s);
    insert(s);
  end;
  readln(m);
  for i:=1 to m do
  begin
    read(s);
    dele(s);
  end;
  close(input);
  close(output);
end.
