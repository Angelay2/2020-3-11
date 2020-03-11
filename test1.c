#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

// 1. 数组元素的删除(没有序)
// 找到这个元素 把后面不等于这个元素的覆盖到这个元素上
// i: 当前遍历的位置  
// idx: 表示被保留的最后一个数据的位置
// 找到第一个元素后 idx 不动  i 继续往后走, 走到不是目标元素的位置 将其放到idx位置 
// 每次存放一个数据后 idx++ 然后不动, i继续++, 
//int removeElement(int* num, int numsSize, int val){
//	int i = 0;
//	int pos = 0;
//	for (; i < numsSize; i++){
//
//	}
//}
// 2. 删除重复元素 只保留一个(有序数组)
// 判断当前位置和下一个位置 找到重复, 覆盖,idx = 当前的num地址, i++ , 再找,找到一个删除后 重复
// 存放不相同的元素后 idx地址到 = &当前, 
// [0,0,1,1,2,2,3,3,4]
int removeDuplicates(int* nums, int numsSize){
	int pos = 0;
	int i = 0;
	int j = 1;
	while (j < numsSize){
		nums[pos++] = nums[i];
		// i(第0个位置)和j(第一个位置的)元素比较
		if (nums[i] != nums[j]){
			++i;
			++j;
		}
		else{
			// 找第一个不相同的位置
			while (j < numsSize && nums[i] == nums[j])
				++j;
			i = j;// 第一个不相同的位置需要存起来
			++j;// j 继续往后走
			}
		}
	// 若 i < size 则最后一个元素需要保存, 
	if (i < numsSize){
		nums[pos++] = nums[i];
	}
	return pos;
}
// 给两个数组 合并有序数组
// nums1 = [1,2,3,0,0,0] , m = 3
// nums2 = [2,5,6]  n = 3
// 输出[1,2,3,4,5,6]
// 1. 申请新的数组空间(复杂度O(N))
// i指向第二个数组的第一个元素  j指向第一个数组里的第一个元素 
// j往后走 边走边和之前的元素以及i处的元素比较
// 申请一个m + n 的新的数组空间 然后分别去遍历第一个和第二个数组元素 遍历的过程中比较
// 如果数组1的元素小于数组2的元素nums1[i] < nums2[j]; ret[idx] = nums[i],++i;
// 如果前者小于后者nums[i] > num[j]; ret[idx] = nums2[j],++j;
// 如果有某个数组的元素没有遍历完, 就把剩余元素拼接到结果数组ret中
// [1,2,2,3,5,6]
void merge(int* nums1, int nums1Size, int* nums2, int nums2Size,int m, int n){
	int total = m + n;
	// 开一个新的数组
	int* ret = (int*)malloc(sizeof(int)*total);
	// 同时遍历两个数组
	int n1 = 0;
	int n2 = 0;
	int idx = 0;
	while (n1 < m && n2 < n){
		// 选择最小的进行存放
		if (nums1[n1] < nums2[n2]){
			ret[idx++] = nums1[n1 + 1];
		}
		else{
			ret[idx++] = nums2[n2 + 1];
		}
	}
	// 有可能还有未合并完的数据
	if (n1 < m){
		memcpy(ret + idx, nums1 + n1, sizeof(int)+(m - n1 - 1));
	}
	if (n2 < n){
		memcpy(ret + idx, nums1 + n1, sizeof(int)+(n - n2));// 后面不能减1,
	}
	// 吧我们的ret 数组中的数据拷贝到nums1中
	memcpy(nums1, ret, total * sizeof(int));
}
// 2. 不申请空间(O(1)复杂度) 冒泡排序复杂度为O(N^2)
// 从后往前先合并大的元素(要算最后一个元素的位置m+n-1)
// 给两个影子, i指向第一个数组最后一个元素的地址 j指向第二个数组的最后一个元素的位置
// 首先去确定最后一个元素在第一个数组的位置 pos= m+n-1;
// 从后向前分别遍历第一个和第二个数组元素,
// 如果nums1[i] > nums2[j], nums1[pos--] = nums1[i--]
// 如果nums1[i] < nums2[j], nums1[pos--] = nums2[j--]
// 如果第一个数组没遍历完 不管
// 如果第二个数组没遍历完 需要把第二个数组的元素存入第一个数组的首位
void merge2(int* nums1, int nums1Size, int* nums2, int nums2Size, int m, int n){
	int pos = m + n - 1;
	int n1 = m - 1;// n1,n2 为两数组最后一个元素下标
	int n2 = n - 1;
	// 从后向前 先合并大元素
	while (n1 >= 0 && n2 >= 0){
		if (nums1[n1] >= nums2[n2]){
			nums1[pos--] = nums1[n1--];
		}
		else{
			nums1[pos--] = nums2[n2--];
		}
	}
	// 检查第二个数组是否还有剩余元素
	if (n2 >= 0){
		memcpy(nums1, nums2, (n2 + 1) * sizeof(int));// n2 + 1为剩余元素个数
	}
}
// 左旋数组中的k(非负)个元素
// [1,2,3,4,5,6,7], k = 3,   输出[5,6,7,1,2,3,4]
// 拆开 [4,3,2,1,5,6,7] 前面的n-k个元素先逆转
// [4,3,2,1,7,6,5] 剩余元素进行逆转
// [5,6,7,1,2,3,4] 整体逆转
//int reserve(int* nums1, int num){
//	int len = sizeof(nums1);
//	num %= len;
//
//
//}

