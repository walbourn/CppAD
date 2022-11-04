# ifndef CPPAD_LOCAL_OP_POW_OP_HPP
# define CPPAD_LOCAL_OP_POW_OP_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-22 Bradley M. Bell
// ----------------------------------------------------------------------------

namespace CppAD { namespace local { // BEGIN_CPPAD_LOCAL_NAMESPACE
/*!
\file pow_op.hpp
Forward and reverse mode calculations for z = pow(x, y).
*/

// --------------------------- Powvv -----------------------------------------
/*!
Compute forward mode Taylor coefficients for result of op = PowvvOp.

In the documentation below,
this operations is for the case where both x and y are variables
and the argument parameter is not used.

\copydetails CppAD::local::forward_pow_op
*/

template <class Base>
void forward_powvv_op(
    size_t        p           ,
    size_t        q           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // 2 = NumRes(PowvvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );
    CPPAD_ASSERT_UNKNOWN( p <= q );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // z_0 = log(x)
    forward_log_op(p, q, i_z, size_t(arg[0]), cap_order, taylor);

    // z_1 = z_0 * y
    addr_t adr[2];
    adr[0] = addr_t( i_z );
    adr[1] = arg[1];
    forward_mulvv_op(p, q, i_z+1, adr, parameter, cap_order, taylor);

    // z_2 = exp(z_1)
    // final result for zero order case is exactly the same as for Base
    if( p == 0 )
    {   // Taylor coefficients corresponding to arguments and result
        Base* x   = taylor + size_t(arg[0]) * cap_order;
        Base* y   = taylor + size_t(arg[1]) * cap_order;
        Base* z_2 = taylor + (i_z+2) * cap_order;

        z_2[0] = pow(x[0], y[0]);
        p++;
    }
    if( p <= q )
        forward_exp_op(p, q, i_z+2, i_z+1, cap_order, taylor);
}
/*!
Multiple directions forward mode Taylor coefficients for op = PowvvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a variable and y is a parameter.

\copydetails CppAD::local::forward_pow_op_dir
*/

template <class Base>
void forward_powvv_op_dir(
    size_t        q           ,
    size_t        r           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // 2 = NumRes(PowvvOp) - 1

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( 0 < q );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // z_0 = log(x)
    forward_log_op_dir(q, r, i_z, size_t(arg[0]), cap_order, taylor);

    // z_1 = y * z_0
    addr_t adr[2];
    adr[0] = addr_t( i_z );
    adr[1] = arg[1];
    forward_mulvv_op_dir(q, r, i_z+1, adr, parameter, cap_order, taylor);

    // z_2 = exp(z_1)
    forward_exp_op_dir(q, r, i_z+2, i_z+1, cap_order, taylor);
}
/*!
Compute zero order forward mode Taylor coefficients for result of op = PowvvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where both x and y are variables
and the argument parameter is not used.

\copydetails CppAD::local::forward_pow_op_0
*/

template <class Base>
void forward_powvv_op_0(
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // NumRes(PowvvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvvOp) == 3 );

    // Taylor coefficients corresponding to arguments and result
    Base* x   = taylor + size_t(arg[0]) * cap_order;
    Base* y   = taylor + size_t(arg[1]) * cap_order;
    Base* z_0 = taylor + i_z    * cap_order;
    Base* z_1 = z_0    +          cap_order;
    Base* z_2 = z_1    +          cap_order;

    z_0[0] = log( x[0] );
    z_1[0] = z_0[0] * y[0];
    z_2[0] = pow(x[0], y[0]);

}

/*!
Compute reverse mode partial derivatives for result of op = PowvvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where both x and y are variables
and the argument parameter is not used.

\copydetails CppAD::local::reverse_pow_op
*/

template <class Base>
void reverse_powvv_op(
    size_t        d           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    const Base*   taylor      ,
    size_t        nc_partial  ,
    Base*         partial     )
{
    // convert from final result to first result
    i_z -= 2; // NumRes(PowvvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( d < cap_order );
    CPPAD_ASSERT_UNKNOWN( d < nc_partial );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // z_2 = exp(z_1)
    reverse_exp_op(
        d, i_z+2, i_z+1, cap_order, taylor, nc_partial, partial
    );

    // z_1 = z_0 * y
    addr_t adr[2];
    adr[0] = addr_t( i_z );
    adr[1] = arg[1];
    reverse_mulvv_op(
    d, i_z+1, adr, parameter, cap_order, taylor, nc_partial, partial
    );

    // z_0 = log(x)
    reverse_log_op(
        d, i_z, size_t(arg[0]), cap_order, taylor, nc_partial, partial
    );
}

// --------------------------- Powpv -----------------------------------------
/*!
Compute forward mode Taylor coefficients for result of op = PowpvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a parameter and y is a variable.

\copydetails CppAD::local::forward_pow_op
*/

template <class Base>
void forward_powpv_op(
    size_t        p           ,
    size_t        q           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // 2 = NumRes(PowpvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowpvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowpvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );
    CPPAD_ASSERT_UNKNOWN( p <= q );

    // Taylor coefficients corresponding to arguments and result
    Base* z_0 = taylor + i_z    * cap_order;

    // z_0 = log(x)
    Base x    = parameter[ arg[0] ];
    size_t d;
    for(d = p; d <= q; d++)
    {   if( d == 0 )
            z_0[d] = log(x);
        else
            z_0[d] = Base(0.0);
    }

    // 2DO: remove requirement that i_z * cap_order <= max addr_t value
    CPPAD_ASSERT_KNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z * cap_order,
        "cppad_tape_addr_type maximum value has been exceeded\n"
        "This is due to a kludge in the pow operation and should be fixed."
    );

