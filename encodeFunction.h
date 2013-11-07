#ifndef ENCODEFUNCTION_H
#define ENCODEFUNCTION_H


#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<fstream>

#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<utility>
#include<set>


#define FOR(i, s, e) for(int i=s; i<e; i++)
#define loop(i, n) FOR(i, 0, n)
#define sf scanf
#define pf printf
#define pb push_back
#define MP make_pair
#define fr first
#define sc second
#define ll long long
#define dd double
#define all(v) v.begin(), v.end()
#define PI acos(-1.0)
#define mem(ara, value) memset(ara, value, sizeof(ara))
#define paii pair<int, int>
#define pall pair<ll, ll>
#define SZ(a) int(a.size())
//#define read(nm) freopen(nm, "r", stdin)
//#define write(nm) freopen(nm, "w", stdout)
#define dump(x) cout<<#x<<" = "<<x<<endl

using namespace std;

#define take(args...) asdf,args
#define debug(args...) asdfg,args; cout<<endl
struct ASDF{
    ASDF& operator,(int &a) {
        sf("%d", &a);
        return *this;
    }
    ASDF& operator,(long int &a){
        sf("%ld", &a);
        return *this;
    }
    ASDF& operator,(long long int &a){
        sf("%lld", &a);
        return *this;
    }
    ASDF& operator,(char &c){
        sf("%c", &c);
        return *this;
    }
    ASDF& operator,(double &d){
        sf("%lf", &d);
        return *this;
    }

    template<typename T>
    ASDF& operator,(T &a){
        cin>>a;
        return *this;
    }
}asdf;
struct ASDFG{
    template<typename T>
    ASDFG& operator,(vector<T> &v){
        pf("[");
        cout<<v[0];
        FOR(i, 1, SZ(v)){
            cout<<", "<<v[i];
        }
        pf("]");
        return *this;
    }

    template<typename T>
    ASDFG& operator,(T x) {
        cout<<x<<" ";
        return *this;
    }


}asdfg;



//Header ends here

//#include<QString>





int encode(string inFileName, string outFileName, string keyFileName = "")
{
    char *code;
    int len;

    bool keyFileGiven = false;

    if(keyFileName.size() == 0)
    {
        code = "efposdf;";              // have to check if it's standard and don't wasting memory;
        len = 8;
    }
    else
    {
        ifstream key(keyFileName.c_str(), ios::in | ios::binary);
        if(!key)
        {
            return 3;
        }
        keyFileGiven = true;
        key.seekg(0, key.end);
        len = key.tellg();
        key.seekg(0, key.beg);

        code = new char[len];

        key.read(code, len);
    }




    ifstream in(inFileName.c_str(), ios::in | ios::binary);
    if(!in)
    {
        return 1;
    }


    ofstream out(outFileName.c_str(), ios::out | ios::binary );

    if(!out)
    {
        return 2;
    }

    char ch;
    int pos  = 0;

    while(!in.eof())
    {
        in.get(ch);
        ch ^= code[pos];
        pos = (pos+1)%len;
        out.put(ch);
    }

    in.close();
    out.close();

    if(keyFileGiven) delete[] code;

    return 0;
}

#endif //ENCODEFUNCTION_H


