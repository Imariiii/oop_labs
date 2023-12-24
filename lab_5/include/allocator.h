#include <list>
#include <iostream>

namespace mystd
{
    template <class T, int BLOCK_SIZE = 100>
    class Allocator{
    private:
        std::list<T> memory;
        typename std::list<T>::iterator currentPosition;

    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;

        Allocator(){
            memory.resize(BLOCK_SIZE);
            currentPosition = memory.begin();
        }

        ~Allocator(){

            while (!memory.empty()){
                memory.pop_back();
            }
        }

        template <class U>
        struct rebind
        {
            using other = Allocator<U,BLOCK_SIZE>;
        };

        T *allocate(int n){
            if (std::distance(currentPosition, memory.end()) >= n) {
                T* ptr = &(*currentPosition);
                std::advance(currentPosition, n);
                return ptr;
            }
        
            return nullptr;
        }

        void deallocate(T *pointer, int){};

        template <typename U, typename... Args>
        void construct(U *p, Args &&...args){
            new (p) U(std::forward<Args>(args)...);
        }

        int get_size(){
            return BLOCK_SIZE;
        }

        void destroy(pointer p){
            p->~T();
        }
    };

    template <class T, class U>
    constexpr bool operator==(const Allocator<T> &lhs, const Allocator<U> &rhs) 
    {
        return true;
    }

    template <typename T, typename U>
    constexpr bool operator!=(const Allocator<T> &lhs, const Allocator<U> &rhs)  
    {
        return false;
    }
}