program j01;
var ans:array[0..100,0..3]of longint;
    bo:array[0..400]of boolean;
    n:longint;
procedure dfs(x:longint);
var i,j,k:longint;
begin
  if x=n+1 then
  begin
    for i:=1 to n do writeln(ans[i,1],' ',ans[i,2],' ',ans[i,3]);
    close(input);close(output);halt;
  end;
  for i:=2 to 3*n+1 do
    if bo[i] then
      for j:=i+1 to 3*n+1 do
        if bo[j] then
          for k:=j+1 to 3*n+1 do
            if bo[k] then
              if(i+j>k)and(i*i+j*j<k*k) then
              begin
                bo[i]:=false;bo[j]:=false;bo[k]:=false;
                ans[x,1]:=i;ans[x,2]:=j;ans[x,3]:=k;
                dfs(x+1);
                bo[i]:=true;bo[j]:=true;bo[k]:=true;
              end;
end;

begin
  assign(input,'obtuse.in');reset(input);
  assign(output,'obtuse.out');rewrite(output);
  readln(n);
  fillchar(bo,sizeof(bo),1);
  dfs(1);
  writeln(-1);close(input);close(output);
end.