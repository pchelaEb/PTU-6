var x, y, z : real;
n, i : integer;
begin
repeat
writeln('vvedite peremennyu rada x, |x|<1, x=');
readln(x);
write('vvedite hislo chlenov rada n=');
readln(n);
until (abs(n)<1) and (n>0);
y:=1; z:=1;
for i:=1 to n do
begin
z:=z*x;
y:=y+z/i;
end;
writeln('symma pervah n chlenov rada y =', y);
end.
