//
// 4.3.tuples.cpp
// chapter 04 containers
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//


#include <tuple>
#include <iostream>
#include <variant>
#include <utility>

auto get_student(int id)
{
    if (id == 0)
        return std::make_tuple(3.8, 'A', "John");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "Jack");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "Ive");
    // return type is std::tuple<double, char, std::string>
    return std::make_tuple(0.0, 'D', "null");
}

template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if constexpr (n >= sizeof...(T))
        throw std::out_of_range("out of range.");
    if (i == n)
        return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tpl) };
    return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(tpl, i);
}
template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}

template <typename T>
auto tuple_len(T &tpl) {
    return std::tuple_size<T>::value;
}

// idiomatic traversal: C++17 fold expression + std::index_sequence
template <typename Func, typename Tuple, std::size_t... idx>
void iterate_impl(Func&& f, Tuple&& tpl, std::index_sequence<idx...>) {
    (f(std::get<idx>(std::forward<Tuple>(tpl))), ...);
}
template <typename Func, typename Tuple>
void iterate_tuple(Func&& f, Tuple&& tpl) {
    iterate_impl(std::forward<Func>(f), std::forward<Tuple>(tpl),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

// idiomatic traversal: C++20 lambda with explicit template parameters
template <typename Func, typename... Args>
void iterate_tuple_cpp20(Func f, const std::tuple<Args...>& tpl) {
    [&]<std::size_t... idx>(std::index_sequence<idx...>) {
        (f(std::get<idx>(tpl)), ...);
    }(std::make_index_sequence<sizeof...(Args)>());
}

template <typename T0, typename ... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) { 
    std::visit([&](auto && x){ s << x;}, v); 
    return s;
}

int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: "   << std::get<0>(student) << ", "
              << "Grade: " << std::get<1>(student) << ", "
              << "Name: "  << std::get<2>(student) << '\n';
    
    double gpa;
    char grade;
    std::string name;
    
    // tuple unpack
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: "   << gpa   << ", "
              << "Grade: " << grade << ", "
              << "Name: "  << name  << '\n';
    
    
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    std::cout << std::get<std::string>(t) << std::endl;
    // std::cout << std::get<double>(t) << std::endl;   // illegal, runtime error
    std::cout << std::get<3>(t) << std::endl;
    
    // concat
    auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
    
    // iteration via runtime indexing
    for(int i = 0; i != tuple_len(new_tuple); ++i) {
        std::cout << tuple_index(new_tuple, i) << std::endl; // runtime indexing
    }

    // idiomatic traversal (C++17 fold + index_sequence)
    auto print = [](const auto& v) { std::cout << v << ' '; };
    iterate_tuple(print, new_tuple);
    std::cout << std::endl;

    // idiomatic traversal (C++20 templated lambda)
    iterate_tuple_cpp20(print, new_tuple);
    std::cout << std::endl;
}
