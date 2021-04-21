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

#ifndef NSAHOO_TUPLETOOLOVERLAP_H
#define NSAHOO_TUPLETOOLOVERLAP_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h" // Interface

/** @class TupleToolOverlap TupleToolOverlap.h
 *
 * @brief common veloID informations to be stored in the Tuple
 *
 *  @author Niladri Sahoo, Tom Blake
 *  @date   2021-03-25
 *
 */

class TupleToolOverlap : public TupleToolBase, virtual public IParticleTupleTool {

 public:
  /// Standard constructor
  TupleToolOverlap( const std::string& type, const std::string& name, const IInterface* parent );
  int nCommonVelo( const LHCb::Track* t1 , const LHCb::Track* t2 ) const ;

  virtual ~TupleToolOverlap(){}; ///< Destructor

  StatusCode fill( const LHCb::Particle*, const LHCb::Particle*, const std::string&, Tuples::Tuple& ) override;
};

#endif // NSAHOO_TUPLETOOLOVERLAP_H
