ldr     r2, [sp, #12]
ldr     r3, [sp, #4]
bics    r3, r3, r3, asr #31
itt     pl
cmppl   r3, r22
movpl   r3, r2
str     r3, [sp, #4]
