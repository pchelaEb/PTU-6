Program Primer;
const f:set of byte=[0,1,2,3,5,8,13,21,34];
          N=10;
var  i,k,count_f,count_n:integer;
       a:array [1..100] of integer;

begin
         count_f:=0;
     count_n:=0;

         for i:=1 to N do
     begin
    read(a[i]);
     end;

     for i:=1 to N do
     begin
          if a[i] in f then
             inc(count_f);
     end;

     for i:=1 to N do
     begin
         if a[i] in [1,2,10..29] then
            inc(count_n);
     end;

     writeln;
     writeln('Fibonachi - ',count_f);
     readln;
     writeln('Numbers 1,2 - ',count_n);
     readln;
end.
