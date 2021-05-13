#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

class matrix
{
public:
	int size[2]; //0-Number of rows, 1-Number of columns
	float values[10][10]; //The matrix itself, [row number][column number], Maximum Size 10x10
	
	matrix()
	{
		size[0] = 0;
		size[1] = 0;
	}
	
	void define()
	{
		//Getting matrix size from user
		string rows, columns;
		cout << "Enter number of rows: ";
		getline(cin, rows);
		cout << "Enter number of columns: ";
		getline(cin, columns);
		size[0] = stoi(rows);
		size[1] = stoi(columns);

		//Getting matrix values from user
		cout << "Enter the matrix as the following: \n '[1 2 3; 4 5 6; 7 8 9]' \n ";
		string input;
		string num;

		//Getting input from user
		getline(cin, input);

		//Removing brackets from input string
		int l = input.length();
		input.erase(0, 1);
		input.erase(l - 1, 1);


		//Extracting numbers from input string
		for (int i = 0; i < size[0]; i++)
		{
			for (int j = 0; j < size[1]; j++) {

				int sc = input.find(";");
				int s = input.find(" ");

				if (sc > 0) {
					input.erase(sc, 1);
				}
				num = input.substr(0, s);
				values[i][j] = stof(num);
				input.erase(0, s + 1);
			}
		}
	}

	void show() //Prints the Matrix
	{
		for (int i = 0; i < size[0]; i++)
		{
			for (int j = 0; j < size[1]; j++)
			{
				cout << values[i][j];
				cout << " ";
			}
			cout << endl;
		}
	}

};


matrix add(matrix A, matrix B)
{
	matrix result;
	if (A.size[0] == B.size[0] && A.size[1] == B.size[1])
	{
		result.size[0] = A.size[0];
		result.size[1] = A.size[1];
		for (int i = 0; i < result.size[0]; i++)
		{
			for (int j = 0; j < result.size[1]; j++)
			{
				result.values[i][j] = A.values[i][j] + B.values[i][j];
			}
		}
	}
	else
	{
		cout << "Matrices should be of the same size for addition" << endl;
	}
	return result;
}

matrix subtract(matrix A, matrix B)
{
	matrix result;
	if (A.size[0] == B.size[0] && A.size[1] == B.size[1])
	{
		result.size[0] = A.size[0];
		result.size[1] = A.size[1];
		for (int i = 0; i < result.size[0]; i++)
		{
			for (int j = 0; j < result.size[1]; j++)
			{
				result.values[i][j] = A.values[i][j] - B.values[i][j];
			}
		}
	}
	else
	{
		cout << "Matrices should be of the same size for subtraction" << endl;
	}
	return result;
}

matrix multiply(matrix A, matrix B)
{
	float sum;
	matrix result{};
	result.size[0] = A.size[0];
	result.size[1] = B.size[1];
	if (A.size[1] == B.size[0])
	{
		for (int iA = 0; iA < A.size[0]; iA++)
		{
			for (int jB = 0; jB < B.size[1]; jB++)
			{
				sum = 0;
				for (int C = 0; C < A.size[1]; C++)
				{
					sum = sum + A.values[iA][C] * B.values[C][jB];
				}
				result.values[iA][jB] = sum;
			}
		}
	}
	else
	{
		cout << "Number of columns of first matrix should be equal to number of rows of second matrix" << endl;
	}
	return result;
}

matrix transpose(matrix A)
{
	matrix result{};
	for (int i = 0; i < A.size[0]; i++)
	{
		for (int j = 0; j < A.size[1]; j++)
		{
			result.values[j][i] = A.values[i][j];
		}
	}
	return result;
}

