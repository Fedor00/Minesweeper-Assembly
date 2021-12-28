felicitari_ati_castigat macro
make_text_macro 'F', area,50,40	
make_text_macro 'E', area,60,40	
make_text_macro 'L', area,70,40	
make_text_macro 'I', area,80,40	
make_text_macro 'C', area,90,40	
make_text_macro 'I', area,100,40	
make_text_macro 'T', area,110,40	
make_text_macro 'A', area,120,40	
make_text_macro 'R', area,130,40	
make_text_macro 'I', area,140,40	
endm
simbol macro symbol,drawArea,x,y    											;macro care afiseaza o bomba sau diferite simboluri
	push y
	push x
	push drawArea
	push symbol
	call make_symbol
	add esp, 16
endm
initialize macro bombe
local loop9                  													;macro pentru umplere zona cu bombe
	mov eax,zona_bombe
	mov ecx,number_of_bombs
	loop9:
	dec ecx
	mov ebx,[vec_rand_n+ecx*4]
	mov dword ptr[eax+ebx*4],1
	cmp ecx,0
	jne loop9
endm

make_text proc               													; functie pentru afisare cifre si litere
	push ebp
	mov ebp, esp
	pusha
	mov eax, [ebp+arg1] ; citim simbolul de afisat
	cmp eax, 'A'
	jl make_digit
	cmp eax, 'Z'
	jg make_digit
	sub eax, 'A'
	lea esi, letters
	mov symbol_width,10
	jmp draw_text
make_digit:
	cmp eax, 0
	jl make_space
	cmp eax, 9
	jg make_space
	lea esi, digits
	mov symbol_width,20
	jmp draw_text
make_space:	
	mov eax, 26 ; de la 0 pana la 25 sunt litere, 26 e space
	lea esi, letters
	
draw_text:
	mov ebx, symbol_width
	mul ebx
	mov ebx, symbol_height
	mul ebx
	add esi, eax
	mov ecx, symbol_height
bucla_simbol_linii:
	mov edi, [ebp+arg2] ; pointer la matricea de pixeli
	mov eax, [ebp+arg4] ; pointer la coord y
	add eax, symbol_height
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] ; pointer la coord x
	shl eax, 2 ; inmultim cu 4, avem un DWORD per pixel
	add edi, eax
	push ecx
	mov ecx, symbol_width
bucla_simbol_coloane:
	cmp byte ptr [esi], 0
	je simbol_pixel_alb
	mov dword ptr [edi], 0FFFFFFH
	jmp simbol_pixel_next
simbol_pixel_alb:
	mov dword ptr [edi], 036543EH
	jmp simbol_pixel_next
simbol_pixel_next:
	inc esi
	add edi, 4
	loop bucla_simbol_coloane
	pop ecx
	loop bucla_simbol_linii
	popa
	mov esp, ebp
	pop ebp
	ret
make_text endp

make_symbol proc															;functie pentru afisarea unei bombe si diferite simboluri
    push ebp
    mov ebp, esp
    pusha
    mov eax, [ebp+arg1] ; citim simbolul de afisat
    lea esi, Bomba
    cmp eax, 0
    jl do_symbol
    cmp eax, 9
    jg do_symbol
    sub eax, 0
    jmp deseneaza_simbol
do_symbol:    
    mov eax, 26 ; de la 0 pana la 25 sunt litere, 26 e space
    lea esi, letters
deseneaza_simbol:
    mov ebx, symbol_width_char
    mul ebx
    mov ebx, symbol_height_char
    mul ebx
    shl eax, 2
    add esi, eax
    mov ecx, symbol_height_char
bucla_linii:
    mov edi, [ebp+arg2] ; pointer la matricea de pixeli
    mov eax, [ebp+arg4] ; pointer la coord y
    add eax, symbol_height_char
    sub eax, ecx
    mov ebx, area_width
    mul ebx
    add eax, [ebp+arg3] ; pointer la coord x
    shl eax, 2 ; inmultim cu 4, avem un DWORD per pixel
    add edi, eax
    push ecx
    mov ecx, symbol_width_char
