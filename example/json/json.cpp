// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-22 Bradley M. Bell
// ----------------------------------------------------------------------------

// CPPAD_HAS_* defines
# include <cppad/configure.hpp>

// system include files used for I/O
# include <iostream>

// C style asserts
# include <cassert>

// for thread_alloc
# include <cppad/utility/thread_alloc.hpp>

// test runner
# include <cppad/utility/test_boolofvoid.hpp>

// BEGIN_SORT_THIS_LINE_PLUS_2
// external compiled tests
extern bool add_op(void);
extern bool atom4_op(void);
extern bool atom_op(void);
extern bool azmul_op(void);
extern bool cexp_op(void);
extern bool comp_op(void);
extern bool discrete_op(void);
extern bool div_op(void);
extern bool from_json(void);
extern bool get_started(void);
extern bool mul_op(void);
extern bool pow_op(void);
extern bool print_op(void);
extern bool sparse(void);
extern bool sub_op(void);
extern bool sum_op(void);
extern bool to_json(void);
extern bool unary_op(void);
// END_SORT_THIS_LINE_MINUS_1

// main program that runs all the tests
int main(void)
{   std::string group = "example/json";
    size_t      width = 20;
    CppAD::test_boolofvoid Run(group, width);

    // This line is used by test_one.sh

    // BEGIN_SORT_THIS_LINE_PLUS_2
    // external compiled tests
    Run( add_op,               "add_op"          );
    Run( atom4_op,             "atom4_op"        );
    Run( azmul_op,             "azmul_op"        );
    Run( cexp_op,              "cexp_op"         );
    Run( comp_op,              "comp_op"         );
    Run( discrete_op,          "discrete_op"     );
    Run( div_op,               "div_op"          );
    Run( from_json,            "from_json"       );
    Run( get_started,          "get_started"     );
    Run( mul_op,               "mul_op"          );
    Run( pow_op,               "pow_op"          );
    Run( print_op,             "print_op"        );
    Run( sparse,               "sparse"          );
    Run( sub_op,               "sub_op"          );
    Run( sum_op,               "sum_op"          );
    Run( to_json,              "to_json"         );
    Run( unary_op,             "unary_op"        );
    // END_SORT_THIS_LINE_MINUS_1

    // check for memory leak
    bool memory_ok = CppAD::thread_alloc::free_all();
    // print summary at end
    bool ok = Run.summary(memory_ok);
    //
    return static_cast<int>( ! ok );
}
