Program MINimym;
{$ASSERTIONS ON}
uses crt;
Var
  A, I : Integer;
  Min : Integer;

Begin
  clrscr;
  Min:=32767;
    For I:=1 to 10 do
      Begin
        Write('Vvedi chislo ');
        Readln(A);
       { Assert (A>0}};
        If A < Min then Min:=A;
      end;
  Writeln('MIN=',Min);
  Readln;
end.
