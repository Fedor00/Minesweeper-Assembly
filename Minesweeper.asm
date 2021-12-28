.386
.model flat, stdcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;includem biblioteci, si declaram ce functii vrem sa importam
includelib msvcrt.lib
extern exit: proc
extern malloc: proc
extern memset: proc
extern printf: proc
extern time: proc
extern rand: proc
extern srand: proc
includelib canvas.lib
extern BeginDrawing: proc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;declaram simbolul start ca public - de acolo incepe executia
public start
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;sectiunile programului, date, respectiv cod
.data
;aici declaram date

include date_in.inc
include digits.inc
include letters.inc
include Bomba.inc
.code
; procedura make_text afiseaza o litera sau o cifra la coordonatele date
; arg1 - simbolul de afisat (litera sau cifra)
; arg2 - pointer la vectorul de pixeli
; arg3 - pos_x
; arg4 - pos_y
include functii.inc
start:
	;alocam memorie pentru zona de desenat
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov area, eax
	mov eax,area_height
	mov ecx,symbol_height_char
	div ecx
	mov patratele_height,eax
	sub patratele_height,2			;inaltimea matricii de joc
	mov edx,0
	mov eax,area_width				;latimea matricii de joc
	mov ecx,symbol_height_char
	div ecx
	mov iteratii_coloane,eax
	mov eax, iteratii_coloane
	mov ebx, patratele_height
	mul ebx
	;mov marime,eax
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov zona_bombe,eax
	memset_macro iteratii_coloane,patratele_height,zona_bombe
	generare_n_numere nr_bombe2
	initialize nr_bombe1
	
	mov eax, 10
	mov ebx, 10
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov expansion_matrix,eax
	
	mov eax, 10
	mov ebx, 10
	mul ebx
	shl eax, 2
	push eax
	push 0
	push expansion_matrix
	call memset
	add esp, 12
	
	;apelam functia de desenare a ferestrei
	; typedef void (*DrawFunc)(int evt, int x, int y);
	; void __cdecl BeginDrawing(const char *title, int width, int height, unsigned int *area, DrawFunc draw);
	push offset draw
	push area
	push area_height
	push area_width
	push offset window_title
	call BeginDrawing
	add esp, 20
	
	;terminarea programului
	push 0
	call exit
end start
