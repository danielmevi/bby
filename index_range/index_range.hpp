//
//
//
//
//
//


#ifndef INDEX_RANGE_HEADER
#define INDEX_RANGE_HEADER

namespace dmv {

template<class T>
class Iterator {
public:
    Iterator(T const position) : position_(position) {}
    T operator*() {return position_;}
    Iterator<T> operator++() {return Iterator<T>{++position_};}
    bool operator!=(Iterator<T>& iterator) { return position_ != *iterator;}
private:
    T position_;
} ;

template<class T>
class Wrapper {
public:
    Wrapper(T const end) : begin_(0), end_(end) {}
    Iterator<T> begin() {return Iterator<T>{begin_};}
    Iterator<T> end() { return Iterator<T>{end_};}
private:
    T const begin_;
    T const end_;
};

template<class T>
auto range(T const& container) {
    return Wrapper<typename T::size_type>(container.size());
}

}
#endif // INDEX_RANGE_HEADER
