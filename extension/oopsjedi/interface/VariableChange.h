/*
 * (C) Copyright 2018-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef OOPSJEDI_INTERFACE_VARIABLECHANGE_H_
#define OOPSJEDI_INTERFACE_VARIABLECHANGE_H_

#include <memory>
#include <string>

#include "oopsjedi/base/State.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace oopsjedi {

// -----------------------------------------------------------------------------
/// \brief Nonlinear variable change
///
/// Note: each implementation should typedef `Parameters_` to the name of a subclass
/// of oopsjedi::VariableChangeParametersBase holding its configuration settings and provide a
/// constructor with the following signature:
///
///     VariableChange(const Parameters_ &, const Geometry_);
template <typename MODEL>
class VariableChange : public utiljedi::Printable,
                       private utiljedi::ObjectCounter<VariableChange<MODEL> >  {
  typedef typename MODEL::VariableChange VariableChange_;
  typedef Geometry<MODEL>                Geometry_;
  typedef State<MODEL>                   State_;

 public:
  typedef typename VariableChange_::Parameters_ Parameters_;

  static const std::string classname() {return "oopsjedi::VariableChange";}

  VariableChange(const Parameters_ &, const Geometry_ &);
  virtual ~VariableChange();
  VariableChange(const VariableChange &) = delete;
  VariableChange(VariableChange &&) = default;
  const VariableChange & operator=(const VariableChange &) = delete;
  VariableChange & operator=(VariableChange &&) = default;

  /// change state variables to those specified in the Variables parameter
  void changeVar(State_ &, const Variables &) const;
  ///  changeVarInverse is no longer needed but remains for legacy code
  void changeVarInverse(State_ &, const Variables &) const;

 private:
  void print(std::ostream &) const override;

  std::unique_ptr<VariableChange_> chvar_;  // pointer to the VariableChange implementation
};

// -----------------------------------------------------------------------------

template<typename MODEL>
VariableChange<MODEL>::VariableChange(const Parameters_ & parameters, const Geometry_ & geometry)
  : chvar_()
{
  Log::trace() << "VariableChange<MODEL>::VariableChange starting" << std::endl;
  utiljedi::Timer timer(classname(), "VariableChange");
  chvar_.reset(new VariableChange_(parameters, geometry.geometry()));
  Log::trace() << "VariableChange<MODEL>::VariableChange done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
VariableChange<MODEL>::~VariableChange() {
  Log::trace() << "VariableChange<MODEL>::~VariableChange starting" << std::endl;
  utiljedi::Timer timer(classname(), "~VariableChange");
  chvar_.reset();
  Log::trace() << "VariableChange<MODEL>::~VariableChange done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void VariableChange<MODEL>::changeVar(State_ & xx, const Variables & vars) const {
  Log::trace() << "VariableChange<MODEL>::changeVar starting" << std::endl;
  utiljedi::Timer timer(classname(), "changeVar");
  chvar_->changeVar(xx.state(), vars);
  Log::trace() << "VariableChange<MODEL>::changeVar done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void VariableChange<MODEL>::changeVarInverse(State_ & xx, const Variables & vars) const {
  Log::trace() << "VariableChange<MODEL>::changeVarInverse starting" << std::endl;
  utiljedi::Timer timer(classname(), "changeVarInverse");
  chvar_->changeVarInverse(xx.state(), vars);
  Log::trace() << "VariableChange<MODEL>::changeVarInverse done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void VariableChange<MODEL>::print(std::ostream & os) const {
  Log::trace() << "VariableChange<MODEL>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *chvar_;
  Log::trace() << "VariableChange<MODEL>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_VARIABLECHANGE_H_
