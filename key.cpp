#include <iostream>
#include <cstdlib>
#include <math.h>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

//NEED TO DOULE CHECK ALL READIN FOR BINARY ARRAYS MUST FOLLOW SAME THROUGHOUT
int decimal(int byteArray[]){
	int decimal = 0;
	for(int i = 0; i<8; i++){
		if(byteArray[i] ==1){
		decimal = decimal + byteArray[i] * pow(2,i);
		}
	}
	return decimal; 
}

unsigned int ROR4(unsigned int x){
	for(int i = 0; i<1; i++){            
		x = (x & 1)<<3|(x>>1);
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
		x = (x>>31)|(x<<1);
	}
	return x;
}

int q0Permutation(int x){
	int fixedSboxQ0[4][16]={0x8,0x1,0x7,0xd,0x6,0xf,0x3,0x2,0x0,0xb,0x5,0x9,0xe,0xc,0xa,0x4,
					0xe,0xc,0xb,0x8,0x1,0x2,0x3,0x5,0xf,0x4,0xa,0x6,0x7,0x0,0x9,0xd,
					0xb,0xa,0x5,0xe,0x6,0xd,0x9,0x0,0xc,0x8,0xf,0x3,0x2,0x4,0x7,0x1,
					0xd,0x7,0xf,0x4,0x1,0x2,0x6,0xe,0x9,0xb,0x3,0x0,0x8,0x5,0xc,0xa};
		int a0 = x/16;//130
		int b0 = (x,16);//2
		int a1 = a0^b0;//xor	128
		int b1 = (a0^(ROR4(b0)))^((8*a0)%16);//% is int mod!!!//need to rotate 4 bit values 138
		int a2 = fixedSboxQ0[0][a1];//but 138 is 1 byte and sboxes take 4 bits
		int b2 = fixedSboxQ0[1][b1];
		int a3 = a2^b2;
		int t = ROR4(b2);
		int b3 = (a2^(ROR4(b2)))^((8*a2)%16);//--used the ROR4 defined fxn
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
		int b0 = (x,16);
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
int hFunction(int x,int listM[1][32]){ //takes in 32 bit word(now just 1 byte which we duplicate here) & either Meven/Modd(list(2) of 32bit words)
	//for Meven M0 is listM[0][], M2 is listM[1]
	int MDS[4][4] = {0x01,0xEF,0x5B,0x5B,
				 0x5B,0xEF,0xEF,0x01,
				 0xEF,0x5B,0x01,0xEF,
				 0xEF,0x01,0xEF,0x5B};
	int m0[7];
	int m1[7];
	int m2[7];
	int m3[7];
//takes M2 or M3(for odd) and divides into bytes which will be converted to decimal
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
		cout<<decimalList[i]<<endl;
	}

	int words[3];
	words[0]=x;
	words[1]=x;
	words[2]=x;
	words[3]=x;

	cout<<"THE X VALUE:"<<x<<endl;


	words[0] = q0Permutation(words[0]);
	words[1] = q1Permutation(words[1]);
	words[2] = q0Permutation(words[2]);
	words[3] = q1Permutation(words[3]);
	for(int i = 0; i< 4; i++){
		cout<<words[i]<<endl;
	}

	for(int i = 0; i<4; i++){
		cout<<i<<":"<<words[i]<<endl;
		words[i] = words[i]^decimalList[i]; 
		cout<<"DOUBLE CHECK"<<words[i]<<endl;//XOR first Meven(M2)with the word
	}//this is what cause the segmentation fault... some ouput is over 1 byte and are unable to be a lookoup in th epermutation 
	
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
		cout<<"2nd stage:"<<words[i]<<"XOR"<<decimalList[i]<<endl;
		stage2Words[i] = words[i]^decimalList[i]; //XOR first Meven(M0)with the word
		cout<<"Result:"<<stage2Words[i]<<endl;
	}
	
	words[0] = q0Permutation(stage2Words[0]);
	words[1] = q0Permutation(stage2Words[1]);
	words[2] = q1Permutation(stage2Words[2]);
	words[3] = q0Permutation(stage2Words[3]);
	for(int i = 0; i<4; i++){
		cout<<"THEFINAL:"<<words[i]<<endl;
	}

	//Now multiply words array by MDS matrix and add em up!
	int toBeAdded[4];
	for(int j = 0; j<4; j++){
		int sum=0;
		for(int i = 0; i<4; i++){
			sum = sum + MDS[j][i]*words[i];
			cout<<MDS[j][i]<<"*"<<words[i]<<endl;
		}
			toBeAdded[j] = sum;
			cout<<"words[j]:"<<toBeAdded[j]<<endl;
		
	}
	int end = toBeAdded[0]+toBeAdded[1]+toBeAdded[2]+toBeAdded[3];
	cout<<"theEnd?:"<<end<<endl;
	return end;

}


