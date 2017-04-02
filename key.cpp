#include <iostream>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

//NEED TO DOULE CHECK ALL READIN FOR BINARY ARRAYS MUST FOLLOW SAME THROUGHOUT -- little endian
int decimal(int byteArray[]){
	int decimal = 0;
	for(int i = 7; i>-1; i--){
		if(byteArray[i] ==1){
		decimal = decimal + byteArray[i] * pow(2,i);
		}
	}
	return decimal; 
}
//convertsion for 32 bit numbers
unsigned int largeDecimal(unsigned int byteArray[]){
	unsigned int largeDecimal = 0;
	for(int i = 31; i>-1; i--){
		//cout<<byteArray[i]<<endl;
		if(byteArray[i] ==1){
			largeDecimal = largeDecimal + byteArray[i] * pow(2,i);
		}
	}
	return largeDecimal;
}
//ALL MY ROTATIONS 
unsigned int ROR4(unsigned int x){
	for(int i = 0; i<1; i++){            
		x = (x & 1)<<3|(x>>1)&0x7;
	}
	return x;
}
unsigned int ROL8(unsigned int x){
	for(int i = 0; i<8; i++){
		x = (x>>31)|(x<<1);
	}
	return x;
}
unsigned int ROL9(unsigned int x){
	for(int i = 0; i<9; i++){
		x = ((x &1)>>31)|(x<<1);
		//x = (x>>31)|(x<<1);
	}
	return x;
}
unsigned int ROL1(unsigned int x){
	x = (x>>31)|(x<<1);	
	return x;
}
unsigned int ROR1(unsigned int x){
	x = ((x&1)<<31)|(x>>1)&0x7FFFFFFF;
	return x;
}