matrix subMatrix(matrix B, int sameRow, int sameCol) {
	matrix sub{};
	int sizeOfmatrix = B.size[0];
	sub.size[0] = B.size[0] - 1;
	sub.size[1] = B.size[1] - 1;
	int j = 0, i = 0;
	for (int row = 0; row < sizeOfmatrix; row++)
	{
		for (int col = 0; col < sizeOfmatrix; col++)
		{
			if (row != sameRow && col != sameCol)
			{
				sub.values[i][j++] = B.values[row][col];


				if (j == sizeOfmatrix - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
	return sub;
}

float det(matrix B) { //the no. of rows represent the dimension of the matrix, since this must be a square matrix
	int sizeOfmatrix = B.size[0];
	int sign = 1;
	float determinant = 0;
	matrix sub{};


	if (sizeOfmatrix == 1) {
		determinant = B.values[0][0];

	}
	else
	{
		for (int col = 0; col < sizeOfmatrix; col++) {
			sub = subMatrix(B, 0, col);
			determinant = determinant + sign * det(sub) * B.values[0][col];
			sign = -sign;
		}
	}

	return determinant;


}


matrix inverse(matrix B, float determinant) {
	matrix Inv{};
	Inv.size[0] = B.size[0];
	Inv.size[1] = B.size[1];
	int sign = 1;
	matrix sub{};
	if (B.size[0] == 1) {
		Inv.values[0][0] = 1;

	}
	else {
		for (int row = 0; row < B.size[0]; row++) {

			for (int col = 0; col < B.size[1]; col++) {

				if (determinant != 0) {
					if ((col + row) % 2 == 0)
						sign = 1;
					else
						sign = -1;

					sub = subMatrix(B, row, col);
					Inv.values[col][row] = sign * det(sub) / determinant;

				}

			}
		}

	}
	return Inv;

}

matrix divide(matrix A, matrix B) {

	matrix result{};
	matrix inv{};
	float determinant = det(B);
	if (determinant != 0 && A.size[0] == B.size[0] && A.size[1] == B.size[1] && A.size[0] == A.size[1]) {
		inv = inverse(B, determinant);
		result.size[0] = A.size[0];
		result.size[1] = A.size[1];
		result = multiply(A, inv);
	}
	else {
		cout << "indivisible matrix \n";
	}
	return result;
}


int main()
{
	cout << fixed << setprecision(3);
	matrix A{};
	matrix B{};
	matrix C{};
	cout << "Welcome to Matrix Calculator!" << endl << "Write help for help or exit to quit!" << endl;
	string command, eqn;
	while (true)
	{
		getline(cin, command);
		if (command == "Define A" || command == "define A")
		{
			A.define();
		}
		else if (command == "Define B" || command == "define B")
		{
			B.define();
		}
		else if (command == "Define C" || command == "define C")
		{
			C.define();
		}
		else if (command == "help" || command == "Help")
		{
			cout << "You have 3 matrices A,B and C. Matrix size is up to 10x10." << endl << "Command List:" << endl;
			cout << "-Define --> Allows you to define matrix values, should be followed by matrix name (e.g. Define A)" << endl;
			cout << "-Show --> Shows matrix values, same format as define" << endl;
			cout << "-Transpose --> Show the transpose of matrix, same format as Define and Show" << endl;
			cout << "-Equation --> Allows you to enter an equation" << endl;
			cout << "You can also write simple equations (e.g. A+B, A*B) and don't use spaces." << endl;
			cout << "The program can do addition(+), subtraction(-), multiplication(*), Division(/) and Transpose" << endl;
		}
		else if (command == "exit")
		{
			break;
		}
		else if (command == "Show A" || command == "show A")
		{
			A.show();
		}
		else if (command == "Show B" || command == "show B")
		{
			B.show();
		}
		else if (command == "Show C" || command == "show C")
		{
			C.show();
		}
		else if (command == "Transpose A")
		{
			matrix result = transpose(A);
			result.show();
		}
		else if (command == "Transpose B")
		{
			matrix result = transpose(B);
			result.show();
		}
		else if (command == "Transpose C")
		{
			matrix result = transpose(C);
			result.show();
		}
		else if (command == "Equation" || command == "equation")
		{
			cout << "Equation: ";
			cin >> eqn;
			if (eqn[1] == '+')
			{
				matrix first{};
				matrix second{};
				switch (eqn[0])
				{
				case 'A':
					first = A;
					break;
				case 'B':
					first = B;
					break;
				case 'C':
					first = C;
					break;
				}
				switch (eqn[2])
				{
				case 'A':
					second = A;
					break;
				case 'B':
					second = B;
					break;
				case 'C':
					second = C;
					break;
				}
				matrix result = add(first, second);
				result.show();
			}
			else if (eqn[1] == '-')
			{
				matrix first{};
				matrix second{};
				switch (eqn[0])
				{
				case 'A':
					first = A;
					break;
				case 'B':
					first = B;
					break;
				case 'C':
					first = C;
					break;
				}
				switch (eqn[2])
				{
				case 'A':
					second = A;
					break;
				case 'B':
					second = B;
					break;
				case 'C':
					second = C;
					break;
				}
				matrix result = subtract(first, second);
				result.show();
			}
			else if (eqn[1] == '*')
			{
				matrix first{};
				matrix second{};
				switch (eqn[0])
				{
				case 'A':
					first = A;
					break;
				case 'B':
					first = B;
					break;
				case 'C':
					first = C;
					break;
				}
				switch (eqn[2])
				{
				case 'A':
					second = A;
					break;
				case 'B':
					second = B;
					break;
				case 'C':
					second = C;
					break;
				}
				matrix result = multiply(first, second);
				result.show();
			}
			else if (eqn[1] == '/')
			{
				matrix first{};
				matrix second{};
				switch (eqn[0])
				{
				case 'A':
					first = A;
					break;
				case 'B':
					first = B;
					break;
				case 'C':
					first = C;
					break;
				}
				switch (eqn[2])
				{
				case 'A':
					second = A;
					break;
				case 'B':
					second = B;
					break;
				case 'C':
					second = C;
					break;
				}
				matrix result = divide(first, second);
				result.show();
			}
		}
	}
	return 0;
}
