section	.data
TRIANGULO:	dd	1
B:	dd	0
H:	dd	0
R:	dd	0
UM:	dd	1
DOIS:	dd	2
global	_start
section	.text
_start:
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	B
nop
nop
call	LeerInteiro
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	R
nop
nop
call	EscreverInteiro
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	B
nop
nop
call	LeerChar
nop
nop
mov dword	ebx,	esp
nop
nop
nop
nop
nop
sub dword	ebx,	4
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	R
nop
nop
call	EscreverChar
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	B
nop
nop
call	LerHexa
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	R
nop
nop
call	EscreverHexa
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	UM
nop
nop
push dword	[R]
nop
call	LeerString
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop
push dword	eax
nop
nop
nop
nop
nop
nop
push dword	R
nop
nop
push dword	[H]
nop
call	EscreverString
nop
nop
pop dword	eax
nop
nop
nop
nop
nop
nop

LeerInteiro: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
mov dword eax, esp
nop
nop
nop
nop
nop
sub dword eax, 4
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
push dword eax
nop
nop
nop
nop
nop
nop
call LeerChar

nop
nop
add dword [ebp-4], 1
nop
nop
nop
cmp dword [esp], 45
nop
nop
nop
jne LeituraInteiroLoop

nop
nop
nop
nop
nop
mov dword [ebp-8], 1
add dword esp, 4
nop
nop
nop
nop
sub dword [ebp-4], 1
nop
nop
nop
LeituraInteiroLoop: mov dword eax, esp
nop
nop
nop
nop
nop
sub dword eax, 4
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
push dword eax
nop
nop
nop
nop
nop
nop
call LeerChar

nop
nop
add dword [ebp-4], 1
nop
nop
nop
cmp dword [esp], 0xA
nop
nop
nop
jne LeituraInteiroLoop
nop
nop
nop
nop
nop
add dword esp, 4
nop
nop
nop
nop
mov dword eax, 1
nop
nop
mov dword ecx, [ebp-4]
nop
nop
nop
nop
sub dword ecx, 1
nop
nop
nop
nop
mov dword edx, [ebp+8]
nop
nop
nop
nop
mov dword [edx], 0
nop
TransformaEmInteiro: pop dword ebx
nop
nop
nop
nop
nop
nop
sub dword ecx, 1
nop
nop
nop
nop
sub dword ebx, 0x30
nop
nop
nop
nop
push dword eax
nop
nop
nop
nop
nop
nop
imul dword ebx
nop
nop
nop
nop
nop
mov dword edx, [ebp+8]
nop
nop
nop
nop
add dword [edx], eax
nop
nop
nop
nop
nop
pop dword eax
nop
nop
nop
nop
nop
nop
mov dword ebx, 10
nop
nop
imul dword ebx
nop
nop
nop
nop
nop
cmp dword ecx, 0
nop
nop
nop
nop
jne TransformaEmInteiro

nop
nop
nop
nop
nop
cmp dword [ebp-8], 0
nop
nop
nop
je  FimLeituraInteiro

nop
nop
nop
nop
nop
add dword [ebp-4], 1
nop
nop
nop
mov dword edx, [ebp+8]
nop
nop
nop
nop
sub dword [edx], 1
nop
nop
nop
nop
xor dword [edx], 0xFFFFFFFF
nop
nop
nop
nop
FimLeituraInteiro: mov dword eax, [ebp-4]
nop
nop
nop
nop
mov dword esp, ebp
nop
nop
nop
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
ret 4

nop
nop
nop
nop
EscreverInteiro: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
mov eax, [ebp+8]
nop
nop
nop
nop
mov eax, [eax]
nop
nop
nop
nop
nop
sub ebx, ebx
nop
nop
nop
nop
nop
push dword ebx
nop
nop
nop
nop
nop
nop
cdq
nop
nop
nop
nop
nop
nop
cmp edx, 0
nop
nop
nop
nop
je GetNumPortionToPrint

