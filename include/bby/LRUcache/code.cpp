#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache : public Cache {
    public:
        LRUCache(int const capacity) : Cache{} {
            Cache::cp = capacity;
            Cache::tail = NULL;
            Cache::head = NULL;
        }
    virtual void set(int const key, int const value){
        if (auto const it {mp.find(key)};
                it == mp.end()){
            auto new_head_node{new Node(key, value)};
            
            if (!Cache::head){
                Cache::tail = new_head_node;
            } else {
                new_head_node->next = Cache::head;
                new_head_node->next->prev = new_head_node;
            }
            Cache::head = new_head_node;
            Cache::mp.emplace(key, new_head_node);

            if (Cache::mp.size() == Cache::cp + 1){
                auto tmp{Cache::tail->prev};
                Cache::tail->prev->next = NULL;
                Cache::mp.erase(Cache::tail->key);
                delete Cache::tail;
                Cache::tail = tmp;
            }
        }
        else {
            if (Cache::head == it->second){
                return;
            } else if (Cache::tail == it->second){
                it->second->prev->next = NULL;
                Cache::tail = it->second->prev;
            } else{
                assert(it->second->prev);
                assert(it->second->next);
                it->second->prev->next = it->second->next;
                it->second->next->prev = it->second->prev;
            }
            Cache::head->prev = it->second;
            it->second->next = Cache::head;
            it->second->prev = NULL;
            Cache::head = it->second;
        }
        
        /*
        std::clog << "set(" << key << ',' << value << ")->[";
        for(auto current{Cache::head}; current; current = current->next){
            std::clog << current->key << ',';
        }
        std::clog << "]->" << Cache::mp.size() << '\n';
        
        std::clog << "set(" << key << ',' << value << ")->[";
        for(auto current{Cache::tail}; current; current = current->prev){
            std::clog << current->key << ',';
        }
        std::clog << "]\n";
        */
        
    }

    virtual int get(int k) {
        if (auto const it{Cache::mp.find(k)};
                    it == Cache::mp.end()){
            return -1;
        } else {
            return it->second->value;
        }
    }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