bucla_coloane:
    mov eax, [esi]
    mov dword ptr [edi], eax
    add esi, 4
    add edi, 4
    loop bucla_coloane
    pop ecx
    loop bucla_linii
    popa
    mov esp, ebp
    pop ebp
    ret
make_symbol endp	
make_text_macro macro symbol, drawArea, x, y          							; un macro ca sa apelam mai usor desenarea cifrelor/literelor
	push y
	push x
	push drawArea
	push symbol
	call make_text
	add esp, 16
endm
afisare_nr_bombe macro g                            							 ;macro pentru afisarea numarului de bombe in butonul din dreapta sus
mov ebx, 10
	mov eax, nr_bombe1
	;cifra unitatilor
	mov edx, 0
	div ebx
	add edx, 0
	make_text_macro edx, area, area_width-30, 10
	;cifra zecilor
	mov edx, 0
	div ebx
	add edx, 0
	make_text_macro edx, area, area_width-50, 10
endm
afisare_timp macro counter         													;;macro pentru afisarea timpului in butonul din stanga
mov edx,0
	cmp counter,5
	jne nu_afisare_timp
	add secunde,1
	mov counter,0
	mov ebx, 10
	mov eax, secunde
	;cifra unitatilor:
	mov edx, 0
	div ebx
	add edx, 0
	make_text_macro edx, area, 40, 10
	;cifra zecilor
	mov edx, 0
	div ebx
	add edx, 0
	make_text_macro edx, area, 20, 10
	;cifra sutelor
	mov edx, 0
	div ebx
	add edx, 0
	make_text_macro edx, area, 0, 10
endm

macro_verifica_bomba macro a, b
	push a
	push b
	call verifica_bomba
endm
pozitia_in_matricea_de_joc proc
	push ebp
	mov ebp, esp
	mov eax, [ebp+arg2]
	mov edx,0
	mov ecx,20
	div ecx
	mov ebx,eax
	sub ebx,2
	mov edx,0
	mov ecx,20
	mov eax,[ebp+arg1]
	div ecx
	mov ecx, iteratii_coloane
	mul ecx
	add eax,ebx
	shl eax,2
	add eax,zona_bombe
	mov esp, ebp
	pop ebp
	ret 8
pozitia_in_matricea_de_joc endp
expansion_function proc
	push ebp
	mov ebp, esp
	mov eax, [ebp+arg2]
	mov edx,0
	mov ecx,20
	div ecx
	mov ebx,eax
	sub ebx,2
	mov edx,0
	mov ecx,20
	mov eax,[ebp+arg1]
	div ecx
	mov ecx, iteratii_coloane
	mul ecx
	add eax,ebx
	shl eax,2
	mov ebx,eax
	mov esp, ebp
	pop ebp
	ret 8
expansion_function endp
verifica_bomba proc ; eax,ebx eax=y,ebx=x   										; functie care verifica daca e bomba la coordonatele click ului/aleese
	push ebp
	mov ebp, esp
	mov eax, [ebp+arg2]
	mov edx,0
	mov ecx,20
	div ecx
	mov ebx,eax
	sub ebx,2
	mov edx,0
	mov ecx,20
	mov eax,[ebp+arg1]
	div ecx
	mov ecx, iteratii_coloane
	mul ecx
	add eax,ebx
	shl eax,2
	add eax,zona_bombe
	cmp dword ptr[eax],1
	je este_bomba
	mov ebx,-1
	jmp out_
	este_bomba:
	mov ebx,1
	out_:
	mov esp, ebp
	pop ebp
	ret 8
verifica_bomba endp
apel2 macro x,y,format        														; macro care apeleaza o functie cu 2 argumente
	push x
	push y
	push format
	call printf
	add esp,12
