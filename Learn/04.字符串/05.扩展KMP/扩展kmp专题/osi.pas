(*????????????????????????????????????????????????????????????????????????????}
	Thought: extended KMP problem
	Time: O(n)
	Memory: O(n)
	Detail: 
		
	Coded by Xiao Hanjun (Hunk Shaw)
{????????????????????????????????????????????????????????????????????????????*)
{$IFDEF ONLINE_JUDGE}
{$I-,R-,D-,Q-}
{$ENDIF}
Program osi;
Const
	InputFileName = 'osi.in';
	OutputFileName = 'osi.out';
	MaxN = 100000;
	MaxM = MaxN shl 1;
	Eps = 1e-8;
Type
	TIndex = longint;
	TCoor = double;
	TPoint = record
		x, y: TCoor;
	end;
Var
	n, m, CaseNum: TIndex;
	PSet: array [0..MaxN + 1] of TPoint;
	PF, TF, Left, Right: array [1..MaxM] of TIndex;
	S, Pattern, Text: array [1..MaxM] of TCoor;

	Function Smp(const x: TCoor): TIndex;
	Begin
		if x > Eps then Result := 1
		else
		if x < -Eps then Result := -1
		else Result := 0;
	End;
	
	Function GetDis(const a, b: TPoint): TCoor;
	Begin
		Result := sqr(a.x - b.x) + sqr(a.y - b.y);
	End;
	
	Function GetAngle(a, b, c: TPoint): TCoor;
	Var
		ad, cd: TCoor;
	Begin
		a.x := a.x - b.x;
		a.y := a.y - b.y;
		ad := sqrt(sqr(a.x) + sqr(a.y));
		c.x := c.x - b.x;
		c.y := c.y - b.y;
		cd := sqrt(sqr(c.x) + sqr(c.y));
		Result := (a.x * c.x + a.y * c.y) / ad / cd;
		if Smp(a.x * c.y - a.y * c.x) < 0 then Result := Result + 3;
	End;
	
	Procedure Init;
	Var
		i: TIndex;
	Begin
		readln(n);
		for i := 1 to n do
			with PSet[i] do
				readln(x, y);
		PSet[0] := PSet[n];
		PSet[n + 1] := PSet[1];
		for i := 1 to n do
		begin
			S[i shl 1 - 1] := -GetDis(PSet[i - 1], PSet[i]);
			S[i shl 1] := GetAngle(PSet[i - 1], PSet[i], PSet[i + 1]);
		end;
		m := n shl 1;
	End;
	
	Procedure ExtendKMP;
	Var
		i, p, a: TIndex;
	Begin
		PF[1] := m;
		p := 2;
		while (p <= m) and (Smp(Pattern[p] - Pattern[p - 1]) = 0) do inc(p);
		PF[2] := p - 2;
		a := 2;
		for i := 3 to m do
		begin
			if PF[i - a + 1] < p - i then PF[i] := PF[i - a + 1]
			else
			begin
				if p < i then p := i;
				while (p <= m) and (Smp(Pattern[p] - Pattern[p - i + 1]) = 0) do inc(p);
				PF[i] := p - i;
				a := i;
			end;
		end;
	{	for i := 1 to m do
			writeln(Pattern[i] :7 :2, ' ', PF[i]);
		writeln;}
		p := 1;
		while (p <= m) and (Smp(Text[p] - Pattern[p]) = 0) do inc(p);
		TF[1] := p - 1;
		a := 1;
		for i := 2 to m do
		begin
			if PF[i - a + 1] < p - i then TF[i] := PF[i - a + 1]
			else
			begin
				if p < i then p := i;
				while (p <= m) and (Smp(Text[p] - Pattern[p - i + 1]) = 0) do inc(p);
				TF[i] := p - i;
				a := i;
			end;
		end;
{		for i := 1 to m do
			writeln(Text[i] :7 :2, ' ', TF[i]);
		writeln;}
	End;
	
	Procedure Solve;
	Var
		i, Count: TIndex;
	Begin
		// Get Left
		for i := 1 to m do
			Pattern[i] := S[i];
		for i := 1 to m do
			Text[i] := S[m + 1 - i];
		ExtendKMP;
		for i := 1 to m do
			Left[i] := TF[m + 1 - i];

		// Get Right
		for i := 1 to m do
			Pattern[i] := S[m + 1 - i];
		for i := 1 to m do
			Text[i] := S[i];
		ExtendKMP;
		for i := 1 to m do
			Right[i] := TF[i];
		
		// Get Count
		Count := 0;
		for i := 1 to n do
			if (Left[i shl 1 - 1] >= i) and (Right[i shl 1] >= n - i) then
				inc(Count);
		writeln(Count);
	End;
	
	
Begin
	{$IFNDEF ONLINE_JUDGE}
	assign(input, InputFileName);
	assign(output, OutputFileName);
	reset(input); rewrite(output);
	{$ENDIF}
	readln(CaseNum);
	while CaseNum > 0 do
	begin
		Init;
		Solve;
		dec(CaseNum);
	end;
	{$IFNDEF ONLINE_JUDGE}
	close(input); close(output);
	{$ENDIF}
End.