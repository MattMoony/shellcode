; launch /bin/sh using the execve syscall
; pretty straightforward
;
; author @m4ttm00ny

section .data

section .bss

section .text
  global _start

_start:
  ; start like any other function
  push  ebp
  mov   ebp, esp
  sub   esp, 0x8

  ; prepare syscall
  xor   ecx, ecx
  xor   edx, edx
  mov   DWORD [esp+0x4], 0x68732f
  mov   DWORD [esp], 0x6e69622f
  mov   ebx, esp
  mov   eax, 0x0b
  int   0x80

  ; end like any other function
  add   esp, 0x8
  pop   ebp
  ret
