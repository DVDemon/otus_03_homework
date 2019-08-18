#ifndef MY_CONTAINER
#define MY_CONTAINER

#include <stdexcept>

namespace homework {
    template <class T, class Allocator> 
    class my_container{
        public:
            // list node 
            struct my_node{
                T value;
                my_node* next;

                my_node() : value{},next{}{
                };
                my_node(const T&& v, my_node* const n): value(v),next(n){
                }
            };

            // one way iterator
            class my_iterator{
                private:
                    my_node* _index;
                public:
                    my_iterator(my_node* index): _index(index){
                    }

                    my_iterator& operator++(){
                        if(_index){
                            _index = _index->next;
                        } else 
                            throw std::logic_error("Out of range");
                        return *this;
                    }

                    T&  operator*(){
                        if(_index){
                            return _index->value;
                        } else
                            throw std::logic_error("Out of range");
                    }

                    bool operator!=(const my_iterator& other){
                        return _index!=other._index;
                    }

                    my_node* get_node(){
                        return _index;
                    }

            };
            
            my_container(): _head{}{
            };

            my_iterator begin(){
                return my_iterator(_head);
            }

            my_iterator end(){
                return my_iterator(nullptr);
            }

            T& at(size_t index){
                size_t   current_index{};
                my_node* current=_head;
                while((current_index<index)) {
                      if(current->next){
                        current=current->next;
                        current_index++;
                      } else throw std::logic_error("Out of range");
                }
                return current->value;
            }

            T& operator[](size_t index){
                return at(index);
            }

            bool empty() const noexcept {
                return !((bool)_head);
            }

            my_iterator erase(my_iterator it){

                my_node* current=_head;
                my_node* to_delete=it.get_node();

                if(!to_delete) return end();
                if(_head == to_delete){
                    _head = _head->next;
                    _allocator_my_node.destroy(to_delete);
                    _allocator_my_node.deallocate(to_delete,1);
                } else {
                    current=_head;
                    while(current->next!=to_delete){
                        if(!current->next) return end();
                                else current=current->next;
                    }
                    if(current->next==to_delete){
                        current->next = to_delete->next;
                        _allocator_my_node.destroy(to_delete);
                        _allocator_my_node.deallocate(to_delete,1);
                        return my_iterator(current);
                    }
                }
                
                return end();
                
            }
            template <class TT>
            void push_back( TT&& value ){
                
                my_node *pointer =  _allocator_my_node.allocate(1);
                _allocator_my_node.construct(pointer,T(value),nullptr);

                if(_head){
                    my_node* last=_head;
                    while(last->next) last=last->next;
                    last->next = pointer;
                } else {
                    _head = pointer;
                }
            }

            size_t size() noexcept {
                 size_t count{};
                 for(auto i: (*this)) {count++; UNUSED(i);}
                
                 return count; 
            }

        private:
            typedef typename  Allocator::template rebind<my_node>::other my_node_allocator_type;
            my_node_allocator_type _allocator_my_node;

            my_node* _head{};


    };
 
}
#endif