    // z_1 = z_0 * y
    addr_t adr[2];
    // offset of z_i in taylor (as if it were a parameter); i.e., log(x)
    adr[0] = addr_t( i_z * cap_order );
    // offset of y in taylor (as a variable)
    adr[1] = arg[1];

    // Trick: use taylor both for the parameter vector and variable values
    forward_mulpv_op(p, q, i_z+1, adr, taylor, cap_order, taylor);

    // z_2 = exp(z_1)
    // zero order case exactly same as Base type operation
    if( p == 0 )
    {   Base* y   = taylor + size_t(arg[1]) * cap_order;
        Base* z_2 = taylor + (i_z+2) * cap_order;
        z_2[0] = pow(x, y[0]);
        p++;
    }
    if( p <= q )
        forward_exp_op(p, q, i_z+2, i_z+1, cap_order, taylor);
}
/*!
Multiple directions forward mode Taylor coefficients for op = PowpvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a parameter and y is a variable.

\copydetails CppAD::local::forward_pow_op_dir
*/

template <class Base>
void forward_powpv_op_dir(
    size_t        q           ,
    size_t        r           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // 2 = NumRes(PowpvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowpvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowpvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( 0 < q );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );

    // Taylor coefficients corresponding to arguments and result
    size_t num_taylor_per_var = (cap_order-1) * r + 1;
    Base* z_0 = taylor + i_z * num_taylor_per_var;

    // z_0 = log(x)
    size_t m  = (q-1) * r + 1;
    for(size_t ell = 0; ell < r; ell++)
        z_0[m+ell] = Base(0.0);

    // 2DO: remove requirement i_z * num_taylor_per_var <= max addr_t value
    CPPAD_ASSERT_KNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z * num_taylor_per_var,
        "cppad_tape_addr_type maximum value has been exceeded\n"
        "This is due to a kludge in the pow operation and should be fixed."
    );

    // z_1 = z_0 * y
    addr_t adr[2];
    // offset of z_0 in taylor (as if it were a parameter); i.e., log(x)
    adr[0] = addr_t( i_z * num_taylor_per_var );
    // ofset of y in taylor (as a variable)
    adr[1] = arg[1];

    // Trick: use taylor both for the parameter vector and variable values
    forward_mulpv_op_dir(q, r, i_z+1, adr, taylor, cap_order, taylor);

    // z_2 = exp(z_1)
    forward_exp_op_dir(q, r, i_z+2, i_z+1, cap_order, taylor);
}
/*!
Compute zero order forward mode Taylor coefficient for result of op = PowpvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a parameter and y is a variable.

\copydetails CppAD::local::forward_pow_op_0
*/

