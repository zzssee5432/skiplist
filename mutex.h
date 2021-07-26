#include<pthread.h>
#include<iostream>
using namespace std;
class mutexlock
{
public:
mutexlock(){pthread_mutex_init(&mutex,NULL);}
~mutexlock()
{
pthread_mutex_lock(&mutex);
pthread_mutex_destroy(&mutex);
}
void lock(){pthread_mutex_lock(&mutex);}
void unlock(){pthread_mutex_unlock(&mutex);}
private:
 pthread_mutex_t mutex;
};


class mutexlockguard{
    public:
    mutexlockguard(mutexlock &_mutex):mutex(_mutex){mutex.lock();}
    ~mutexlockguard(){
        mutex.unlock();}
  
    private:
    mutexlock &mutex;
};
