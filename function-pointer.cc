#include<iostream>
#include<cstring>

using namespace std;

typedef int (*CFT) (const void*, const void*);

/*
    对向量base的n个元素按照递增顺寻排序,
    用有'cmp'所指向的函数做计较，
    元素的大小是'sz'
 */
void SSort(void *base, size_t n, size_t sz, CFT cmp){
    for(int gap=n/2; 0<gap; gap/=2){
        for(int i=gap; i<n; i++){
            for(int j=i-gap; 0<=j; j-=gap){
                char *b = static_cast<char*>(base);
                char *pj = b + j*sz;
                char *pjg = b + (j + gap) * sz;

                if(cmp(pjg, pj) < 0){
                    for(int k=0; k<sz; k++){
                        char temp = pj[k];
                        pj[k] = pjg[k];
                        pjg[k] = temp;
                    }
                }
            }
        }
    }
}

struct User{
    char *name;
    char *id;
    int dept;
};

User heads[] = {
    "Ritchie",  "dmr",  11271,
    "Sethi",    "ravi", 11272,
    "Schryer",  "nls",  11273,
    "Kernighan","bwk",  11274
};

void PrintId(User *v, int n){
    for(int i=0; i<n; i++){
        cout << v[i].name << '\t' << v[i].id << '\t' << v[i].dept << '\n';
    }
}

int CmpName(const void *p, const void *q){
    return strcmp(static_cast<const User*>(p)->name, static_cast<const User*>(q)->name);
}

int CmpDept(const void *p, const void *q){
    return static_cast<const User*>(p)->dept - static_cast<const User*>(q)->dept;
}

int main(){
    cout << "Heads in alphabetical order:\n";
    SSort(heads, 4, sizeof(User), CmpName);
    PrintId(heads, 4);
    cout << "\n";

    cout << "Heads in order of department number:\n";
    SSort(heads, 4, sizeof(User), CmpDept);
    PrintId(heads, 4);
}
