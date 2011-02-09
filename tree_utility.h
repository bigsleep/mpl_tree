#ifndef SYKES_MPL_TREE_UTILITY_H
#define SYKES_MPL_TREE_UTILITY_H
#include "tree_fwd.h"
#include "deref.h"
#include "vector_utility.h"

namespace sykes{
namespace mpl{
    //-----------------------------------------------------------
    //    has_child
    //-----------------------------------------------------------
    namespace detail{
        template<bool IsLeaf, branch B, typename Iterator>
        struct has_child_impl;
    }
    
    template<typename Iterator>
    struct has_child_left
    {
        static bool const value =
            detail::has_child_impl<
                deref<Iterator>::is_leaf,
                branch::left,
                Iterator>::value;
    };
    
    template<typename Iterator>
    struct has_child_right
    {
        static bool const value =
            detail::has_child_impl<
                deref<Iterator>::is_leaf,
                branch::right,
                Iterator>::value;
    };
    
    template<typename Iterator>
    struct has_child
    {
        static bool const value =
            has_child_left<Iterator>::value ||
            has_child_right<Iterator>::value;
    };
    
    namespace detail{
        template<branch B, typename Iterator>
        struct has_child_impl<true, B, Iterator>
        {
            static bool const value = false;
        };
        
        template<branch B, typename Iterator>
        struct has_child_impl<false, B, Iterator>
        {
            static bool const
                value = !std::is_same<
                    typename get_child<
                        B,
                        typename deref<Iterator>::subtree
                    >::type,
                    null_type
                >::value;
        };
        
    }//---- detail
    
    //-----------------------------------------------------------
    //    get_child
    //-----------------------------------------------------------
    template<typename Iterator>
    struct get_child_left;
    
    template<typename Tag, typename Route, typename Tree>
    struct get_child_left<tree_iterator<Tag, Route, Tree>>
    {
        static_assert(has_child_left<tree_iterator<Tag, Route, Tree>>::value, "sykes::mpl::get_child_left");
        typedef tree_iterator<
            Tag,
            typename push_back<
                Route,
                std::integral_constant<branch, branch::left>>::type,
            Tree> type;
    };
    
    template<typename Iterator>
    struct get_child_right;
    
    template<typename Tag, typename Route, typename Tree>
    struct get_child_right<tree_iterator<Tag, Route, Tree>>
    {
        static_assert(has_child_right<tree_iterator<Tag, Route, Tree>>::value, "sykes::mpl::get_child_left");
        typedef tree_iterator<
            Tag,
            typename push_back<
                Route,
                std::integral_constant<branch, branch::right>>::type,
            Tree> type;
    };
    
    //-----------------------------------------------------------
    //    has_parent
    //-----------------------------------------------------------
    template<typename Iterator>
    struct has_parent;
    
    template<typename Tag, branch Bhead, branch ... Btail, typename Tree>
    struct has_parent<tree_iterator<Tag, vector_c<branch, Bhead, Btail...>, Tree>>
    {
        static bool const value = true &&
            !std::is_same<
                typename deref<
                    tree_iterator<
                        Tag, typename pop_back<vector_c<branch, Bhead, Btail...>>::type, Tree
                    >
                >::type,
                null_type
            >::value;
    };
    
    template<typename Tag, typename Tree>
    struct has_parent<tree_iterator<Tag, vector_c<branch>, Tree>>
    {
        static bool const value = false;
    };
    
    //-----------------------------------------------------------
    //    get_parent
    //-----------------------------------------------------------
    template<typename Iterator>
    struct get_parent;
    
    template<typename Tag, typename Route, typename Tree>
    struct get_parent<tree_iterator<Tag, Route, Tree>>
    {
        static_assert(has_parent<tree_iterator<Tag, Route, Tree>>::value, "sykes::mpl::get_parent");
        typedef tree_iterator<
            Tag,
            typename pop_back<Route>::type,
            Tree> type;
    };
    
    //-----------------------------------------------------------
    //    has_sibling
    //-----------------------------------------------------------
    namespace detail{
        template<bool HasParent, typename Iterator>
        struct has_sibling_impl;
    }//---- detail
    
    template<typename Iterator>
    struct has_sibling
    {
        static bool const value =
            detail::has_sibling_impl<
                has_parent<Iterator>::value,
                Iterator>::value;
    };
    
    template<typename Iterator>
    struct has_older_sibling;
    
    template<typename Tag, typename Route, typename Tree>
    struct has_older_sibling<tree_iterator<Tag, Route, Tree>>
    {
        static bool const
            value = has_sibling<tree_iterator<Tag, Route, Tree>>::value &&
                (at<size<Route>::value - 1, Route>::value == branch::right);
    };
    
    template<typename Tag, typename Tree>
    struct has_older_sibling<tree_iterator<Tag, vector_c<branch>, Tree>>
    {
        static bool const value = false;
    };
    
    template<typename Iterator>
    struct has_younger_sibling;
    
    template<typename Tag, typename Route, typename Tree>
    struct has_younger_sibling<tree_iterator<Tag, Route, Tree>>
    {
        static bool const
            value = has_sibling<tree_iterator<Tag, Route, Tree>>::value &&
                (at<size<Route>::value - 1, Route>::value == branch::left);
    };
    
    template<typename Tag, typename Tree>
    struct has_younger_sibling<tree_iterator<Tag, vector_c<branch>, Tree>>
    {
        static bool const value = false;
    };
    
    namespace detail{
        template<typename Tag, typename Route, typename Tree>
        struct has_sibling_impl<true, tree_iterator<Tag, Route, Tree>>
        {
            static bool const
                value = ((at<size<Route>::value - 1, Route>::value == branch::left) &&
                    (has_child_right<typename get_parent<tree_iterator<Tag, Route, Tree>>::type>::value)) ||
                    ((at<size<Route>::value - 1, Route>::value == branch::right) &&
                    (has_child_left<typename get_parent<tree_iterator<Tag, Route, Tree>>::type>::value));
        };
        
        template<typename Iterator>
        struct has_sibling_impl<false, Iterator>
        {
            static bool const value = false;
        };
        
    }//---- detail
    //-----------------------------------------------------------
    //    get_sibling
    //-----------------------------------------------------------
    template<typename Iterator>
    struct get_sibling;
    
    template<typename Tag, typename Route, typename Tree>
    struct get_sibling<tree_iterator<Tag, Route, Tree>>
    {
        static_assert(has_sibling<tree_iterator<Tag, Route, Tree>>::value, "sykes::mpl::get_sibling");
        typedef tree_iterator<
            Tag,
            typename
                replace_at<
                    size<Route>::value - 1,
                    Route, 
                    std::integral_constant<
                        branch,
                        (at<size<Route>::value - 1, Route>::value == branch::left) ? branch::right : branch::left
                    >
                >::type,
            Tree> type;
    };
}}//----

#endif

