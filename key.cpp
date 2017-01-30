#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	//generate 128 bit key 
	int key[128];
	for (int n = 0; n<128; n++){
	  int i  = rand()%2;
	  key[n] = i;
	  cout << key[n];
	}

	
}