
#include <iostream>
#include "tree.h"

int main()
{
    using namespace sykes::mpl;
    typedef
        tree<int,
            tree<double,
                tree<unsigned char, char, float>,
                unsigned int
            >,
            tree<long double, int, int>
        > mytree;
    // get_parent
    {
        typedef tree_iterator<void, vector_c<branch, branch::left, branch::right>, mytree> it;
        typedef deref<it>::type type;
        static_assert(std::is_same<type, unsigned int>::value, "fail");
        
        typedef get_parent<it>::type it2;
        typedef deref<it2>::type type2;
        static_assert(std::is_same<type2, double>::value, "fail");
        
        typedef get_parent<it2>::type it3;
        typedef deref<it3>::type type3;
        static_assert(std::is_same<type3, int>::value, "fail");
        
    }
    
    // get_child
    {
        typedef tree_iterator<void, vector_c<branch>, mytree> root;
        typedef get_child_left<root>::type it;
        typedef deref<it>::type type;
        static_assert(std::is_same<type, double>::value, "fail");
        
        typedef get_child_left<it>::type it2;
        typedef deref<it2>::type type2;
        static_assert(std::is_same<type2, unsigned char>::value, "fail");
        
        typedef get_child_left<it2>::type it3;
        typedef deref<it3>::type type3;
        static_assert(std::is_same<type3, char>::value, "fail");
        
        typedef get_child_right<root>::type it4;
        typedef deref<it4>::type type4;
        static_assert(std::is_same<type4, long double>::value, "fail");
    }
    
    // preorder_iterator
    {
        typedef preorder_begin<mytree>::type it1;
        typedef deref<it1>::type type1;
        static_assert(std::is_same<type1, int>::value, "fail");
        
        typedef next<it1>::type it2;
        typedef deref<it2>::type type2;
        static_assert(std::is_same<type2, double>::value, "fail");
        
        typedef next<it2>::type it3;
        typedef deref<it3>::type type3;
        static_assert(std::is_same<type3, unsigned char>::value, "fail");
        
        typedef next<it3>::type it4;
        typedef deref<it4>::type type4;
        static_assert(std::is_same<type4, char>::value, "fail");
        
        typedef next<it4>::type it5;
        typedef deref<it5>::type type5;
        static_assert(std::is_same<type5, float>::value, "fail");
        
        typedef next<it5>::type it6;
        typedef deref<it6>::type type6;
        static_assert(std::is_same<type6, unsigned int>::value, "fail");
        
        typedef next<it6>::type it7;
        typedef deref<it7>::type type7;
        static_assert(std::is_same<type7, long double>::value, "fail");
        
        typedef next<it7>::type it8;
        typedef deref<it8>::type type8;
        static_assert(std::is_same<type8, int>::value, "fail");
        
        typedef next<it8>::type it9;
        typedef deref<it9>::type type9;
        static_assert(std::is_same<type9, int>::value, "fail");
        
        typedef next<it9>::type it10;
        static_assert(std::is_same<it10, preorder_end<mytree>::type>::value, "fail");
    }
    std::cout << "hello world" << std::endl;
}

