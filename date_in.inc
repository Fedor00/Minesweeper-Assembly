window_title DB "MINESWEEPER",0
area_width EQU 200
area_height EQU 240
stop dd 0
area DD 0
linie dd 40
coloana dd 0
initializare dd 0
counter DD 0 ; numara evenimentele de tip timer
neighbout_bombs_nr dd 0			; aici se pune numarul de bombe adiacente a unui patrat
expansion_matrix dd 0
maybe_yes dd 8 dup(-1)
maybe_yes2 dd 8 dup(-1)
i dd 0
temporar dd 0
k dd 49
j dd -1
M dd -1				; index
vec1 dd 100 dup(-1)				; vecin coordonate  x
vec2 dd 100 dup(-1)				; vecin coordonate y
symbol_height_char equ 20
symbol_width_char equ 20
arg1 EQU 8
arg2 EQU 12
arg3 EQU 16
arg4 EQU 20
arg5 equ 24
x equ 0
y equ 0
number_of_bombs equ 12	; numarul de bombe
vec_rand_n dd number_of_bombs dup(-1)
is_game_over dd 0					; ne ajuta sa aflam daca jocul s a terminat fara succes
butX dd 0
butY dd 0
patratele_height dd 0
patratele_width dd 0
iteratii_coloane dd 0
nr_bombe dd number_of_bombs
nr_bombe1 equ number_of_bombs
nr_bombe2 dd number_of_bombs
secunde dd 0
zona_bombe dd 0
marime dd 0
lungime dd 0
zona_bombe_posibile dd 0
symbol_width dd 20						; latimea simbolurilor
symbol_height dd 20						; inaltimea simbolurilor
format db "%d-%d ",10,0
variabila_castiga dd 0					; variabla care ne ajuta sa aflam daca jocul a fost terminat cu succes
temp dd 0