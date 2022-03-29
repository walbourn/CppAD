# ifndef CPPAD_EXAMPLE_ATOMIC_FOUR_LIN_ODE_FORWARD_HPP
# define CPPAD_EXAMPLE_ATOMIC_FOUR_LIN_ODE_FORWARD_HPP
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-22 Bradley M. Bell

CppAD is distributed under the terms of the
             Eclipse Public License Version 2.0.

This Source Code may also be made available under the following
Secondary License when the conditions for such availability set forth
in the Eclipse Public License, Version 2.0 are satisfied:
      GNU General Public License, Version 2.0 or later.
---------------------------------------------------------------------------- */
/*
$begin atomic_four_lin_ode_forward.hpp$$
$spell
    Jacobian
    jac
$$

$section
Atomic Linear ODE Forward Mode: Example Implementation
$$

$head Purpose$$
The $code forward$$ routine overrides the virtual functions
used by the atomic_four base; see
$cref/forward/atomic_four_forward/$$.

$head Source$$
$srcthisfile%0%// BEGIN C++%// END C++%1%$$
$end
*/
// BEGIN C++
# include <cppad/example/atomic_four/lin_ode/lin_ode.hpp>

namespace CppAD { // BEGIN_CPPAD_NAMESPACE
//
// forward override for Base matrix multiply
template <class Base>
bool atomic_lin_ode<Base>::forward(
    size_t                                     call_id     ,
    const CppAD::vector<bool>&                 select_y    ,
    size_t                                     order_low   ,
    size_t                                     order_up    ,
    const CppAD::vector<Base>&                 taylor_x    ,
    CppAD::vector<Base>&                       taylor_y    )
{
    // only order zero implemented so far
    if( order_up > 0 )
        return false;
# ifndef NDEBUG
    // n, m
    size_t n     = taylor_x.size();
    size_t m     = taylor_y.size();
    assert( n == m * m + m);
# endif
    //
    // r, n_step
    Base r;
    size_t n_step;
    get(call_id, r, n_step);
    //
    // taylor_y
    base_lin_ode(r, n_step, taylor_x, taylor_y);
    //
    return true;
}
} // END_CPPAD_NAMESPACE
// END C++
# endif
