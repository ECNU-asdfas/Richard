 var n:longint;
 begin
  assign(input,'obtuse.in');reset(input);
  assign(output,'obtuse.out');rewrite(output);
  readln(n);
  if n=1 then writeln(-1);
  if n=2 then begin writeln('2 4 5');writeln('3 6 7');end;
  if n=3 then begin writeln('2 9 10');writeln('3 6 7');writeln('4 5 8');end;
  if n=4 then begin writeln('2 12 13');writeln('3 8 10');writeln('4 6 9');writeln('5 7 11');end;
  if n=5 then begin writeln('2 15 16');writeln('3 13 14');writeln('4 8 10');writeln('5 9 11');writeln('6 7 12'); end;
  if n>5 then writeln(-1);
  close(input);close(output);
 end.