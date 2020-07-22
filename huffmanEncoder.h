#include <bits/stdc++.h>

struct text{
    int idx;
    char data;
    int frequency;
    std::string code = "";

    text(){}
    text(int idx, char data, int freq){
        this->idx = idx;
        this->data = data;
        this->frequency = frequency;
    }

    friend bool operator<(text a, text b){
        return a.frequency > b.frequency;
    }
};
class huffmanEncoder{
    struct node{
        text* data; 
        node* left;
        node* right;
    };

    node* root;
    std::vector<node> nodes;
    void makeCodes(node* nd, node* parent){
        if(nd==nullptr){return ;}
        nd->data->code = parent->data->code + nd->data->code[0];
        makeCodes(nd->left, nd);
        makeCodes(nd->right,nd);
    }
    public:
    huffmanEncoder(std::vector<text> & dat):nodes(2*dat.size()){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution d(0.5);
        std::priority_queue<text> pq;
        int idx = 0;
        for(; idx < dat.size(); idx++){
            pq.push(dat[idx]);
            nodes[idx]={&dat[idx],nullptr,nullptr};
        }
        while(pq.size()>1){
            text a = pq.top();
            pq.pop();
            text b = pq.top();
            pq.pop();
            text *ne = new text(idx,'\0',a.frequency+b.frequency);
            int ran = d(gen);
            nodes[idx++].data = ne;
            nodes[ne->idx].left = &nodes[a.idx];
            nodes[ne->idx].right = &nodes[b.idx];
            nodes[a.idx].data->code.push_back(ran + '0');
            nodes[b.idx].data->code.push_back(!ran + '0');
            pq.push(*ne);
        }
        root = &nodes[pq.top().idx];
        makeCodes();
        for(int i = dat.size(); i < nodes.size(); i++){
            delete nodes[i].data;
        }
        nodes.resize(dat.size());
    }
    void makeCodes(){
        makeCodes(root->left,root);      
        makeCodes(root->right,root);      
    }
};