int q0Permutation(int x){
	int fixedSboxQ0[4][16]={0x8,0x1,0x7,0xd,0x6,0xf,0x3,0x2,0x0,0xb,0x5,0x9,0xe,0xc,0xa,0x4,
					0xe,0xc,0xb,0x8,0x1,0x2,0x3,0x5,0xf,0x4,0xa,0x6,0x7,0x0,0x9,0xd,
					0xb,0xa,0x5,0xe,0x6,0xd,0x9,0x0,0xc,0x8,0xf,0x3,0x2,0x4,0x7,0x1,
					0xd,0x7,0xf,0x4,0x1,0x2,0x6,0xe,0x9,0xb,0x3,0x0,0x8,0x5,0xc,0xa};
		int a0 = x/16;//130
		int b0 = (x%16);//2
		int a1 = a0^b0;//xor	128
		unsigned int b1 = (a0^(ROR4(b0)))^((8*a0)%16);
		//% is int mod!!!//need to rotate 4 bit values 138
		int a2 = fixedSboxQ0[0][a1];//but 138 is 1 byte and sboxes take 4 bits
		int b2 = fixedSboxQ0[1][b1];
		int a3 = a2^b2;
		unsigned int b3 = (a2^(ROR4(b2)))^((8*a2)%16);//--used the ROR4 defined fxn
		int a4 = fixedSboxQ0[2][a3];
		int b4 = fixedSboxQ0[3][b3];
		int y = 16*b4 + a4;
		//y is 1 byte
		//cout<<words[i]<<endl;
		return y;
	
}
int q1Permutation(int x){
		int fixedSboxQ1[4][16]={0x2,0x8,0xb,0xd,0xf,0x7,0x6,0xe,0x3,0x1,0x9,0x4,0x0,0xa,0xc,0x5,
					0x1,0xe,0x2,0xb,0x4,0xc,0x3,0x7,0x6,0xd,0xa,0x5,0xf,0x9,0x0,0x8,
					0x4,0xc,0x7,0x5,0x1,0x6,0x9,0xa,0x0,0xe,0xd,0x8,0x2,0xb,0x3,0xf,
					0xb,0x9,0x5,0x1,0xc,0x3,0xd,0xe,0x6,0x4,0x7,0xf,0x2,0x0,0x8,0xa};
		int a0 = x/16;
		int b0 = (x%16);
		int a1 = a0^b0;//xor	
		int b1 = (a0^(ROR4(b0)))^((8*a0)%16);//% is int mod!!!//need to rotate 4 bit values 
		int a2 = fixedSboxQ1[0][a1];
		int b2 = fixedSboxQ1[1][b1];
		int a3 = a2^b2;
		int b3 = (a2^(ROR4(b2)))^((8*a2)%16);//--used the ROR4 defined fxn
		int a4 = fixedSboxQ1[2][a3];
		int b4 = fixedSboxQ1[3][b3];
		int y = 16*b4 + a4;
		//y is 1 byte
	
		return y;
	
}
//To obtain the round keys
int hFunction(unsigned int x,unsigned int listM[1][32]){ //takes in 32 bit word(now just 1 byte which we duplicate here) & either Meven/Modd(list(2) of 32bit words)
	//for Meven M0 is listM[0][], M2 is listM[1]
	int MDS[4][4] = {0x01,0xEF,0x5B,0x5B,
				 0x5B,0xEF,0xEF,0x01,
				 0xEF,0x5B,0x01,0xEF,
				 0xEF,0x01,0xEF,0x5B};

	int m0[7];
	int m1[7];
	int m2[7];
	int m3[7];
//takes M2 or M3(for odd) and divides into bytes which will be converted to decimal - for round keys
	//takes S vector - for key dependent s-boxes
	for (int i = 0; i<8; i++){
		m0[i] = listM[1][i];
	}
	int j = 0;
	for (int i =8; i<16; i++){
		m1[j]=listM[1][i];
		j++;
	}
	j = 0;
	for (int i =16; i<24; i++){
		m2[j]=listM[1][i];
		j++;
	}
	j = 0;
	for (int i =24; i<32; i++){
		m3[j]=listM[1][i];
		j++;
	}

	int decimalList[3];
	decimalList[0]=decimal(m0);
	decimalList[1]=decimal(m1);
	decimalList[2]=decimal(m2);
	decimalList[3]=decimal(m3);
	for(int i = 0; i<4; i++){
		//cout<<decimalList[i]<<endl;
	}

	int words[3];
	words[0]=x;
	words[1]=x;
	words[2]=x;
	words[3]=x;

	//cout<<"THE X VALUE:"<<x<<endl;


	words[0] = q0Permutation(words[0]);
	words[1] = q1Permutation(words[1]);
	words[2] = q0Permutation(words[2]);
	words[3] = q1Permutation(words[3]);


	for(int i = 0; i<4; i++){
		//cout<<i<<":"<<words[i]<<endl;
		words[i] = words[i]^decimalList[i]; 
		//cout<<"DOUBLE CHECK"<<words[i]<<endl;//XOR first Meven(M2)with the word
	}
	
	words[0] = q0Permutation(words[0]);
	words[1] = q0Permutation(words[1]);
	words[2] = q1Permutation(words[2]);
	words[3] = q1Permutation(words[3]);

	
//takes M0 and divides into bytes which will be converted to decimal
	int l0[7];
	int l1[7];
	int l2[7];
	int l3[7];
	int k =0;
	for (int i = 0; i<8; i++){
		l0[i] = listM[0][i];	
	}

	for (int i =8; i<16; i++){
		l1[k]=listM[0][i];
		k++;
	}
	k = 0;
	for (int i =16; i<24; i++){
		l2[k]=listM[0][i];
		k++;
	}
	k = 0;
	for (int i =24; i<32; i++){
		l3[k]=listM[0][i];
		k++;
	}

	decimalList[0]=decimal(l0);
	decimalList[1]=decimal(l1);
	decimalList[2]=decimal(l2);
	decimalList[3]=decimal(l3);


 	int stage2Words[3];
	for(int i = 0; i<4; i++){
		//cout<<"2nd stage:"<<words[i]<<"XOR"<<decimalList[i]<<endl;
		stage2Words[i] = words[i]^decimalList[i]; //XOR first Meven(M0)with the word
		//cout<<"Result:"<<stage2Words[i]<<endl;
	}
	
	words[0] = q0Permutation(stage2Words[0]);
	words[1] = q0Permutation(stage2Words[1]);
	words[2] = q1Permutation(stage2Words[2]);
	words[3] = q0Permutation(stage2Words[3]);
	for(int i = 0; i<4; i++){
		//cout<<"THEFINAL:"<<words[i]<<endl;
	}

	//Now multiply words array by MDS matrix and add em up!
	int toBeAdded[4];
	for(int j = 0; j<4; j++){
		int sum=0;
		for(int i = 0; i<4; i++){
			sum = sum + MDS[j][i]*words[i];
			//cout<<MDS[j][i]<<"*"<<words[i]<<endl;
		}
			toBeAdded[j] = sum;
			//cout<<"words[j]:"<<toBeAdded[j]<<endl;
		
	}
	int end = toBeAdded[0]+toBeAdded[1]+toBeAdded[2]+toBeAdded[3];
	//cout<<"theEnd:"<<end<<endl;
	return end;

}

