// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-22 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
$begin cppadcg_det_lu.cpp$$
$spell
    cppadcg
    Lu
$$

$section Cppadcg Speed: Gradient of Determinant Using Lu Factorization$$


$head Specifications$$
$cref link_det_lu$$

$head Implementation$$
A cppadcg version of this test is not yet implemented
$srccode%cpp% */
# include <map>
# include <cppad/utility/vector.hpp>

// list of possible options
extern std::map<std::string, bool> global_option;

bool link_det_lu(
    size_t                     size     ,
    size_t                     repeat   ,
    CppAD::vector<double>     &matrix   ,
    CppAD::vector<double>     &gradient )
{   return false; }
/* %$$
$end
*/
