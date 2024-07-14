class LFUCache {
public:
    unordered_map<int,list<vector<int>>::iterator> mp;//key to nodes
    map<int,list<vector<int>>> flist;//frequency to nodes{key,val,freq} 
    int cap;
    LFUCache(int capacity) {
        this->cap=capacity;
        flist.clear();
        mp.clear();
    }
    void updatefreq(int key){
        auto &node=*(mp[key]);
        int f=node[2];
        int v=node[1];
        flist[f].erase(mp[key]);
        if(flist[f].empty()) flist.erase(f);
        f++;
        flist[f].push_front({key,v,f});
        mp[key]=flist[f].begin();
    }
    int get(int key) {
        if(mp.find(key)==mp.end()) return -1;
        auto node=*(mp[key]);
        int val=node[1];
        updatefreq(key);
        return val;
    }
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            auto &node=*(mp[key]);
            node[1]=value;
            updatefreq(key);
        }
        else if(mp.size()<cap){
            flist[1].push_front({key,value,1});
            mp[key]=flist[1].begin();
        }
        else{
            auto k=(*flist.begin()).second.back()[0];
            (*flist.begin()).second.pop_back();
            mp.erase(k);
            flist[1].push_front({key,value,1});
            mp[key]=flist[1].begin();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
