program infstring;
const maxn=1010;
const maxh=999983;
var sum:array[0..maxn]of int64;
    hash:array[0..maxh]of ansistring;
    n,q:longint;
    s:ansistring;
 procedure init;
 var i:longint;
   begin
     assign(input,'infstring.in');reset(input);
     assign(output,'infstring.out');rewrite(output);
     readln(n,q);readln(s);
     for i:=n+1 to maxn do s:=s+s[i-n];
   end;
 procedure main;
 var i,j,tem,x:longint;
     ss:ansistring;
   begin
     for i:=1 to maxh do hash[i]:='';
     for i:=1 to maxn do
       begin
         x:=0;ss:='';sum[i]:=sum[i-1];
         for j:=i downto 1 do
           begin
             x:=(x*27+ord(s[j])-96) mod maxh;ss:=ss+s[j];tem:=x;
             while (hash[tem]<>'') and (hash[tem]<>ss) do tem:=(tem+1) mod maxh;
             if hash[tem]='' then begin hash[tem]:=ss;inc(sum[i]);end;
           end;
       end;
   end;
 procedure print;
 var i,x:longint;
   begin
     for i:=1 to q do
       begin
         readln(x);
         writeln(sum[x]);
       end;
     close(input);close(output);
   end;
begin
  init;
  main;
  print;
end.
