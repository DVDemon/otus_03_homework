#ifndef MY_ALLOCATOR
#define MY_ALLOCATOR
#include <list>

namespace homework {
    template<class T,size_t BLOCK_SIZE>
    class my_allocator {
        private:
            std::list<T*> _blocks;
        public:
            using value_type = T;
            using pointer = T * ;
            using const_pointer = const T*;
            using size_type = std::size_t;

            my_allocator(){
            }
            
            template<typename U>
            struct rebind {
                using other = my_allocator<U,BLOCK_SIZE>;
            };

            T* allocate(size_t n) {
                auto p = std::malloc(n * sizeof(T));
                if (!p) {
                    throw std::bad_alloc();
                }
                return reinterpret_cast<T*>(p);
            }

            void deallocate(T* p, [[maybe_unused]] size_t n) {
                std::free(p);
            }


            template<typename U, typename ...Args>
            void construct(U *p, Args &&...args) {
                new (p) U(std::forward<Args>(args)...);
            }

            void destroy(pointer p) {
                p->~T();
            }

    };
}

#endif

