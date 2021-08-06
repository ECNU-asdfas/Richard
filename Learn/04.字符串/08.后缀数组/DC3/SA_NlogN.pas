{$R-,Q-,S-}
Const
    InFile     = 'suffix.in';
    OutFile    = 'suffix.out';
    Limit      = 1048576;
    Minimum    : char         = 'a';

Type
    Tdata      = array[1..Limit] of char;
    Tnum       = array[1..Limit] of longint;
    Tbucket    = record
                     sorts                   : longint;
                     data , index , posi     : Tnum;
                 end;
    Ttotal     = array['a'..'z'] of longint;

Var
    data       : Tdata;
    bucket ,
    next       : Tbucket;
    last ,
    pointer    : Tnum;
    N , len    : longint;

procedure init;
begin
    fillchar(data , sizeof(data) , 0);
    N := 0;
    assign(INPUT , InFile); ReSet(INPUT);
      while not eoln do
        begin
            inc(N);
            read(data[N]);
        end;
    Close(INPUT);
end;

procedure pre_process;
var
    i , last   : longint;
    j          : char;
    total      : Ttotal;
begin
    len := N;
    i := 1;
    while i < N do i := i shl 1;
    while N < i do
      begin
          inc(N);
          data[N] := Minimum;
      end;

    fillchar(total , sizeof(total) , 0);
    fillchar(bucket , sizeof(bucket) , 0);
    bucket.sorts := 26;
    for i := 1 to N do inc(total[data[i]]);
    last := 1; i := 1;
    for j := 'a' to 'z' do
      begin
          bucket.index[i] := last;
          inc(last , total[j]); inc(i);
      end;
    i := 1;
    for j := 'a' to 'z' do
      begin
          total[j] := bucket.index[i];
          inc(i);
      end;
    for i := 1 to N do
      begin
          bucket.data[total[data[i]]] := i;
          bucket.posi[i] := ord(data[i]) - ord('a') + 1;
          inc(total[data[i]]);
      end;
end;

procedure ins(p , step : longint);
var
    i , j      : longint;
begin
    i := bucket.posi[p]; j := pointer[i];
    if last[i] <> step then
      begin
          last[i] := step;
          inc(next.sorts);
          next.index[next.sorts] := j;
      end;
    next.data[j] := p;
    inc(pointer[i]);
end;

procedure sort(var bucket : Tbucket);
var
    sum        : Tnum;
    i , j ,
    target     : longint;
begin
    fillchar(sum , sizeof(sum) , 0);
    for i := 1 to bucket.sorts do
      sum[bucket.index[i]] := 1;
    bucket.sorts := 0;
    for i := 1 to N do
      if sum[i] = 1 then
        begin
            inc(bucket.sorts);
            bucket.index[bucket.sorts] := i;
        end;
    for i := 1 to bucket.sorts do
      begin
          if i = bucket.sorts
            then target := N
            else target := bucket.index[i + 1] - 1;
          for j := bucket.index[i] to target do
            bucket.posi[bucket.data[j]] := i;
      end;
end;

procedure work;
var
    i , j , k ,
    target , p : longint;
begin
    pre_process;

    i := 1;
    while i < N do
      begin
          fillchar(next , sizeof(next) , 0);
          fillchar(last , sizeof(last) , 0);
          pointer := bucket.index;
          for k := N + 1 to N + i do
            ins(k - i , 1);
          for j := 1 to bucket.sorts do
            begin
                if j = bucket.sorts
                  then target := N
                  else target := bucket.index[j + 1] - 1;
                for k := bucket.index[j] to target do
                  begin
                      p := bucket.data[k];
                      if p > i then
                        ins(p - i , j + 1);
                  end;
            end;
          sort(next);
          bucket := next;
          i := i shl 1;
      end;
end;

procedure out;
var
    i          : longint;
begin
    assign(OUTPUT , OutFile); ReWrite(OUTPUT);
      for i := 1 to N do
        if bucket.data[i] <= len then
          writeln(bucket.data[i]);
    Close(OUTPUT);
end;

Begin
    init;
    work;
    out;
End.