unsigned int gFunction(unsigned int a0, unsigned int a1,unsigned int a2, unsigned int a3){
	int MDS[4][4] = {0x01,0xEF,0x5B,0x5B,
				 0x5B,0xEF,0xEF,0x01,
				 0xEF,0x5B,0x01,0xEF,
				 0xEF,0x01,0xEF,0x5B};
	unsigned int word[3];
	word[0]=a0;
	word[1]=a1;
	word[2]=a2;
	word[3]=a3;
	

	int toBeAdded[4];
	for(int j = 0; j<4; j++){
		int sum=0;
		for(int i = 0; i<4; i++){
			sum = sum + MDS[j][i]*word[i];
			//cout<<MDS[j][i]<<"*"<<words[i]<<endl;
		}
			toBeAdded[j] = sum;
			//cout<<"words[j]:"<<toBeAdded[j]<<endl;		
	}
	unsigned int end = toBeAdded[0]+toBeAdded[1]+toBeAdded[2]+toBeAdded[3];
	return end;
	//cout<<end<<endl;
}

int pht(int t, int a, int b, int k){
	int end;
	if(t == 0){
		end = a + b;
	}
	if(t==1){
		end = a+2*b;
	}	
	end = end +k;
	end = end%(4294967296);

	return end;
}

int fFunction(){

}




