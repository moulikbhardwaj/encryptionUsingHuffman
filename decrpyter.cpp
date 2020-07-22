#include <bits/stdc++.h>

std::ifstream cypher("cypher.txt");
std::ifstream key("key.txt");
std::ofstream output("output.txt");

int bitPos = 8;
uint8_t IPdata = 0;
std::set<int> st;

struct text{
    int idx;
    char data;
    std::string code = "";

    text(){}
    text(int idx, char data, std::string code){
        this->idx = idx;
        this->data = data;
        this->code = code;
    }
};

std::vector<text> dt;

char readInput(){
    auto cpy = st;
    int idx = 0;
    bool found = 0;
    while(true){
        if(bitPos==8){
            bitPos=0;
            cypher >> IPdata; 
        }
        std::vector<int> eraser;
        for(auto i:cpy){
            if(dt[i].code[idx]-'0'!=((IPdata>>bitPos)&(1))){
                eraser.push_back(i);
            }
            else{
                if(dt[i].code.size()==idx+1){
                    cpy.clear();
                    cpy.insert(i);
                    found=1;
                    break;
                }
            }
        }
        bitPos++;
        idx++;
        if(cpy.size()==0){
            throw "ERROR";
        }
        if(found){break;}
        for(auto i:eraser){
            cpy.erase(cpy.find(i));
        }
    }
    return dt[*cpy.begin()].data;
}

int main(){
    int n;
    cypher.unsetf(std::ios_base::skipws);
    key.unsetf(std::ios_base::skipws);
    key >> n;
    char dmy;
    dmy = key.get();
    int idx = 0;
    while(true){
        char c;
        key >> c;
        if(key.eof()){break;}
        dmy = key.get();
        int idx;
        key >> idx;
        st.insert(idx);
        dmy = key.get();
        std::string code;
        key >> code;
        dmy = key.get();
        dt.push_back(text(idx,c,code));
    }
    while(n--){
        output << readInput();
    }
}