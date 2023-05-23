/*
 * (C) Copyright 2018-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef OOPSJEDI_INTERFACE_LINEARVARIABLECHANGE_H_
#define OOPSJEDI_INTERFACE_LINEARVARIABLECHANGE_H_

#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

#include "oopsjedi/base/Geometry.h"
#include "oopsjedi/base/Increment.h"
#include "oopsjedi/base/LinearVariableChangeParametersBase.h"
#include "oopsjedi/base/State.h"
#include "oopsjedi/base/Variables.h"
#include "oopsjedi/util/abor1_cpp.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/parameters/ConfigurationParameter.h"
#include "oopsjedi/util/parameters/GenericParameters.h"
#include "oopsjedi/util/parameters/Parameters.h"
#include "oopsjedi/util/parameters/ParametersOrConfiguration.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace eckit {
  class Configuration;
}

namespace oopsjedi {

// -----------------------------------------------------------------------------
/// \brief MODEL-agnostic part of the linear variable change
///
/// Note: each implementation should typedef `LinVariableChangeParams_` to the name of a
/// subclass of oopsjedi::LinearVariableChangeParametersBase holding its configuration settings and
/// provide a constructor with the following signature:
///
///     LinearVariableChange(const Geometry_ &, const LinVariableChangeParams_ &);
template <typename MODEL>
class LinearVariableChange {
  typedef Geometry<MODEL>            Geometry_;
  typedef Increment<MODEL>           Increment_;
  typedef State<MODEL>               State_;

 public:
  /// A subclass of oops::LinearVariableChangeParametersBase holding the configuration settings of
  /// the variable change.
  /// Defined as LinearVariableChange_::Parameters_ if LinearVariableChange_ defines a Parameters_
  /// type; otherwise as GenericLinearVariableChangeParameters.
  typedef GenericLinearVariableChangeParameters Parameters_;
  static const std::string classname() {return "oops::LinearVariableChange";}

  LinearVariableChange(const Geometry_ &, const Parameters_ &)
    {ABORT("not implemented in oopsjedi");}
  LinearVariableChange(const Geometry_ &, const eckit::Configuration &)
    {ABORT("not implemented in oopsjedi");}

  virtual ~LinearVariableChange() {}

  void changeVarTraj(const State_ &, const Variables &)
    {ABORT("not implemented in oopsjedi");}
  void changeVarTL(Increment_ &, const Variables &) const
    {ABORT("not implemented in oopsjedi");}
  void changeVarInverseTL(Increment_ &, const Variables &) const
    {ABORT("not implemented in oopsjedi");}
  void changeVarAD(Increment_ &, const Variables &) const
    {ABORT("not implemented in oopsjedi");}
  void changeVarInverseAD(Increment_ &, const Variables &) const
    {ABORT("not implemented in oopsjedi");}

 private:
  void print(std::ostream &) const;
};
// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_LINEARVARIABLECHANGE_H_
