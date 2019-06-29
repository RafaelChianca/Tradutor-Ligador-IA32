global _start

section .data

section .bss
hexa_lido   resd    8

section .text
_start:
    push dword EAX
    push dword hexa_lido
    call LerHexa
    pop dword eax

    push dword EAX
    push dword hexa_lido
    call EscreverHexa
    pop dword eax

    mov eax, 1
    mov ebx,0
    int 80h


    LerHexa: enter 4,0
    mov dword [ebp-4], 0; zera o contador
    mov dword ebx, [ebp+8]; copia o endereço para ebx

    LeituraHexaLoop: push ebx ;salva o endereço
    push ebx ;endereço de retorno do char
    call LeerChar
    pop ebx ;recupera o endereço
    cmp dword [ebx], 0xA ;Analisa se acabou a digitação (foi digitado um 'enter')
    je FimLeituraHexa
    add dword [ebp-4], 0x1 ;Adiciona 1 ao contador de caracteres lidos
    cmp dword [ebx], 0x40  ;Analisa se o numero é superior (A,B,C,D,E,F)
    jb  DigitoNumerico
    add dword ebx, 0x1 ;aumenta o endereço em 1B
    cmp dword [ebp-4], 0x9 ;limite máximo estabelecido pelo usuário
    jb LeituraHexaLoop
    DigitoNumerico: sub dword [ebx], 0x30 ;Transforma de char em numero
    add dword ebx, 0x1 ;aumenta o endereço em 1B
    cmp dword [ebp-4], 0x9 ;limite máximo estabelecido pelo usuário
    jb LeituraHexaLoop

    FimLeituraHexa: mov eax, dword[ebp-4] ; move a quantidade lida para eax
    leave
    ret 8 ;elimina o endereço que foi gravado da pilha

    LeerChar: push dword ebp      ;Salva o valor de ebp na pilha
    mov ebp, esp	    ;Copia o valor da posição de esp para ebp
    mov edx, 1          ;Quantos caracteres serão lidos
    mov ecx, [ebp+8]    ;O endereço de onde será escrito o caracter digitado
    mov ebx, 0          ;Descritor do arquivo (stdin)
    mov eax, 3          ;Chamada do sistema 3 (sys_read)
    int 80h             ;Chamada do kernel
    pop dword ebp       ;Restaura o valor de ebp
    mov dword eax, 1    ;Bota em eax a quantidade de caracteres lidos
    ret 4



    EscreverHexa:  enter 0,0
      mov dword ebx, [ebp+8] ;copia o endereço para ebx
      push dword 0	;Bota 0 no contador de caracteres impressos

    loop3: push ebx ;salva o endereço
      push ebx ;endereço que está o char
      call EscreverCharSemEnter
      pop ebx ;recupera o endereço
      add dword [esp], 1	;Adiciona 1 no contador de caracteres impressos
      cmp dword [ebx], 0xA
      je  FimDaString
      add ebx, 0x1 ; aumenta em 1B
      loop loop3 ;se não for 0 pula
      add dword [esp], 1	;Adiciona 1 no contador de caracteres impressos
      call EscreveEnter		  ;Escreve o enter no final da impressão

    FimDaString: mov eax, [esp] ;quantidade escrita
      leave
      ret 8

      EscreverCharSemEnter: push dword ebp            ;Salva o valor de ebp na pilha
      mov ebp, esp			  ;Copia o valor da posição de esp para ebp
      mov eax, [ebp+8]          ;Coloca o conteúdo de ebp+8 em eax (endereço do conteudo a ser impresso)
      cmp byte [eax], 0x09      ;Checar se é um número (0 a 9)
      jbe SomaNumeroChar
      ImprimeChar: mov edx, 1   ;Quantos caracteres serão impressos
      mov dword ecx, eax        ;O que será impresso (eax contem o endereço do conteúdo)
      mov ebx, 1                ;Descritor do arquivo (stdout)
      mov eax, 4                ;Número de chamada do sistema (sys_write)
      int 0x80                  ;Chamada do kernel
      pop dword ebp			  ;Restaura o valor de ebp
      mov dword eax, 2          ;Retorna a quantidade de caracteres impressos em eax (1 caracter + 0xA)
      ret 4				      ;desenpilha o retorno para o PC e o argumento (numero que foi impresso)

      SomaNumeroChar:
      add dword  [eax], 0x30	      ;transforma em char numérico (soma 0x30) no conteudo a ser impresso
      jmp ImprimeChar

      EscreveEnter: push dword ebp            ;Salva o valor de ebp na pilha
      mov ebp, esp			  ;Copia o valor da posição de esp para ebp
      push dword 0xA	  		  ;Bota o caracter 'enter' na pilha (ebp-4)
      mov dword eax, ebp		  ;Bota o endereço de ebp em eax
      sub dword eax, 4          ;Posiciona o conteudo de eax para apontar para '0xA' (enter)
      mov edx, 1                ;Quantos caracteres serão impressos
      mov dword ecx, eax        ;O que será impresso (eax contem o endereço do conteúdo)
      mov ebx, 1                ;Descritor do arquivo (stdout)
      mov eax, 4                ;Número de chamada do sistema (sys_write)
      int 0x80                  ;Chamada do kernel
      add dword esp, 4		  ;Desenpilha o '0xA'
      pop dword ebp			  ;Restaura o valor de ebp
      ret