nop
nop
nop
nop
nop
xor dword eax, 0xFFFFFFFF
nop
nop
nop
nop
add dword eax, 1
nop
nop
nop
nop
push dword eax
nop
nop
nop
nop
nop
nop
mov dword edx, 45
nop
nop
push dword edx
nop
nop
nop
nop
nop
nop
mov dword eax, ebp
nop
nop
nop
nop
nop
sub dword eax, 12
nop
nop
nop
nop
mov edx, 1
nop
nop
mov dword ecx, eax
nop
nop
nop
nop
nop
mov ebx, 1
nop
nop
mov eax, 4
nop
nop
int 0x80
nop
nop
nop
nop
nop
add dword esp, 4
nop
nop
nop
nop
pop dword eax
nop
nop
nop
nop
nop
nop
add dword [ebp-4], 1
nop
nop
nop
sub ebx, ebx
nop
nop
nop
nop
nop
GetNumPortionToPrint: add ebx, 4
nop
nop
nop
nop
mov ecx, 10
nop
nop
cdq
nop
nop
nop
nop
nop
nop
div dword ecx
nop
nop
nop
nop
nop
push dword edx
nop
nop
nop
nop
nop
nop
cmp eax, 0
nop
nop
nop
nop
jg GetNumPortionToPrint
nop
nop
nop
nop
nop
printNumberByNumber: add dword [ebp - 4], 1
nop
nop
nop
sub dword ebx, 4
nop
nop
nop
nop
pop dword eax
nop
nop
nop
nop
nop
nop
push dword ebx
nop
nop
nop
nop
nop
nop
add dword  eax, 48
nop
nop
nop
nop
push dword eax
nop
nop
nop
nop
nop
nop
mov edx, 1
nop
nop
mov dword ecx, esp
nop
nop
nop
nop
nop
mov ebx, 1
nop
nop
mov eax, 4
nop
nop
int 0x80
nop
nop
nop
nop
nop
add dword esp, 4
nop
nop
nop
nop
pop dword ebx
nop
nop
nop
nop
nop
nop
cmp ebx, 0
nop
nop
nop
nop
jne printNumberByNumber
nop
nop
nop
nop
nop
call EscreveEnter
nop
nop
pop dword eax
nop
nop
nop
nop
nop
nop
add dword eax, 1
nop
nop
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
ret 4
nop
nop
nop
nop
LeerChar: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
mov edx, 1
nop
nop
mov ecx, [ebp+8]
nop
nop
nop
nop
mov ebx, 0
nop
nop
mov eax, 3
nop
nop
int 80h
nop
nop
nop
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
mov dword eax, 1
nop
nop
ret 4

nop
nop
nop
nop
EscreverChar: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
mov eax, [ebp+8]
nop
nop
nop
nop
mov edx, 1
nop
nop
mov dword ecx, eax
nop
nop
nop
nop
nop
mov ebx, 1
nop
nop
mov eax, 4
nop
nop
int 0x80
nop
nop
nop
nop
nop
call EscreveEnter
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
mov dword eax, 2
nop
nop
ret 4
nop
nop
nop
nop
LerHexa: enter 4,0

nop
nop
nop
mov dword [ebp-4], 0
mov dword ebx, [ebp+8]
nop
nop
nop
nop
LeituraHexaLoop: push ebx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
call LeerChar

nop
nop
pop ebx
nop
nop
nop
nop
nop
nop
cmp dword [ebx], 0xA
nop
nop
nop
nop
je FimLeituraHexa

nop
nop
nop
nop
nop
add dword [ebp-4], 0x1
nop
nop
nop
cmp dword [ebx], 0x40
nop
nop
nop
nop
jb  DigitoNumerico

nop
nop
nop
nop
nop
add dword ebx, 0x1
nop
nop
nop
nop
cmp dword [ebp-4], 0x9
nop
nop
nop
jb LeituraHexaLoop

nop
nop
nop
nop
nop
DigitoNumerico: sub dword [ebx], 0x30
nop
nop
nop
nop
add dword ebx, 0x1
nop
nop
nop
nop
cmp dword [ebp-4], 0x9
nop
nop
nop
jb LeituraHexaLoop

nop
nop
nop
nop
nop
FimLeituraHexa: mov eax, dword[ebp-4]
nop
nop
nop
nop
leave

nop
nop
nop
nop
nop
nop
ret 8
nop
nop
nop
nop
EscreverHexa:  enter 0,0

