/* concept, tag dispatch テスト用 */

#include <iostream>
using namespace std;

/* Tag Dispatch */
struct tag_int
{
};

template <class T>
void _print(const T &value, tag_int)
{
    printf("%d\n", value);
}

class Int
{
    int value;

public:
    operator int() { return value; }
    Int(int i) : value(i) {}
    using tag = tag_int;
};

template <class T>
concept HasTag = requires(T) {
    typename T::tag;
};

// T が tag の型を持つことを判定したい
template <class T>
    requires HasTag<T>
void print(const T &value)
{
    _print(value, T::tag());
}

// Test
void test()
{
    Int it = int(10);
    print(it);
}

/* Tag Dispatch End */

/* concept */

template <class T>
concept Drawable = requires(T &x) {
    x.draw(); // 型Tに要求する操作をセミコロン区切りで列挙する
};

template <Drawable T>
void f(T const &x)
{
    x.draw();
}

// bool型は定数式でコンセプトを定義できる
template <class T>
concept Integral = std::is_integral_v<T>;

template <class T, class U>
concept EqualityComparable = requires(T a, U b) {
    {
        a == b
    } -> std::convertible_to<bool>;
};

template <class T, class U>
concept SizeType = requires(T c) {
    typename T::size_type; // 型Tがメンバ型として size_type を持っていること
};

/* concept end */