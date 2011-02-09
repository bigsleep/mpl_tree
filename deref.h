#ifndef SYKES_MPL_TREE_DEREF_H
#define SYKES_MPL_TREE_DEREF_H

#include "tree_fwd.h"
namespace sykes{
namespace mpl{    
    namespace detail{
        template<typename Route, typename Tree>
        struct deref_impl;
    }
    
    template<typename TraverseTag, typename Route, typename Tree>
    struct deref<tree_iterator<TraverseTag, Route, Tree>>
    {
        typedef typename detail::deref_impl<Route, Tree>::type type;
        typedef typename detail::deref_impl<Route, Tree>::subtree subtree;
        static bool const is_leaf = detail::deref_impl<Route, Tree>::is_leaf;
    };
    
    namespace detail{
        template<typename T1, typename T2, typename T3>
        struct deref_impl<vector_c<branch>, tree<T1, T2, T3>>
        {
            static_assert(!std::is_same<T1, null_type>::value, "sykes::mpl::detail::deref_impl");
            typedef typename tree<T1, T2, T3>::type type;
            typedef tree<T1, T2, T3> subtree;
            static bool const is_leaf = false;
        };
        
        template<typename T1>
        struct deref_impl<vector_c<branch>, T1>
        {
            static_assert(!std::is_same<T1, null_type>::value, "sykes::mpl::detail::deref_impl");
            static_assert(!std::is_same<T1, null_type>::value, "struct sykes::mpl::detail::deref_helper");
            typedef T1 type;
            typedef T1 subtree;
            static bool const is_leaf = true;
        };
        
        template<branch B1, branch ... B2, typename Tree>
        struct deref_impl<vector_c<branch, B1, B2...>, Tree>
        {
            static_assert(is_tree<Tree>::value, "struct sykes::mpl::detail::deref_helper");
            typedef typename
                deref_impl<
                    vector_c<branch, B2...>,
                    typename get_child<B1, Tree>::type
                >::type type;
            
            typedef typename
                deref_impl<
                    vector_c<branch, B2...>,
                    typename get_child<B1, Tree>::type
                >::subtree subtree;
            
            static bool const
                is_leaf = deref_impl<
                    vector_c<branch, B2...>,
                    typename get_child<B1, Tree>::type
                >::is_leaf;
        };
    }//---- detail
    
}}//----
#endif

