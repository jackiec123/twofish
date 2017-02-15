#include <iostream>
#include <cstdlib>
#include <math.h>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

//To obtain the round keys
int hFunction(int x,int listM[1][32]){ //takes in 32 bit word from S vector and eiter Meven/Modd
	int fixedSboxQ0[4][16]={0x8,0x1,0x7,0xd,0x6,0xf,0x3,0x2,0x0,0xb,0x5,0x9,0xe,0xc,0xa,0x4,
					0xe,0xc,0xb,0x8,0x1,0x2,0x3,0x5,0xf,0x4,0xa,0x6,0x7,0x0,0x9,0xd,
					0xb,0xa,0x5,0xe,0x6,0xd,0x9,0x0,0xc,0x8,0xf,0x3,0x2,0x4,0x7,0x1,
					0xd,0x7,0xf,0x4,0x1,0x2,0x6,0xe,0x9,0xb,0x3,0x0,0x8,0x5,0xc,0xa};
	int fixedSboxQ1[4][16]={0x2,0x8,0xb,0xd,0xf,0x7,0x6,0xe,0x3,0x1,0x9,0x4,0x0,0xc,0x5,
					0x1,0xe,0x2,0xb,0x4,0xc,0x3,0x7,0x6,0xd,0xa,0x5,0xf,0x9,0x0,0x8,
					0x4,0xc,0x7,0x5,0x1,0x6,0x9,0xa,0x0,0xe,0xd,0x8,0x2,0xb,0x3,0xf,
					0xb,0x9,0x5,0x1,0xc,0x3,0xd,0xe,0x6,0x4,0x7,0xf,0x2,0x0,0x8,0xa};
	int MDS[4][4] = {0x01,0xEF,0x5B,0x5B,
				 0x5B,0xEF,0xEF,0x01,
				 0xEF,0x5B,0x01,0xEF,
				 0xEF,0x01,0xEF,0x5B};
	//obtaining the 4 bytes for the sboxes
	int words[4];
	for(int i = 0; i<4; i++){
		words[i] = fmod(x/(pow(2,(8*i))),256);
		//cout<<words[i]<<endl;
	}
	for(int h = 1; h>0; h--){
	//permutations q0 and q1
	for(int i = 0; i<4; i++){
		int a0 = words[i]/16;
		int b0 = (words[i],16);
		int a1 = a0^b0;//xor	
		int b1 = (a0^(b0>>1))^((8*a0)%16);//% is int mod!!!//need to rotate 4 bit values -- no correct
		int a2 = fixedSboxQ0[0][a1];
		int b2 = fixedSboxQ0[1][b1];
		int a3 = a2^b2;
		int b3 = (a2^(b2>>1))^((8*a2)%16);//--NOT CORRECT see above --- unsure what ROR4 is????
		int a4 = fixedSboxQ0[2][a3];
		int b4 = fixedSboxQ0[3][b3];
		int y = 16*b4 + a4;
		//cout<<y<<endl;
		words[i]=y;//y is 1 byte
		cout<<words[i]<<endl;
	}
	int mult =  7;
	int total;
	for(int i = 0; i<8; i++){
		//total = total + (*pow(2,mult));//convert byte to decimal
		mult = mult -1;
	}
	for(int i = 0; i<32; i++){

		words[i]=words[i]^listM[h][i];//listM goes 0 to 31 words 0 to 4
		//WRONG DOES NOT properly XOR rn 1 byte with 1 bit
	}
	}
	//Now multiply words array by MDS matrix
	for(int j = 0; j<4; j++){
		int sum;
		for(int i = 0; i<4; i++){
			sum = sum + MDS[j][i]*words[i];
			words[i] = sum;
		}
	}
	//so words[0] is good
	//words[1] needs to 
	cout<<words[2]<<endl;

	return words[0];
}


