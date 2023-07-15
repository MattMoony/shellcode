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
  push  rbp
  mov   rbp, rsp
  sub   rsp, 0x8

  ; prepare syscall
  xor   rsi, rsi
  xor   rdx, rdx
  mov   DWORD [rsp+0x4], 0x68732f
  mov   DWORD [rsp], 0x6e69622f
  mov   rdi, rsp
  mov   al, 0x3b
  syscall

  ; end like any other function
  add   rsp, 0x8
  pop   rbp
  ret
