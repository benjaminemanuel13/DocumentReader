#include <stdio.h>
#include <stdlib.h>
#include <rs232.h>
#include <spectrum.h>

#include "codepage.c"

uint8_t byte[1];

int f;

int add = 32768;

void run()
{
	#asm
		jmp 8000
	#endasm
}

void assPut()
{
	#asm
		ld b,0x0FF
	EACH:
		push bc
		ld a, 0x41
		RST 0x0008
		DEFB 0x1E
		pop bc
		DJNZ EACH
		RET
	#endasm
}

void assGet()
{
	#asm
		XOR a
		RST 0x0008
		defb 0x31
		ld B, 0x0ff
	Each2:
		push bc
		RST 0x0008
		defb 0x1d
		rst 0x0008
		defb 0x1c
		pop bc
		djnz Each2
		ret
	#endasm
}

int poke(char v, unsigned char *address)
{
  #asm
  
  ld hl,2
  add hl,sp              ; skip over return address on stack
  ld e,(hl)
  inc hl
  ld d,(hl)              ; de = address
  inc hl
  ld a,(hl)              ; a = v, "char v" occupies 16 bits on stack
                         ;  but only the LSB is relevant
  ld (de), a
  
  ld hl,1                ; hl is the return parameter

  #endasm
}

uint8_t convert(uint8_t innumber)
{
	if(innumber >= 48 && innumber <= 57)
	{
		return innumber - 48;
	}

	return innumber -65 + 10;
}

uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

char* GetCommand()
{
	char command[250];
	command[0] = 'a';
	command[1] = 'b';
	command[2] = 'c';
	command[3] = 'd';
	command[4] = 'e';
	command[5] = 'f';
	command[6] = 'g';
	command[7] = 'h';
	command[8] = 'i';
	command[9] = 'j';
	command[10] = 'k';
	command[11] = 'l';
	command[12] = 'm';
	command[13] = 'n';
	command[14] = 'o';
	command[15] = 'p';
	command[16] = 'q';
	command[17] = 'r';
	command[18] = 's';
	command[19] = 't';
	command[20] = 'u';
	command[21] = 'v';
	command[22] = 'w';
	command[23] = 'x';
	command[24] = 'y';
	command[25] = 'z';
	command[26] = 'X';

	for(int i = 27; i < 250; i++)
	{
		command[i] = "+";
	}

	command[249] = "\n";

	return command;
}

int GetLength()
{
	uint8_t len[6];

	printf ("\nEchoing 6 bytes to length: ");
	for (f=0; f<6; f++) {
		while (rs232_get(&len[f]) != RS_ERR_OK);

		//printf("GotOne");
		//printf ("%c", len[f]);
	}

	int length = strtol(len, NULL, 10);

	printf("Document Length: ");
	printf ("%d", length);

	return length;
}

void GetDocument(int length)
{
	uint8_t doc[1];

	for (f=0; f<length; f++) {
		while (rs232_get(&doc[0]) != RS_ERR_OK);

		printf ("%c", doc[0]);
	}
}

void pause()
{
	int c, d;
   
   	for (c = 1; c <= 327; c++)
    {}
}

void main()
{
	char chr[6];

	//poke(10, 32768);

	setChars();

    printf("Hello, welcome to Bens Document Loader.\n");

    printf ("\nInitializing at 1200 baud:");
	if (rs232_params(RS_BAUD_9600 | RS_BITS_8 | RS_STOP_1, RS_PAR_NONE) != RS_ERR_OK) {
		printf ("  Error setting baud rate.  Exiting...\n");
		exit(0);
	}
	if (rs232_init() != RS_ERR_OK) {
		printf ("  Initialization error.  Exiting...\n");
		exit(0);
	}

	zx_cls();

	uint8_t command[250];
	command[0] = 'A';
	command[1] = 'B';
	command[2] = 'C';
	command[3] = 'D';
	command[4] = '0';
	command[5] = '1';
	command[6] = '2';
	command[7] = '3';
	command[8] = '4';
	command[9] = 'j';
	command[10] = 'k';
	command[11] = 'l';
	command[12] = 'm';
	command[13] = 'n';
	command[14] = 'o';
	command[15] = 'p';
	command[16] = 'q';
	command[17] = 'r';
	command[18] = 's';
	command[19] = 't';
	command[20] = 'u';
	command[21] = 'v';
	command[22] = 'w';
	command[23] = 'x';
	command[24] = 'y';
	command[25] = 'z';
	command[26] = 'X';

	for(int i = 27; i < 250; i++)
	{
		command[i] = "+";
	}

	command[58] = '#';
	command[59] = '#';

	printf("Stage 1");

	uint8_t ch[1];
	uint8_t cn[1];

	//while (rs232_get(&ch[0]) != RS_ERR_OK);
	//printf ("%c", ch[0]);

	for(int i = 0; i < 59; i++)
	{
		rs232_put(command[i]);

		pause();
	}

	//cn[0] = '#';
	//rs232_put(cn);
	//pause();

	ch[0] = 0;
	for(int i = 0; i < 27; i++)
	{
		while (rs232_get(&ch[0]) != RS_ERR_OK || ch[0] == 0);
		pause();
		printf(" %u ", ch[0]);
	}

	while (rs232_get(&ch[0]) != RS_ERR_OK);
	printf("%d", ch[0]);
	printf("\n");

	printf("Stage 2");
	sleep(30);

	exit(0);

	printf("Stage 2B");

	int length = GetLength();

	printf("Stage 3");

	GetDocument(length);
	
	printf("Stage 4");

	printf ("\n\nClosing RS232 port:\n");
	if (rs232_close() != RS_ERR_OK) {
		printf ("  Error.  Exiting...\n");
		exit(0);
	}
}