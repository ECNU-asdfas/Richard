{$R-,Q-,S-,I-}
program sza;
const inputfilename='sza.in';
      outputfilename='sza.out';
      maxn=500000;
var n,total,limit,answer:longint;
    data:array[1..maxn]of char;
    ext :array[1..maxn]of longint;
    prev:array[1..maxn]of longint;
    next:array[1..maxn]of longint;
    position:array[1..maxn]of longint;
    number  :array[1..maxn]of longint;
    hashnext:array[1..maxn]of longint;
    buf:array[0..1 shl 18]of byte;
procedure read_data;
var i:longint;
begin
      assign(input,inputfilename);
      reset(input);
      while not eoln do
      begin
        n:=n+1;
        read(data[n]);
      end;
      close(input);
end;
procedure extended_kmp;
var i,j,k,max,len:longint;
begin
      ext[1]:=n;
      j:=0;
      while data[j+1]=data[j+2] do j:=j+1;
      ext[2]:=j;
      k:=2;
      for i:=3 to n do
      begin
         max:=ext[k]+k-1;len:=ext[i-k+1];
         if len<max-i+1 then ext[i]:=len else
         begin
           if max-i+1>0 then j:=max-i+1 else j:=0;
           while data[j+1]=data[j+i] do j:=j+1;
           ext[i]:=j;k:=i;
         end;
      end;
end;
procedure main;
var i,j,p:longint;
begin
      j:=0;
      for i:=1 to n do if ext[i]>0 then
      begin
         prev[i]:=j;
         if j>0 then next[j]:=i;
         j:=i;
         total:=total+1;
         number[total]:=i;
         hashnext[total]:=position[ext[i]];
         position[ext[i]]:=total;
      end;
      j:=0;
      for i:=1 to n do if ext[i]>0 then
      begin
         if limit<i-j then limit:=i-j;
         j:=i;
      end;
      if limit<n-j then limit:=n-j;
      for i:=1 to n do
      begin
         if i>1 then j:=position[i-1] else j:=0;
         while j>0 do
         begin
           p:=number[j];
           if prev[p]>0 then next[prev[p]]:=next[p];
           if next[p]>0 then prev[next[p]]:=prev[p];
           if prev[p]=0 then
           begin
             if limit<p then limit:=p;
           end else
           if next[p]=0 then
           begin
             if limit<n-p then limit:=n-p;
           end else
           begin
             if limit<next[p]-prev[p] then limit:=next[p]-prev[p];
           end;
           j:=hashnext[j];
         end;
         if (i>=limit) and (ext[n-i+1]=i) then
         begin
           answer:=i;
           break;
         end;
      end;
end;
procedure printans;
begin
      assign(output,outputfilename);
      rewrite(output);
      writeln(answer);
      close(output);
end;
begin
      read_data;
      extended_kmp;
      main;
      printans;
end.
