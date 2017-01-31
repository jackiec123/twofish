#include <iostream>
#include <cstdlib>

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
	//generate 128 bit key, N=128,192, 256 can set this in the future, for now its 128
	int key[128];
	for (int n = 0; n<128; n++){
	  int i  = rand()%2;
	  key[n] = i;
	  cout << key[n];
	}

	//k = N/64, where N=128
	int k = 128/64;
	cout<<"\n";
	cout<<k;

	
}
