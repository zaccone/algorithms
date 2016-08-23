#include <iostream>

using namespace std;

namespace maro {


    struct node {
        int val;
        node* next;
        node* prev;
    };
    class Stack {
        private:
            size_t size_;
            node* head;

        public:
        Stack() {
            size_ = 0;
            head = new node;
            head->next = head;
            head->prev = head;
            head->val = -1;
        }
            int top() {
                return head->prev->val;
            }

            void pop() {
                if(empty())
                    return;

                node* last = head->prev;
                last->prev->next = head;
                head->prev = last->prev;
                delete last;
                size_--;
            }
            void push(int i) {
                node* newNode = new node;

                node* last = head->prev;

                newNode->val = i;
                newNode->next = head;
                newNode->prev = last;


                last->next= newNode;
                head->prev = newNode;
                size_++;
            }
            bool empty() {
                return head->next == head;
            }
            size_t size() {
                return size_;
            }
    };
}

int main() {
    maro::Stack s;
    cout << s.top() << endl;
    cout << "adding..." << endl;
    for (int i = 0; i <= 10; i++) {
        s.push(i);
    }
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}

