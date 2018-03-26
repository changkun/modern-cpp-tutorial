//
// 4.3.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// std::tuple 及其操作


#include <tuple>
#include <iostream>
#include <boost/variant.hpp>

auto get_student(int id)
{
    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    // 返回类型被推断为 std::tuple<double, char, std::string>
    return std::make_tuple(0.0, 'D', "null");
}

template <size_t n, typename... T>
boost::variant<T...> _tuple_index(size_t i, const std::tuple<T...>& tpl) {
    if (i == n)
        return std::get<n>(tpl);
    else if (n == sizeof...(T) - 1)
        throw std::out_of_range("越界.");
    else
        return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(i, tpl);
}
template <typename... T>
boost::variant<T...> tuple_index(size_t i, const std::tuple<T...>& tpl) {
    return _tuple_index<0>(i, tpl);
}

template <typename T>
auto tuple_len(T &tpl) {
    return std::tuple_size<T>::value;
}

int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
    << "GPA: " << std::get<0>(student) << ", "
    << "成绩: " << std::get<1>(student) << ", "
    << "姓名: " << std::get<2>(student) << '\n';
    
    double gpa;
    char grade;
    std::string name;
    
    // 元组进行拆包
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
    << "GPA: " << gpa << ", "
    << "成绩: " << grade << ", "
    << "姓名: " << name << '\n';
    
    
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    std::cout << std::get<std::string>(t) << std::endl;
    // std::cout << std::get<double>(t) << std::endl;   // 非法, 引发编译期错误
    std::cout << std::get<3>(t) << std::endl;
    
    // 拼接元组
    auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
    
    // 迭代
    for(int i = 0; i != tuple_len(new_tuple); ++i)
        // 运行期索引
        std::cout << tuple_index(i, new_tuple) << std::endl;
}
