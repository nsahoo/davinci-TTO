/*****************************************************************************\
 * (c) Copyright 2000-2018 CERN for the benefit of the LHCb Collaboration      *
 *                                                                             *
 * This software is distributed under the terms of the GNU General Public      *
 * Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
 *                                                                             *
 * In applying this licence, CERN does not waive the privileges and immunities *
 * granted to it by virtue of its status as an Intergovernmental Organization  *
 * or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
// Include files

// local
#include "TupleToolOverlap.h"

#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"

#include "Event/Particle.h"
//-----------------------------------------------------------------------------
// Implementation file for class : EventInfoTupleTool
//
// 2021-03-25 : Niladri Sahoo, Tom Blake
//-----------------------------------------------------------------------------

using namespace LHCb;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolOverlap::TupleToolOverlap( const std::string& type, const std::string& name, const IInterface* parent )
  : TupleToolBase( type, name, parent ) {
  declareInterface<IParticleTupleTool>( this );
}


StatusCode TupleToolOverlap::fill( const LHCb::Particle *     mother,
				   const LHCb::Particle *     P,
				   const std::string &     head,
				   Tuples::Tuple &     tuple
				   ){

  const std::string prefix = fullName( head );

  StatusCode sc = StatusCode::SUCCESS;

  if ( P == mother ) return sc;

  // if it's a basic particle, store number of IDs
  bool test = true;

  if ( P->isBasicParticle() ){
    test &= tuple->column( prefix + "_nLHCbIDs", P->proto()->track()->nLHCbIDs() );
  }

  auto _daughters = P->daughters();

  if ( _daughters.size() != 2 ) return sc;

  auto p1 = _daughters[0];
  auto p2 = _daughters[1];

  auto t1 = p1->proto()->track();
  auto t2 = p2->proto()->track();

  if ( !t1 || !t2 ) return sc;


  test &= tuple->column( prefix + "_nCommonIDs",    t1->nCommonLhcbIDs( *t2 ));
  test &= tuple->column( prefix + "_nCommonVELOIDs",   nCommonVelo( t1, t2 ));


  return StatusCode( test );


}


int TupleToolOverlap::nCommonVelo( const LHCb::Track* t1 , const LHCb::Track* t2 ) const {

  auto ids1 = t1->lhcbIDs();
  auto ids2 = t2->lhcbIDs();

  int nOverlap = 0;

  for ( auto & id1: t1->lhcbIDs() ){
    for ( auto & id2: t2->lhcbIDs() ){
      if ( id1 == id2 && id1.isVelo() ){
        nOverlap++;
      }
    }
  }

  return nOverlap;

}




// Declaration of the Tool Factory
DECLARE_COMPONENT( TupleToolOverlap )