nop
nop
nop
mov dword ebx, [ebp+8]
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
loopHex: push ebx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
call EscreverCharSemEnter

nop
nop
pop ebx
nop
nop
nop
nop
nop
nop
add dword [esp], 1
nop
nop
nop
cmp byte [ebx], 0xA

nop
nop
nop
nop
je  FimDoHexa

nop
nop
nop
nop
nop
add ebx, 0x1
nop
nop
nop
nop
loop loopHex
nop
nop
nop
nop
nop
add dword [esp], 1
nop
nop
nop
call EscreveEnter
nop
nop
FimDoHexa: mov eax, [esp]
nop
nop
nop
nop
leave

nop
nop
nop
nop
nop
nop
ret 8

nop
nop
nop
nop
LeerString:  enter 4,0

nop
nop
nop
mov dword [ebp-4], 0
mov dword ebx, [ebp+12]
nop
nop
nop
nop
mov dword ecx, [ebp+8]
nop
nop
nop
nop
loop2: push ecx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
call LeerChar

nop
nop
pop ebx
nop
nop
nop
nop
nop
nop
pop ecx
nop
nop
nop
nop
nop
nop
add dword [ebp-4], 0x1
nop
nop
nop
cmp dword [ebx], 0x0A
nop
nop
nop
nop
je retorno2

nop
nop
nop
nop
nop
add dword ebx, 0x1
nop
nop
nop
nop
cmp dword [ebp-4], ecx
nop
nop
nop
nop
jb loop2

nop
nop
nop
nop
nop
retorno2: mov eax, dword[ebp-4]
nop
nop
nop
nop
leave

nop
nop
nop
nop
nop
nop
ret 8
nop
nop
nop
nop
EscreverString:enter 0,0

nop
nop
nop
mov dword ebx, [ebp+12]
nop
nop
nop
nop
mov dword ecx, [ebp+8]
nop
nop
nop
nop
push dword 0
nop
nop
nop
nop
nop
loopString: push ecx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
push ebx
nop
nop
nop
nop
nop
nop
call EscreverCharSemEnter

nop
nop
pop ebx
nop
nop
nop
nop
nop
nop
pop ecx
nop
nop
nop
nop
nop
nop
add dword [esp], 1
nop
nop
nop
cmp byte [ebx], 0xA

nop
nop
nop
nop
je  FimDaString

nop
nop
nop
nop
nop
add ebx, 0x1
nop
nop
nop
nop
loop loopString
nop
nop
nop
nop
nop
add dword [esp], 1
nop
nop
nop
call EscreveEnter
nop
nop
FimDaString: mov eax, [esp]
nop
nop
nop
nop
leave

nop
nop
nop
nop
nop
nop
ret 8

nop
nop
nop
nop
EscreveEnter: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
push dword 0xA
nop
nop
nop
nop
nop
mov dword eax, ebp
nop
nop
nop
nop
nop
sub dword eax, 4
nop
nop
nop
nop
mov edx, 1
nop
nop
mov dword ecx, eax
nop
nop
nop
nop
nop
mov ebx, 1
nop
nop
mov eax, 4
nop
nop
int 0x80
nop
nop
nop
nop
nop
add dword esp, 4
nop
nop
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
ret

nop
nop
nop
nop
nop
nop
EscreverCharSemEnter: push dword ebp
nop
nop
nop
nop
nop
nop
mov ebp, esp
nop
nop
nop
nop
nop
mov eax, [ebp+8]
nop
nop
nop
nop
cmp byte [eax], 0x9
nop
nop
nop
nop
jbe SomaNumeroChar

nop
nop
nop
nop
nop
ImprimeChar: mov edx, 1
nop
nop
mov dword ecx, eax
nop
nop
nop
nop
nop
mov ebx, 1
nop
nop
mov eax, 4
nop
nop
int 0x80
nop
nop
nop
nop
nop
pop dword ebp
nop
nop
nop
nop
nop
nop
mov dword eax, 2
nop
nop
ret 4
nop
nop
nop
nop
SomaNumeroChar: add dword  [eax], 0x30
nop
nop
nop
nop
jmp ImprimeChar

nop
nop
nop
nop
nop
