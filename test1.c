#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

// 1. ����Ԫ�ص�ɾ��(û����)
// �ҵ����Ԫ�� �Ѻ��治�������Ԫ�صĸ��ǵ����Ԫ����
// i: ��ǰ������λ��  
// idx: ��ʾ�����������һ�����ݵ�λ��
// �ҵ���һ��Ԫ�غ� idx ����  i ����������, �ߵ�����Ŀ��Ԫ�ص�λ�� ����ŵ�idxλ�� 
// ÿ�δ��һ�����ݺ� idx++ Ȼ�󲻶�, i����++, 
//int removeElement(int* num, int numsSize, int val){
//	int i = 0;
//	int pos = 0;
//	for (; i < numsSize; i++){
//
//	}
//}
// 2. ɾ���ظ�Ԫ�� ֻ����һ��(��������)
// �жϵ�ǰλ�ú���һ��λ�� �ҵ��ظ�, ����,idx = ��ǰ��num��ַ, i++ , ����,�ҵ�һ��ɾ���� �ظ�
// ��Ų���ͬ��Ԫ�غ� idx��ַ�� = &��ǰ, 
// [0,0,1,1,2,2,3,3,4]
int removeDuplicates(int* nums, int numsSize){
	int pos = 0;
	int i = 0;
	int j = 1;
	while (j < numsSize){
		nums[pos++] = nums[i];
		// i(��0��λ��)��j(��һ��λ�õ�)Ԫ�رȽ�
		if (nums[i] != nums[j]){
			++i;
			++j;
		}
		else{
			// �ҵ�һ������ͬ��λ��
			while (j < numsSize && nums[i] == nums[j])
				++j;
			i = j;// ��һ������ͬ��λ����Ҫ������
			++j;// j ����������
			}
		}
	// �� i < size �����һ��Ԫ����Ҫ����, 
	if (i < numsSize){
		nums[pos++] = nums[i];
	}
	return pos;
}
// ���������� �ϲ���������
// nums1 = [1,2,3,0,0,0] , m = 3
// nums2 = [2,5,6]  n = 3
// ���[1,2,3,4,5,6]
// 1. �����µ�����ռ�(���Ӷ�O(N))
// iָ��ڶ�������ĵ�һ��Ԫ��  jָ���һ��������ĵ�һ��Ԫ�� 
// j������ ���߱ߺ�֮ǰ��Ԫ���Լ�i����Ԫ�رȽ�
// ����һ��m + n ���µ�����ռ� Ȼ��ֱ�ȥ������һ���͵ڶ�������Ԫ�� �����Ĺ����бȽ�
// �������1��Ԫ��С������2��Ԫ��nums1[i] < nums2[j]; ret[idx] = nums[i],++i;
// ���ǰ��С�ں���nums[i] > num[j]; ret[idx] = nums2[j],++j;
// �����ĳ�������Ԫ��û�б�����, �Ͱ�ʣ��Ԫ��ƴ�ӵ��������ret��
// [1,2,2,3,5,6]
void merge(int* nums1, int nums1Size, int* nums2, int nums2Size,int m, int n){
	int total = m + n;
	// ��һ���µ�����
	int* ret = (int*)malloc(sizeof(int)*total);
	// ͬʱ������������
	int n1 = 0;
	int n2 = 0;
	int idx = 0;
	while (n1 < m && n2 < n){
		// ѡ����С�Ľ��д��
		if (nums1[n1] < nums2[n2]){
			ret[idx++] = nums1[n1 + 1];
		}
		else{
			ret[idx++] = nums2[n2 + 1];
		}
	}
	// �п��ܻ���δ�ϲ��������
	if (n1 < m){
		memcpy(ret + idx, nums1 + n1, sizeof(int)+(m - n1 - 1));
	}
	if (n2 < n){
		memcpy(ret + idx, nums1 + n1, sizeof(int)+(n - n2));// ���治�ܼ�1,
	}
	// �����ǵ�ret �����е����ݿ�����nums1��
	memcpy(nums1, ret, total * sizeof(int));
}
// 2. ������ռ�(O(1)���Ӷ�) ð�������Ӷ�ΪO(N^2)
// �Ӻ���ǰ�Ⱥϲ����Ԫ��(Ҫ�����һ��Ԫ�ص�λ��m+n-1)
// ������Ӱ��, iָ���һ���������һ��Ԫ�صĵ�ַ jָ��ڶ�����������һ��Ԫ�ص�λ��
// ����ȥȷ�����һ��Ԫ���ڵ�һ�������λ�� pos= m+n-1;
// �Ӻ���ǰ�ֱ������һ���͵ڶ�������Ԫ��,
// ���nums1[i] > nums2[j], nums1[pos--] = nums1[i--]
// ���nums1[i] < nums2[j], nums1[pos--] = nums2[j--]
// �����һ������û������ ����
// ����ڶ�������û������ ��Ҫ�ѵڶ��������Ԫ�ش����һ���������λ
void merge2(int* nums1, int nums1Size, int* nums2, int nums2Size, int m, int n){
	int pos = m + n - 1;
	int n1 = m - 1;// n1,n2 Ϊ���������һ��Ԫ���±�
	int n2 = n - 1;
	// �Ӻ���ǰ �Ⱥϲ���Ԫ��
	while (n1 >= 0 && n2 >= 0){
		if (nums1[n1] >= nums2[n2]){
			nums1[pos--] = nums1[n1--];
		}
		else{
			nums1[pos--] = nums2[n2--];
		}
	}
	// ���ڶ��������Ƿ���ʣ��Ԫ��
	if (n2 >= 0){
		memcpy(nums1, nums2, (n2 + 1) * sizeof(int));// n2 + 1Ϊʣ��Ԫ�ظ���
	}
}
// ���������е�k(�Ǹ�)��Ԫ��
// [1,2,3,4,5,6,7], k = 3,   ���[5,6,7,1,2,3,4]
// �� [4,3,2,1,5,6,7] ǰ���n-k��Ԫ������ת
// [4,3,2,1,7,6,5] ʣ��Ԫ�ؽ�����ת
// [5,6,7,1,2,3,4] ������ת
//int reserve(int* nums1, int num){
//	int len = sizeof(nums1);
//	num %= len;
//
//
//}

