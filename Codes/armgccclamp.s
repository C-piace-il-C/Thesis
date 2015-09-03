movs    r2, #0       ;r2 <- 0
ldr     r3, [sp, #4] ;r3 <- val
cmp     r3, r2       ;CPSR <- r3-r2
itt     lt           ;enable lt
movlt   r3, r2       ;r3 <- r2 
strlt   r3, [sp, #4] ;val <- r3
ldr     r2, [sp, #4] ;r2 <- val
ldr     r3, [sp, #12];r3 <- maxVal
cmp     r2, r3       ;CPSR <- r2-r3
itt     gt           ;enable gt
ldrgt   r3, [sp, #12];r3 <- maxVal
strgt   r3, [sp, #4] ;val <- r3

