#include <cassert>

#include <iostream>
#include <vector>
using namespace std;

enum DIRECTION
{
	LEFT_UP,
	LEFT,
	UP
};

template<typename T>
void lcs_length(vector<T> &X, vector<T> &Y,
		vector<vector<int> > &c,
		vector<vector<int> > &b)
{
	int x_len = X.size();
	int y_len = Y.size();
	int i, j;

	assert(x_len > 0);
	assert(y_len > 0);

	c.resize(y_len + 1);
	b.resize(y_len + 1);
	for (i = 0; i < c.size(); ++i)
	{
		c[i].resize(x_len + 1);
		b[i].resize(x_len + 1);
		c[i][0] = 0;
	}

#ifdef NDEBUG
	cout << "size of c: " << c[0].size() << ", " << c.size() << endl;
#endif

	for (i = 1; i < x_len + 1; ++i)
	{
		c[0][i] = 0;
	}

	for (i = 1; i < y_len + 1; ++i)
	{
		for (j = 1; j < x_len + 1; ++j)
		{
			if (X[j] == Y[i])
			{
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = LEFT_UP;
			}
			else if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i][j] = UP;
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i][j] = LEFT;
			}
		}
	}
}

#define LENGTH_OF(x)	(sizeof(x) / sizeof(x[0]))

void print_array(vector<vector<int> > &array)
{
	int i, j;

	for (i = 0; i < array.size(); ++i)
	{
		for (j = 0; j < array[0].size(); ++j)
		{
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void print_array(vector<int> &array)
{
	int i;

	for (i = 0; i < array.size(); ++i)
	{
		cout << array[i] << "\t";
	}
	cout << endl;
}

void print_lcs(vector<vector<int> > &b, vector<int> &X, int i, int j)
{
	assert(i >= 0);
	assert(j >= 0);
	assert(i < b.size());
	assert(j < b[0].size());

	if (i == 0 || j == 0)
	{
		return;
	}
	if (LEFT_UP == b[i][j])
	{
		print_lcs(b, X, i-1, j-1);
		cout << X[j] << "\t";
	}
	else if (UP == b[i][j])
	{
		print_lcs(b, X, i - 1, j);
	}
	else if (LEFT == b[i][j])
	{
		print_lcs(b, X, i, j - 1);
	}
	else
	{
		cout << "Wrong value" << endl;
		return;
	}
}

int main(int argc, char *argv[])
{
	int v1[] = {1, 3, 2, 3, 5, 6, 8, 7, 3, 2};
	int v2[] = {2, 3, 4, 3, 6, 3, 2};
	vector<int> seq1(&v1[0], &v1[LENGTH_OF(v1)]);
	vector<int> seq2(&v2[0], &v2[LENGTH_OF(v2)]);
	vector<vector<int> > c, b;

	cout << LENGTH_OF(v1) << endl;

	cout << "Seq 1:\t";
	print_array(seq1);

	cout << "Seq 2:\t";
	print_array(seq2);
	cout << endl;

	lcs_length<int>(seq1, seq2, c, b);

	cout << "Array c:" << endl;
	print_array(c);

	cout << "Array b:" << endl;
	print_array(b);

	cout << "LCS:\t";
	print_lcs(b, seq1, seq2.size(), seq1.size());
	cout << endl;

	return 0;
}
