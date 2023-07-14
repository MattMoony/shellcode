; naive prime computation up to a certain limit
; could perhaps be useful to waste some time without
; using something like "sleep" - could perhaps evade
; some memory scanning techniques
;
; author @m4ttm00ny

section .data

section .bss

section .text
  global _start

_start:
  ; start like any function would
  push	rbp
  mov	rbp, rsp
  sub	rsp, 0x20

  ; number up to which to compute primes
  ; is moved into RDI - you could alter this
  ; part of the shellcode before writing it into
  ; memory, in order to adjust the time wasted
  mov	rdi, 0x20000
  
  ; setup stuff for prime computation
  ; R10 ... number currently being checked
  ; R11 ... total number of primes found
  mov	r10b, 0x2
  xor	r11, r11
  
_compute_primes:
  ; check if already at limit
  cmp	r10, rdi
  jae	_done_computing_primes
  xor 	r12, r12

_inner_prime_check:
  cmp	r12, r10
  jae	_is_prime
  
  ; actually compute modulus
  xor	rdx, rdx
  mov	rax, r10
  div	r12
  
  ; and check it
  test	rdx, rdx
  je	_continue_computing_primes

  inc	r12
  jmp	_inner_prime_check

_is_prime:
  ; wow, found one
  inc	r11

_continue_computing_primes:
  ; yeah, continue
  inc	r10
  jmp	_compute_primes

_done_computing_primes:
  ; exit like any function would
  add 	rsp, 0x20
  pop	rbp
  ret
