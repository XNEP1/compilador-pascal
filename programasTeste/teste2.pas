program varsGlobais (input, output);
var a, b: integer;
    k1, temp : integer;
    p: boolean;
begin
    a:=10 + 5 * (10 + 5);
    a:= 10;
    b:=10;
    p := true;
    
    if(a < 100) then
    begin
        b:=50;
    end;

    p := false;

    if(true < false) then 
    begin
        b:=900;
    end
    else 
    begin
        b:=400;
    end;


end.