endm
random_numere  PROC              													 ; functie care genereaza un numar random
	push ebp
	mov ebp, esp
	call rand
	mov esp, ebp
	pop ebp
	ret 0
random_numere  ENDP
memset_macro macro iteratii_coloane,patratele_height,zona_bombe						; macro pentru setarea pixelilor la o anumita culoare
mov eax, iteratii_coloane
	mov ebx, patratele_height
	mul ebx
	shl eax, 2
	push eax
	push 0
	push zona_bombe
	call memset
endm
buton_middle macro																	; macro pentru afisarea butonului din mijloc (reset)
	simbol 4,area,60,0
	simbol 4,area,80,0
	simbol 4,area,100,0
	simbol 4,area,60,20
	simbol 4,area,80,20
	simbol 4,area,100,20
	simbol 4,area,120,20
	simbol 4,area,120,0
endm
buton_middle_sad macro																	; macro pentru afisarea butonului din mijloc la pierderea jocului (reset)
	simbol 6,area,60,0
	simbol 6,area,80,0
	simbol 6,area,100,0
	simbol 6,area,60,20
	simbol 6,area,80,20
	simbol 6,area,100,20
	simbol 6,area,120,20
	simbol 6,area,120,0
endm
generare_n_numere macro n  															;macro care genereaza n numere intre 0-100 si le salveaza intr un vector
local loop_generare,verifica, nu_decrementare
	push 0
	call time
	add esp,4
	push eax
	call srand
	add esp,4
	loop_generare:
	dec n
	nu_decrementare:
	call random_numere
	mov ecx,100
	div ecx
	mov ecx,number_of_bombs
	verifica:
	dec ecx
	cmp [vec_rand_n+ecx*4],edx
	je nu_decrementare
	cmp ecx,0
	jne verifica
	mov ecx,n
	mov [vec_rand_n+ecx*4],edx
	cmp n,0
	jne loop_generare
endm
game_over macro																		;macro care afiseaza pe ecran "GAME OVER"
	make_text_macro 'G', area, 60, 120
	make_text_macro 'A', area, 70, 120
	make_text_macro 'M', area, 80, 120
	make_text_macro 'E', area, 90, 120
	
	make_text_macro 'O', area, 120, 120
	make_text_macro 'V', area, 130, 120
	make_text_macro 'E', area, 140, 120
	make_text_macro 'R', area, 150, 120
endm
afisare_toate_bombele proc 
	push ebp
	mov ebp, esp
	mov patratele_height,10
	mov patratele_width,10
	loop_linie:
	mov eax,linie
	cmp eax,area_height
	mov ecx,iteratii_coloane
	mov patratele_width,ecx
	loop_coloanaa:
	push linie
	push coloana	
	call verifica_bomba
	cmp ebx,1
	jne nu_este
	simbol 0,area,coloana,linie
	nu_este:
	add coloana,20
	sub patratele_width,1
	cmp patratele_width,0
	jne loop_coloanaa
	mov coloana,0
	add linie,20
	sub patratele_height,1
	cmp patratele_height,0
	jne loop_linie
	mov linie,40
	mov esp, ebp
	pop ebp
	ret
afisare_toate_bombele endp
do_interface proc										; functie care printeaza  interfata jocului la inceput si la reset
	push ebp
	mov ebp, esp
	buton_middle
	loop_linie:
	mov eax,linie
	cmp eax,area_height
	;jge done
	mov ecx,iteratii_coloane
	mov patratele_width,ecx
	loop_coloanaa:
	simbol 1,area,coloana,linie
	add coloana,20
	sub patratele_width,1
	cmp patratele_width,0
	jne loop_coloanaa
	mov coloana,0
	add linie,20
	sub patratele_height,1
	cmp patratele_height,0
	jne loop_linie
	mov linie,40
	mov esp, ebp
	pop ebp
	ret
