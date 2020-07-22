#include "huffmanEncoder.h"

std::vector<text> dt;
std::ofstream output("cypher.txt", std::ios_base::out);
int bitPos;
uint8_t OPdata;

void writeData(std::string s){
    int sidx = 0;
    while(sidx<s.length()){
        OPdata |= (s[sidx]-'0')<< bitPos; 
        sidx++;
        bitPos++;
        if(bitPos==8){
            output << OPdata;
            bitPos=0;
            OPdata = 0;
        }
    }
}

int main(){
    std::map<char,int> mp;
    std::ifstream input("input.txt");
    int sz = 0;
    int idx = 0;
    while(true){
        char c = input.get();
        if(input.eof()){break;}
        sz++;
        if(mp.find(c)==mp.end()){
            mp.insert({c,idx++});
        }
    }
    input.clear();
    input.seekg(0,input.beg);
    dt.resize(mp.size());
    for(auto i:mp){
        dt[i.second].data = i.first;
        dt[i.second].idx = i.second;
    }
    while(true){
        char c = input.get();
        if(input.eof()){break;}
        dt[mp[c]].frequency++;
    }
    if(sz!=0){
        huffmanEncoder encoder(dt);
    }
    else{return 0;}
    input.clear();
    input.seekg(0,input.beg);
    while(true){
        char c = input.get();
        if(input.eof()){break;}
        writeData(dt[mp[c]].code);
    }
    if(bitPos!=0){
        output << OPdata;
    }
    std::ofstream key("key.txt", std::ios::out);
    key << sz << '\n';
    for(auto i:mp){
        key << dt[i.second].data << ' ' << dt[i.second].idx << ' ' << dt[i.second].code << std::endl;
    }
}