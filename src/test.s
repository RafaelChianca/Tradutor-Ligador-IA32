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
	push dword	B	
	call	LeerInteiro	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	call	EscreverInteiro	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	call	LeerChar	
	mov dword	ebx,	esp
	sub dword	ebx,	4
	push dword	eax	
	push dword	B	
	call	EscreverChar	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	call	LerHexa	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	call	EscreverHexa	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	push dword	[H]	
	call	LeerString	
	pop dword	eax	
	push dword	eax	
	push dword	B	
	push dword	[H]	
	call	EscreverString	
	pop dword	eax	
	mov	eax,	1
	mov	ebx,	0
	int 80h		

LeerInteiro: push dword ebp      
mov ebp, esp	    
push dword 0        
push dword 0        
mov dword eax, esp  
sub dword eax, 4    
push dword 0        
push dword eax      
call LeerChar

add dword [ebp-4], 1 
cmp dword [esp], 45       
jne LeituraInteiroLoop

mov dword [ebp-8], 1  
add dword esp, 4      
sub dword [ebp-4], 1  
LeituraInteiroLoop: mov dword eax, esp  
sub dword eax, 4    
push dword 0        
push dword eax      
call LeerChar

add dword [ebp-4], 1 
cmp dword [esp], 0xA       
jne LeituraInteiroLoop  
add dword esp, 4      
mov dword eax, 1      
mov dword ecx, [ebp-4]  
sub dword ecx, 1      
mov dword edx, [ebp+8]  
mov dword [edx], 0 
TransformaEmInteiro: pop dword ebx       
sub dword ecx, 1    
sub dword ebx, 0x30 
push dword eax      
imul dword ebx      
mov dword edx, [ebp+8]  
add dword [edx], eax  
pop dword eax     
mov dword ebx, 10 
imul dword ebx    
cmp dword ecx, 0  
jne TransformaEmInteiro

cmp dword [ebp-8], 0  
je  FimLeituraInteiro

add dword [ebp-4], 1  
mov dword edx, [ebp+8]  
sub dword [edx], 1  
xor dword [edx], 0xFFFFFFFF 
FimLeituraInteiro: mov dword eax, [ebp-4]    
mov dword esp, ebp    
pop dword ebp       
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
printNumberByNumber: add dword [ebp - 4], 1    
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

EscreverChar: push dword ebp            
mov ebp, esp			  
mov eax, [ebp+8]          
mov edx, 1                
mov dword ecx, eax        
mov ebx, 1                
mov eax, 4                
int 0x80                  
call EscreveEnter		  
pop dword ebp			  
mov dword eax, 2          
ret 4				      
LerHexa: enter 4,0

mov dword [ebp-4], 0
mov dword ebx, [ebp+8]
LeituraHexaLoop: push ebx 
push ebx 
call LeerChar

pop ebx 
cmp dword [ebx], 0xA 
je FimLeituraHexa

add dword [ebp-4], 0x1 
cmp dword [ebx], 0x40  
jb  DigitoNumerico

add dword ebx, 0x1 
cmp dword [ebp-4], 0x9 
jb LeituraHexaLoop

DigitoNumerico: sub dword [ebx], 0x30 
add dword ebx, 0x1 
cmp dword [ebp-4], 0x9 
jb LeituraHexaLoop

FimLeituraHexa: mov eax, dword[ebp-4] 
leave

ret 8 
EscreverHexa:  enter 0,0

mov dword ebx, [ebp+8] 
push dword 0	
loop3: push ebx 
push ebx 
call EscreverCharSemEnter

pop ebx 
add dword [esp], 1	
cmp byte [ebx], 0xA

je  FimDoHexa

add ebx, 0x1 
loop loop3 
add dword [esp], 1	
call EscreveEnter		  
FimDoHexa: mov eax, [esp] 
leave

ret 8

LeerString:  enter 4,0

mov dword [ebp-4], 0 
mov dword ebx, [ebp+12] 
mov dword ecx, [ebp+8] 
loop2: push ecx 
push ebx 
push ebx 
call LeerChar

pop ebx 
pop ecx 
add dword [ebp-4], 0x1 
cmp dword [ebx], 0x0A 
je retorno2

add dword ebx, 0x1 
cmp dword [ebp-4], ecx 
jb loop2

retorno2: mov eax, dword[ebp-4] 
leave

ret 8 
EscreverString:enter 0,0

mov dword ebx, [ebp+12] 
mov dword ecx, [ebp+8] 
push dword 0	
loop3: push ecx 
push ebx 
push ebx 
call EscreverCharSemEnter

pop ebx 
pop ecx 
add dword [esp], 1	
cmp byte [ebx], 0xA

je  FimDaString

add ebx, 0x1 
loop loop3 
add dword [esp], 1	
call EscreveEnter		
FimDaString: mov eax, [esp] 
leave

ret 8

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

EscreverCharSemEnter: push dword ebp            
mov ebp, esp			  
mov eax, [ebp+8]          
cmp byte [eax], 0x9      
jbe SomaNumeroChar

ImprimeChar: mov edx, 1   
mov dword ecx, eax        
mov ebx, 1                
mov eax, 4                
int 0x80                  
pop dword ebp			  
mov dword eax, 2          
ret 4				      
SomaNumeroChar: add dword  [eax], 0x30	      
jmp ImprimeChar

