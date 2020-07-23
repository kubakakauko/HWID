#include "Hash.h"
#include <vector>

//The hashing function
using namespace std;


string Hash::EncryptMessage(std::string message)
{
	
	//creating empty matrix
	
	const int messageLenght = message.length();		//Lets say the value is 11

	//Creates a vector with two parameters of char like so v[][] 
	vector<vector<char>> v;
	v.resize(key);
	for(int i = 0; i < key; i++)
	{
		v[i].resize(messageLenght);
	}

	//Fills up the vectors with empty spaces to distinguish them easier
	for (int a = 0; a < key; a++)
	{
		for (int b = 0; b < messageLenght; b++)
		{
			v[a][b] = '\n';
		}
	}

	//Checking the direction of flow, changing the direction whenever TOP or BOTTOM rows are filled
	bool dir_down = false;
	int row = 0, col = 0;
	
	for (int i =0; i< messageLenght; i++)	//For each Column
	{
		//If row = 0 or its one less than than the key value
		if (row == 0 || row == key - 1)		
			dir_down = !dir_down;
		//Fill the row with characters.
		v[row][col++] = message[i];
		
		//find the next raw using next direction flag
		dir_down ? row++ : row--;			//When dir_down is true increment the row, else decrement the row
	}

	//Constructing the cipher using the rail matrix
	string result;
	for(int i = 0; i < key; i++)
	{
		for (int j = 0; j < messageLenght; j++)
		{
			if(v[i][j] != '\n')
			{
				result.push_back(v[i][j]);
			}
		}
	}
	return result;
}

string Hash::DecryptMessage(string cipher)
{

	//Creation of matrix for the cyphered string 
	vector<vector<char>> vd;
	vd.resize(key);
	for (int i = 0; i < key; i++)
	{
		vd[i].resize(cipher.length());
	}

	//Fill the matrix with empty spaces

	for(int a = 0; a < key; a++)
	{
		for(int b = 0; b < cipher.length(); b++)
		{
			vd[a][b] = '\n';
		}
	}

	//Check which direction we will apply
	bool dir_down;
	int row = 0, col = 0;

	for (int i =0; i < cipher.length(); i++)
	{
		if(row == 0)
			dir_down = true;
		if (row == key - 1)
			dir_down = false;
		
		
		//starting from row 0 and column 0 replace the space with  *
		vd[row][col++] = '*';

		//If dir_down is true increase the row when its false decrease the row
		dir_down ? row++ : row--;
	}

	int index = 0;
	for(int i = 0; i < key; i++)
		for (int j = 0; j < cipher.length(); j++)
			if (vd[i][j] == '*' && index < cipher.length())
				vd[i][j] = cipher[index++];
			
	//Reading the zig-zag to construct the result

	string result;
	row = 0, col = 0;
	for (int i =0; i < cipher.length(); i++)
	{
		if(row == 0)
		{
			dir_down = true;
		}
		if (row == key-1)
		{
			dir_down = false;
		}

		if (vd[row][col] != '*')
		{
			result.push_back(vd[row][col++]);
		}

		//Find the next row
		dir_down ? row++ : row--;
	}
	
	return result;
}