int main(){
	std::ofstream outfile("key.txt");


	//Message "encrypt twofish!" in binary
	//Message is 128 bits for now, but can be any with padding
	unsigned int message[128]={0,1,1,0,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1, 
		0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,
		0,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,
		0,1,0,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1};
	for (int i = 0; i<128; i++){
		//cout <<message[i]; //prints message
	}
	//split message into 4 x 32 bit words
	unsigned int p0[32];
	unsigned int p1[32];
	unsigned int p2[32];
	unsigned int p3[32];
	for(int i=0; i<32; i++){
		p0[i] = message[i];
	}
	int place = 0;
	for(int i=32; i<64; i++){
		p1[place] = message[i];
		place++;
	}
	cout<<"\n";
	place = 0;
	for(int i = 64; i<96; i++){
		p2[place] = message[i];
		place++;

	}
	place = 0;
	for(int i = 96; i<128; i++){
		p3[place] = message[i];
		place++;
	}


	outfile<<"THE KEY"<<endl;


	//generate 128 bit key, N=128,192, 256. can set this in the future, for now its 128
	int N = 128; //key size
	unsigned int key[128];

	for(int i = 0; i<128; i++){///128 zero's as the key
	key[i] = 0;
outfile<<key[i];
}
	for (int n = 0; n<128; n++){
	  int i  = rand()%2;
	  //key[n] = i;
	  //cout << key[n];
	  //outfile<<key[n];
	}
outfile<<"\n";

	//k = N/64, where N=128
	int k = N/64;
	
	//cout<<k;
	//cout<<"\n";

	//Divide 128 bit key into 2k words of 32 bits, so 4 words
	unsigned int Meven[1][32];
	unsigned int Modd[1][32];
	unsigned int M0[32]; //bits 0-31 from key array
	unsigned int M1[32]; //bits 32-63
	unsigned int M2[32];
	unsigned int M3[32];
	//cout<< pow (2.0, 0);
	outfile<<"M0: ";
	for (int i = 0; i<32; i++){
		M0[i] = key[i];
		Meven[0][i]=key[i];
		outfile<<M0[i];
	}
	int j = 0;
	outfile<<"\n M1: ";
	for (int i =32; i<64; i++){
		M1[j]=key[i];
		Modd[0][j]=key[i];
		outfile<<M1[j];
		j++;
	}
	j=0;
	outfile<<"\n M2: ";
	for (int i = 64; i<96; i++){
		M2[j] = key[i];
		Meven[1][j]=key[i];
		outfile<<M2[j];
		j++;
	}
	j=0;
	outfile<<"\n M3: ";
	for (int i = 97; i<128; i++){
		M3[j] = key[i];
		Modd[1][j] = key[i];
		outfile<<M3[j];
		j++;
	}
	outfile<<"\n Meven0: ";
	for(int i = 0; i<2; i++){
		for(int k = 0; k<32; k++){
			outfile<<Meven[i][k];
		}
		outfile<<"\n";
	}
	
	
	//Reed Solomon Matrix
	int RS[4][8] = 
	{0x01,0xA4,0x55,0x87,0x5A,0x58,0xDB,0x9E,
	0xA4,0x56,0x82,0xF3,0x1E,0xC6,0x68,0xE5,
	0x02,0xA1,0xFC,0xC1,0x47,0xAE,0x3D,0x19,
	0xA4,0x55,0x87,0x5A,0x58,0xDB,0x9E,0x03};
	
	//generates the two 8x1(byte) vectors that are multiplied by RS Matrix
	unsigned int vector1[2][8][8];//[vector][row][byte]
	unsigned int firstVector[8];
	unsigned int secondVector[8];

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
	//RECALL: sArray has second vector first (which is odd) (and i did this) NEED TO CONVERT TO 2 WORDS OF 32 BITS
	unsigned int sArrays[1][3];
	unsigned int sArrayDec[1];
	unsigned int sArrayBit[1][32];
	unsigned int sum1 = 0;

	for(int c = 0; c<2; c++){
		unsigned int sum2 = 0;
		for(int l = 0; l<4; l++){
			int sum = 0;

			
			for (int j = 0; j<8; j++){//MATRIX MULTIPLCATION - RESULT 4 X 8BITS
				if(c == 0){
					sum = sum + RS[l][j]*firstVector[j];
					sArrays[1][l] = sum;
					sum1 = sum1 + sum;
				}
			 	
				if(c ==1){
					sum = sum + RS[l][j]*secondVector[j];
					sArrays[0][l] = sum;
					sum2 = sum2 + sum;
				}
				sArrayDec[0] = sum2;
			}
		}
		sArrayDec[1] = sum1;
	}
	//converting decimal to binary
	outfile<<"SVector"<<sArrayDec[0]<<" & "<<sArrayDec[1]<<endl;
	int rem;
	int quotient;
	int num = 31;
	for(int i = 0; i<2;i++){
		num = 31;
		quotient = 0;
		rem = 0;
		while ( num !=-1){

			quotient = sArrayDec[i]/2;
			rem = sArrayDec[i] - quotient * 2;
			sArrayBit[i][num] = rem;
			sArrayDec[i] = quotient;
			num = num -1;
		}
		
		}
	outfile<<"S[0]:";

	for(int j = 0; j<2; j++){
	for(int i = 0; i<32;i++){
		outfile<<sArrayBit[j][i];
	}	
	outfile<<"\n S[1]:";
}
	

	unsigned int p = 16843009;
	unsigned int word;
	unsigned int hWords[40];
 	for(int round = 0; round<40; round++){
		if(round%2 == 0){
		word = 2*round;//Got rid of *p;
	}
	if(round%2 != 0){
		word = (2*round + 1); //got rid of*p;
	}
		hWords[round] = word;
		
}



//Actually obtains 40 subkeys and places in array 
unsigned int subkeys[39];
unsigned int subkey;
for(int i = 0; i<40; i++){
	if(i%2 == 0){
		//outfile<<"even:"<<hWords[i]<<endl;
		subkey = hFunction(hWords[i],Meven);
	}
	else{
		//outfile<<"odd:"<<hWords[i]<<endl;
		subkey = ROL8(hFunction(hWords[i],Modd));
	}
	subkeys[i] = subkey;
	outfile<<i<<" "<<subkeys[i]<<endl;
	//cout<<i<<" "<< subkeys[i]<<" end "<<endl;
}

	unsigned int roundKeys[39];
	for(int i = 0; i<40; i++){
		if(i%2 ==0){
			roundKeys[i] = (subkeys[i] + subkeys[i+1])%4294967296;
		}
		else{

			unsigned int math = subkeys[i-1]+2*subkeys[i];
			math = math%4294967296;
			roundKeys[i] = ROL9(math);

		}
		//cout<<i<<" "<<roundKeys[i]<<endl;
	}
	outfile<<"OFFICIAL KEYS:"<<endl;
	for (int i = 0; i<40; i++){
		outfile<<std::dec<<i<<":"<<std::dec<<roundKeys[i]<<", "<<hex<<uppercase<<roundKeys[i]<<endl;
}
//generates 4 S-boxes for the g function :) takes in 8 its and outputs 8 bits
	int sboxes[4][256];
	for(int i=0;i<256; i++){
		sboxes[0][i] = hFunction(i,sArrayBit);
		sboxes[1][i] = hFunction(i,sArrayBit);
		sboxes[2][i] = hFunction(i,sArrayBit);
		sboxes[3][i] = hFunction(i,sArrayBit);

	}
//Input Whitening - pre fiestal rounds
unsigned int r0, r1, r2, r3;
r0 = largeDecimal(p0)^subkeys[0];
r1 = largeDecimal(p1)^subkeys[1];
r2 = largeDecimal(p2)^subkeys[2];
r3 = largeDecimal(p3)^subkeys[3];

//the 16 rounds
for(int i =0; i<16; i++){
	r3 = ROL1(r3);
	r1 = ROL8(r1);
	unsigned int a0 = (r0>>24) & 0xff;			 
	unsigned int a1 = (r0>>16)& 0xff;
	unsigned int a2 = (r0>>8) & 0xff;
	unsigned int a3 = r0 & 0xff;
	a0 = sboxes[0][a0];
	a1 = sboxes[0][a1];
	a2 = sboxes[0][a2];
	a3 = sboxes[0][a3];
	unsigned int a = gFunction(a0,a1,a2,a3); //from r0

	unsigned int b0 = (r1>>24) & 0xff;			 
	unsigned int b1 = (r1>>16)& 0xff;
	unsigned int b2 = (r1>>8) & 0xff;
	unsigned int b3 = r1 & 0xff;
	b0 = sboxes[0][b0];
	b1 = sboxes[0][b1];
	b2 = sboxes[0][b2];
	b3 = sboxes[0][b3];
	//cout<<b0<<" "<<b1<<" "<<b2<<" "<<b3<<endl;
	unsigned int b = gFunction(b0,b1,b2,b3); //from r2
	a = pht(0,a,b,subkeys[2*i+8]);
	b = pht(1,a,b,subkeys[2*i+9]);
	r2 = a^r2;
	r3 = b^r3;
	
	a = ROL1(a);
	//now we swap for the next round
	int copyr0 = r0;
	r0 = r2;
	r2 = copyr0;
	int copyr1 = r1;
	r1 = r3;
	r3 = copyr1;

}

//cout<<r0<<endl;
unsigned int cipher[4];
//Output Whitening
cipher[0] = r0^subkeys[4];
cipher[1] = r1^subkeys[5];
cipher[2] = r2^subkeys[6];
cipher[3] = r3^subkeys[7];
for(int i =0; i<4; i++){
	cout<<cipher[i]<<endl;
}

unsigned int ciphertext1[128];
rem;
quotient;
num = 0;
	for(int i = 0; i<4;i++){
		quotient = 0;
		rem = 0;
		int spot = 31;
		while ( num <(i+1)*32){

			quotient = cipher[i]/2;
			rem = cipher[i] - quotient * 2;
	 		ciphertext1[spot+(i*32)] = rem;
			cipher[i] = quotient;
			num = num +1;
			spot = spot -1;
		}
		
		}
//for(int i = 0; i<4; i++){
	for (int j = 0; j<128; j++){
		outfile<<ciphertext1[j];
	}
	outfile<<" "<<endl;
//}
//Decryption Portion:
//Divide ciphertext into 4 32 bit chunks
unsigned int c0[32];
unsigned int c1[32];
unsigned int c2[32];
unsigned int c3[32];
int spot = 0;
for(int i=31; i>-1; i--){
	c0[spot] = ciphertext1[i];
	spot = spot +1;
}
 place = 0;

for(int i=63; i>31; i--){
	c1[place] = ciphertext1[i];
		place++;
	}
	cout<<"\n";
	place = 0;
	for(int i = 95; i>64; i--){
		c2[place] = ciphertext1[i];
		place++;

	}
	place = 0;
	for(int i = 127; i>95; i--){
		c3[place] = ciphertext1[i];
		place++;
	}
//Reverse output whitening

unsigned int a =largeDecimal(c0)^subkeys[4];
unsigned int b = largeDecimal(c1)^subkeys[5];
unsigned int c = largeDecimal(c2)^subkeys[6];
unsigned int d = largeDecimal(c3)^subkeys[7];
cout<<d<<endl;
cout<<r3<<endl;
//Now lets reverse the rounds


}
//TODO - CHECK ALL BITARRAYS ARE INPUTTED CORRECTLY
