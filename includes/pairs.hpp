#ifndef PAIRS_HPP
#define PAIRS_HPP

namespace ft{

template <typename U, typename V>
class pair
{
    public:
        U   first;
        V   second;
        //constructors and destructor
        pair();
        pair(U const &a, V const &b);
        pair(const pair &obj);
        ~pair();
        //operators
        pair &operator=(const pair &obj);

};
//member func
template <typename U, typename V>
pair<U,V>::pair(){}

template <typename U, typename V>
pair<U,V>::pair(const U &a, const V &b): first(a), second(b){}

template <typename U, typename V>
pair<U,V>::pair(const pair<U,V> &obj): first(obj.first), second(obj.second){
}

template <typename U, typename V>
pair<U,V>::~pair(){}

template <typename U, typename V>
pair<U,V> &pair<U,V>::operator=(const pair &obj) {
    if (this != &obj){
        first = obj.first;
        second = obj.second;
    }
    return *this;
}
//non-member func
template<typename U, typename V>
bool    operator==(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first == rh.first && lh.second == rh.second;
}

template<typename U, typename V>
bool    operator!=(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first != rh.first && lh.second != rh.second;
}
//page 38 in STL book

template<typename U, typename V>
bool    operator<(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first < rh.first || lh.second < rh.second;
}

template<typename U, typename V>
bool    operator<=(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first <= rh.first || lh.second <= rh.second;
}

template<typename U, typename V>
bool    operator>(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first > rh.first || lh.second > rh.second;
}

template<typename U, typename V>
bool    operator>=(const pair<U,V> &lh, const pair<U,V> &rh){
    return lh.first >= rh.first || lh.second >= rh.second;
}

template <typename U, typename V>
ft::pair<U, V> make_pair(U const &a, V const &b){
    return ft::pair<U, V>(a, b);
}

}

#endif