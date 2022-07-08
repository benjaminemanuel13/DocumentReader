#include <stdio.h>
#include <stdlib.h>
#include <rs232.h>
#include <spectrum.h>

uint8_t byte[1];

int f;

int add = 32768;

void run()
{
	#asm
		jmp 8000
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
	char command[255];
	command[0] = "l";
	command[1] = "o";
	command[2] = "a";
	command[3] = "d";
	command[4] = "d";
	command[5] = "o";
	command[6] = "c";
	command[7] = "X";

	return command;
}

int GetLength()
{
	uint8_t len[6];

	printf ("\nEchoing 6 bytes to length: ");
	for (f=0; f<6; f++) {
		while (rs232_get(&len[f]) != RS_ERR_OK);

		printf ("%c", len[f]);
	}

	int length = strtol(len, NULL, 10);

	printf("Length: ");
	printf ("%d", length);

	return length;
}

void GetDocument(int length)
{
	uint8_t* doc;

	for (f=0; f<length; f++) {
		while (rs232_get(&doc[f]) != RS_ERR_OK);

		printf ("%c", doc[f]);
	}
}

void main()
{
	char chr[6];

	//poke(10, 32768);

    printf("Hello, welcome to Bens Document Loader.\n");

    printf ("\nInitializing at 1200 baud:");
	if (rs232_params(RS_BAUD_9600, RS_PAR_NONE) != RS_ERR_OK) {
		printf ("  Error setting baud rate.  Exiting...\n");
		exit(0);
	}
	if (rs232_init() != RS_ERR_OK) {
		printf ("  Initialization error.  Exiting...\n");
		exit(0);
	}

	zx_cls();

	char* comm;

	fgets(comm, 5, stdin);

	printf ("  Done.\n");
	//lseek(stdout, 0, 0);
	printf ("AT START.\n");

	exit(0);

	char* command = GetCommand();

	for(int i = 0; i < 255; i++)
	{
		rs232_put(command[i]);
	}

	int length = GetLength();

	GetDocument(length);
	
	//Get Length Working First...
	exit(0);

	printf ("\n\nClosing RS232 port:\n");
	if (rs232_close() != RS_ERR_OK) {
		printf ("  Error.  Exiting...\n");
		exit(0);
	}
}