// ������ʽ�������ӷ�
// ���� A = {1,2,0,0}, K = 34;
// ��� {1,2,3,4} ģ��ӷ�����
// ���жμ���֮����ֵ�Ƿ����10 Ȼ�� %10 ��1
// ÿһλ�Ľ��, ��ӦΪ�����ֺ� + ��һ���Ľ�λ -> �����Ƿ��н�λ -> ���½���ͽ�λ
// ��ȡ������ÿһλֵ: %10/10 ����,
// �����ֵ����һλ��ʼ�����ǵ��������
// �õ�ÿһλ��ӵĽ��

// ret������ idxһ��ʼָ��λ��0
// �ӵĽ���Ӹ�λ��ʼ�Ž�����ret, ������� ��������תһ��
void Reverse(int* ret, int left, int right){
	// ���һλԪ�غ͵�һλԪ�ؽ���
	while (left < right){
		int tmp = ret[left];
		ret[left] = ret[right];
		ret[right] = tmp;
		++left;
		--right;
	}
}
// AΪ����, KΪ����
int* addToArrayForm(int* A, int ASize, int K, int* returnSize){
	// �¿��ռ�, ������ ��ȡ��������󳤶�
	// ���ȵ��� K���������ֵĳ���
	int Klen = 0;
	int tmp = K;
	while (tmp){
		++Klen;
		tmp /= 10;// 3/10 = 0, => Klen = 2
	}
	// ���ǽ�λ�Ĵ�� �������Ĵ�С����������������
	int retSize = ASize > Klen ? ASize + 1 : Klen + 1;
	int* ret = (int*)malloc(sizeof(int) * retSize);
		
	int len = ASize - 1;// �����±�
	int step = 0;// ��λ��ֵ
	int idx = 0;// �¿�������±�(�ӷ������λ���ڵ�һλ)
	// �ӷ�ѭ�� ֱ�����������鳤�������ֳ�����������һλ �����ӷ�ѭ��
	while (len >= 0 || K > 0){
		// ��ǰ��Ӧλ��ֵ ���� ���� ��һ����λ��ֵ
		// ���ս��ÿ��ret�д���һλ֮ǰ����λ
		ret[idx] = step;
		// ��λ���
		if (len >= 0){
			ret[idx] += A[len];// �Ȱ�����������һλ����ret��
		}
		if (K > 0){
			ret[idx] += K % 10;// �ٰ����ָ�λ�����������һλ���
		}
		// ���¼���֮��Ľ�� �����>9, ��ȡ��λ����ret ��λ1
		if (ret[idx] > 9){
			ret[idx] %= 10;
			step = 1;
		}
		// �����������0 �򲻽�λ
		else{
			step = 0;
		}
	// ʵ�������������һλԪ�������ָ�λ��ӵ������ �±�-1 ����ָ��ʮλ ��������ѭ��
	// ���浱ǰλ�Ľ�� ���ܱ����ڵ�ǰA���������(���ܱ�֤��С��) ���¿�һ������
	// ��ת���Ӷ�(O(N)) �¿������迼�Ǽӷ����λ�Ľ�λ
		--len;
		K /= 10;// ѭ���������λ ����һλ�����鵹��ǰ��һλ���
		++idx;
	}
	// ѭ������
	// �����λ�Ƿ��н�λ
	if (step == 1){
		ret[idx++] = 1;
	}
	// ��ת
	reverse(ret, 0, idx - 1);
	*returnSize = idx;
	return ret;
}
int main(){
	int nums1[] = { 1, 2, 3, 0, 0, 0 }, m = 3;
	int nums2[] = { 2, 5, 6 }, n = 3;
	int nums1Size = sizeof(nums1);
	int nums2Size = sizeof(nums2);
	merge(nums1, nums1Size, nums2, nums2Size, m, n);


	//int nums[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4 };
	//int numsSize = sizeof(nums);
	//removeDuplicates(nums, numsSize);
	//// ��ѭ����ӡ������
	system("pause");
	return 0;
}