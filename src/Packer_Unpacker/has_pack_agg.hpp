/*
 * has_pack_agg.hpp
 *
 *  Created on: Feb 10, 2016
 *      Author: yaroslav
 */

#ifndef SRC_PACKER_UNPACKER_HAS_PACK_AGG_HPP_
#define SRC_PACKER_UNPACKER_HAS_PACK_AGG_HPP_

#include "prp_all_zero.hpp"

/*! \brief These set of classes generate an array definition at compile-time
 *
 * These set of classes generate an array definition at compile-time
 *
 * \see generate_array
 *
 */

#include <boost/fusion/mpl.hpp>

///////////////////////////////////////////////////



/////////////// Classes to generate at compile time arrays from a boost::mpl::vector

//! Generate the array specializing ArrayHolder
template<class T, size_t N , typename result_p ,class vprp>
struct has_pack_agg_impl
{
	typedef typename boost::mpl::at<vprp,typename boost::mpl::int_<N-1>>::type vprp_N;
	typedef typename boost::mpl::at<typename T::type,vprp_N>::type stype;
	typedef typename boost::mpl::bool_<has_pack<stype>::value | result_p::value> result_n;
    typedef typename has_pack_agg_impl<T,N-1,result_n,vprp>::result result;
};

//! terminator of the variadic template
template<class T, typename result_p, class vprp>
struct has_pack_agg_impl<T,0,result_p,vprp>
{
    typedef boost::mpl::bool_<result_p::value> result;
//    typedef std::vector<result_p::value> fail;
};







template<class T, int ... prp>
struct has_pack_agg
{
	typedef typename prp_all_zero<T,sizeof...(prp) == 0,prp...>::type vprp;
	//typedef typename to_boost_vmpl<prp...>::type vprp;
    typedef typename has_pack_agg_impl<T,sizeof ... (prp), boost::mpl::bool_<false> , vprp>::result result;
};


#endif /* SRC_PACKER_UNPACKER_HAS_PACK_AGG_HPP_ */