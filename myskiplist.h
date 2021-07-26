#include<fstream>
#include<vector>
#include "mutex.h"
#include<algorithm>
#include<iostream>
#include<memory.h>
#include<string>
using namespace std;

template<class K,class V>
class node
{
public:
node(){};
~node(){delete []forward_list;
}
node(K _key,V _value,int _level):key(_key),value(_value),level(_level)
{
     this->forward_list = new node<K, V>*[level];
    memset(this->forward_list, 0, sizeof(node<K, V>*)*(level));
}
K get_key()
{return key;}
V get_value()
{return value;}
int get_level()
{
    return level;
}
void set(V _value)
{
    value=_value;
}
node<K,V> **forward_list;
private:
K key;
V value;
int level;


};


template<typename K, typename V> 
class skiplist
{
    public: 
    skiplist(int);
    ~skiplist();
    int get_level();
    void insert_element(K, V);
    void display_list();
    bool search_element(K);
    void delete_element(K);
    void write_to_file(const string &);
    void read_from_file(const string &);
    int size();
     int list_level;
private:    
    std::ofstream writer;
    std::ifstream reader;
    int max_level;

    node<K, V> *head;
    int element_count;
       mutexlock mutex;
};

template<typename K, typename V> 
skiplist<K,V>::skiplist(int _max_level):max_level(_max_level),
list_level(0),
element_count(0)
{
    K k;
    V v;
    head= new node<K,V>(k,v,max_level);
}

template<typename K, typename V> 
skiplist<K,V>::~skiplist()
{
    node<K,V>* cur=head;
    while(cur!=nullptr)
    {
        node<K,V>* tmp=cur->forward_list[0];
        delete cur;
        cur=tmp;
    }
    if(writer.is_open())
    writer.close();
    if(reader.is_open())
    reader.close();
}



template<class K,class V>
int skiplist<K,V>::get_level()
{
   int l=1;
   while(rand()%2)
   l++;
   return l>max_level?max_level:l;
}


template<class K,class V>
void skiplist<K,V>::insert_element(K key, V value)
{
     mutexlockguard lock(mutex);
    vector<node<K,V>*>  tmp(max_level,head);
    node<K,V> *cur=head;
  
for(int i=list_level-1;i>=0;--i)
{
    while(cur->forward_list[i]!=nullptr&&cur->forward_list[i]->get_key()<key)
    {
    cur=cur->forward_list[i];
    }
    tmp[i]=cur;
}

cur=cur->forward_list[0];

if(cur==nullptr||cur->get_key()!=key)
{
    int r_level=get_level();
    node<K,V> *n_node=new node<K,V>(key,value,r_level);
    for(int i=0;i<r_level;++i)
    {
        n_node->forward_list[i]=tmp[i]->forward_list[i];
        tmp[i]->forward_list[i]=n_node;
    }
  ++element_count;
list_level=max(list_level,r_level);
}
return ;
}


template<typename K, typename V> 
void skiplist<K, V>::display_list() {

    std::cout << "\n*****structure*****"<<"\n"; 
    for (int i = 0; i <list_level; ++i) {
        node<K, V> *cur = this->head->forward_list[i]; 
        std::cout << "level " << i << ": ";
        while (cur != nullptr) {
            std::cout << cur->get_key() << ":" << cur->get_value() << ";";
            cur = cur->forward_list[i];
        }
        std::cout << std::endl;
    }
    cout<<"******************"<<endl;
}

template<typename K, typename V> 
void skiplist<K,V>::write_to_file(const string &s)
{
     writer.open(s);
   node<K, V> *tmp = this->head->forward_list[0]; 

    while (tmp !=nullptr) {
        writer << tmp->get_key() <<"    "<< tmp->get_value() << endl;
        tmp = tmp->forward_list[0];
    }
    writer.close();
    return ;
}


template<typename K, typename V> 
void skiplist<K,V>::read_from_file(const string &s)
{
     reader.open(s);
       
    K key;
    V value;
      
    while (reader >> key>>value) {
        insert_element(key,value);
    }
    reader.close();
    return ;
}


template<typename K, typename V> 
void skiplist<K, V>::delete_element(K key) {
mutexlockguard  lock(mutex);
    node<K, V> *cur = this->head; 
    vector<node<K,V>*> tmp(list_level,head);


    for(int i=list_level-1;i>=0;--i)
    {
        while(cur->forward_list[i]!=nullptr&&cur->forward_list[i]->get_key()<key)
        cur=cur->forward_list[i];
        tmp[i]=cur;
    }
    cur=cur->forward_list[0];

    if(cur!=nullptr&&cur->get_key()==key)
    {
        for(int i=cur->get_level()-1;i>=0;--i)
            tmp[i]->forward_list[i]=cur->forward_list[i];
        delete cur;


        for(int i=list_level-1;i>=0;--i)
        {
            if(head->forward_list[i]==nullptr)
        --list_level;
        else
        return ; 
        }
    }
    return;
}



template<typename K, typename V> 
bool skiplist<K, V>::search_element(K key) {
mutexlockguard  lock(mutex);
    node<K, V> *cur = this->head; 
    vector<node<K,V>*> tmp(list_level,head);


    for(int i=list_level-1;i>=0;--i)
    {
        while(cur->forward_list[i]!=nullptr&&cur->forward_list[i]->get_key()<key)
        cur=cur->forward_list[i];
        tmp[i]=cur;
    }
    cur=cur->forward_list[0];

    if(cur!=nullptr&&cur->get_key()==key)
    {
       return true;
    }
    return false;
}