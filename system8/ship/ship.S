

.text

.global ship
@
@ int ship (double x0, double y0)
@ param x0 x starting value
@ param y0 y start
@ return the number of iterations
@

@ the register use is as follows
@ r0 : iteration 
@ r1 : 255 to compare
@ r2 : address of zero
@ r3 : address of four
@ d0 : x0 
@ d1 : y0 
@ d2 : x1 / x
@ d3 : y1 / y
@ d4 : x^2
@ d5 : y^2
@ d6 : free space
@ d7 : free space / 0.0 to create negative and compare

ship:
stmfd sp!, {lr}
mov r0, #0
mov r1, #255
ldr r2, =zero
ldr r3, =four
vldr d2, [r2]
vldr d3, [r2]
vmul.f64 d4, d2, d2
vmul.f64 d5, d3, d3

loop:

cmp r0, r1
bge end                  @ checking loop conditions

vldr d6, [r3]
vadd.f64 d7, d5, d4      @ filling registers and preparing comparison   
vcmp.f64 d7, d6
vmrs APSR_nzcv, fpscr    @ moving flags
bge end                  @ checking loop conditions

b checkx

checkx:                  @ ?: check for x
vldr d7, [r2]
vcmp.f64 d2, d7
vmrs APSR_nzcv, fpscr    @ moving flags
blt negx
b checky

checky:                  @ ?: check for y
vldr d7, [r2]
vcmp.f64 d3, d7
vmrs APSR_nzcv, fpscr    @ moving flags
blt negy
b loop_cont

loop_cont:
vmul.f64 d6, d2, d3     @ x * y
vadd.f64 d7, d6, d6      @ 2xy
vadd.f64 d3, d7, d1      @ 2xy + y0 or new y

vsub.f64 d6, d4, d5      @ x^2 - y^2
vadd.f64 d2, d6, d0      @ adding on x0 and completing new x1/ x

vmul.f64 d4, d2, d2      @ new x ^ 2
vmul.f64 d5, d3, d3      @ new y ^ 2
add r0, r0, #1           @counter addition
b loop

negx:
vsub.f64 d2, d7, d2      @ subtracting 0 - x
b checky

negy:
vsub.f64 d3, d7, d3      @ subtracting 0 - y
b loop_cont

end:
ldmfd sp!, {lr}
bx lr

.data
.balign 8

zero: .double 0.0
four: .double 4.0  

