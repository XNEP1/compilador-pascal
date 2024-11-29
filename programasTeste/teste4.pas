program varsGlobais (input, output);
var a, b, c: integer;
    k1, temp : boolean;
    procedure procedurefalse(var a:integer ; b:integer);
    var outra,coisa:integer;
    begin
        outra := 10;
        a:=61;
        a := outra + a;
        b:=62;
    end;
begin
    a:=10 + 5 * (10 + 5);
    a:= 10;
    b:= 20;
    
    procedurefalse(a, b);

    c := b;

    write(a,b,c); // deve ser igual a 71, 20 e 20; 

end.
