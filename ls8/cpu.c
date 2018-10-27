#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  return cpu->ram[mar];
}

void cpu_ram_write(struct cpu *cpu, unsigned char mar, unsigned char mdr)
{
  cpu->ram[mar] = mdr;
}

void cpu_load(char *filename, struct cpu *cpu)
{

  FILE *fp;
  int address = 0;
  char line[1024];

  // open file
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("INVALID FILE NAME");
    return;
  }

  while (fgets(line, sizeof line, fp) != NULL) //not at eof
  {
    char *end_of_instr;
    unsigned char *data;

    data = strtol(line, &end_of_instr, 2);

    // if data != 0, save
    if (data != end_of_instr)
    {
      cpu->ram[address] = data;
      address++;
    }
    // else ignore
  }
  fclose(fp);

}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO

    unsigned char IR = cpu->ram[cpu->PC];
    unsigned char operandA = cpu->ram[cpu->PC + 1];
 
    unsigned char operandB = cpu->ram[cpu->PC + 2];
    //get opcode
    unsigned char opcode = IR;

    switch (opcode)
    {
    case LDI:
      cpu->registers[operandA] = operandB;
      cpu->PC += 3;
      break;
    case HLT:
      running = 0;
      cpu->PC += 1;
      break;
    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      cpu->PC += 2;
      break;
    case MUL:
      cpu->registers[operandA] = cpu->registers[operandA] * cpu->registers[operandB];
      cpu->PC += 3; 
      break;
    default:
      running = 0;
      printf("%s\n", "ERROR");
    }
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  memset(cpu->ram, 0, sizeof cpu->ram);             //8
  memset(cpu->registers, 0, sizeof cpu->registers); //256

  // TODO: Zero registers and RAM
}
