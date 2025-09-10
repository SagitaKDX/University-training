import java.util.ArrayList;

public class Solution {
    final int MAXVAL =(int) 1e6;
    private int n;
    private ArrayList<Integer> arr = new ArrayList<>();

    private boolean check_val(int k , int val){
        int num = 0;
        for(int v : arr){
            num += (val > v ? 1 : 0);
        }
        return (num < k);
    }
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
       double median_value = 0.0;
       n = nums1.length + nums2.length;
       int maxx = MAXVAL * (-1) - 1;
       int minn = MAXVAL + 1;
       for(int i = 0 ; i < nums1.length ; i ++){
        arr.add(nums1[i]);
        maxx = (maxx < nums1[i] ? maxx : nums1[i]);
        minn = (minn > nums1[i] ? minn : nums1[i]);
       }
       for(int i = 0 ; i < nums2.length ; i ++){
        arr.add(nums2[i]);
        maxx = (maxx < nums2[i] ? maxx : nums2[i]);
        minn = (minn > nums2[i] ? minn : nums2[i]);
       }
       int save = MAXVAL * (-1) - 1;
       int left = MAXVAL * (-1);
       int right = MAXVAL;
       if(n % 2 == 1){
            while (left <= right){
                int mid = left + right;
                mid = mid >> 1;
                if(check_val(n / 2 + 1, mid)){
                    save = mid;
                    left = mid + 1;
                }else{
                    right = mid - 1;
                }
            }
            median_value = save;
       }else{
            while (left <= right){
                int mid = left + right;
                mid = mid >> 1;
                if(check_val(n / 2, mid)){
                    save = mid;
                    left = mid + 1;
                }else{
                    right = mid - 1;
                }
            }
            median_value = save;
            left = MAXVAL * (-1);
            right = MAXVAL;
            save = MAXVAL * (-1) - 1;
            while (left <= right){
                int mid = left + right;
                mid = mid >> 1;
                if(check_val(n / 2 + 1, mid)){
                    save = mid;
                    left = mid + 1;
                }else{
                    right = mid - 1;
                }
            }
            median_value += save;
            median_value /= 2;
            
        }
        return median_value;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {1, 3};
        int[] nums2 = {2 , 3};
        double result = sol.findMedianSortedArrays(nums1, nums2);
        System.out.println("Median: " + result);
    }
}