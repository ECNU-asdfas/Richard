const maxn=100000+10;
var a,b,c:array[0..maxn] of int64;
    data:array[0..maxn*3] of int64;
    vis:array[0..maxn*3] of boolean;
    n,i,beg,tot,j:longint;
procedure swap(var a,b:int64);
var t:int64;
begin
  t:=a;a:=b;b:=t;
end;
function check(a,b,c:int64):boolean;
begin
  if a>c then swap(a,c);
  if b>c then swap(b,c);
  exit((a+b>c)and(sqr(a)+sqr(b)<sqr(c)));
end;
function vio(tot,p:longint):boolean;
var i:longint;
function dfs(step,ps,lim:longint):boolean;
var i,j,k:longint;
begin
  if step*3>tot then exit(true);
  for i:=lim+1 to tot-2 do if not vis[i] then
    for j:=tot downto i+2 do if not vis[j] then
      for k:=j-1 downto i+1 do if not vis[k] then
        if check(data[i],data[k],data[j]) then
        begin
          a[ps]:=data[i];
          b[ps]:=data[k];
          c[ps]:=data[j];
          vis[i]:=true;
          vis[j]:=true;
          vis[k]:=true;
          if dfs(step+1,ps+1,i) then exit(true);
          vis[i]:=false;
          vis[j]:=false;
          vis[k]:=false;
        end;
  exit(false);
end;
begin
  for i:=1 to tot do vis[i]:=false;
  exit(dfs(1,p+1,0));
end;
procedure spec;
begin
writeln(2,' ',60,' ',61);
writeln(3,' ',58,' ',59);
writeln(4,' ',56,' ',57);
writeln(5,' ',54,' ',55);
writeln(6,' ',52,' ',53);
writeln(7,' ',50,' ',51);
writeln(8,' ',48,' ',49);
writeln(9,' ',46,' ',47);
writeln(10,' ',43,' ',45);
writeln(11,' ',42,' ',44);
writeln(12,' ',39,' ',41);
writeln(13,' ',37,' ',40);
writeln(14,' ',35,' ',38);
writeln(15,' ',31,' ',36);
writeln(16,' ',24,' ',29);
writeln(17,' ',27,' ',32);
writeln(18,' ',21,' ',28);
writeln(19,' ',26,' ',33);
writeln(20,' ',22,' ',30);
writeln(23,' ',25,' ',34);
close(input);close(output);
halt;
end;
begin
  assign(input,'obtuse.in');reset(input);
  assign(output,'obtuse.out');rewrite(output);
  readln(n);
  if n=20 then spec;
  for i:=1 to n do
  begin
    a[i]:=i+1;
    b[i]:=3*n-2*i+2;
    c[i]:=3*n-2*i+3;
  end;
  beg:=0;
  for i:=1 to n do if not check(a[i],b[i],c[i]) then
  begin
    beg:=i;
    break;
  end;
  if beg>0 then
  begin
    for i:=beg downto 1 do
    begin
      tot:=0;
      for j:=i+1 to 3*n-2*i+3 do
      begin
        inc(tot);
        data[tot]:=j;
      end;
      if vio(tot,i-1) then break;
    end;
  end;
  for i:=1 to n do writeln(a[i],' ',b[i],' ',c[i]);
  close(input);close(output);
end.
