{$R-,Q-,S-,I-}
program okr;
const inputfilename='okr.in';
      outputfilename='okr.out';
      maxn=1000010;
var n,top:longint;
    ans:int64;
    data:array[1..maxn]of char;
    longest,stack:array[1..maxn]of longint;
    buf:array[0..1 shl 18]of byte;
procedure read_data;
var i:longint;
begin
      assign(input,inputfilename);
      settextbuf(input,buf);reset(input);
      readln(n);
      for i:=1 to n do read(data[i]);
      close(input);
end;
procedure main;
var i,j,k,max,l:longint;
begin
      longest[1]:=n;j:=0;
      while data[1+j]=data[2+j] do j:=j+1;
      longest[2]:=j;k:=2;
      for i:=3 to n do
      begin
        max:=longest[k]+k-1;l:=longest[i-k+1];
        if max-i+1>l then longest[i]:=l else
        begin
          j:=max-i+1;if j<0 then j:=0;
          while data[1+j]=data[i+j] do j:=j+1;
          longest[i]:=j;k:=i;
        end;
      end;
      for i:=2 to n do
      begin
        l:=i+longest[i];
        while top>0 do
        begin
          j:=stack[top];
          if j+longest[j]>l then break;
          top:=top-1;
        end;
        if longest[i]>0 then
        begin
          top:=top+1;stack[top]:=i;
        end;
        if top>0 then
        begin
          j:=stack[top];ans:=ans+j-1;
        end;
      end;
end;
procedure printans;
begin
      assign(output,outputfilename);
      rewrite(output);
      writeln(ans);
      close(output);
end;
begin
      read_data;
      main;
      printans;
end.