template <class Base>
void forward_powpv_op_0(
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // convert from final result to first result
    i_z -= 2; // NumRes(PowpvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowpvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowpvOp) == 3 );

    // Paraemter value
    Base x = parameter[ arg[0] ];

    // Taylor coefficients corresponding to arguments and result
    Base* y   = taylor + size_t(arg[1]) * cap_order;
    Base* z_0 = taylor + i_z    * cap_order;
    Base* z_1 = z_0    +          cap_order;
    Base* z_2 = z_1    +          cap_order;

    // z_0 = log(x)
    z_0[0] = log(x);

    // z_1 = z_0 * y
    z_1[0] = z_0[0] * y[0];

    // z_2 = exp(z_1)
    // zero order case exactly same as Base type operation
    z_2[0] = pow(x, y[0]);
}

/*!
Compute reverse mode partial derivative for result of op = PowpvOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a parameter and y is a variable.

\copydetails CppAD::local::reverse_pow_op
*/

template <class Base>
void reverse_powpv_op(
    size_t        d           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    const Base*   taylor      ,
    size_t        nc_partial  ,
    Base*         partial     )
{
    // convert from final result to first result
    i_z -= 2; // NumRes(PowpvOp) - 1;

    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvvOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvvOp) == 3 );
    CPPAD_ASSERT_UNKNOWN( d < cap_order );
    CPPAD_ASSERT_UNKNOWN( d < nc_partial );

    // z_2 = exp(z_1)
    reverse_exp_op(
        d, i_z+2, i_z+1, cap_order, taylor, nc_partial, partial
    );

    // 2DO: remove requirement that i_z * cap_order <= max addr_t value
    CPPAD_ASSERT_KNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z * cap_order,
        "cppad_tape_addr_type maximum value has been exceeded\n"
        "This is due to a kludge in the pow operation and should be fixed."
    );

    // z_1 = z_0 * y
    addr_t adr[2];
    adr[0] = addr_t( i_z * cap_order ); // offset of z_0[0] in taylor
    adr[1] = arg[1];                    // index of y in taylor and partial
    // use taylor both for parameter and variable values
    reverse_mulpv_op(
        d, i_z+1, adr, taylor, cap_order, taylor, nc_partial, partial
    );

    // z_0 = log(x)
    // x is a parameter
}

// --------------------------- Powvp -----------------------------------------
/*!
Compute forward mode Taylor coefficients for result of op = PowvpOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a variable and y is a parameter.

\copydetails CppAD::local::forward_pow_op
*/

template <class Base>
void forward_powvp_op(
    size_t        p           ,
    size_t        q           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvpOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvpOp) == 1 );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );
    CPPAD_ASSERT_UNKNOWN( p <= q );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // Taylor coefficients corresponding to arguments and result
    Base* x = taylor + size_t(arg[0]) * cap_order;
    Base* z = taylor + i_z    * cap_order;

    // Paraemter value
    Base y = parameter[ arg[1] ];

    // Special solution when x[0] is zero
    Base b0 = Base( 0.0 );

    // special case zero order
    if( p == 0 )
    {   z[0] = pow(x[0], y);
        p++;
    }
    for(size_t j = p; j <= q; ++j)
    {   Base sum = Base(0);
        for(size_t k = 1; k < j; ++k)
        {   Base bk = Base( double(k) );
            sum += bk * (y * x[k] * z[j-k] - z[k] * x[j-k]);
        }
        Base bj = Base( double(j) );
        Base zj = ( y * z[0] * x[j] + sum / bj ) / x[0];
        z[j] = CondExpEq(x[0], b0, b0, zj);
    }
}
/*!
Multiple directions forward mode Taylor coefficients for op = PowvpOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a variable and y is a parameter.

\copydetails CppAD::local::forward_pow_op_dir
*/

template <class Base>
void forward_powvp_op_dir(
    size_t        q           ,
    size_t        r           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvpOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvpOp) == 1 );
    CPPAD_ASSERT_UNKNOWN( 0 < q );
    CPPAD_ASSERT_UNKNOWN( q < cap_order );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // Taylor coefficients corresponding to arguments and result
    size_t num_taylor_per_var = (cap_order-1) * r + 1;
    Base* x = taylor + size_t(arg[0]) * num_taylor_per_var;
    Base* z = taylor +    i_z * num_taylor_per_var;

    // Parameter value
    Base y = parameter[ arg[1] ];

    // special solution when x[0] is zero
    Base b0 = Base( 0.0 );

    // index in Taylor coefficients where multiple directions start
    size_t m = (q-1)*r + 1;
    //
    // loop over directions
    for(size_t ell = 0; ell < r; ell++)
    {   Base sum = Base(0);
        for(size_t k = 1; k < q; ++k)
        {   Base xk   = x[(k-1)*r   + ell + 1];
            Base zk   = z[(k-1)*r   + ell + 1];
            Base xqk  = x[(q-k-1)*r + ell + 1];
            Base zqk  = z[(q-k-1)*r + ell + 1];
            Base bk   = Base( double(k) );
            sum += bk * (y * xk * zqk - zk * xqk);
        }
        Base xq  = x[(q-1)*r + ell + 1];
        Base bq   = Base( double(q) );
        Base zell = ( y * z[0] * xq + sum / bq ) / x[0];
        z[m+ell]  = CondExpEq(x[0], b0, b0, zell);
    }
}