// 数组形式的整数加法
// 输入 A = {1,2,0,0}, K = 34;
// 输出 {1,2,3,4} 模拟加法操作
// 先判段加了之后数值是否大于10 然后 %10 进1
// 每一位的结果, 对应为的数字和 + 上一步的进位 -> 考虑是否有进位 -> 更新结果和进位
// 获取整数的每一位值: %10/10 交替,
// 从数字的最后一位开始与我们的整数相加
// 拿到每一位相加的结果

// ret的数组 idx一开始指向位置0
// 加的结果从个位开始放进数组ret, 结果倒序 所以再逆转一下
void Reverse(int* ret, int left, int right){
	// 最后一位元素和第一位元素交换
	while (left < right){
		int tmp = ret[left];
		ret[left] = ret[right];
		ret[right] = tmp;
		++left;
		--right;
	}
}
// A为数组, K为数字
int* addToArrayForm(int* A, int ASize, int K, int* returnSize){
	// 新开空间, 保存结果 获取两数的最大长度
	// 首先得算 K中所有数字的长度
	int Klen = 0;
	int tmp = K;
	while (tmp){
		++Klen;
		tmp /= 10;// 3/10 = 0, => Klen = 2
	}
	// 考虑进位的存放 结果数组的大小等于这两个里最大的
	int retSize = ASize > Klen ? ASize + 1 : Klen + 1;
	int* ret = (int*)malloc(sizeof(int) * retSize);
		
	int len = ASize - 1;// 数组下标
	int step = 0;// 进位的值
	int idx = 0;// 新开数组的下标(加法结果个位存于第一位)
	// 加法循环 直到遍历完数组长度与数字长度中最大的那一位 结束加法循环
	while (len >= 0 || K > 0){
		// 当前对应位的值 首先 加上 上一步进位的值
		// 最终结果每在ret中存入一位之前检查进位
		ret[idx] = step;
		// 逐位相加
		if (len >= 0){
			ret[idx] += A[len];// 先把数组里的最后一位存入ret中
		}
		if (K > 0){
			ret[idx] += K % 10;// 再把数字个位与数组中最后一位相加
		}
		// 更新加了之后的结果 若结果>9, 则取个位存入ret 进位1
		if (ret[idx] > 9){
			ret[idx] %= 10;
			step = 1;
		}
		// 若结果不大于0 则不进位
		else{
			step = 0;
		}
	// 实现了数组中最后一位元素与数字个位相加的运算后 下标-1 数字指向十位 继续进入循环
	// 保存当前位的结果 不能保存在当前A的这个数组(不能保证大小够) 需新开一个数组
	// 逆转复杂度(O(N)) 新开数组需考虑加法最高位的进位
		--len;
		K /= 10;// 循环舍弃最低位 将下一位与数组倒数前移一位相加
		++idx;
	}
	// 循环结束
	// 看最高位是否有进位
	if (step == 1){
		ret[idx++] = 1;
	}
	// 逆转
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
	//// 用循环打印出数组
	system("pause");
	return 0;
}