#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "node.h"
#include <memory>

namespace my_q{
    template <typename T, typename Allocator = std::allocator<T>>
    class Queue {
    public:
        class Iterator;
        using value_type = T;
        using node_pointer = Node<T>*;
        using allocator_type = Allocator;
        using size_type = size_t;
        using reference = T&;
        using const_reference = const T&;

        using Alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node<T>>;
        Alloc alloc;
        using AllocTraits = std::allocator_traits<Alloc>;


        node_pointer head = nullptr;
        node_pointer block_ptr = nullptr;
        size_type size = 0;

        Queue();
        Queue(const allocator_type& alloc);
        Queue(const Queue<value_type, allocator_type>& rhs);
        Queue(Queue<value_type, allocator_type>&& rhs) noexcept;
        Queue<value_type, allocator_type>& operator=(const Queue<value_type, allocator_type>& rhs);
        Queue<value_type, allocator_type>& operator=(Queue<value_type, allocator_type>&& rhs) noexcept;
        ~Queue();

        bool operator==(const Queue<value_type, allocator_type>& rhs) const noexcept;
        bool operator!=(const Queue<value_type, allocator_type>& rhs) const noexcept;
        bool empty() const;

        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        size_type get_size() const;
        void pop();
        void push(const_reference value);
        void clear();

        Iterator begin();
        Iterator end();
        const Iterator cbegin() const;
        const Iterator cend() const;

        class Iterator {
        public:
            using difference_type = int;
            using value_type = Queue::value_type;
            using reference = Queue::value_type&;
            using iterator_category = std::bidirectional_iterator_tag;
            
            Iterator(Node<value_type>* ptr);
            reference operator*();
            Iterator& operator=(const Iterator& it);
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);
            Iterator& operator+=(size_t n);
            Iterator& operator-=(size_t n);
            Iterator operator+(size_t rhs) const;

            bool operator==(const Iterator& it) const;
            bool operator!=(const Iterator& it) const;
            
