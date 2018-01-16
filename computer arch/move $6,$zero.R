move $6,$zero
b $L2
nop
$L3:
lw $3,%got(x)($28)
sll $2,$6,2
addu $2,$2,$3
lw $3,0($2)
nop
move $2,$3
sll $2,$2,1
addu $4,$2,$3
lw $3,%got(y)($28)
sll $2,$6,2
addu $2,$2,$3
lw $2,0($2)
nop
addu $4,$4,$2
lw $3,%got(y)($28)
sll $2,$6,2
addu $2,$2,$3
sw $4,0($2)
addiu$6,$6,1
$L2:
slt$2,$6,100
bne $2,$0,$L3
nop
