class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        data = new int[k];
        size = k;
        front = rear = -1;
    }
    
    ~MyCircularQueue(){
        delete []data;
    }

    bool enQueue(int value) {//向循环队列插入一个元素。如果成功插入则返回真。
        if(isFull()){
            return false;
        }
        if(isEmpty()){
            front++;
        }
        rear = (rear + 1) % size; 
        data[rear] = value;
        return true;
    }
    
    bool deQueue() {//从循环队列中删除一个元素.如果成功删除则返回真.
        if(isEmpty()){
            return false;
        }
        if(rear == front && front != -1){
            front = rear = -1;
        }else{
            front = (front + 1) % size;
        }
        return true;
    }
    
    int Front() {
        if(isEmpty()){
            return -1;
        }
        return data[front];
    }
    
    int Rear() {
        if(isEmpty()){
            return -1;
        }
        return data[rear];
    }
    
    bool isEmpty() {
        if(front == rear && front == -1){
            return true;
        }
        return false;
    }
    
    bool isFull() {
        if((rear + 1) % size == front){
            return true;
        }
        return false;
    }

private:
int *data;
int front,rear;
int size;
};