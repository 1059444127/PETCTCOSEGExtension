/*
 ==========================================================================
 |   
 |   $Id: optnet_mc_fs_3d.hxx 135 2005-02-06 06:47:08Z kangli $
 |
 |   Written by Kang Li <kangl@cmu.edu>
 |   Department of Electrical and Computer Engineering
 |   Carnegie Mellon University
 |   
 ==========================================================================
 |   This file is a part of the OptimalNet library.
 ==========================================================================
 | Copyright (c) 2004-2005 Kang Li <kangl@cmu.edu>. All Rights Reserved.
 | 
 | This software is supplied under the terms of a license agreement or
 | nondisclosure agreement  with the author  and may not be copied  or
 | disclosed except in accordance with the terms of that agreement.
 ==========================================================================
 */

#ifndef ___OPTNET_MC_FS_3D_HXX___
#   define ___OPTNET_MC_FS_3D_HXX___

#   if defined(_MSC_VER) && (_MSC_VER > 1000)
#       pragma once
#       pragma warning(disable: 4786)
#       pragma warning(disable: 4284)
#       pragma warning(disable: 4127)
#   endif

#   include <optnet/_alpha/graphspec.hxx>
#   include <optnet/_alpha/optnet_mc_fs_maxflow.hxx>
#   include <optnet/_base/array.hxx>
#   include <optnet/_base/array_ref.hxx>
#   include <optnet/_base/array2.hxx>
#   include <optnet/_base/point3.hxx>
#   include <vector>

namespace optnet {

///////////////////////////////////////////////////////////////////////////
///  @class optnet_mc_fs_3d
///  @brief Implementation of the single-surface Optimal Net algorithm
///         using the Boykov-Kolmogorov max-flow algorithm on a
///         forward-star represented multicolumn graph.
///////////////////////////////////////////////////////////////////////////
template <typename _Cost, typename _Cap, typename _Tg = net_f_xy>
class optnet_mc_fs_3d
{
    typedef optnet_mc_fs_maxflow<_Cap>  graph_type;

public:

    typedef _Cost                           cost_type;              /// Cost function value type.
    typedef _Cap                            capacity_type;          /// Graph arc capacity type.
    typedef double                          real_value_type;        /// Real value type (default: double).
    typedef size_t                          size_type;              /// Size type.

    typedef graphspec                       graphspec_type;         /// Graph specification type.

    typedef array_base<cost_type, _Tg>      cost_array_base_type;   /// Cost array base class.
    typedef array_ref<cost_type, _Tg>       cost_array_ref_type;    /// Cost array reference class.
    typedef array<cost_type, _Tg>           cost_array_type;        /// Cost array class.
    
    typedef point3<real_value_type>         point_type;             /// Point type with real-valued coordinates.
    typedef std::vector<real_value_type>    real_value_vector;      /// Real-valued vector.


    ///////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////
    optnet_mc_fs_3d();

    ///////////////////////////////////////////////////////////////////////
    ///  Create graph and set the cost values.
    ///
    ///  @param cost  The array containing the cost values for each voxel.
    ///  @param orig  The origin relative to which the graph will be
    ///                 constructed.
    ///  @param spec  The graph specification.
    ///  @param rmin  Lower physical boundary of each column.
    ///  @param rmax  Upper physical boundary of each column.
    ///  @param npc   Number of nodes per column.
    ///  @param sc    The smoothness constraint.
    ///
    ///  @remarks This function will re-create the graph and re-assign
    ///           the node costs of the underlying graph based on the
    ///           given cost array and graph specification.
    ///
    ///////////////////////////////////////////////////////////////////////
    void create(const cost_array_base_type& cost,
                const point_type&           orig,
                graphspec_type&             spec,
                real_value_type             rmin,
                real_value_type             rmax,
                size_type                   npc,
                int                         sc
                );
    
    ///////////////////////////////////////////////////////////////////////
    ///  Solve the optimal surface problem using the given cost function
    ///  and smoothness constraints.
    ///////////////////////////////////////////////////////////////////////
    void solve(capacity_type* pflow);


private:
    int                     m_sc;
    graph_type              m_graph;
    real_value_vector       m_vfact;
    graphspec_type*         m_pgs;
};
    
} // namespace

#   ifndef __OPTNET_SEPARATION_MODEL__
#       include <optnet/_alpha/optnet_mc_fs_3d.cxx>
#   endif

#endif // ___OPTNET_MC_FS_3D_HXX___