/*!
Compute zero order forward mode Taylor coefficients for result of op = PowvpOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a variable and y is a parameter.

\copydetails CppAD::local::forward_pow_op_0
*/

template <class Base>
void forward_powvp_op_0(
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    Base*         taylor      )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvpOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvpOp) == 1 );

    // Paraemter value
    Base y = parameter[ arg[1] ];

    // Taylor coefficients corresponding to arguments and result
    Base* x = taylor + size_t(arg[0]) * cap_order;
    Base* z = taylor + i_z * cap_order;

    z[0] = pow(x[0], y);
}

/*!
Compute reverse mode partial derivative for result of op = PowvpOp.

The C++ source code corresponding to this operation is
\verbatim
    z = pow(x, y)
\endverbatim
In the documentation below,
this operations is for the case where x is a variable and y is a parameter.

\copydetails CppAD::local::reverse_pow_op
*/

template <class Base>
void reverse_powvp_op(
    size_t        d           ,
    size_t        i_z         ,
    const addr_t* arg         ,
    const Base*   parameter   ,
    size_t        cap_order   ,
    const Base*   taylor      ,
    size_t        nc_partial  ,
    Base*         partial     ,
    CppAD::vector<Base>& work )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( NumArg(PowvpOp) == 2 );
    CPPAD_ASSERT_UNKNOWN( NumRes(PowvpOp) == 1 );
    CPPAD_ASSERT_UNKNOWN( d < cap_order );
    CPPAD_ASSERT_UNKNOWN( d < nc_partial );
    CPPAD_ASSERT_UNKNOWN(
        size_t( std::numeric_limits<addr_t>::max() ) >= i_z
    );

    // Taylor coefficients
    const Base* x = taylor + size_t( arg[0] ) * cap_order;
    const Base* z = taylor + i_z * cap_order;

    // parameter value
    const Base  y = parameter[ arg[1] ];

    // Partial derivatives corresponding to arguments and result
    Base* px = partial + size_t(arg[0]) * nc_partial;
    Base* pz = partial + i_z * nc_partial;

    // Special solution when x[0] is zero
    Base b0 = Base( 0.0 );

    // Place to hold px for this operator until conditional assigment at end
    work.resize(nc_partial);
    for(size_t j = 0; j <= d; ++j)
        work[j] = px[j];

    // reverse z^j for j = d, ..., 1
    size_t j = d;
    while(j)
    {   // j
        Base bj = Base( double(j) );
        //
        // x^j term
        work[j] += azmul(pz[j], y * z[0] / x[0]);
        //
        // x^k terms
        for(size_t k = 1; k < j; ++k)
        {   Base bk   = Base( double(k) );
            Base term = (bk * y - Base(j-k) ) * z[j-k] / (bj * x[0]);
            work[k] += azmul(pz[j], term);
        }
        //
        // z^k terms
        for(size_t k = 1; k < j; ++k)
        {   Base bk   = Base( double(k) );
            Base term = (Base(j-k) * y - bk) * x[j-k] / (bj * x[0]);
            pz[k] += azmul(pz[j], term);
        }
        //
        // x^0 term
        work[0] -= azmul(pz[j], z[j] / x[0]);
        //
        // z^0 term
        pz[0] += azmul(pz[j], y * x[j] / x[0] );
        //
        // next j
        --j;
    }
    // reverse z^0
    work[0] += azmul(pz[0], y * z[0] / x[0]);
    //
    for(j = 0; j <=d; ++j)
        px[j] = CondExpEq(x[0], b0, b0, work[j]);
}

} } // END_CPPAD_LOCAL_NAMESPACE
# endif
