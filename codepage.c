
uint8_t charset[256];

void setChars()
{
    //These are sent from ESP32

    for(int i = 0; i < 256; i++)
    {
        charset[i] = ' ';
    }

    //numbers
    charset[48] = '0';
    charset[49] = '1';
    charset[50] = '2';
    charset[51] = '3';
    charset[52] = '4';
    charset[53] = '5';
    charset[54] = '6';
    charset[55] = '7';
    charset[56] = '8';
    charset[57] = '9';

    //upper case alphabet
    charset[65] = 'A';
    charset[66] = 'B';
    charset[67] = 'C';
    charset[68] = 'D';
    charset[69] = 'E';
    charset[70] = 'F';
    charset[71] = 'G';
    charset[72] = 'H';
    charset[73] = 'I';
    charset[74] = 'J';
    charset[75] = 'K';
    charset[76] = 'L';
    charset[77] = 'M';
    charset[78] = 'N';
    charset[79] = 'O';
    charset[80] = 'P';
    charset[81] = 'Q';
    charset[82] = 'S';
    charset[83] = 'T';
    charset[84] = 'U';
    charset[85] = 'V';
    charset[86] = 'W';
    charset[87] = 'X';
    charset[88] = 'Y';
    charset[89] = 'Z';

    //lower case alphabet
    charset[97] = 'a';
    charset[98] = 'b';
    charset[99] = 'c';
    charset[100] = 'd';
    charset[101] = 'e';
    charset[102] = 'f';
    charset[103] = 'g';
    charset[104] = 'h';
    charset[105] = 'i';
    charset[106] = 'j';
    charset[107] = 'k';
    charset[108] = 'l';
    charset[109] = 'm';
    charset[110] = 'n';
    charset[111] = 'o';
    charset[112] = 'p';
    charset[113] = 'q';
    charset[114] = 'r';
    charset[115] = 's';
    charset[116] = 't';
    charset[117] = 'u';
    charset[118] = 'v';
    charset[119] = 'w';
    charset[120] = 'x';
    charset[121] = 'y';
    charset[122] = 'z';
}