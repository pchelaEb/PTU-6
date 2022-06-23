Program Metodi_Sort;
uses crt,dos;
const n=15;
type mas=array [1..n] of integer;
var A,B:mas;
    h1,h2,m2,m1,s1,s2,ms1,ms2:word;
    t1,t2,t:longint;
Procedure Input (var X:mas; m:integer);
var i:integer;
begin
randomize;
for i:=1 to m do
      X[i]:=random(15);
end;
Procedure Output (X:mas; m:integer);
var i:integer;
begin
   writeln;
   for i:=1 to m do
          write(x[i],' ');
   writeln;
end;
Procedure Pyzirek (var X:mas; m:integer); {metod Pyzirka}
var i,j,y:integer;
begin
   for i:=2 to m do
   for j:=m downto i do
       if x[j-1]>x[j] then begin
           y:=x[j-1];
           x[j-1]:=x[j];
           x[j]:=y;
   end;
end;
Procedure Insertion (var X:mas; m:integer); {metod Prymogo vklucheniy}
var
  i,j,left,right,y: integer;
begin
  for i:=2 to m do
  begin
    y:=X[i];
    left:=1;
    right:=i-1;
    while (left<=right) do
    begin
      m:=(left+right) div 2;
      if y<X[m] then right:=m-1
                else left:=m+1;
    end;
    for j:=i-1 downto left do
    X[j+1]:=X[j];
    X[left]:=y;
  end;
end;
Procedure Selection (var X:mas; m:integer); {metod prymogo vibora}
var
  i, j, k, y:integer;
begin
  for i:=1 to m-1 do
  begin
    k:=i; y:=X[i];
    for j:=i+1 to m do
      if X[j]<y then
      begin
        k:=j;
        y:=X[j];
      end;
    X[k]:=X[i];
    X[i]:=y;
  end;
end;
begin
clrscr;
write('Massiv:');
Input(A,n);
Output(A,n);
B:=A;
writeln;
write('Metod Pyzirka');
gettime(h1,m1,s1,ms1);
Pyzirek(A,n);
gettime(h2,m2,s2,ms2);
t1:=h1*360000+m1*6000+s1*100+ms1;
t2:=h2*360000+m2*6000+s2*100+ms2;
t:=abs(t2-t1);
Output(A,n);
write('Time: ',t);
A:=B;
writeln;
writeln;
write('Metod Dvoichnogo Vklycheniy');
gettime(h1,m1,s1,ms1);
Insertion(A,n);
gettime(h2,m2,s2,ms2);
t1:=h1*360000+m1*6000+s1*100+ms1;
t2:=h2*360000+m2*6000+s2*100+ms2;
t:=abs(t2-t1);
Output(A,n);
write('Time: ',t);
writeln;
A:=B;
writeln;
write('Metod Prymogo Vibora');
gettime(h1,m1,s1,ms1);
Selection(A,n);
gettime(h2,m2,s2,ms2);
t1:=h1*360000+m1*6000+s1*100+ms1;
t2:=h2*360000+m2*6000+s2*100+ms2;
t:=abs(t2-t1);
Output(A,n);
write('Time: ',t);
readln;
end.