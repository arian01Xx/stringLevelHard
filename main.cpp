#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

class Solution {
private:
    long long mod=1e9+7;
    long long appendLast(long long hash, long long l, long long val){
        long long f=power(31, l);
        return (hash+(val*f)%mod) % mod;
    }

    long long removeFirst(long long hash, long long val){
        hash -= val;
        hash = (hash*power(31, mod-2)) % mod;
        return hash;
    }

    unordered_map<long long, long long> ump;
    long long power(long long a, long long b){
        if(ump.find(b)!=ump.end()) return ump[b];
        if(b==0) return 1;
        if(b&1) return ump[b]=(a*(power(a, b-1)% mod)) % mod;
        long long x=power(a, b/2) % mod;
        return ump[b]=(x*x) % mod;
    }
public:
    bool ff(string& s, vector<int>& inds, int ind, int l){
        for(auto& it: inds){
            int ct=0;
            bool flag=1;
            for(int i=it; i<it+l; i++){
                if(s[i]!=s[ind+ct]){
                    flag=0;
                    break;
                }
                ct++;
            }
            if(flag) return 1;
        }
        return 0;
    }

    int f(string& s, int l){
        queue<int> q;
        int hash=0, len=0;
        for(int i=0; i<l; i++){
            q.push(i);
            hash=appendLast(hash, len++, s[i]-'a');
        }

        unordered_map<int, vector<int>> mp;
        mp[hash].push_back(0);
        for(int i=l; i<s.size(); i++){
            hash=appendLast(hash, len++, s[i]-'a');
            hash=removeFirst(hash, s[q.front()]-'a');
            len--;
            q.pop();
            q.push(i);
            if(mp.find(hash)!=mp.end()){
                int ind=i-l+1;
                vector<int> inds=mp[hash];
                if(ff(s, inds, ind, l)) return i-l+1;
            }
            mp[hash].push_back(i-l+1);
        }
        return -1;
    }

    string longestDupSubstring(string s) {
        int low=1, high=s.size();
        pair<int,int> ans={0,0};

        while(low<=high){
            int mid=low+(high-low)/2;
            int val=f(s, mid);
            if(val!=-1){
                ans.first=mid;
                ans.second=val;
                low=mid+1;
            }else high=mid-1;
        }
        string str=s.substr(ans.second, ans.first);
        return str;
    }
};

int main(){
    return 0;
}