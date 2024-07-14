class Node{
    public:
    int val,key,freq;
    Node* next=NULL,*prev=NULL;
    Node(int k,int v,int f){
        next=NULL;
        prev=NULL;
        key=k;
        val=v;
        freq=f;
    }
};
class List{
    public:
    Node* beg=NULL,*end=NULL;
    List(){
        beg=new Node(0,0,0);
        end=new Node(0,0,0);
        beg->next=end;
        end->prev=beg;
    }
    void deletenode(Node* node){
        node->prev->next=node->next;
        node->next->prev=node->prev;
        delete node;
    }
    void addnode(Node* node){
        node->next=beg->next;
        beg->next->prev=node;
        node->prev=beg;
        beg->next=node;
    }
};
class LFUCache {
public:
    unordered_map<int,Node*> mp;//key to nodes
    map<int,List*> flist;//frequency to nodes{key,value,freq}
    int cap;
    LFUCache(int capacity) {
        this->cap=capacity;
    }
    void updatefreq(int key){
        Node* node=mp[key];
        int k=node->key;
        int v=node->val;
        int f=node->freq;
        flist[f]->deletenode(node);
        if(flist[f]->beg->next==flist[f]->end) flist.erase(f);
        f++;
        node=new Node(k,v,f);
        if(flist.find(f)==flist.end()){
            flist[f]=new List();
        }
        flist[f]->addnode(node);
        mp[key]=node;
    }
    int get(int key) {
        if(mp.find(key)==mp.end()) return -1;
        Node* node=mp[key];
        int v=node->val;
        updatefreq(key);
        return v;
    }
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            Node* node=mp[key];
            node->val=value;
            updatefreq(key);
        }
        else if(mp.size()<cap){
            if(flist.find(1)==flist.end()){
                flist[1]=new List();
            }
            Node* node=new Node(key,value,1);
            mp[key]=node;
            flist[1]->addnode(node);
        }
        else{
            List* list_to_remove=(*flist.begin()).second;
            int k=list_to_remove->end->prev->key;
            list_to_remove->deletenode(list_to_remove->end->prev);
            mp.erase(k);
            if(flist.find(1)==flist.end()){
                flist[1]=new List();
            }
            Node* node=new Node(key,value,1);
            mp[key]=node;
            flist[1]->addnode(node);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
