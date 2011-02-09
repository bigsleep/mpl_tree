#ifndef SYKES_MPL_TREE_FWD_H
#define SYKES_MPL_TREE_FWD_H

#include <type_traits>
#include "vector_c.h"

namespace sykes{
namespace mpl{
    //-----------------------------------------------------------
    //    null_type
    //-----------------------------------------------------------
    struct null_type{};
    
    //-----------------------------------------------------------
    //    branch, route
    //-----------------------------------------------------------
    enum class branch
    {
        left,
        right
    };
    
    //-----------------------------------------------------------
    //    iterator tag
    //-----------------------------------------------------------
    struct preorder_tag{};
    struct postorder_tag{};
    struct inorder_tag{};
    
    //-----------------------------------------------------------
    //    template struct tree
    //-----------------------------------------------------------
    template<typename T, typename Left, typename Right>
    struct tree
    {
        typedef T type;
        typedef Left left_type;
        typedef Right right_type;
    };
    
    //-----------------------------------------------------------
    //    tree_iterator
    //-----------------------------------------------------------
    template<typename TraverseTag, typename Route, typename Tree>
    struct tree_iterator;
    
    //-----------------------------------------------------------
    //    begin, end
    //-----------------------------------------------------------
    template<typename Tree>
    struct preorder_begin;
    template<typename Tree>
    struct postorder_begin;
    template<typename Tree>
    struct inorder_begin;
    template<typename Tree>
    struct preorder_end;
    template<typename Tree>
    struct postorder_end;
    template<typename Tree>
    struct inorder_end;
    
    //-----------------------------------------------------------
    //    next
    //-----------------------------------------------------------
    template<typename Iterator>
    struct next;
    
    //-----------------------------------------------------------
    //    deref
    //-----------------------------------------------------------
    template<typename Iterator>
    struct deref;
    
    //-----------------------------------------------------------
    //    is_tree
    //-----------------------------------------------------------
    template<typename T>
    struct is_tree
    {
        static bool const value = false;
    };
    
    template<typename T1, typename T2, typename T3>
    struct is_tree<tree<T1, T2, T3>>
    {
        static bool const value = true;
    };
    
    //-----------------------------------------------------------
    //    get_child
    //-----------------------------------------------------------
    template<branch B, typename TreeOrIterator>
    struct get_child;
    
    template<typename T1, typename T2, typename T3>
    struct get_child<branch::left, tree<T1, T2, T3>>
    {
        typedef T2 type;
    };
    
    template<typename T1, typename T2, typename T3>
    struct get_child<branch::right, tree<T1, T2, T3>>
    {
        typedef T3 type;
    };
}}//----
#endif

