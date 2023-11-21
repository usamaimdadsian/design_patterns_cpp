/*
    CLASS OR TYPE SHOULD BE OPEN FOR EXTENSION CLOSED FOR MODIFICATION
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color
{
    Red,
    Green,
    Blue
};

enum class Size
{
    Small,
    Medium,
    Large
};

struct Product
{
    string name;
    Color color;
    Size size;
};

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T *item) = 0;
};

template <typename T>
struct Filter
{
    virtual vector<T *> filter(
        vector<T *> items,
        Specification<T> &spec)
        const = 0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product *> filter(
        vector<Product *> items, Specification<Product> &spec) const override
    {
        // Your filtering logic here
        vector<Product *> result;
        for (auto &p : items)
        {
            if (spec.is_satisfied(p))
            {
                result.push_back(p);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;
    explicit ColorSpecification(const Color color) : color{color} {}
    bool is_satisfied(Product *item) override
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;
    explicit SizeSpecification(const Size size) : size{size} {}
    bool is_satisfied(Product *item) override
    {
        return item->size == size;
    }
};

template <typename T>
struct AndSpecification : Specification<T>
{
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first{first}, second{second} {}

    bool is_satisfied(T *item) override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template <typename T> AndSpecification<T> operator&&(Specification<T>& first, Specification<T>& second)
{
    return AndSpecification(first,second);
}

// struct ProductFilter
// {
//     typedef vector<Product *> Items;

//     Items by_color(Items items, Color color)
//     {
//         Items result;
//         for (auto &i : items)
//             if (i->color == color)
//                 result.push_back(i);

//         return result;
//     }
//     Items by_size(Items items, Size size)
//     {
//         Items result;
//         for (auto &i : items)
//             if (i->size == size)
//                 result.push_back(i);

//         return result;
//     }
//     Items by_color_and_size(Items items, Size size, Color color)
//     {
//         Items result;
//         for (auto &i : items)
//             if (i->size == size && i->color == color)
//                 result.push_back(i);

//         return result;
//     }
// };

int main()
{
    Product apple{"Apple", Color::Green, Size::Small};
    Product banana{"Banana", Color::Red, Size::Medium};
    Product car{"Car", Color::Blue, Size::Large};

    vector<Product *> products = {&apple, &banana, &car};

    // ProductFilter filter;

    // // Test filtering by color
    // ProductFilter::Items greenProducts = filter.by_color(products, Color::Green);
    // cout << "Green products:" << endl;
    // for (auto &product : greenProducts)
    // {
    //     cout << "- " << product->name << endl;
    // }

    // // Test filtering by size
    // ProductFilter::Items largeProducts = filter.by_size(products, Size::Large);
    // cout << "Large products:" << endl;
    // for (auto &product : largeProducts)
    // {
    //     cout << "- " << product->name << endl;
    // }

    // // Test filtering by color and size
    // ProductFilter::Items greenAndSmallProducts = filter.by_color_and_size(products, Size::Small, Color::Green);
    // cout << "Green and Small products:" << endl;
    // for (auto &product : greenAndSmallProducts)
    // {
    //     cout << "- " << product->name << endl;
    // }

    BetterFilter bf;
    ColorSpecification green(Color::Green);
    SizeSpecification small(Size::Small);
    // AndSpecification green_and_small(green, small);
    auto green_and_small = green && small;

    auto green_things = bf.filter(products, green);
    for (auto &x : green_things)
        cout << x->name << " is green" << endl;

    auto small_things = bf.filter(products, small);
    for (auto &x : small_things)
        cout << x->name << " is small" << endl;

    auto green_and_small_things = bf.filter(products, green_and_small);
    for (auto &x : green_and_small_things)
        cout << x->name << " is green and small." << endl;

    return 0;
}
