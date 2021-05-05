## Dayevska Anabel Caceres Budiel
## CCOMP 3-1

.text
.globl __start
__start:
la $a0, 0   # ptr ini de sort
la $a1, 24  # (n-1)*4 ptr fin dde sort

li $t0, 0          # nos ayuda a tener el ptr ini de max
mul $t1, $t0, 4   # $t1 ptr ini de max
la $s0, 0          # con ella haremos comparaciones para saber el val max en max
la $s1, 28          # (n)*4 ptr fin dde max

sort: 
#     a0 ptr ini       a1 ptr fin        en sort y max
#     t1 ptr ini       s1 ptr fin        en max 
#     v0 ptr           v1 valor          devuelve max 
bge $a0, $a1, endSort   #si $s0>=$s1 , si ptr ini y ptr fin chocan o ptr ini lo pasa, ya ordenaste la lista
j max                   # busco la pos y el val max

sort2:
##cambio el val max con el val del ptr fin
lw $t0,a($a1)   #$t0 tiene el num al que apunta el ptr fin 
sw $t0, a($v0)  #en la pos del ptr fin se guarda el val max 
sw $v1, a($a1)  #la pos dond e estaba el val max ahora tiene el num que tenia el ptr fin 
addi $a1, $a1, -4       # el puntero fin sube una pos hasta chocar con ini 
##limpi mis variables para entrar a buscar el val max
la $s0, 0          # con ella haremos comparaciones para saber el val max en max
li $t0, 0          # nos ayuda a tener el ptr ini de max
mul $t1, $t0, 4   # $t1 ptr ini de max
addi $s1, $s1, -4  #sube una pos para no comparar con el val max que ya pusimos 
j sort


max:
# t1 ptr ini, 
# t0 inidi ayuda a t1 
# t2 valor del ptr ini 
#ptr din a1
bge $t1, $s1, m3  #si $t0>=$s1 salta a m3, llego al limite del array, sal de la funcion 
lw $t2, a($t1)    # $t2=a[i] leemos el num en la lista
ble $t2, $s0, m2  #si $t2<=$s0 salta a m2
move $s0, $t2     # ahora $s0 tiene el valor de $t2, $s0 tiene el valor max
addi $t3, $t1, 0  # $t3 tiene la direccion del val max

m2:  #i++
addi $t1, $t1, 4  #vanzar al sig num el ptr 
b max              #regresa a la funcion m1

m3:
move $v1, $s0     #$v1 el max val
addi $v0, $t3, 0  # $v0 direccion del val max
b sort2            #regresa a sort, ya encontramos val y direccion max



endSort:
la $a0, mostrar
li $v0, 4 # print string
syscall
li $t0, 0
mul $t1,$t0,4
la $s1, 28       #saber hasta donde recorrer la lista para imprimir
j fin2

fin2:
bge $t1, $s1, fin3
lw $t2, a($t1)  # $t2= a[i] 
addi $a0, $t2,0
li $v0, 1  #muestro en pantalla el entero del array
syscall
addi $t0, $t0, 1 #recorro la matriz para imprimir
mul $t1,$t0,4
bge $t1, $s1, fin3
la $a0,coma       #a0 se le asigna la pos de la variable coma
li $v0,4          
syscall           #imprime ", " 
j fin2
fin3:   
la $a0,endl      #a0 se le asgina la pos de la variable "endl"
li $v0,4         #v0 = 4
syscall
#fin del programa
li $v0, 10
syscall 
   
.data
a: .word 1,2,1,7,10,9    #array
mostrar: .asciiz "La lista ordenada es: "
coma:    .asciiz ", "
endl:    .asciiz "\n"

