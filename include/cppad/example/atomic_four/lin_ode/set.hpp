# ifndef CPPAD_EXAMPLE_ATOMIC_FOUR_LIN_ODE_SET_HPP
# define CPPAD_EXAMPLE_ATOMIC_FOUR_LIN_ODE_SET_HPP
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-22 Bradley M. Bell

CppAD is distributed under the terms of the
             Eclipse Public License Version 2.0.

This Source Code may also be made available under the following
Secondary License when the conditions for such availability set forth
in the Eclipse Public License, Version 2.0 are satisfied:
      GNU General Public License, Version 2.0 or later.
--------------------------------------------------------------------------- */
/*
$begin atomic_four_lin_ode_set.hpp$$
$spell
    mul
    lin
$$

$section atomic_lin_ode Set Routine: Example Implementation$$

$head Syntax$$
$icode%call_id% = %lin_ode%.set(%r%, %n_step%)%$$

$head Prototype$$
$srcthisfile%0%// BEGIN PROTOTYPE%// END PROTOTYPE%1%$$

$head Purpose$$
Stores the auxillary information for a an atomic operation that computes
the solution of a linear ODE.

$head r$$
This argument is the final value for the variable that the ODE is with
respect to.

$head n_step$$
This argument is the number of steps to use when approximating
to solution of the ODE.

$head Source$$
$srcthisfile%0%// BEGIN C++%// END C++%1%$$
$end
*/
// BEGIN C++
# include <cppad/example/atomic_four/lin_ode/lin_ode.hpp>

namespace CppAD { // BEGIN_CPPAD_NAMESPACE
// BEGIN PROTOTYPE
template <class Base>
size_t atomic_lin_ode<Base>::set(const Base& r, size_t n_step)
// END PROTOTYPE
{
    // thread
    size_t thread = thread_alloc::thread_num();
    //
    // work_[thread]
    if( work_[thread] == nullptr )
        work_[thread] = new call_vector;
    //
    // call_id
    size_t call_id = work_[thread]->size();
    //
    // call
    call_struct call;
    call.r      = r;
    call.n_step = n_step;
    call.thread = thread;
    //
    // work_[thread]
    work_[thread]->push_back( call );
    //
    return call_id;
}
} // END_CPPAD_NAMESPACE
// END C++
# endif
