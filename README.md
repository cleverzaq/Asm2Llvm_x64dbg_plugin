<br/>
<p align="center">
  <h1 align="center">Asm2LLVM - Convert machine code to LLVM IR</h1>
</p>

## About the project

**Asm2LLVM** is a library for convert x86-64 machine code to LLVM IR.</br>
The LLVM IR can be optimized and compiled again for the x86_64 target and executed but with better performance.</br>
The LLVM IR contains the virtual CPU registers.

## Available functions

- Converting x86-64 machine code to LLVM IR using bddisasm
- LLVM IR to x86_64 using AsmJit
- x64dbg plugin

## Example of conversion

![Screen Shot](Test/example.png)