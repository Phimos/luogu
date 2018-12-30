#include<iostream>
#include<cstring>
using namespace std;

#define mod 1000000007

class Matrix
{
public:
	long long mat[100][100];
	Matrix()
	{
		memset(mat, 0, sizeof(mat));
	}
};

Matrix temp, ans;

long long k;
int n;

Matrix operator*(const Matrix& A, const Matrix&B)
{
	Matrix ans;
	for (int i = 0; i < n; ++i)
		for (int k = 0; k < n; ++k)		//cache友好
			for (int j = 0; j < n; ++j)
				ans.mat[i][j] = (ans.mat[i][j] % mod + (A.mat[i][k] % mod) * (B.mat[k][j] % mod)) % mod;
	return ans;
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> temp.mat[i][j];
	for (int i = 0; i < n; ++i)
		ans.mat[i][i] = 1;
	while (k)
	{
		if (k & 1)
			ans = ans * temp;
		temp = temp * temp;
		k >>= 1;
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n - 1; ++j)
			cout << ans.mat[i][j] % mod << ' ';
		cout << ans.mat[i][n - 1] % mod << endl;
	}
}