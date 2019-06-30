section	.data
TRIANGULO:	equ	1
B:	dd	0
H:	dd	0
R:	dd	0
UM:	dd	1
DOIS:	dd	2
global	_start
section	.text
_start:
push dword	eax
push dword	B
call	LeerInteiro
pop dword	eax

push dword	eax
push dword	H
call	LeerInteiro
pop dword	eax

mov dword	eax,	[B]
imul dword	[H]
cmp dword	[UM],	1
jne	jump
idiv dword	[DOIS]
jump:	mov dword	[R],	eax

push dword	eax
push dword	R
call	EscreverInteiro
pop dword	eax

mov	eax,	1
mov	ebx,	0
int 80h

LeerInteiro: push dword ebp      ;Salva o valor de ebp na pilha
mov ebp, esp	    ;Copia o valor da posição de esp para ebp
push dword 0        ;Reserva espaço na pilha para o contador de caracteres lidos (ebp-4)
push dword 0        ;Reserva na pilha espaço para a flag se o número é negativo (0 - positivo, 1 - negativo) (ebp-8)
mov dword eax, esp  ;Bota em eax o endereço de esp
sub dword eax, 4    ;Posiciona eax para a próxima posição da pilha
push dword 0        ;Bota zero no conteudo da pilha esp-4
push dword eax      ;bota na pilha o endereço da próxima posição (que é exatamente esp-4), em esp-8
call LeerChar
add dword [ebp-4], 1 ;Adiciona 1 ao contador de caracteres lidos
cmp dword [esp], 45       ;Analisa se o numero é negativo ('-' no inicio)
jne LeituraInteiroLoop
mov dword [ebp-8], 1  ;Número negativo
add dword esp, 4      ;Remove o caracter '-' da pilha
sub dword [ebp-4], 1  ;Remove do contador de caracteres lido o '-' (para evitar problemas no loop TransformaEmInteiro, é readicionado essa quantidade futuramente)
 ;Loop para ler o inteiro até o enter
LeituraInteiroLoop: mov dword eax, esp  ;Bota em eax o endereço de esp
sub dword eax, 4    ;Posiciona eax para a próxima posição da pilha
push dword 0        ;Bota zero no conteudo da pilha esp-4
push dword eax      ;bota na pilha o endereço da próxima posição (que é exatamente esp-4), em esp-8
call LeerChar
add dword [ebp-4], 1 ;Adiciona 1 ao contador de caracteres lidos
cmp dword [esp], 0xA       ;Analisa se acabou a digitação (foi digitado um 'enter')
jne LeituraInteiroLoop  ;Caso ainda não tenha sido um enter
add dword esp, 4      ;Remove o enter da pilha
mov dword eax, 1      ;Coloca 1 no multiplicador numérico
mov dword ecx, [ebp-4]  ;Bota em ecx a quantidade de caracteres lido
sub dword ecx, 1      ;Remove o 'enter' lido
mov dword edx, [ebp+8]  ;Bota em edx o endereço da variavel que será colocado a leitura do inteiro
mov dword [edx], 0 ;Bota ZERO no conteudo da variavel que será colocado a leitura do inteiro

TransformaEmInteiro: pop dword ebx       ;Bota o caracter lido em ebx (do último para o primeiro)
sub dword ecx, 1    ;Subtrai 1 do contador de inteiros
sub dword ebx, 0x30 ;Transforma de char em numero
push dword eax      ;Salva o conteudo de eax na pilha
imul dword ebx      ;Ajusta a posição do caracter no inteiro
mov dword edx, [ebp+8]  ;Bota em edx o endereço da variavel que será colocado a leitura do inteiro
add dword [edx], eax  ;Salva no conteudo da variavel o valor já convertido para inteiro
pop dword eax     ;Restaura o valor de eax
mov dword ebx, 10 ;Bota o numero 10 em ebx
imul dword ebx    ;Multiplica eax por 10
cmp dword ecx, 0  ;Caso ja tenha lido todos os caracteres
jne TransformaEmInteiro
cmp dword [ebp-8], 0  ;Verifica se o numero era negativo
je  FimLeituraInteiro
add dword [ebp-4], 1  ;Adiciona o '-' como caracter lido
mov dword edx, [ebp+8]  ;Bota em edx o endereço da variavel que será colocado a leitura do inteiro
sub dword [edx], 1  ;Subtrai 1 do numero inteiro
xor dword [edx], 0xFFFFFFFF ;Faz o 'Ou' exclusivo, adicionando o negativo

FimLeituraInteiro: mov dword eax, [ebp-4]    ;Bota em eax a quantidade de caracteres lidos
mov dword esp, ebp    ;Apaga todos os itens da pilha
pop dword ebp       ;Restaura o valor de ebp
ret 4


EscreverInteiro: push dword ebp
mov ebp, esp
mov eax, [ebp+8]
mov eax, [eax]
sub ebx, ebx
push dword ebx
cdq
cmp edx, 0
je GetNumPortionToPrint

xor dword eax, 0xFFFFFFFF
add dword eax, 1
push dword eax
mov dword edx, 45
push dword edx
mov dword eax, ebp
sub dword eax, 12
mov edx, 1
mov dword ecx, eax
mov ebx, 1
mov eax, 4
int 0x80
add dword esp, 4
pop dword eax
add dword [ebp-4], 1
sub ebx, ebx
GetNumPortionToPrint: add ebx, 4
mov ecx, 10
cdq
div dword ecx
push dword edx
cmp eax, 0
jg GetNumPortionToPrint
printNumberByNumber:

add dword [ebp - 4], 1
sub dword ebx, 4
pop dword eax
push dword ebx
add dword  eax, 48
push dword eax
mov edx, 1
mov dword ecx, esp
mov ebx, 1
mov eax, 4
int 0x80
add dword esp, 4
pop dword ebx
cmp ebx, 0
jne printNumberByNumber
call EscreveEnter
pop dword eax
add dword eax, 1
pop dword ebp
ret 4

LeerChar: push dword ebp
mov ebp, esp
mov edx, 1
mov ecx, [ebp+8]
mov ebx, 0
mov eax, 3
int 80h
pop dword ebp
mov dword eax, 1
ret 4

EscreveEnter: push dword ebp
mov ebp, esp
push dword 0xA
mov dword eax, ebp
sub dword eax, 4
mov edx, 1
mov dword ecx, eax
mov ebx, 1
mov eax, 4
int 0x80
add dword esp, 4
pop dword ebp
ret
