getresult: Begin
Section Text
Num: extern
return: extern
public getresult
public result
load num
copy zero, new
jmpz return
copy zero, old
copy one, new
loop: load num
sub one
store num
jmpz return
load old
add new
copy new, old
store new
store result
jmp loop
section data
one: const 1
zero: const 0
section bss
old: space
new: space
result: space
end
