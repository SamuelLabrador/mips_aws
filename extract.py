data = """add	100000	f $d, $s, $t	$d = $s + $t
addu	100001	f $d, $s, $t	$d = $s + $t
addi	001000	f $d, $s, i	$d = $s + SE(i)
addiu	001001	f $d, $s, i	$d = $s + SE(i)
and	100100	f $d, $s, $t	$d = $s & $t
andi	001100	f $d, $s, i	$t = $s & ZE(i)
div	011010	f $s, $t	lo = $s / $t; hi = $s % $t
divu	011011	f $s, $t	lo = $s / $t; hi = $s % $t
mult	011000	f $s, $t	hi:lo = $s * $t
multu	011001	f $s, $t	hi:lo = $s * $t
nor	100111	f $d, $s, $t	$d = ~($s | $t)
or	100101	f $d, $s, $t	$d = $s | $t
ori	001101	f $d, $s, i	$t = $s | ZE(i)
sll	000000	f $d, $t, a	$d = $t << a
sllv	000100	f $d, $t, $s	$d = $t << $s
sra	000011	f $d, $t, a	$d = $t >> a
srav	000111	f $d, $t, $s	$d = $t >> $s
srl	000010	f $d, $t, a	$d = $t >>> a
srlv	000110	f $d, $t, $s	$d = $t >>> $s
sub	100010	f $d, $s, $t	$d = $s - $t
subu	100011	f $d, $s, $t	$d = $s - $t
xor	100110	f $d, $s, $t	$d = $s ^ $t
xori	001110	f $d, $s, i	$d = $s ^ ZE(i)
lhi	011001	o $t, immed32	HH ($t) = i
llo	011000	o $t, immed32	LH ($t) = i
slt	101010	f $d, $s, $t	$d = ($s < $t)
sltu	101001	f $d, $s, $t	$d = ($s < $t)
slti	001010	f $d, $s, i	$t = ($s < SE(i))
sltiu	001001	f $d, $s, i	$t = ($s < SE(i))
beq	000100	o $s, $t, label	if ($s == $t) pc += i << 2
bgtz	000111	o $s, label	if ($s > 0) pc += i << 2
blez	000110	o $s, label	if ($s <= 0) pc += i << 2
bne	000101	o $s, $t, label	if ($s != $t) pc += i << 2
j	000010	o label	pc += i << 2
jal	000011	o label	$31 = pc; pc += i << 2
jalr	001001	o labelR	$31 = pc; pc = $s
jr	001000	o labelR	pc = $s
lb	100000	o $t, i ($s)	$t = SE (MEM [$s + i]:1)
lbu	100100	o $t, i ($s)	$t = ZE (MEM [$s + i]:1)
lh	100001	o $t, i ($s)	$t = SE (MEM [$s + i]:2)
lhu	100101	o $t, i ($s)	$t = ZE (MEM [$s + i]:2)
lw	100011	o $t, i ($s)	$t = MEM [$s + i]:4
sb	101000	o $t, i ($s)	MEM [$s + i]:1 = LB ($t)
sh	101001	o $t, i ($s)	MEM [$s + i]:2 = LH ($t)
sw	101011	o $t, i ($s)	MEM [$s + i]:4 = $t
mfhi	010000	f $d	$d = hi
mflo	010010	f $d	$d = lo
mthi	010001	f $s	hi = $s
mtlo	010011	f $s	lo = $s
trap	011010	o i	Dependent on OS; different values for immed26 specify different operations."""


data = """add	Add	R	0x00	0x20
addi	Add Immediate	I	0x08	NA
addiu	Add Unsigned Immediate	I	0x09	NA
addu	Add Unsigned	R	0x00	0x21
and	Bitwise AND	R	0x00	0x24
andi	Bitwise AND Immediate	I	0x0C	NA
beq	Branch if Equal	I	0x04	NA
blez	Branch if Less Than or Equal to Zero	I	0x06	NA
bne	Branch if Not Equal	I	0x05	NA
bgtz	Branch on Greater Than Zero	I	0x07	NA
div	Divide	R	0x00	0x1A
divu	Unsigned Divide	R	0x00	0x1B
j	Jump to Address	J	0x02	NA
jal	Jump and Link	J	0x03	NA
jr	Jump to Address in Register	R	0x00	0x08
lb	Load Byte	I	0x20	NA
lbu	Load Byte Unsigned	I	0x24	NA
lhu	Load Halfword Unsigned	I	0x25	NA
lui	Load Upper Immediate	I	0x0F	NA
lw	Load Word	I	0x23	NA
mfhi	Move from HI Register	R	0x00	0x10
mthi	Move to HI Register	R	0x00	0x11
mflo	Move from LO Register	R	0x00	0x12
mtlo	Move to LO Register	R	0x00	0x13
mfc0	Move from Coprocessor 0	R	0x10	NA
mult	Multiply	R	0x00	0x18
multu	Unsigned Multiply	R	0x00	0x19
nor	Bitwise NOR (NOT-OR)	R	0x00	0x27
xor	Bitwise XOR (Exclusive-OR)	R	0x00	0x26
or	Bitwise OR	R	0x00	0x25
ori	Bitwise OR Immediate	I	0x0D	NA
sb	Store Byte	I	0x28	NA
sh	Store Halfword	I	0x29	NA
slt	Set to 1 if Less Than	R	0x00	0x2A
slti	Set to 1 if Less Than Immediate	I	0x0A	NA
sltiu	Set to 1 if Less Than Unsigned Immediate	I	0x0B	NA
sltu	Set to 1 if Less Than Unsigned	R	0x00	0x2B
sll	Logical Shift Left	R	0x00	0x00
srl	Logical Shift Right (0-extended)	R	0x00	0x02
sra	Arithmetic Shift Right (sign-extended)	R	0x00	0x03
sub	Subtract	R	0x00	0x22
subu	Unsigned Subtract	R	0x00	0x23
sw	Store Word	I	0x2B	NA"""

data = data.split('\n')

opcodes = list()

for line in data:
	tab = line.find('\t')
	opcode = line[:tab].upper()
	
	tab = line.find('\t', tab + 1)
	tab = line.find('\t', tab + 1)
	prev = tab + 1
	tab = line.find('\t', tab + 1)

	opcode_bits = line[prev:tab].replace('0x', '')

	value = int(opcode_bits, 16)
	funct = 0

	if value == 0:
		prev = tab + 1
		funct_bits = (line[prev:])
		funct = int(funct_bits, 16)

	opcodes.append((opcode, value, funct))

print("switch(opcode){\n\tcase ALU:\n\t\tswitch(funct){")
for opcode in opcodes:
	if opcode[1] == 0:
		print("\t\t\tcase {}:\n\t\t\t\tstrcpy(opcodeString->value, \"{} \");\n\t\t\t\topcodeString->size = {};".format(opcode[0].upper(), opcode[0], len(opcode[0]) + 1))

print("\t\t}")
for opcode in opcodes:
	if opcode[1] != 0:
		print("\tcase {}:\n\t\tstrcpy(opcodeString->value, \"{} \");\n\t\topcodeString->size = {};".format(opcode[0].upper(), opcode[0], len(opcode[0]) + 1))
print("\t\n}")