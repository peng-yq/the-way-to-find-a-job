#include <bits/stdc++.h>
using namespace std;

class myQueue {
    private:
        vector<int> data;
        int head;
        int tail;
        int count;
        int capacity;
    public:
        myQueue(int size) : data(size), head(0), tail(0), count(0), capacity(size) {}

        void enQueue(int val) {
            if (isFull()) 
                cout << "The queue is full." << endl;
            else {
                data[tail] = val;
                tail = (++tail) % capacity;
                count++;
            }
        }

        int deQueue() {
            if (isEmpty()) {
                cout << "The queue is empty." << endl;
                return -1;
            }
            else {
                int num = front();
                head = (++head) % capacity;
                count--;
                return num;
            }
        }

        int front() {
            if (isEmpty()) {
                cout << "The queue is empty." << endl;
                return -1;
            }
            return data[head];
        }

        int back() {
            if (isEmpty()) {
                cout << "The queue is empty." << endl;
                return -1;
            }
            return data[(tail - 1 + capacity) % capacity];
        }

        int size() {
            return count;
        }

        bool isEmpty() {
            return count == 0;
        }

        bool isFull() {
            return count == capacity;
        }
};