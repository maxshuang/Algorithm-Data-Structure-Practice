#include <vector>
using namespace std;

int binary_search(std::vector<int>& vec, int target) {
    int l=0, r=vec.size()-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(vec[mid]==target) {
            return mid;
        }else if(vec[mid]>target) {
            r=mid-1;
        }else {
            l=mid+1;
        }
    }

    return -1;
}

// the first one that is not smaller than target
int lower_bound(std::vector<int>& vec, int target) {
    int l=0, r=vec.size()-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(vec[mid]>=target) {
            r=mid-1;
        }else {
            l=mid+1;
        }
    }

    // all smaller than target
    if(l==vec.size()) return -1;

    return l;
}

// the first one that is larger than target
int upper_bound(std::vector<int>& vec, int target) {
    int l=0, r=vec.size()-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(vec[mid]>target) {
            r=mid-1;
        }else {
            l=mid+1;
        }
    }

    // all smaller than target
    if(l==vec.size()) return -1;

    return l;
}

// floor has the same semantic as the lower_bound
int floor(std::vector<int>& vec, int target) {
    return lower_bound(vec, target);
}

// the first one that is not larger than target
int ceilling(std::vector<int>& vec, int target) {
    int p=upper_bound(vec, target);
    // 0, -1, others
    if(p==0) return -1;
    else if(p==-1) return vec.size()-1;
    return p-1;
}