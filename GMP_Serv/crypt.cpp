
/*
MIT License

Copyright (c) 2022 Gothic Multiplayer Team (pampi, skejt23, mecio)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//Miejsce na r�ne funkcje od liczenia sum kontrolnych itp...
//by Pampi

//tablica losowo wygenerowana za pomoc� rand()%0x10000
//potem trzeba b�dzie sprawdzi� czy sie warto�ci nie powtarzaj�
static const unsigned short crc16_tab[256]={0x0FF4,0xB694,0x18EA,0xB549,0x0EA5,0xF2EE,0x0215,0x8CC0,0xC949,0x9E8D,0x4A3B,0x336A,0xB8BE,0xDDBA,0xA329,0x12F0,0x57EA,0xB022,0x049A,0x5B33,0xBD54,0x23CE,0xA363,0x6C84,0xCF6E,0x68DC,0xA754,0x8CDE,0xC0C7,0x1BED,0xC34E,0xD0BB,0xD282,0xDC38,0x8604,0xE127,0xCF27,0x8819,0x6DE7,0x9870,0x26A6,0xB823,0xCBDB,0xDF64,0x95DD,0x6F04,0xF254,0xEDC7,0x1F27,0xF6EE,0x48FA,0xDC7B,0x1ABD,0xEC5D,0x4900,0xEA2B,0x5539,0xF054,0x770A,0x1601,0x0C41,0x3A58,0xE6BC,0xDEC3,0x1690,0x6CC1,0xBFEA,0xE5B7,0xF4DA,0x2DD2,0x7E28,0x1B81,0xE5F5,0x4A03,0xFAE5,0x7BD2,0xB907,0xED3A,0x6999,0xD82E,0xE428,0xB293,0xB4AA,0xFEE5,0x9EF0,0xFDAA,0xE911,0xF429,0xEDFE,0x601B,0x0A2A,0xFA3F,0x9A73,0xF0E7,0xD903,0xB103,0x5DA8,0x98ED,0x96BB,0x5282,0xC6BF,0x14E3,0x6E03,0xACB4,0x5EE6,0x68E9,0x2886,0x17ED,0x5623,0x921F,0xF01C,0x3A4B,0x44B2,0xA4C6,0x3931,0xE3A2,0xA270,0x2242,0xD7CC,0x906E,0x825D,0xE1F6,0x8AAD,0x1CD0,0xD2DD,0x63B0,0xCDD3,0x3085,0xFC9E,0x648E,0x8308,0xC35D,0x7971,0xF10B,0x7012,0xD857,0x59F4,0x9898,0xF045,0xB017,0x2AB8,0xE061,0xEA63,0x6F6A,0x8527,0x2394,0x530D,0x2797,0x45D6,0x2AD9,0xB805,0xC833,0x0CCF,0x42B2,0xE503,0xDFAD,0xA663,0xB2D6,0x1032,0xA301,0x1765,0x933A,0x665E,0x90D6,0x8446,0xD670,0x692E,0xDE3A,0x6F09,0x5973,0x8E52,0x99C1,0x39D4,0x78B5,0x092B,0xBEFB,0x9C49,0x5C38,0xE692,0xE21F,0x8711,0x9E97,0xAA52,0x93E1,0xE149,0x8F55,0x738E,0x87AC,0x422B,0x83C0,0x2AAD,0x5990,0x16FB,0x910C,0xEA67,0x9B41,0x677C,0x5395,0x797B,0xD685,0xAD08,0x07CD,0x7046,0xE6DC,0x8082,0x7972,0xA5D7,0x1CCB,0xD5AA,0x8C69,0xFEEA,0x5CBC,0x2B00,0xA93C,0xF09D,0x0C49,0x3891,0x642B,0x93F6,0x7ABD,0xE7EB,0xBEA3,0xD44D,0xFEE6,0x4FAF,0xBEB4,0x9A27,0xB72C,0x1249,0x13A3,0x8DB1,0xBF51,0x1B70,0xFDF8,0xA62D,0x9BF3,0x776A,0x4C04,0xB8BE,0x4D14,0xD86D,0xB7A9,0xA9D0,0x036D,0x60E5,0x9A6D,0x0FB7,0x9977,0xFE98,0xA3AD,0x1434,0xE684,0x6250,0xE881,0xE56A,0xB200};

//jaki� tw�r przypominaj�cy liczenie crc-16
unsigned short GetCRC16(unsigned char* data, int length){
	unsigned short val=0xFFFF;
	unsigned char *ptr=data;
	int i=length;
	while(0!=i--){
		val=static_cast<unsigned short>((val<<8) ^ crc16_tab[(val>>8) ^ *ptr++]);
	}
	return val;
}