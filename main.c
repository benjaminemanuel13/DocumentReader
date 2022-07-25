#include <stdio.h>
#include <stdlib.h>
#include <rs232.h>
#include <spectrum.h>
#include <unistd.h>
#include <string.h>

#include "codepage.c"

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
	for (int f=0; f < 6; f++) {
		while (rs232_get(&len[f]) != RS_ERR_OK);
	}

	int length = strtol(len, NULL, 10);

	printf("Document Length: ");
	printf ("%d", length);

	return length;
}

void GetDocument(int length)
{
	uint8_t doc[1];

	for (int f=0; f < length; f++) {
		while (rs232_get(&doc[0]) != RS_ERR_OK);

		printf ("%c", doc[0]);
	}
}

void pause()
{
	for (int c = 1; c <= 654; c++)
    {}
}

int runMain()
{
	if (rs232_params(RS_BAUD_600 | RS_BITS_8 | RS_STOP_1, RS_PAR_NONE) != RS_ERR_OK) {
		printf ("  Error setting baud rate.  Exiting...\n");
		exit(0);
	}
	
	if (rs232_init() != RS_ERR_OK) {
		printf ("  Initialization error.  Exiting...\n");
		exit(0);
	}

	pause();
	
	char* comm;
	uint8_t command[60];
	
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

	for(int i = 27; i < 60; i++)
	{
		command[i] = "+";
	}

	command[58] = '#';
	command[59] = '#';

	printf("Stage 1\n");

	char* com;
	char con[60];

	printf("Command:");
	scanf("%59s", com);
	strcpy(con, com);

	int len = strlen(con);

	for(int i = 1; i <= len; i++)
	{
		command[i] = con[i - 1];
	}

	command[len + 1] = '=';

	for(int i = 0; i < 59; i++)
	{
		rs232_put(command[i]);
		pause();
	}

	uint8_t ch[1];
	uint8_t cn[1];

	ch[0] = 0;
	for(int i = 0; i < len + 2; i++)
	{
		while (rs232_get(&ch[0]) != RS_ERR_OK || ch[0] == 0);
		pause();
		printf(" %u ", ch[0]);
	}

	printf("\n");

	if (rs232_close() != RS_ERR_OK) {
		printf ("  Error.  Exiting...\n");
		exit(0);
	}

	return 1;
}

void main()
{
	char chr[6];
	int running = 1;

	setChars();

    printf("Hello, welcome to Bens RS232 Project.\n");

	//zx_cls();

	while(running)
	{
		running = runMain();
		pause();
	}

	printf("Stage 2");
	sleep(30);

	exit(0);

	//printf("Stage 2B");

	//int length = GetLength();

	//printf("Stage 3");

	//GetDocument(length);
	
	//printf("Stage 4");

	printf ("\n\nClosing RS232 port:\n");
	if (rs232_close() != RS_ERR_OK) {
		printf ("  Error.  Exiting...\n");
		exit(0);
	}
}