        private:
            Node<value_type>* current_node_ptr = nullptr;
        };    

    };
    template <typename T, typename Allocator>
    Queue<T, Allocator>::Queue(): block_ptr(AllocTraits::allocate(alloc, 1)) {
        AllocTraits::construct(alloc, block_ptr);
        head = block_ptr;
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>::Queue(const allocator_type& alloc): alloc(alloc), block_ptr(AllocTraits::allocate(alloc, 1)) {
        AllocTraits::construct(alloc, block_ptr);
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>::Queue(const Queue<value_type, allocator_type>& rhs): alloc(rhs.alloc), block_ptr(AllocTraits::allocate(alloc, 1)) {
        AllocTraits::construct(alloc, block_ptr);
        head = block_ptr;
        
        for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
            push(*it);
        }
        
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>::Queue(Queue<value_type, allocator_type>&& rhs) noexcept {
    alloc = std::move(rhs.alloc);

    head = rhs.head;
    rhs.head = nullptr;

    block_ptr = rhs.block_ptr;
    rhs.block_ptr = nullptr;

    size = rhs.size;
    rhs.size = 0;
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>& Queue<T, Allocator>::operator=(const Queue<value_type, allocator_type>& rhs) {
        clear();
        
        for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
            push(*it);
        }

        return *this;
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>& Queue<T, Allocator>::operator=(Queue<value_type, allocator_type>&& rhs) noexcept {
    clear();
    AllocTraits::deallocate(alloc, block_ptr, 1);

    alloc = std::move(rhs.alloc);

    head = rhs.head;
    rhs.head = nullptr;

    block_ptr = rhs.block_ptr;
    rhs.block_ptr = nullptr;

    size = rhs.size;
    rhs.size = 0;

    return *this;
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>::~Queue() {
        while (head) {
            Node<value_type>* temp_ptr = head;
            head = head->next;

            AllocTraits::destroy(alloc, temp_ptr);
            AllocTraits::deallocate(alloc, temp_ptr, 1);
        }
    }

    template <typename T, typename Allocator>
    bool Queue<T, Allocator>::operator==(const Queue<value_type, allocator_type>& rhs) const noexcept {
    if (size != rhs.size) {
        return false;
    }

    auto it_rhs = rhs.cbegin();
    for (auto it = cbegin(); it != cend(); ++it) {
        if (*it != *it_rhs) {
        return false;
        }

        ++it_rhs;
    }

    return true;
    }

    template <typename T, typename Allocator>
    bool Queue<T, Allocator>::operator!=(const Queue<value_type, allocator_type>& rhs) const noexcept {
    return !(*this == rhs);
    }

    template <typename T, typename Allocator>
    bool Queue<T, Allocator>::empty() const {
        return size == 0;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::size_type Queue<T, Allocator>::get_size() const {
        return size;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::reference Queue<T, Allocator>::front() {
        if (size != 0) {
            return head->value;
        }
        
        throw std::range_error("Queue is empty");
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::const_reference Queue<T, Allocator>::front() const {
        if (size != 0) {
            return head->value;
        }
        
        throw std::range_error("Queue is empty");
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::reference Queue<T, Allocator>::back() {
        if (size != 0) {
            return block_ptr->prev->value;
        }
        
        throw std::range_error("Queue is empty");
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::const_reference Queue<T, Allocator>::back() const {
        if (size != 0) {
            return block_ptr->prev->value;
        }
        
        throw std::range_error("Queue is empty");
    }

    template <typename T, typename Allocator>
    void Queue<T, Allocator>::pop(){
        if (size == 0) {
            throw std::range_error("Queue is empty!");
        }    

        if (size == 1) {
            AllocTraits::destroy(alloc, head);
            AllocTraits::deallocate(alloc, head, 1);
            block_ptr->prev = nullptr;
            head = nullptr;
            --size;
            return;
        }

        head = head->next;
        AllocTraits::destroy(alloc, head->prev);
        AllocTraits::deallocate(alloc, head->prev, 1);
        head->prev = nullptr;
        --size;
    }

    template <typename T, typename Allocator>
    void Queue<T, Allocator>::push(const_reference value) {
        if (size == 0) {
            if (block_ptr == nullptr) {
                block_ptr = AllocTraits::allocate(alloc, 1);
                AllocTraits::construct(alloc, block_ptr);
            }
            ++size;
            Node<value_type>* ptr = AllocTraits::allocate(alloc, 1);
            AllocTraits::construct(alloc, ptr, value, nullptr, block_ptr);
            head = ptr;
            block_ptr->prev = head;
            return;
        }

        Node<value_type>* prev = block_ptr->prev;
        Node<value_type>* ptr = AllocTraits::allocate(alloc, 1);
        AllocTraits::construct(alloc, ptr, value, prev, block_ptr);
        prev->next = ptr;
        block_ptr->prev = ptr;
        ++size;
    }

    template <typename T, typename Allocator>
    void Queue<T, Allocator>::clear() {
        while (head != block_ptr) { 
            Node<T>* tmp = head;
            head = head->next;
            AllocTraits::destroy(alloc, tmp);
            AllocTraits::deallocate(alloc, tmp, 1);
        }
        size = 0;   
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::begin() {
        Iterator iter(head);
        return iter;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::end() {
        Iterator iter(block_ptr);
        return iter;
    }

    template <typename T, typename Allocator>
    const typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::cbegin() const {
    return Iterator(head);
    }

    template <typename T, typename Allocator>
    const typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::cend() const {
    return Iterator(block_ptr);
    }

    template <typename T, typename Allocator>
    Queue<T, Allocator>::Iterator::Iterator(Node<value_type>* ptr): current_node_ptr(ptr) {}

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator& Queue<T, Allocator>::Iterator::operator++() {
        if (current_node_ptr) {
            current_node_ptr = current_node_ptr->next;
        }
        return *this;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::Iterator::operator++(int) {
        Iterator iterator = *this;
        ++*this;
        return iterator;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator& Queue<T, Allocator>::Iterator::operator--() {
        if (current_node_ptr) {
            current_node_ptr = current_node_ptr->prev;
        }
        return *this;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::Iterator::operator--(int) {
        Iterator iterator = *this;
        --*this;
        return iterator;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator& Queue<T, Allocator>::Iterator::operator=(const Iterator& it) {
        current_node_ptr = it.current_node_ptr;;
        return *this;
    }

    template <typename T, typename Allocator>
    bool Queue<T, Allocator>::Iterator::operator==(const Iterator& it) const {
        return current_node_ptr == it.current_node_ptr;
    }

    template <typename T, typename Allocator>
    bool Queue<T, Allocator>::Iterator::operator!=(const Iterator& it) const {
        return current_node_ptr != it.current_node_ptr;
    }

    template <typename T, typename Allocator>
    T& Queue<T, Allocator>::Iterator::operator*() {
        return current_node_ptr->value;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator& Queue<T, Allocator>::Iterator::operator+=(size_t n) {
        Iterator& it = *this;
        for (size_t i = 0; i < n; ++i) {
            ++it;
        }
        return it;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator& Queue<T, Allocator>::Iterator::operator-=(size_t n) {
        Iterator& it = *this;
        for (size_t i = 0; i < n; ++i, --it) {}
        return it;
    }

    template <typename T, typename Allocator>
    typename Queue<T, Allocator>::Iterator Queue<T, Allocator>::Iterator::operator+(size_t rhs) const {
    Iterator temp = *this;
    temp += rhs;

    return temp;
    }

};

#endif