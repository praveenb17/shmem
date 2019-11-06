void
shmemx_memcpy8(void* dst, const void* src, size_t nbytes)
{
	__asm__ __volatile__(
	"mov r24, %[src]                  \n" // this saves program space at cost of one instruction
	"mov %[src], %[nbytes]            \n"
	"lsr r3, %[nbytes], #3            \n"
	"beq .LByteHandler%=              \n"
	"orr r3, %[dst], r24              \n"
	"lsl r3, r3, #29                  \n" // No bytes, just double words
	"beq .LDwordHandler%=             \n"
	"mov %[nbytes], #8                \n"
	"lsr r3, r3, #29                  \n"
	"sub %[nbytes], %[nbytes], r3     \n" // Correction for misalignment (8-r3)
	"eor r3, %[dst], r24              \n"
	"lsl r3, r3, #29                  \n" // Can the array alignment be corrected?
	"beq .LByteHandler%=              \n"
	"mov %[nbytes], %[src]            \n" // perform full misaligned copy (slow)
	".LByteHandler%=:                 \n"
	"sub %[src], %[src], %[nbytes]    \n"
	"b .LSubtractByte%=               \n"
	".LBloop%=:                       \n"
	"ldrb r3, [r24], #1               \n"
	"strb r3, [%[dst]], #1            \n"
	".LSubtractByte%=:                \n"
	"sub %[nbytes], %[nbytes], #1     \n"
	"bgte .LBloop%=                   \n"
	".LDwordHandler%=:                \n"
	"mov %[nbytes], #7                \n" // This is here for alignment and is used below
	"lsr r3, %[src], #5               \n" // Checking number dwords >= 4
	"beq .LDremainder%=               \n"
	"gid                              \n"
	"movts lc, r3                     \n"
	"mov r3, %%low(.LDstart%=)        \n"
	"movts ls, r3                     \n"
	"mov r3, %%low(.LDend%=-4)        \n"
	"movts le, r3                     \n"
	".balignw 8,0x01a2                \n" // If alignment is correct, no need for nops
	".LDstart%=:                      \n"
	"ldrd r16, [r24], #1              \n"
	"ldrd r18, [r24], #1              \n"
	"strd r16, [%[dst]], #1           \n"
	"ldrd r20, [r24], #1              \n"
	"strd r18, [%[dst]], #1           \n"
	"ldrd r22, [r24], #1              \n"
	"strd r20, [%[dst]], #1           \n"
	"strd r22, [%[dst]], #1           \n"
	".LDend%=:                        \n"
	"gie                              \n"
	".LDremainder%=:                  \n"
	"lsl r3, %[src], #27              \n"
	"lsr r3, r3, #30                  \n"
	"beq .LDdone%=                    \n"
	".LDloop%=:                       \n"
	"sub r3, r3, #1                   \n"
	"ldrd r16, [r24], #1              \n"
	"strd r16, [%[dst]], #1           \n"
	"bne .LDloop%=                    \n"
	".LDdone%=:                       \n"
	"and %[nbytes], %[src], %[nbytes] \n"
	"sub %[src], %[nbytes], #0        \n"
	"bgt .LByteHandler%=              \n"
			: [dst] "+r" (dst), [src] "+r" (src), [nbytes] "+r" (nbytes)
			:
			: "r3", "r24",
			  "r16", "r17", "r18", "r19",
			  "r20", "r21", "r22", "r23",
			  "ls", "le", "lc", "memory"
		);
}
