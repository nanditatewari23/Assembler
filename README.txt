 
			Nandita Tewari	CSE B		5th Sem		Roll no. 33	2007494
	

** The project done is Assembler.
** The code should be compiled in Codeblocks.
** INSTRUCTIONS-->

		1. You cannot leave any line without any label. If you do not want to use any label in a line, you have to use "##".
		2. As we normally use BYTE with X and C in SIC, we have defined two new mnemonics CHAR and HEX 
		   HEX will treat the operand as a hexadecimal.
		   CHAR will treat the operand as a character.
		3. Instruction Format of our assembler: 
			8 bit opcode|16 bit address
		   We are not using index adressing.
	           HEX C1 --> C1
		   CHAR CAB --> 676566
		4. Program should start with START statement and ends with END statement.
		5. PROGRAM STRUCTURE: 
				label("##" for no label) mnemonic OPERAND
		6. The program has an external file "opcode.txt" which contains all mnemonics with their codes.
		
	The program contains 2 header files(user defined):-

		1. Assemble.h: it contains:
					a) pass1(): performs addressing, mnemonic verification, SYMTAB entry
					b) pass2(): calculates object code
					c) interf(): write intermediate file (mid.txt)
					d) mainp(): call several functions according to the procedure
		2. Read.h: it contains:
				     	a)functions used to read differnet files:
						1)sym
						2)ob
						3)op
						4)mid
					b) read main: menu to read text files 
 
** Thanks To Dr. Devesh Pratap Singh for guiding us through the Project.
** A Special Thanks to Hon. HOD Sir for giving us such an oppurtunity.
