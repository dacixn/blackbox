# Blackbox documentation
### Info
Syntax is Intel assembly-like (DST, SRC).\
Labels start with a period (.) and end with a colon (:) (.label:)\
The interpreter now uses a heap-backed stack that is initially allocated with 16384 elements\
Each stack element is a 64-bit integer (`int64_t`), so the initial heap allocation is 16384 × 8 = 131072 bytes (128 KiB).\
The stack grows automatically when needed using a 1.5× growth policy. The interpreter also exposes an `ALLOC` opcode to explicitly reserve stack capacity.\
There are 99 registers from R0-R98. The CMP flag/result is stored in `R98`.
### Calls/Opcodes:
| Instruction | Description                              | Operands                     | Notes                                           |
| ----------- | ---------------------------------------- | ---------------------------- | ----------------------------------------------- |
| `WRITE`     | Write a string to a stream               | `<stream number> "<string>"` | `stream number = 1` for stdout, `2` for stderr  |
| `NEWLINE`   | Prints a newline                         | None                         | Equivalent to `\n`                              |
| `PRINT`     | Print a single character                 | `<char>`                     | Example: `PRINT 'A'`                            |
| `PUSH`      | Push 32-bit integer or reg to the stack  | `<value or register>`        | Stack grows; check for overflow                 |
| `POP`       | Pop the top of the stack into a register | `<register>`                 | Stack shrinks; check for underflow              |
| `MOV`       | Move a value into a register             | `<dst>, <src>`               | `<src>` can be immediate or another register    |
| `ADD`       | Add two registers                        | `<dst>, <src>`               | `dst = dst + src`                               |
| `SUB`       | Subtract two registers                   | `<dst>, <src>`               | `dst = dst - src`                               |
| `MUL`       | Multiply two registers                   | `<dst>, <src>`               | `dst = dst * src`                               |
| `DIV`       | Divide two registers                     | `<dst>, <src>`               | `dst = dst / src`, division by zero is an error |
| `PRINT_REG` | Print integer value of a register        | `<register>`                 | Outputs decimal number                          |
| `JMP`       | Jump unconditionally                     | `<label>`                    | Sets PC to the label’s address                  |
| `JZ`        | Jump if register is zero                 | `<register>, <label>`        | Conditional branch                              |
| `JNZ`       | Jump if register is non-zero             | `<register>, <label>`        | Conditional branch                              |
| `HALT`      | Stop program execution                   | None                         | Ends the program                                |
| `INC`       | Increment register by one                | `<register>`                 | `<register> + 1`                                |
| `DEC`       | Decrement register by one                | `<register>`                 | `<register> - 1`                                |
| `CMP`       | Compare 2 registers                      | `<register>, <register>`     | Subtracts the registers, if bigger than 0, R8=1 |
| `ALLOC`     | Reserve stack capacity (bytes)           | `<bytes>`                    | |