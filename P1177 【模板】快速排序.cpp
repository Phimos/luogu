#include<cstdio>
#include<algorithm>
using namespace std;

int nums[100010];

void quickSort(int nums[], int ll, int rr)
{
	if (ll >= rr)
		return;
	int l = ll, r = rr;
	int mid = (l + r) >> 1;
	swap(nums[mid], nums[l]);
	int temp = nums[l];
	while (l < r)
	{
		while (l < r && temp < nums[r])
			--r;
		if (l < r)
			nums[l++] = nums[r];
		while (l < r && temp > nums[l])
			++l;
		if (l < r)
			nums[r--] = nums[l];
	}
	nums[l] = temp;
	quickSort(nums, ll, l - 1);
	quickSort(nums, l + 1, rr);
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", nums + i);
	quickSort(nums, 0, n - 1);
	for (int i = 0; i < n - 1; ++i)
		printf("%d ", nums[i]);
	printf("%d\n", nums[n - 1]);
}