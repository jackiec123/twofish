#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

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
	int M0[32]; //bits 0-31 from key array
	int M1[32]; //bits 32-63
	int M2[32];
	int M3[32];
	//cout<< pow (2.0, 0);
	
	for (int i = 0; i<32; i++){
		M0[i] = key[i];
		//cout<<M0[i];
	}

	for (int i =32; i<64; i++){
		M1[i]=key[i];
	}
	for (int i = 64; i<96; i++){
		M2[i] = key[i];
	}
	for (int i = 97; i<128; i++){
		M3[i] = key[i];
		//cout<<M3[i];
	}
	



	
}
