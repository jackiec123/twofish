#include <iostream>
#include <cstdlib>
#include <math.h>
#include <bitset>
#include <sstream>
//#include <boost/utility/binary.hpp>
#include <iomanip>
#include <stdlib.h>
//#include <stdio>
#include <string>
using namespace std;

//int byteToDecimal(string byte[])

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
				
				total = total + (vector1[i][j][l]*pow(2,mult));//convert byte to dcimal
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
	//Vector Mult. of RS(hexadecimal) and Vector(reg. deceimal) from key
	int sArrays[2][4];
	for(int c = 0; c<2; c++){
		for(int l = 0; l<4; l++){
			int sum = 0;
			for (int j = 0; j<8; j++){
				if(c == 0){
					sum = sum + RS[0][j]*firstVector[j];
					sArrays[0][l] = sum;
				}
				if(c ==1){
					sum = sum + RS[0][j]*secondVector[j];
					sArrays[1][l] = sum;
				}
			}
		}
	}

	cout<<sArrays[0][0]<<endl;
	
	


}