int main(){
	std::ofstream outfile("key.txt");


	//Message "encrypt twofish!" in binary
	//Message is 128 bits for now, but can be any with padding
	int message[128]={0,1,1,0,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1, 
		0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,
		0,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,
		0,1,0,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1};
	for (int i = 0; i<128; i++){
		//cout <<message[i]; //prints message
	}
	//cout <<"\n";
	outfile<<"THE KEY"<<endl;


	//generate 128 bit key, N=128,192, 256. can set this in the future, for now its 128
	int N = 128; //key size
	int key[128];
	for (int n = 0; n<128; n++){
	  int i  = rand()%2;
	  key[n] = i;
	  //cout << key[n];
	  outfile<<key[n];
	}
outfile<<"\n";

	//k = N/64, where N=128
	int k = N/64;
	
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
	outfile<<"M0: ";
	for (int i = 0; i<32; i++){
		M0[i] = key[i];
		Meven[0][i]=key[i];
		//cout<<M0[i];
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
		//cout<<Meven[1][j];
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
	}//so i now found the S vector
	//cout<<hFunction(sArrays[0][0], Meven)<<endl;
	//cout<<hFunction(sArrays[1][0], Modd)<<endl;

	

	int p = 16843009;
	int word;
	int hWords[40];
 	for(int round = 0; round<40; round++){
		if(round%2 == 0){
		word = 2*round;//Got rid of *p;
	}
	if(round%2 != 0){
		word = (2*round + 1); //got rid of*p;
	}
		hWords[round] = word;
		//cout<<round<<" ";
		//cout<<word<<endl;
}



//Actually obtains 40 subkeys and places in array 
int subkeys[39];
int subkey;
for(int i = 0; i<40; i++){
	if(i%2 == 0){
	//if (hWords[i]%2 == 0){
	//subkey = hFunction(hWords[i],Meven);
		outfile<<"even"<<hWords[i]<<endl;
		subkey = hFunction(hWords[i],Meven);
	}
	else{
		//subkey = (hFunction(hWords[i], Modd))<<8;
		outfile<<"odd"<<endl;
		subkey = ROL8(hFunction(hWords[i],Modd));
	}
	subkeys[i] = subkey;
	outfile<<i<<" "<<subkeys[i]<<endl;
	//cout<<i<<" "<< subkeys[i]<<" end "<<endl;
}

	int roundKeys[39];
	for(int i = 0; i<40; i++){
		if(i%2 ==0){
			roundKeys[i] = (subkeys[i] + subkeys[i+1])%256;
		}
		else{
			roundKeys[i]= ROL9((subkeys[i-1]+2*subkeys[i])%256);
		}
		//cout<<i<<" "<<roundKeys[i]<<endl;
	}
	outfile<<"OFFICIAL KEYS:"<<endl;
for (int i = 0; i<40; i++){
	outfile<<roundKeys[i]<<endl;
}

	//int evenkey = (hFunction(hWords[17], Meven));

	// + hFunction(sArrays[0][0], Modd))%32;
	//int oddkey = ((hFunction(sArrays[0][0], Meven) + hFunction(sArrays[0][0], Modd))%32)<<9;
	//cout<<"k0 = "<<evenkey<<endl;
	//cout<<"k1 = "<<oddkey<<endl;

}

