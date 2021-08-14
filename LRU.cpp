class LRUCache {
struct Node{
    Node *next;
    Node *prev;
    int value_;
    int key_;
    Node():key_(0),value_(0),next(nullptr),prev(nullptr){};
    Node(int key,int value):key_(key),value_(value),next(nullptr),prev(nullptr){};
};

public:
    LRUCache(int capacity):capacity_(capacity),size_(0) {
        tail = new Node();
        head = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(Cache.count(key)){//如果key存在 则头插
            auto curNode = Cache[key];
            moveToHead(curNode);
            return curNode->value_;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(Cache.count(key)){
            auto curNode = Cache[key];
            curNode->value_ = value;
            moveToHead(curNode);
            return;
        }else{
            Node *newNode = new Node(key,value);
            Cache[key] = newNode;
            addToHead(newNode);//因为不存在 则直接头插
            size_++;
            if(size_ > capacity_){
                auto delNode = getDelNode();//获取删除节点
                Cache.erase(delNode->key_);
                delete delNode;
                size_--;
                return;
            }
        }
    }

private:
    unordered_map<int,Node*>Cache;
    int capacity_;
    int size_;
    Node *tail;
    Node *head;

private:
    void moveToHead(Node *node){//移动到头部
        moveNode(node);
        addToHead(node);
    }

    void moveNode(Node *node){//将这个节点从链表中剔除
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(Node *node){//头插
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    Node *getDelNode(){//获取删除节点
        auto delNode = tail->prev;
        moveNode(delNode);
        return delNode;
    }
};