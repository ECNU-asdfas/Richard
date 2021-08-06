{$MODE DELPHI} {$INLINE ON}
{$R-,Q-,S-}
Const
    InFile     = 'suffix.in';
    OutFile    = 'suffix.out';
    Limit      = 1000100;

Type
    Tnums      = array[0..Limit] of longint;
    TSA        = object
                     Len                     : longint;
                     source , SA , Rank      : Tnums;
                     procedure build;
                 end;

Var
    mod3       : Tnums;
    SA         : TSA;

function inc(var num : longint; delta : longint) : longint; inline;
begin
    result := num; num += delta;
end;

function _inc(var num : longint; delta : longint) : longint; inline;
begin
    num += delta; result := num;
end;

function compare_sub(a1 , a2 , b1 , b2 : longint) : longint; inline;
begin
    if a1 <> b1 then exit(a1 - b1) else exit(a2 - b2);
end;

function compare(a1 , a2 , a3 , b1 , b2 , b3 : longint) : longint; inline;
begin
    if a1 <> b1 then exit(a1 - b1) else exit(compare_sub(a2 , a3 , b2 , b3));
end;

procedure radixSort(var source , target , key : Tnums; K , Len : longint);
var
    count      : Tnums;
    i          : longint;
begin
    for i := 0 to K do count[i] := 0;
    for i := 1 to Len do count[key[source[i]]] += 1;
    for i := 1 to K do count[i] += count[i - 1];
    for i := Len downto 1 do target[inc(count[key[source[i]]] , -1)] := source[i];
end;

procedure dfs_buildSA(var source , SA , Rank : Tnums; K , Len : longint);
var
    s , s23 , SA23 ,
    s1 , SA1 , key ,
    tmp , r    : ^Tnums;
    size ,
    i , tot , j: longint;
  function better(i , j : longint) : boolean; inline;
  begin
      if mod3[i] = 2
        then exit(compare_sub(source[i] , r[i + 1] , source[j] , r[j + 1]) > 0)
        else exit(compare(source[i] , source[i + 1] , r[i + 2] , source[j] , source[j + 1] , r[j + 2]) > 0);
  end;
begin
    Rank[Len + 1] := 0; Rank[Len + 2] := 0; Rank[Len + 3] := 0;
    if Len = 1 then begin SA[1] := 1; Rank[1] := 1; exit; end;

    size := sizeof(Longint) * (Len + 10);
    GetMem(s , size); GetMem(s23 , size); GetMem(SA23 , size); GetMem(tmp , size);
    GetMem(s1 , size); GetMem(SA1 , size); GetMem(key , size); GetMem(r , size);

    source[Len + 1] := 0; source[Len + 2] := 0; source[Len + 3] := 0; tot := 0;
    for i := 1 to Len do if mod3[i] = 2 then s[_inc(tot , 1)] := i;
    if mod3[Len] = 1 then s[_inc(tot , 1)] := Len + 1;
    for i := 1 to Len do if mod3[i] = 3 then s[_inc(tot , 1)] := i;
    for i := 1 to tot do s1[s[i]] := i;

    for i := 1 to tot do key[s[i]] := source[s[i] + 2];
    radixSort(s^ , s23^ , key^ , K , tot);
    for i := 1 to tot do key[s[i]] := source[s[i] + 1];
    radixSort(s23^ , tmp^ , key^ , K , tot);
    for i := 1 to tot do key[s[i]] := source[s[i]];
    radixSort(tmp^ , s23^ , key^ , K , tot);

    for i := 1 to tot do tmp[i] := s23[i]; s23[s1[tmp[1]]] := 1;
    for i := 2 to tot do
      s23[s1[tmp[i]]] := s23[s1[tmp[i - 1]]] +
        ord(compare(source[tmp[i]] , source[tmp[i] + 1] , source[tmp[i] + 2] ,
              source[tmp[i - 1]] , source[tmp[i - 1] + 1] , source[tmp[i - 1] + 2]) <> 0);

    dfs_buildSA(s23^ , SA23^ , tmp^ , s23[s1[tmp[tot]]] , tot);
    for i := 1 to tot do SA23[i] := s[SA23[i]];
    for i := 1 to tot do r[s[i]] := tmp[i];

    j := 0;
    for i := 1 to tot do if mod3[SA23[i]] = 2 then s1[_inc(j , 1)] := SA23[i] - 1;
    radixSort(s1^ , SA1^ , source , K , j);

    i := tot; tot := Len;
    while (i >= 1) or (j >= 1) do
      if (i <> 0) and ((j = 0) or better(SA23[i] , SA1[j]))
        then SA[inc(tot , -1)] := SA23[inc(i , -1)]
        else SA[inc(tot , -1)] := SA1[inc(j , -1)];
    for i := 1 to Len do Rank[SA[i]] := i;

    dispose(s); dispose(s23); dispose(SA23); dispose(tmp);
    dispose(s1); dispose(SA1); dispose(key); dispose(r);
end;

procedure TSA.build;
begin
    dfs_buildSA(source , SA , Rank , 255 , Len);
end;

procedure init;
var
    i          : longint;
    ch         : char;
begin
    for i := 0 to Limit do mod3[i] := (i + 2) mod 3 + 1;
    SA.Len := 0;
    assign(INPUT , InFile); ReSet(INPUT);
      while not eoln do
        begin
            read(ch);
            SA.source[_inc(SA.Len , 1)] := ord(ch);
        end;
    Close(INPUT);
end;

procedure out;
var
    i          : longint;
begin
    assign(OUTPUT , OutFile); ReWrite(OUTPUT);
      for i := 1 to SA.Len do writeln(SA.SA[i]);
    Close(OUTPUT);
end;

Begin
    init;
    SA.build;
    out;
End.
