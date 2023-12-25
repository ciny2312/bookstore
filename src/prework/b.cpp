#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
struct datam{
    string index;
    int val;
    bool operator < (const datam &x)const{
        if(index!=x.index) return index<x.index;
        return val<x.val;
    }
};
/*
bool operator < ( datam x,datam y){
    if(y.index!=x.index) return x.index<y.index;
    return x.val<y.val;
}
*/
set<datam>s;
set<datam>::iterator it;
int main(){
    freopen("a.in","r",stdin);
    freopen("b.out","w",stdout);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string op,index;
        cin>>op>>index;
        if(op=="insert"){
            int x;
            cin>>x;
            s.insert((datam){index,x});
        }
        else if(op=="delete"){
            int x;
            cin>>x;
            s.erase((datam){index,x});
        }
        else{
            it=s.lower_bound((datam){index,0});
            int cnt=0;
            while(it!=s.end()){
                if((*it).index>index) break;
                printf("%d ",(*it).val);
                it++;cnt++;
            }
            if(!cnt) printf("null");
            printf("\n");
        }
    }
    return 0;
}