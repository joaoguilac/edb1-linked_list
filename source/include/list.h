#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as STL).
    /*!
     * A class representing a biderectional iterator defined over a linked list.
     *
     * \note
     * This iterator only works for traversing elements inside the same list.
     *
     * This class is incomplete and it is provided "as is".
     *
     * \date May, 2nd 2017.
     * \author Selan R. dos Santos
     */

    template < typename T >
    class list
    {
        private:
        //=== the data node.
        struct Node
        {
            T data; // Tipo de informação a ser armazenada no container.
            Node * next;
            Node * prev;

            Node( const T &d=T{} , Node * n=nullptr, Node * p=nullptr )
                : data {d}, next{n}, prev{p}
            { /* empty */ }
        };


        //=== The iterator classes.
        public:

        class const_iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T;         //!< The type of the value stored in the list.
                using pointer           = T *;       //!< Pointer to the value.
                using reference         = T &;       //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:

                // Construtor regular 
                /*! Constrói iterador constante para o tipo Node.
                 *  @param ptr Ponteiro para tipo Node.
                 */
                const_iterator(Node * ptr = nullptr ) : m_ptr{ ptr }
                {/*empty*/}

                // Destrutor
                /*! Destrói o iterador.
                 */
                ~const_iterator() = default;

                // Construtor por cópia
                /*! Constrói um iterador constante com a cópia do conteúdo de outro iterador constante.
                 *  @param iterator Iterador constante cujo conteúdo será copiado para a construção do novo iterador constante.
                 */
                const_iterator( const const_iterator & ) = default;

                // Operador de atribuição de cópia
                /*! Substitui o conteúdo do iterador constante pela cópia do conteúdo de outro iterador constante.
                 *  @param iterator Outro iterador constante cujo conteúdo irá substituir o conteúdo do iterador constante objeto da atribuição.
                 */
                const_iterator& operator=( const const_iterator & ) = default;


                reference  operator*() { /* TODO */ return m_ptr->data; }

                const_reference  operator*() const { /* TODO */ return m_ptr->data; }


                /// Operador de incremento
                /*! Avança o iterador constante para a próxima localização na lista encadeada. Corresponde ao pré-incremento.
                 *  @return Iterador constante apontando para a próxima localização da lista encadeada.
                 */
                const_iterator operator++() { m_ptr = m_ptr->next; return const_iterator{m_ptr}; }

                /// Operador de incremento
                /*! Avança o iterador constante para a próxima localização na lista encadeada. Corresponde ao pós-incremento.
                 *  @return Iterador constante apontando para a localização da lista encadeada antes do incremento.
                 */
                const_iterator operator++(int) { const_iterator retval{m_ptr}; m_ptr = m_ptr->next; return retval; }

                /// Operador de decremento
                /*! Retrocede o iterador constante para a localização anterior na lista encadeada. Corresponde ao pré-decremento.
                 *  @return Iterador constante apontando para a localização anterior da lista encadeada.
                 */
                const_iterator operator--() { m_ptr = m_ptr->prev; return const_iterator{m_ptr}; }

                /// Operador de decremento
                /*! Retrocede o iterador constante para a localização anterior na lista encadeada. Corresponde ao pós-decremento.
                 *  @return Iterador constante apontando para a localização da lista encadeada antes do decremento.
                 */
                const_iterator operator--(int) { const_iterator retval{m_ptr}; m_ptr = m_ptr->prev; return retval; }

                /// Operador de igualdade
                /*! Verifica se ambos iteradores apontam para a mesma localização.
                 *  @return Verdadeiro se ambos iteradores apontarem para a mesma localização na lista encadeada; e falso caso contrário.
                 */
                bool operator==( const const_iterator & rhs ) const { return m_ptr == rhs.m_ptr; }

                /// Operador de diferença
                /*! Verifica se os iteradores apontam para localizações distintas.
                 *  @return Verdadeiro se cada iterador apontar para uma localização diferente na lista encadeada; e falso caso contrário.
                 */
                bool operator!=( const const_iterator & rhs ) const { return m_ptr != rhs.m_ptr; }

                //=== Other methods that you might want to implement.

                /// it += 3; // Go back  3 positions within the container. 
                const_iterator operator+=( difference_type step) {
                     for(auto i{0}; i < step; i++) m_ptr = m_ptr->next; 
                     return const_iterator{m_ptr}; 
                }

                /// it -= 3; // Go back  3 positions within the container. 
                const_iterator operator-=(  difference_type step ) {
                     for(auto i{0}; i < step; i++) m_ptr = m_ptr->prev; 
                     return const_iterator{m_ptr}; 
                }

                
                /// Operador de salto para trás
                /*! Retorna um iterador apontando para o n-ésimo antecessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo antecessor de it na lista encadeada.
                */
                friend const_iterator operator-( const_iterator it, difference_type valor) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it--;
                    }
                    return it; 
                }

                /// Operador de salto para frente
                /*! Retorna um iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                */
                friend const_iterator operator+( const_iterator it, difference_type valor ) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it++;
                    }
                    return it; 
                }
                
                /// Operador de salto para frente
                /*! Retorna um iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                */
                friend const_iterator operator+( difference_type valor, const_iterator it ) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it++;
                    }
                    return it;
                }


                /// it->method()
                pointer operator->( void ) const { /* TODO */ return nullptr; }
                /// it1 - it2
                difference_type operator-( const const_iterator & rhs ) const { /* TODO */ return 0; }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const const_iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        class iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T; //!< The type of the value stored in the list.
                using pointer           = T *; //!< Pointer to the value.
                using reference         = T &; //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:

                // Construtor regular 
                /*! Constrói iterador para o tipo Node.
                 *  @param ptr Ponteiro para tipo Node.
                 */
                iterator( Node * ptr = nullptr ) : m_ptr{ ptr }
                { /*empty*/ }

                // Destrutor
                /*! Destrói o iterador.
                 */
                ~iterator() = default;

                // Construtor por cópia
                /*! Constrói um iterador com a cópia do conteúdo de outro iterador.
                 *  @param iterator Iterador cujo conteúdo será copiado para a construção do novo iterador.
                 */
                iterator( const iterator & ) = default;

                // Operador de atribuição de cópia
                /*! Substitui o conteúdo do iterador pela cópia do conteúdo de outro iterador.
                 *  @param iterator Outro iterador cujo conteúdo irá substituir o conteúdo do iterador objeto da atribuição.
                 */
                iterator& operator=( const iterator & ) = default;

                
                reference  operator*() { /* TODO */ return m_ptr->data; }

                // const_reference  operator*() const { /* TODO */ return nullptr; }
                const_reference  operator*() const { return m_ptr->data; }

                /// Operador de incremento
                /*! Avança o iterador para a próxima localização na lista encadeada. Corresponde ao pré-incremento.
                 *  @return Iterador apontando para a próxima localização da lista encadeada.
                 */
                iterator operator++() { m_ptr = m_ptr->next; return iterator{m_ptr}; }

                /// Operador de incremento
                /*! Avança o iterador para a próxima localização na lista encadeada. Corresponde ao pós-incremento.
                 *  @return Iterador apontando para a localização da lista encadeada antes do incremento.
                 */
                iterator operator++(int) { iterator retval{m_ptr}; m_ptr = m_ptr->next; return retval; }

                /// Operador de decremento
                /*! Retrocede o iterador para a localização anterior na lista encadeada. Corresponde ao pré-decremento.
                 *  @return Iterador apontando para a localização anterior da lista encadeada.
                 */
                iterator operator--() { m_ptr = m_ptr->prev; return iterator{m_ptr}; }

                /// Operador de decremento
                /*! Retrocede o iterador para a localização anterior na lista encadeada. Corresponde ao pós-decremento.
                 *  @return Iterador apontando para a localização da lista encadeada antes do decremento.
                 */
                iterator operator--(int) { iterator retval{m_ptr}; m_ptr = m_ptr->prev; return retval; }

                /// Operador de igualdade
                /*! Verifica se ambos iteradores apontam para a mesma localização.
                 *  @return Verdadeiro se ambos iteradores apontarem para a mesma localização na lista encadeada; e falso caso contrário.
                 */
                bool operator==( const iterator & rhs ) const { return m_ptr == rhs.m_ptr; }

                /// Operador de diferença
                /*! Verifica se os iteradores apontam para localizações distintas.
                 *  @return Verdadeiro se cada iterador apontar para uma localização diferente na lista encadeada; e falso caso contrário.
                 */
                bool operator!=( const iterator & rhs ) const { return m_ptr != rhs.m_ptr; }


                //=== Other methods that you might want to implement.

                /// it += 3; // Go back  3 positions within the container. 
                iterator operator+=( difference_type step) {
                    for(auto i{0}; i < step; i++) m_ptr = m_ptr->next;
                    return iterator{m_ptr}; 
                }

                /// it -= 3; // Go back  3 positions within the container. 
                iterator operator-=(  difference_type step ) { 
                    for(auto i{0}; i < step; i++) m_ptr = m_ptr->prev;
                    return iterator{m_ptr};
                }

                /// Operador de salto para trás
                /*! Retorna um iterador apontando para o n-ésimo antecessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo antecessor de it na lista encadeada.
                */
                friend iterator operator-( iterator it, difference_type valor) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it--;
                    }
                    return it; 
                }

                /// Operador de salto para frente
                /*! Retorna um iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                */
                friend iterator operator+( iterator it, difference_type valor ) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it++;
                    }
                    return it; 
                }
                
                /// Operador de salto para frente
                /*! Retorna um iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                *  @return Iterador apontando para o n-ésimo sucessor de it na lista encadeada.
                */
                friend iterator operator+( difference_type valor, iterator it ) { 
                    for(difference_type i = 0 ; i < valor ; i++){
                        it++;
                    }
                    return it;
                }


                /// it->method()
                pointer operator->( void ) const { /* TODO */ return nullptr; }
                /// it1 - it2
                difference_type operator-( const iterator & rhs ) const { /* TODO */ return 0; }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        //=== Private members.
        private:
            size_t m_len;  // comprimento da lista.
            Node * m_head; // nó cabeça.
            Node * m_tail; // nó calda.

        public:
        //=== Public interface

        //!=== [I] Special members
        ///* (1) Default constructor that creates an empty list. 
        list()
        { 
            /*  Head & tail nodes.
             *     +---+    +---+
             *     |   |--->|   |--+
             *     | H |    | T |  |
             *  +--|   |<---|   |  |
             *  |  +---+    +---+  |
             *  |                  |
             * ===                ===
             *  =                  =
             */
            m_len = 0;
            m_head = new Node();
            m_tail = new Node();
            m_head->prev = nullptr;
            m_tail->next = nullptr;
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

        ///* (2) Constructs the list with 'count' default-inserted instances of T.
        explicit list( size_t count ) 
        {
            m_head = new Node();
            m_tail = new Node();
            m_head->prev = nullptr;
            m_tail->next = nullptr;
            m_len = count; // Set size of list.
            // If the list don't will be empty.
            if (count > 0) {
                Node * prev_node = m_head;
                for (size_t i{0}; i < count; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == count - 1) {
                        temp->next = m_tail;
                        m_tail->prev = temp;
                    }
                    temp->prev = prev_node;
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
        }

        ///* (3) Constructs the list with the contents of the range [first, last).
        template< typename InputIt >
        list( InputIt first, InputIt last )
        {
            m_head = new Node();
            m_tail = new Node();
            m_head->prev = nullptr;
            m_tail->next = nullptr;
            size_t sz = std::distance(first, last);
            m_len = sz; // Set size of list.
            // std::cout << m_len << std::endl;
            // std::cout << sz << std::endl;
            // The range is not empty.
            if (sz > 0) {
                Node * prev_node = m_head;
                for (auto i{0}; i < sz; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == sz - 1) {
                        temp->next = m_tail;
                        m_tail->prev = temp;
                    }
                    temp->prev = prev_node;
                    temp->data = *(first+i); // Set the value/data of node.
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
        }

        ///* (4) Copy constructor. Constructs a new list with the content of the 'clone_'.
        list( const list & clone_ )
        {
            m_head = new Node();
            m_tail = new Node();
            m_head->prev = nullptr;
            m_tail->next = nullptr;
            m_len = clone_.size(); // Set size of list.
            // The list passed is not empty.
            if (m_len > 0) {
                Node * prev_node = m_head;
                Node * clone_node = (clone_.m_head)->next;
                for (size_t i{0}; i < m_len; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == m_len - 1) {
                        temp->next = m_tail;
                        m_tail->prev = temp;
                    }
                    temp->prev = prev_node;
                    temp->data = clone_node->data; // Set the value/data of node.
                    clone_node = clone_node->next; // Get the next data of clone.
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
        }

        ///* (5) Constructs the list with the contents of the initializer list 'ilist_'.
        list( std::initializer_list<T> ilist_ )
        {
            m_head = new Node();
            m_tail = new Node();
            m_head->prev = nullptr;
            m_tail->next = nullptr;
            size_t sz = ilist_.size();
            m_len = sz; // Set size of list.
            // The initializer list is not empty.
            if (sz > 0) {
                Node * prev_node = m_head;
                for (size_t i{0}; i < sz; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == sz - 1) {
                        temp->next = m_tail;
                        m_tail->prev = temp;
                    }
                    temp->prev = prev_node;
                    temp->data = *(ilist_.begin()+i); // Set the value/data of node.
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
        }

        ///* (6) Destructs the list.
        ~list()
        {
            clear();
            delete m_head;
            delete m_tail;
        }

        ///* (7) Copy assignment operator. Replaces the contents with a copy of the contents of 'rhs'.
        list & operator=( const list & rhs )
        {
            if (this != &rhs) {
                this->clear();
                // this->m_len = rhs.size();
                auto first = rhs.cbegin();
                auto last = rhs.cend();
                auto last_this = this->end();
                // std::cout << "*first = " << *first << "\n";
                // std::cout << "*last = " << *last << "\n";
                // getchar();
                while(first != last){
                    // std::cout << "*first = " << *first << "\n";
                    // getchar();
                    this->insert(last_this, *first);      // Insere nó antes de last.
                    first++;                        // Vai para próximo elemento a ser inserido, se houver.
                }
            }
            return *this;
        }

        ///* (8) Replaces the contents with those identified by initializer list 'ilist_'.
        list & operator=( std::initializer_list<T> ilist_ )
        {
                this->clear();
                // this->m_len = ilist_.size();
                auto first = ilist_.begin();
                auto last = ilist_.end();
                auto last_this = this->end();
                while(first != last){
                    this->insert(last_this, *first);      // Insere nó antes de last.
                    first++;                        // Vai para próximo elemento a ser inserido, se houver.
                }
            return *this;
        }

        //!=== [II] ITERATORS

        /// Iterador para o início da lista encadeada.
        /*! Retorna iterador apontando para o primeiro nó válido da lista encadeada.
         *  @return Iterador apontando para o primeiro nó válido da lista encadeada.
         */
        iterator begin() { return iterator{m_head->next}; }

        /// Iterador constante para o início da lista encadeada.
        /*! Retorna iterador constante apontando para o primeiro nó válido da lista encadeada.
         *  @return Iterador constante apontando para o primeiro nó válido da lista encadeada.
         */
        const_iterator cbegin() const  { return const_iterator{m_head->next}; }

        /// Iterador para o final da lista encadeada.
        /*! Retorna iterador apontando para o nó calda da lista encadeada.
         *  @return Iterador apontando para o nó calda da lista encadeada.
         */
        iterator end() { return iterator{ m_tail }; }

        /// Iterador constante para o final da lista encadeada.
        /*! Retorna iterador constante apontando para o nó calda da lista encadeada.
         *  @return Iterador constante apontando para o nó calda da lista encadeada.
         */
        const_iterator cend() const  { return const_iterator{ m_tail }; }

        //!=== [III] Capacity/Status
        ///* Check if the vector is empty, that is, there are no elements.
        bool empty( void ) const { return m_len == 0; }
        
        ///* Check the size of the list.
        size_t size( void ) const { return m_len; }
        
        //!=== [IV] Modifiers
        ///* Remove all elements from the container.
        void clear()
        {
            // In an empty list we don't need to clear nothing.
            if (m_len > 0) {
                Node * temp1 = m_head->next;
                // Clean all nodes until it reaches the tail node.
                while (temp1 != m_tail) {
                    Node * temp2 = temp1->next;
                    delete temp1;
                    temp1 = temp2;
                }
                m_len = 0;
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
        }
        
        ///* Returns the object at the beginning of the list.
        T front( void )
        {
            // I can not return an element of an empty list.
            if (empty())
                throw std::length_error("[list::front()]: empty list.");
            // There is at least one element in the list.
            Node * temp = m_head->next;
            return temp->data;
        }
        T front( void ) const 
        {
            // I can not return an element of an empty list.
            if (empty())
                throw std::length_error("[list::front()]: empty list.");
            // There is at least one element in the list.
            Node * temp = m_head->next;
            return temp->data;
        }

        ///* Returns the object at the end of the list.
        T back( void )
        { 
            // I can not return an element of an empty list.
            if (empty())
                throw std::length_error("[list::back()]: empty list.");
            // There is at least one element in the list.
            Node * temp = m_tail->prev;
            return temp->data;
        }
        T back( void ) const 
        { 
            // I can not return an element of an empty list.
            if (empty())
                throw std::length_error("[list::back()]: empty list.");
            // There is at least one element in the list.
            Node * temp = m_tail->prev;
            return temp->data;
        }

        ///* Adds 'value' to the front of the list.
        void push_front( const T & value_ )
        {
            this->insert(this->begin(), value_);
        }
        
        ///* Adds 'value' to the end of the list.
        void push_back( const T & value_ )
        {
            this->insert(this->end(), value_);
        }

        ///* Removes the object at the front of the list.
        void pop_front( void )
        {
            Node * rem_node = m_head->next; //< Store the element that will be removed.
            Node * new_front = rem_node->next; //< Store the element that will be the new front.
            // Relink the nodes.
            m_head->next = new_front;
            new_front->prev = m_head;
            // Release memory.
            delete rem_node;
            m_len--;
        }

        ///* Removes the object at the end of the list.
        void pop_back( void )
        {
            Node * rem_node = m_tail->prev; //< Store the element that will be removed.
            Node * new_back = rem_node->prev; //< Store the element that will be the new back.
            // Relink the nodes.
            m_tail->prev = new_back;
            new_back->next = m_tail;
            // Release memory.
            delete rem_node;
            m_len--;
        }

        //!=== [IV-a] MODIFIERS W/ ITERATORS
        ///* Replaces the contents of the list 
        ///* with copies of the elements in the range [first; last).
        template < class InItr >
        void assign( InItr first_, InItr last_ )
        {
            size_t sz = last_ - first_;
            // Se a lista (this) for maior, precisar remover os nós excedentes.
            if (m_len > sz) {
                // Removes surplus nodes
                for (size_t i{sz}; i < m_len; i++) {
                    this->pop_back();
                }
            }
            // The range is not empty.
            if (sz > 0) {
                Node * prev_node = m_head;
                for (size_t i{0}; i < m_len; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == m_len - 1) {
                        temp->next = m_tail;
                    }
                    temp->prev = prev_node;
                    temp->data = *(first_+i); // Set the value/data of node.
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
                // Se a lista (this) for menor, precisa acrescentar mais nós.
                if (m_len < sz) {
                    // Add the values that did not fit the list size.
                    // While having elements missing to add, give a 'push_back' with the value of the position element.
                    for (size_t i{m_len}; i < sz; i++) {
                        this->push_back( *(first_+i) );
                    }
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
            m_len = sz; // Set size of list.
        }
        ///* Replaces the contents of the list
        ///* with copies of the elements in the initializer_list 'ilist_'.
        void assign( std::initializer_list<T> ilist_ )
        {
            size_t sz = ilist_.size();
            // Se a lista (this) for maior, precisar remover os nós excedentes.
            if (m_len > sz) {
                // Removes surplus nodes
                for (size_t i{sz}; i < m_len; i++) {
                    this->pop_back();
                }
            }
            // The range is not empty.
            if (sz > 0) {
                Node * prev_node = m_head;
                for (size_t i{0}; i < m_len; i++) {
                    Node * temp = new Node();
                    // The last node in the list before the tail.
                    if (i == m_len - 1) {
                        temp->next = m_tail;
                    }
                    temp->prev = prev_node;
                    temp->data = *(ilist_.begin()+i); // Set the value/data of node.
                    prev_node->next = temp;
                    prev_node = prev_node->next;
                }
                // Se a lista (this) for menor, precisa acrescentar mais nós.
                if (m_len < sz) {
                    // Add the values that did not fit the list size.
                    // While having elements missing to add, give a 'push_back' with the value of the position element.
                    for (size_t i{m_len}; i < sz; i++) {
                        this->push_back( *(ilist_.begin()+i) );
                    }
                }
            }
            else {
                m_head->next = m_tail;
                m_tail->prev = m_head;
            }
            m_len = sz; // Set size of list.
        }

        /*!
         *  Inserts a new value in the list before the iterator 'it'
         *  and returns an iterator to the new node.
         *
         *  \param pos_ An iterator to the position before which we want to insert the new data.
         *  \param value_ The value we want to insert in the list.
         *  \return An iterator to the new element in the list.
         */
        iterator insert( iterator pos_, const T & value_ ){
            Node * new_node = new Node(value_, pos_.m_ptr, pos_.m_ptr->prev); // Inicializa novo nó com o valor passado e com os links para o próximo nó e para o nó anterior.
            (pos_.m_ptr->prev)->next = new_node;    // Faz o next do anterior apontar para o novo nó.
            pos_.m_ptr->prev = new_node;            // Faz o prev do seguinte apontar para o novo nó.
            this->m_len++;
            return iterator{new_node};              // Retorna iterador apontando para o novo nó.
        }

        /*! Insere elementos do range [first_, last_) na lista antes da posição apontada pelo iterador pos_.
         *  @param pos_ Iterador apontando para a posição antes da qual serão inseridos os elementos do range [first_, last_) na lista.
         *  @param first_ Iterador apontando para o primeiro elemento do range.
         *  @param last_ Iterador apontando para a posição logo após o último elemento do range.
         *  @return Iterador apontando para a posição do primeiro elemento inserido do range.
         */
        template < typename InItr >
        iterator insert( iterator pos_, InItr first_, InItr last_ ) {
            Node * prev_node = pos_.m_ptr->prev; // Armazena o endereço do nó anterior ao pos_ antes das inserções de novos nós.
            while(first_ != last_){
                this->insert(pos_, *first_);      // Insere nó antes de pos_.
                first_++;                        // Vai para próximo elemento a ser inserido, se houver.
            }
            return iterator{prev_node->next};    // Retorna iterador para o primeiro nó inserido.
        }
        
        /*! Insere elementos da lista de inicialização ilist_ antes da posição apontada pelo iterador pos_.
         *  @param cpos_ Iterador apontando para a posição antes da qual serão inseridos os elementos da lista de inicialização ilist_.
         *  @param ilist_ Lista de inicialização a ser inserida.
         *  @return Iterador apontando para a posição do primeiro elemento inserido da lista de inicialização.
         */
        iterator insert( iterator cpos_, std::initializer_list<T> ilist_ ){
            Node * prev_node = cpos_.m_ptr->prev; // Armazena o endereço do nó anterior ao cpos_ antes das inserções de novos nós.
            auto first_ = ilist_.begin();
            auto last_ = ilist_.end();
            while(first_ != last_){
                this->insert(cpos_, *first_);      // Insere nó antes de cpos_.
                first_++;                        // Vai para próximo elemento a ser inserido, se houver.
            }
            return iterator{prev_node->next};    // Retorna iterador para o primeiro nó inserido.
        }

        /*!
         *  Erases the node pointed by 'it_' and returns an iterator
         *  to the node just past the deleted node.
         *
         *  \param it_ The node we wish to delete.
         *  \return An iterator to the node following the deleted node.
         */
        iterator erase( iterator it_ )
        {
            Node * rem_node = it_.m_ptr;
            // auto ite2 = 
            // auto ret_node{it_++};
            Node * prev_node = rem_node->prev;
            Node * next_node = rem_node->next;
            // Relink the nodes.
            prev_node->next = next_node;
            next_node->prev = prev_node;
            // iterator ite = next_node;
            // Release memory.
            delete rem_node;
            m_len--;
            return iterator{next_node};
        }
        /// Erase items from [start; end) and return a iterator just past the deleted node.
        /*! Remove elementos no range [start, end).
         *  @param start Iterador apontando para o primeiro elemento do range.
         *  @param end Iterador apontando para a posição logo após o último elemento do range.
         *  @return Iterador apontando para a nova posição do elemento seguinte ao último elemento apagado.
         */
        iterator erase( iterator start, iterator end )
        {
            iterator it_rem{start};
            iterator it_ret;
            while (start != end) {
                start++;
                it_ret = erase(it_rem);
                it_rem = start;
            }
            return iterator{it_ret};
        }

        const_iterator find( const T & value_ ) const
        { /* TODO */ return const_iterator{}; }

        iterator find( const T & value_ )
        { /* TODO */ return iterator{}; }

        //!=== [V] UTILITY METHODS
        
        /*! This method merges the two lists into one.
         *  The lists should be sorted in ascending order.
         *  The container other becomes empty after the operation.
         *  @param other Another container to transfer the content from.
         */
        void merge( list & other ){
            if(other.empty()) return;
            auto current = this->begin();                   // Primeiro nó válido de this.
            auto last = this->end();                        // Nó calda de this.
            auto other_current = other.begin();             // Primeiro nó válido de other.
            auto other_last = other.end();                  // Nó calda de other.
            auto other_next{other_current+1};               // Iterador auxiliar apontando para o nó seguinte de other.
            while(other_current != other_last && current != last){
                if(*other_current < *current){
                    (current.m_ptr->prev)->next = other_current.m_ptr;      // Faz o next do nó anterior ao atual apontar para o nó de other.
                    other_current.m_ptr->prev = current.m_ptr->prev;        // Faz o prev do nó de other apontar para o nó anterior ao atual.
                    other_current.m_ptr->next = current.m_ptr;              // Faz o next do nó de other apontar para o nó atual.
                    current.m_ptr->prev = other_current.m_ptr;              // Faz o prev do nó atual apontar para o nó de other.
                    other_current = other_next;                             // O nó atual de other passa a ser o próximo.
                    other_next++;
                }
                else current++;                                             // Vai para o próximo nó de this.
            }

            // Versão alternativa do if acima.
            if(other_current != other_last){
                (m_tail->prev)->next = other_current.m_ptr;             // Faz o next do último nó válido de this apontar para o nó atual de other.
                other_current.m_ptr->prev = m_tail->prev;               // Faz o prev do nó atual de other apontar para o último nó válido de this.
                (other.m_tail->prev)->next = m_tail;                    // Faz o next do último nó válido de other apontar para o nó calda de this.
                m_tail->prev = other.m_tail->prev;                      // Faz o prev do nó calda de this apontar para o último nó válido de other.
            }

            this->m_len += other.size();                // Atualiza o tamanho da lista.
            other.m_head->next = other.m_tail;          // Faz o next do head de other apontar para o tail de other.  
            other.m_tail->prev = other.m_head;          // Faz o prev do tail de other apontar para o head de other.
            other.m_len = 0;                            // Atualiza o tamanho de other.
        }

        /*! This method transfers all elements from other into *this.
         *  The elements are inserted before the element pointed to by pos.
         *  The container other becomes empty after the operation.
         *  The behavior is undefined if other refers to the same object as *this.
         *  @param pos Iterator pointing to the element before which the content will be inserted.
         *  @param other Another container to transfer the content from.
         */
        void splice( const_iterator pos, list & other ){
            if(other.empty()) return;
            auto first = other.begin();                 // Primeiro nó válido de other.
            auto other_last = other.end()-1;            // Último nó válido de other.
            (pos.m_ptr->prev)->next = first.m_ptr;      // Faz o next do nó anterior ao pos apontar para o primeiro nó de other.
            first.m_ptr->prev = pos.m_ptr->prev;        // Faz o prev do primeiro nó de other apontar para o nó anterior ao pos.
            other_last.m_ptr->next = pos.m_ptr;         // Faz o next do último nó de other apontar para pos.
            pos.m_ptr->prev = other_last.m_ptr;         // Faz o prev de pos apontar para o último nó de other.
            this->m_len += other.size();                // Atualiza o tamanho da lista.
            other.m_head->next = other.m_tail;          // Faz o next do head de other apontar para o tail de other.  
            other.m_tail->prev = other.m_head;          // Faz o prev do tail de other apontar para o head de other.
            other.m_len = 0;                            // Atualiza o tamanho de other.
        }

        /*! This method reverses the order of the elements in the container.
         */
        void reverse( void ){
            if(m_len <= 1) return;                      // Se a lista tiver um ou menos nós válidos retorne.
            auto first_node = this->begin();            // Primeiro nó válido da lista.
            auto last_node = this->end()-1;             // Último nó válido da lista.
            auto current_node{first_node};              // Iterador para o nó atual.
            Node * new_next{m_tail};                    // Variável auxiliar para armazenar o endereço do nó que será agora o seguinte.
            while(current_node != last_node){
                current_node.m_ptr->prev = current_node.m_ptr->next;    // Faz o prev do nó atual apontar para o antigo nó seguinte, que agora será o nó anterior.
                current_node.m_ptr->next = new_next;                    // Faz o next do nó atual apontar para o novo nó seguinte.
                new_next = current_node.m_ptr;                          // O nó atual será o novo nó seguinte do novo nó anterior.
                current_node--;
            }
            last_node.m_ptr->prev = m_head;             // Faz o prev do antigo último nó, novo primeiro nó, apontar para o head.
            last_node.m_ptr->next = new_next;           // Faz o next do antigo último nó, novo primeiro nó, apontar para o novo nó seguinte.
            m_head->next = last_node.m_ptr;             // Faz o next do head apontar para o novo primeiro nó.
            m_tail->prev = first_node.m_ptr;            // Faz o prev do tail apontar para o novo último nó.
        }

        //! This method removes all consecutive duplicate elements from the container.
        void unique( void ){
            auto first = this->begin();
            auto last = this->end();
            auto next{first};
            while(first != last){
                next = first+1;
                if(first.m_ptr->data == next.m_ptr->data) next = this->erase(next);
                else first++;
            }
        }

        void sort( void ){ return; }
    };

    //!=== [VI] OPERATORS
    ///* Checks if the contents of 'l1_' and 'l2_' are equal, that is,
    ///* whether l1_.size() == l2_.size() and each element in 'l1_'
    ///* compares equal with the element in 'l2_' at the same position.
    template < typename T >
    inline bool operator==( const sc::list<T> & l1_, const sc::list<T> & l2_ )
    {
        if (l1_.size() != l2_.size())
			return false;
		for (size_t i{0}; i < l1_.size(); i++)
			if ( *(l1_.cbegin()+i) != *(l2_.cbegin()+i) )
				return false;
		return true;
    }

    ///* Similar to the previous operator, but the opposite result.
    template < typename T >
    inline bool operator!=( const sc::list<T> & l1_, const sc::list<T> & l2_ )
    {
        if (not (l1_ == l2_))
			return true;
		return false;
    }
}
#endif