do_interface endp
aflare_care_patratel proc														;functie care afla care patratel a fost selectat(coordonate)
	push ebp
	mov ebp, esp
	mov edx,0
	mov eax,[ebp+arg1]
	mov ecx,20
	mov ebx,eax
	inc ebx
	loop1:
	mov edx,0
	sub ebx,1
	mov eax,ebx
	div ecx
	cmp edx,0
	jne loop1
	push ebx
	mov eax,[ebp+arg2]
	mov ebx,eax
	inc ebx
	loop2:
	mov edx,0
	sub ebx,1
	mov eax,ebx
	div ecx
	cmp edx,0
	jne loop2
	;ok:
	mov eax,ebx
	pop ebx
	mov esp, ebp
	pop ebp
	ret 8
aflare_care_patratel endp
how_many_neghbours proc  											; functie care afiseaza numarul de bombe adiacente la patratul selectat
	push ebp
	mov ebp, esp
	mov eax,[ebp+arg1]
	mov ebx,[ebp+arg2]
	mov ecx,[ebp+arg3]
	cmp ecx,0
	je gicolo
	make_text_macro ecx,area,eax,ebx
	jmp finish
	gicolo:
	simbol 7,area,eax,ebx
	finish:
	mov esp, ebp
	pop ebp
	ret 12
how_many_neghbours endp
line_horizontal macro x, y, len, color
    local bucla_linie
    mov ebx, area_width
    mov eax, y
    mul ebx
    add eax, x
    shl eax, 2
    add eax, area
    mov ecx, len
bucla_linie:
    mov ebx, color
    mov dword ptr [eax], ebx
    add eax, 4
    loop bucla_linie
endm
draw_rectangle proc
    push ebp
    mov ebp, esp
    push esi
    cmp dword ptr [ebp+arg1], 0
    jl eroare
    mov eax, area_width
    sub eax, [ebp+arg3]
    cmp dword ptr [ebp+arg1], eax
    jg eroare
    cmp dword ptr [ebp+arg2], 0
    jl eroare
    mov eax, area_height
    sub eax, [ebp+arg4]
    cmp dword ptr [ebp+arg2], eax
    jg eroare
    xor ecx,ecx
    mov esi, [ebp+arg1]
bucla_orizontal:
    cmp ecx, [ebp+arg4]
    jge over_bucla_orizontal
    push ecx
    line_horizontal esi, [ebp+arg2], [ebp+arg3], [ebp+arg5]
    pop ecx
    add esi, area_width
    inc ecx
    jmp bucla_orizontal
over_bucla_orizontal:
    xor eax, eax
    jmp final
eroare:
   
    mov eax, -1
final:
    pop esi
    pop ebp
    ret
draw_rectangle endp

