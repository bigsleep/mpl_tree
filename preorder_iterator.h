#ifndef SYKES_MPL_PREORDER_ITERATOR
#define SYKES_MPL_PREORDER_ITERATOR
#include "tree_fwd.h"
#include "deref.h"
#include "tree_utility.h"

namespace sykes{
namespace mpl{
    //-----------------------------------------------------------
    //    preorder_begin
    //-----------------------------------------------------------
    template<typename Tree>
    struct preorder_begin
    {
        static_assert(is_tree<Tree>::value, "struct sykes::mpl::preorder_begin");
        typedef tree_iterator<preorder_tag, vector_c<branch>, Tree> type;
    };
    
    //-----------------------------------------------------------
    //    preorder_end
    //-----------------------------------------------------------
    template<typename Tree>
    struct preorder_end
    {
        static_assert(is_tree<Tree>::value, "struct sykes::mpl::preorder_end");
        typedef null_type type;
    };
    
    //-----------------------------------------------------------
    //    next
    //-----------------------------------------------------------
    namespace detail{
        template<bool HasChild, typename Iterator>
        struct next_preorder_impl;
    }//----
    
    template<typename Route, typename Tree>
    struct next<tree_iterator<preorder_tag, Route, Tree>>
    {
        typedef typename
            detail::next_preorder_impl<
                has_child<tree_iterator<preorder_tag, Route, Tree>>::value,
                tree_iterator<preorder_tag, Route, Tree>
            >::type type;
    };
    
    namespace detail{
        template<bool HasParent, bool HasYoungerSibling, typename Curr>
        struct next_preorder_impl2;
        
        template<typename Route, typename Tree>
        struct next_preorder_impl<true, tree_iterator<preorder_tag, Route, Tree>>
        {
            typedef typename std::conditional<
                has_child_left<tree_iterator<preorder_tag, Route, Tree>>::value,
                tree_iterator<preorder_tag,
                    typename push_back<Route, std::integral_constant<branch, branch::left>>::type, Tree>,
                tree_iterator<preorder_tag,
                    typename push_back<Route, std::integral_constant<branch, branch::right>>::type, Tree>
            >::type type;
        };
        
        template<typename Iterator>
        struct next_preorder_impl<false, Iterator>
        {
            typedef typename next_preorder_impl2<
                    has_parent<Iterator>::value,
                    has_younger_sibling<Iterator>::value,
                    Iterator
                >::type type;
        };
        
        template<bool HasYoungerSibling, typename Curr>
        struct next_preorder_impl2<false, HasYoungerSibling, Curr>
        {
            typedef null_type type;
        };
        
        template<typename Curr>
        struct next_preorder_impl2<true, false, Curr>
        {
            typedef typename next_preorder_impl2<
                    has_parent<typename get_parent<Curr>::type>::value,
                    has_younger_sibling<typename get_parent<Curr>::type>::value,
                    typename get_parent<Curr>::type
                >::type type;
        };
        
        template<typename Curr>
        struct next_preorder_impl2<true, true, Curr>
        {
            typedef typename get_sibling<Curr>::type type;
        };
    }//---- detail
}}//----
#endif