//Need function to conert decimal to binary
int* decimalToByte(int decimal){
	int byteArray[8];
	int* byte(byteArray);
	int i = 7;
	while(decimal !=0 || decimal>0){
		
		int moddec = decimal;
		int bit;
		decimal = decimal/2;
		bit = moddec%2;
		byteArray[i] = bit;
		i--;
		cout<<bit<<endl;
	}
	//byte = byteArray;
	return byte;
}





int main(){

	//Message "encrypt twofish!" in binary
	//Message is 128 bits for now, but can be any with padding
	int message[128]={0,1,1,0,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1, 
		0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,
		0,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,
		0,1,0,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1};
	for (int i = 0; i<128; i++){
		cout <<message[i];
	}
	cout <<"\n";

	cout<<"\n THE KEY";
	//generate 128 bit key, N=128,192, 256. can set this in the future, for now its 128
	int N = 128; //key size
	int key[128];
	for (int n = 0; n<128; n++){
	  int i  = rand()%2;
	  key[n] = i;
	  cout << key[n];
	}

	//k = N/64, where N=128
	int k = N/64;
	cout<<"\n";
	//cout<<k;
	cout<<"\n";

	//Divide message into 2k words of 32 bits, so 4 words
	int Meven[1][32];
	int Modd[1][32];
	int M0[32]; //bits 0-31 from key array
	int M1[32]; //bits 32-63
	int M2[32];
	int M3[32];
	//cout<< pow (2.0, 0);
	
	for (int i = 0; i<32; i++){
		M0[i] = key[i];
		Meven[0][i]=key[i];
		//cout<<M0[i];
	}
	for (int i =32; i<64; i++){
		M1[i]=key[i];
		Modd[0][i]=key[i];
	}
	for (int i = 64; i<96; i++){
		M2[i] = key[i];
		Meven[1][i]=key[i];
	}
	for (int i = 97; i<128; i++){
		M3[i] = key[i];
		Modd[0][i] = key[i];
		//cout<<M3[i]<<endl;
	}
	
	//cout<<M0[0]<<endl;
	//cout<<Meven[0][0]<<endl;
	
	//Reed Solomon Matrix
	int RS[4][8] = 
	{0x01,0xA4,0x55,0x87,0x5A,0x58,0xDB,0x9E,
	0xA4,0x56,0x82,0xF3,0x1E,0xC6,0x68,0xE5,
	0x02,0xA1,0xFC,0xC1,0x47,0xAE,0x3D,0x19,
	0xA4,0x55,0x87,0x5A,0x58,0xDB,0x9E,0x03};
	//cout<<RS[0][8]<<endl;
	//generates the two 8x1(byte) vectors that are multiplied by RS Matrix
	int vector1[2][8][8];//[vector][row][byte]
	int firstVector[8];
	int secondVector[8];

	for (int i = 0; i<2; i++){
		for (int j = 0; j<8; j++){
			int total = 0;
			int mult = 7;
			for(int l = 0; l<8; l++){
				vector1[i][j][l] = key[l+j*8];
				
				total = total + (vector1[i][j][l]*pow(2,mult));//convert byte to decimal
				mult = mult -1;
				if(i ==0 ){
					firstVector[j] = total;
				}	
				if(i ==1){
					secondVector[j] = total;
				}
			
			}

		}
	}
	//Third Vector Mult. of RS(hexadecimal) and Vector(reg. decimal) from key
	//RECALL: sArray has second vector first (which is odd)
	int sArrays[2][4];
	for(int c = 0; c<2; c++){
		for(int l = 0; l<4; l++){
			int sum = 0;
			
			for (int j = 0; j<8; j++){
				if(c == 0){
					sum = sum + RS[l][j]*firstVector[j];
					sArrays[1][l] = sum;
				}
				if(c ==1){
					sum = sum + RS[l][j]*secondVector[j];
					sArrays[0][l] = sum;
				}
			}
		}
	}//so i now should have my 8 words of 8 bytes used in the h function...
	cout<<hFunction(sArrays[0][0], Meven)<<endl;
	


}