nr_bombe_vecine proc  													; fucntie care verifica toti vecinii unui patrat
	push ebp
	mov ebp, esp
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	push eax
	push ebx
	call expansion_function
	mov eax, expansion_matrix
	cmp dword ptr [ebx+eax], 2
	je gata
	mov dword ptr[ebx+eax],2
	add variabila_castiga,1
	mov ecx,8
	loop2:
	dec ecx
	mov [maybe_yes+ecx*4],-1
	mov [maybe_yes2+ecx*4],-1
	cmp ecx,0
	jne loop2
	mov neighbout_bombs_nr,0
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	
	add ebx,20
	cmp ebx,area_width
	je over
	mov [maybe_yes+0],eax
	mov [maybe_yes2+0],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over
	add neighbout_bombs_nr,1
	over:
	
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	sub ebx,20
	cmp ebx,0
	jl over1
	mov [maybe_yes+4],eax
	mov [maybe_yes2+4],ebx
	macro_verifica_bomba  eax,ebx
	cmp ebx,1
	jne over1
	add neighbout_bombs_nr,1
	over1:
	
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	sub eax,20
	cmp eax,40
	jl over2
	mov [maybe_yes+2*4],eax
	mov [maybe_yes2+2*4],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over2
	add neighbout_bombs_nr,1
	over2:
	
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	add eax,20
	cmp eax,area_height
	je over3
	mov [maybe_yes+3*4],eax
	mov [maybe_yes2+3*4],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over3
	add neighbout_bombs_nr,1
	over3:
	
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	sub eax,20
	add ebx,20
	
	cmp ebx,area_width
	je over4
	cmp eax,20
	jle over4
	mov [maybe_yes+4*4],eax
	mov [maybe_yes2+4*4],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over4
	
	add neighbout_bombs_nr,1
	over4:
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	sub eax,20
	sub ebx,20
	cmp ebx,0
	jl over5
	cmp eax,20
	jle over5
	mov [maybe_yes+5*4],eax
	mov [maybe_yes2+5*4],ebx
	
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over5
	
	add neighbout_bombs_nr,1
	over5:
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	add eax,20
	sub ebx,20
	cmp eax,area_height
	jge over6
	cmp ebx,0
	jl over6
	mov [maybe_yes+6*4],eax
	mov [maybe_yes2+6*4],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over6
	add neighbout_bombs_nr,1
	over6:
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	add eax,20
	add ebx,20
	cmp eax,area_height
	jge over7
	cmp ebx, area_width
	je over7
	mov [maybe_yes+7*4],eax
	mov [maybe_yes2+7*4],ebx
	macro_verifica_bomba eax,ebx
	cmp ebx,1
	jne over7
	add neighbout_bombs_nr,1
	over7:
	mov eax, [ebp+arg1]
	mov ebx,[ebp+arg2]
	;make_text_macro ,area,ebx,eax
	push neighbout_bombs_nr
	push eax
	push ebx
	call how_many_neghbours
	cmp neighbout_bombs_nr,0
	jne gata
	mov i,-1
coordonate_vecini:
	inc i
	cmp i,8
	je gata
	mov ecx,i
	cmp [maybe_yes+ecx*4],-1
	je peste1
	cmp [maybe_yes2+ecx*4],-1
	je peste1
	push [maybe_yes+ecx*4]
	push [maybe_yes2+ecx*4]
	call expansion_function
	mov temp,ebx
	mov k,-1
	loop3:
	inc k
	mov ecx,k
	cmp [vec1+ecx*4],0
	je zero
	jmp yes
	zero:
	cmp [vec2+ecx*4],0
	je urmator
	yes:
	push [vec1+ecx*4]
	push [vec2+ecx*4]
	call expansion_function
	cmp temp,ebx
	je coordonate_vecini
	urmator:
	cmp k,99
	jne loop3
	add j,1
	mov edx,j
	mov ecx,i
	mov eax,[maybe_yes+ecx*4]
	mov ebx,[maybe_yes2+ecx*4]
	mov [vec1+edx*4],eax
	mov [vec2+edx*4],ebx
	peste1:
	cmp i,7
	jne coordonate_vecini
	gata:
	mov esp, ebp
	pop ebp
	ret 8
nr_bombe_vecine endp

toti_vecinii proc
	push ebp
	mov ebp,esp
	push [ebp+arg2]
	push [ebp+arg1]
	call nr_bombe_vecine
	cmp neighbout_bombs_nr ,0
	jne finish
	mov M,-1
	loop1:
	inc M
	mov ecx,M
	cmp [vec1+ecx*4],-1
	je finish
	;cmp [vec2+ecx*4],8
	;je loop1
	push [vec2+ecx*4]
	push [vec1+ecx*4]
	call nr_bombe_vecine
	jmp loop1
	finish:
	mov ecx,100
	looo:
	dec ecx
	mov [vec1+ecx*4],-1
	mov [vec2+ecx*4],-1
	cmp ecx,0
	jne looo
	mov j,-1
	mov esp,ebp
	pop ebp
	ret 8
toti_vecinii endp

draw proc
	push ebp
	mov ebp, esp
	pusha
	mov eax, [ebp+arg1]
	cmp eax, 1
	jz evt_click
	cmp eax, 2
	jz evt_timer ; nu s-a efectuat click pe nimic
	;mai jos e codul care intializeaza fereastra cu pixeli albi
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	push 255
	push area
	call memset
	add esp, 12
	jmp afisare_litere
