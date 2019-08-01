#ifndef MY_CONTAINER
#define MY_CONTAINER
#include <memory>

namespace homework {
    template <class T> 
    class my_container{
        public:
            struct my_node{
                T value;
                std::shared_ptr<my_node> next;

                my_node() : value{},next{}{
                };
                my_node(const T& v,const std::shared_ptr<my_node> n): value(v),next(n){
                }
            };


            class my_iterator{
                private:
                    std::weak_ptr<my_node> _index;
                public:
                    my_iterator(std::weak_ptr<my_node> index): _index(index){
                    }

                    my_iterator& operator++(){
                        if(std::shared_ptr<my_node> ptr=_index.lock()){
                            if(ptr->next){
                                _index = std::weak_ptr<my_node>(ptr->next);
                            } else
                                _index = std::weak_ptr<my_node>();
                            
                        }
                        return *this;
                    }

                    T&  operator*(){
                        if(std::shared_ptr<my_node> ptr=_index.lock()){
                            return ptr->value;
                        }
                        throw std::exception();
                    }

                    bool operator!=(const my_iterator& other){
                        return _index.lock()!=other._index.lock();
                    }

                    std::shared_ptr<my_node> get_node(){
                        return _index.lock();
                    }

            };
            
            my_container(): _head{}{
            };

            my_iterator begin(){
                return my_iterator(_head);
            }

            my_iterator end(){
                return my_iterator(std::make_shared<my_node>());
            }
            T& at(size_t index){
                size_t current_index{};
                std::shared_ptr<my_node> current=_head;
                while((current_index<index)) {
                      if(current->next){
                        current=current->next;
                        current_index++;
                      } else throw std::exception();
                }
                return current->value;
            }

            T& operator[](size_t index){
                return std::ref(at(index));
            }

            size_t max_size() const noexcept { 
                return size();
            }

            bool empty() const noexcept {
                return !((bool)_head);
            }

            my_iterator erase(my_iterator it){

                std::shared_ptr<my_node> current=_head,to_delete=it.get_node();

                if(!to_delete) return end();
                if(_head == to_delete){
                    _head = _head->next;
                } else {
                    current=_head;
                    while(current->next!=to_delete){
                        if(!current->next) return end();
                                else current=current->next;
                    }
                    if(current->next==to_delete){
                        current->next = to_delete->next;
                        return my_iterator(current);
                    }
                }
                
                return end();
                
            }

            void push_back( T&& value ){
                if(_head){
                    std::shared_ptr<my_node> last=_head;
                    while(last->next) last=last->next;
                    last->next = std::make_shared<my_node>(value,nullptr);
                } else {
                    _head = std::make_shared<my_node>(value,nullptr);
                }
            }

            size_t size() noexcept {
                 size_t count{};
                 for(auto i: (*this)) {count++; UNUSED(i);}
                
                 return count; 
            }

        private:
            std::shared_ptr<my_node> _head;

    };
 
}
#endif