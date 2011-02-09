#ifndef SYKES_MPL_VECTOR_C_H
#define SYKES_MPL_VECTOR_C_H

namespace sykes{
namespace mpl{
    template<typename Tp, Tp ... V>
    struct vector_c{
        typedef Tp value_type;
    };
}}//----
#endif