evt_click:
	push [ebp+arg2]
	push [ebp+arg3]
	call aflare_care_patratel   				;aflam care patratel am selectat
	mov butX,ebx   ; linia
	mov butY,eax   ; coloana
	cmp is_game_over,-1
	je apasa_unde_nu_trebuie
	cmp ebx,40
	jl apasa_unde_nu_trebuie
	
	push butX
	push butY
	call verifica_bomba         					; verificam daca la patratelul ala exista o bomba
	cmp ebx,1
	je is_bomb
			
	push butY
	push butX
	call toti_vecinii 							   ; daca nu exista bombe, verificam la toti vecinii sai si afisam nr de bombe in patratelul selectat
	
	push butX
	push butY
	call pozitia_in_matricea_de_joc
	cmp dword ptr[eax],2
	je peste

	mov dword ptr[eax],2
	peste:
	jmp not_bomb
	is_bomb:
	call afisare_toate_bombele					   ; daca la patratelul selectat este o bomba, afisam toate bombele si mesajul 'GAME OVER', oprim timpul
	;game_over
	buton_middle_sad
	mov is_game_over,-1			
	mov stop,1 					
	not_bomb:
	apasa_unde_nu_trebuie:
	cmp butY,60
	jl finish
	cmp butY,140
	jge finish
	cmp butX,40
	jge finish
												   ; daca apasam pe buotnul din mijloc, jocul se reseteaza
	MOV variabila_castiga,0
	mov stop,0
	mov is_game_over,0
	simbol 7, area, 40, 10
	simbol 7, area, 20, 10
	simbol 7, area, 0, 10
	mov secunde,0
	mov counter,0
	mov patratele_width,10
	mov patratele_height,10
	mov coloana,0
	mov initializare,0							  ; afisam din nou prefata matricii de joc
	mov patratele_height,10
	mov eax, iteratii_coloane
	mov ebx, patratele_height
	mul ebx
	shl eax, 2
	push eax
	push 0
	push zona_bombe								  ; resetam matricea de joc
	call memset
	add esp,12
	mov eax, 10
	mov ebx, 10
	mul ebx
	shl eax, 2
	push eax
	push 0
	push expansion_matrix
	call memset
	add esp, 12
	mov ecx,number_of_bombs
	mov nr_bombe2,ecx
	generare_n_numere nr_bombe2					  ; generam dupa resetare, n numere aleatorii
	initialize nr_bombe1						  ; punem bombele la coordonatele respective
	finish:
evt_timer:
	inc counter
	jmp afisare_litere
afisare_litere:
	mov eax,nr_bombe1
	add eax, variabila_castiga
	cmp eax,100
	jne nu_ati_castigat_inca
	felicitari_ati_castigat
	mov is_game_over,-1
	jmp done
	nu_ati_castigat_inca:
	continuare:
	push 0000000h
	push 40
	push 60
	push 0
	push 140
	call draw_rectangle
	add esp,20						; afisam butonul din dreapta		
	afisare_nr_bombe nr_bombe1    	; afisam nr de bombe in dreapta sus
	;afisare timp
	cmp stop ,0
	jne nu_afisare_timp
	afisare_timp counter			; afisam timpul in stanga sus
	nu_afisare_timp:
	cmp initializare,0
	jne done
	push 0000000h
	push 40
	push 60
	push 0
	push 0
	call draw_rectangle				;afisam butonul din stanga sus
	add esp,20				
	make_text_macro 0, area, 40, 10
	make_text_macro 0, area, 20, 10
	make_text_macro 0, area, 0, 10
	call do_interface; afisam prefata matricii de joc, o singura data la inceput
	done:
	mov initializare,1
	;scriem un mesaj
final_draw:
	popa
	mov esp, ebp
	pop ebp
	ret
draw endp

