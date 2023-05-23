/*
 * (C) Copyright 2009-2016 ECMWF.
 * (C) Copyright 2017-2021 UCAR.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef OOPSJEDI_INTERFACE_STATE_H_
#define OOPSJEDI_INTERFACE_STATE_H_

#include <memory>
#include <string>
#include <vector>

#include "eckit/config/Configuration.h"

#include "oops/interface/State.h"

#include "oopsjedi/base/Geometry.h"
#include "oopsjedi/base/Variables.h"
#include "oopsjedi/util/DateTime.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/parameters/GenericParameters.h"
#include "oopsjedi/util/parameters/HasParameters_.h"
#include "oopsjedi/util/parameters/HasWriteParameters_.h"
#include "oopsjedi/util/parameters/Parameters.h"
#include "oopsjedi/util/parameters/ParametersOrConfiguration.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Serializable.h"
#include "oopsjedi/util/Timer.h"

namespace atlas {
  class FieldSet;
}

namespace oopsjedi {

namespace interface {

/// \brief Encapsulates the model state.
///
/// Note: implementations of this interface can opt to extract their settings either from
/// a Configuration object or from a subclass of Parameters.
///
/// In the former case, they should provide a constructor and read()/write() methods with the
/// following signatures:
///
///    State(const Geometry_ &, const eckit::Configuration &);
///    void read(const eckit::Configuration &);
///    void write(const eckit::Configuration &) const;
///
/// In the latter case, the implementer should first define (a) a subclass of Parameters holding
/// the settings needed by the constructor and the read() method and (b) a subclass of
/// WriteParametersBase holding the settings needed by the write() method. The implementation of
/// the State interface should then typedef `Parameters_` and `WriteParameters_` to the names of
/// these subclasses and provide a constructor and read()/write() method with the following
/// signatures:
///
///    State(const Geometry_ &, const Parameters_ &);
///    void read(const Parameters_ &);
///    void write(const WriteParameters_ &) const;
// -----------------------------------------------------------------------------

template <typename MODEL>
class State : public utiljedi::Printable,
              public utiljedi::Serializable,
              private utiljedi::ObjectCounter<State<MODEL> > {
  typedef typename MODEL::State      State_;
  typedef oopsjedi::Geometry<MODEL>  Geometry_;

 public:
  /// Set to State_::Parameters_ if State_ provides a type called Parameters_ and to
  /// GenericParameters (a thin wrapper of an eckit::LocalConfiguration object) if not.
  typedef TParameters_IfAvailableElseFallbackType_t<State_, GenericParameters> Parameters_;

  /// Set to State_::WriteParameters_ if State_ provides a type called WriteParameters_ and to
  /// GenericWriteParameters (a thin wrapper of an eckit::LocalConfiguration object) if not.
  typedef TWriteParameters_IfAvailableElseFallbackType_t<State_, GenericWriteParameters>
    WriteParameters_;

  static const std::string classname() {return "oopsjedi::State";}

  /// Constructor for specified \p resol, with \p vars, valid at \p time
  State(const Geometry_ & resol, const Variables & vars, const utiljedi::DateTime & time);
  /// Constructor for specified \p resol and parameters \p params specifying e.g. a file to read
  /// or an analytic state to generate
  State(const Geometry_ & resol, const Parameters_ & params);
  /// Constructor for specified \p resol and parameters \p params specifying e.g. a file to read
  /// or an analytic state to generate
  State(const Geometry_ & resol, const eckit::Configuration & conf);
  /// Copies \p other State, changing its resolution to \p geometry
  State(const Geometry_ & resol, const State & other);
  /// Copy constructor
  State(const State &);
  /// Constructor from MODEL::State
  State(const State_ &);
  /// Destructor (defined explicitly for timing and tracing)
  ~State();
  /// Assignment operator
  State & operator =(const State &);

  /// Accessor
  State_ & state() {fset_.clear(); return *state_;}
  /// const accessor
  const State_ & state() const {return *state_;}

  /// Accessor to the time of this State
  const utiljedi::DateTime validTime() const {return utiljedi::DateTime(state_->validTime().toString());}
  /// Update this State's valid time by \p dt
  void updateTime(const utiljedi::Duration & dt) {state_->validTime()+=dt;}

  /// Read this State from file
  void read(const Parameters_ &);
  void read(const eckit::Configuration &);
  /// Write this State out to file
  void write(const WriteParameters_ &) const;
  void write(const eckit::Configuration &) const;
  /// Norm (used in tests)
  double norm() const;

  /// Accessor to variables associated with this State
  const Variables & variables() const
    {ABORT("not implemented in oopsjedi");return Variables();}

  /// Zero out this State
  void zero();
  /// Accumulate (add \p w * \p x to the state)
  void accumul(const double & w, const State & x);

  /// ATLAS FieldSet interface
  /// For models that are not using ATLAS fieldsets for their own State data:
  /// - "toFieldSet" allocates the ATLAS fieldset based on the variables present in the State and
  ///    copies State data into the fieldset, including halo.
  /// - "fromFieldSet" copies fieldset data back into the State (interior points only).
  /// For models that are using ATLAS fieldsets for their own Incerment data, fields are shared from
  /// a fieldset to another. A working example is available with the QUENCH testbed of SABER
  /// inf saber/test/quench.
  void toFieldSet(atlas::FieldSet &) const;
  void fromFieldSet(const atlas::FieldSet &);

  /// Serialize and deserialize (used in 4DEnVar, weak-constraint 4DVar and Block-Lanczos minimizer)
  size_t serialSize() const override;
  void serialize(std::vector<double> &) const override;
  void deserialize(const std::vector<double> &, size_t &) override;

 private:
  std::unique_ptr<State_> state_;
  void print(std::ostream &) const override;

 protected:
  mutable atlas::FieldSet fset_;
};

// =============================================================================

template<typename MODEL>
State<MODEL>::State(const Geometry_ & resol, const Variables & vars,
                    const utiljedi::DateTime & time) : state_(), fset_()
{
  Log::trace() << "State<MODEL>::State starting" << std::endl;
  utiljedi::Timer timer(classname(), "State");
  // TODO: how to use vars in model?
  eckit::LocalConfiguration modelConf;
  oops::Model<MODEL> model(resol, modelConf);
  state_.reset(new State_(resol.geometry(), model.model(), time));
//  this->setObjectSize(state_->serialSize()*sizeof(double));
  Log::trace() << "State<MODEL>::State done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
State<MODEL>::State(const Geometry_ & resol,
                    const Parameters_ & params) : state_(), fset_()
{
  Log::trace() << "State<MODEL>::State read starting" << std::endl;
  utiljedi::Timer timer(classname(), "State");
  eckit::LocalConfiguration modelConf;
  oops::Model<MODEL> model(resol, modelConf);
  state_.reset(new State_(
                 resol.geometry(),
                 model.model(),
                 parametersOrConfiguration<HasParameters_<State_>::value>(params)));
//  this->setObjectSize(state_->serialSize()*sizeof(double));
  Log::trace() << "State<MODEL>::State read done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
State<MODEL>::State(const Geometry_ & resol, const State & other)
  : state_(), fset_()
{
  Log::trace() << "State<MODEL>::State interpolated starting" << std::endl;
  utiljedi::Timer timer(classname(), "State");
  state_.reset(new State_(resol.geometry(), *other.state_));
//  this->setObjectSize(state_->serialSize()*sizeof(double));
  Log::trace() << "State<MODEL>::State interpolated done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
State<MODEL>::State(const State & other) : state_(), fset_()
{
  Log::trace() << "State<MODEL>::State starting copy" << std::endl;
  utiljedi::Timer timer(classname(), "State");
  state_.reset(new State_(*other.state_));
//  this->setObjectSize(state_->serialSize()*sizeof(double));
  Log::trace() << "State<MODEL>::State copy done" << std::endl;
}

// -----------------------------------------------------------------------------

template <typename MODEL>
State<MODEL>::State(const State_ & state)
  : state_(std::make_unique<State_>(state))
{
  Log::trace() << "State<MODEL>::State copy done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
State<MODEL>::~State() {
  Log::trace() << "State<MODEL>::~State starting" << std::endl;
  utiljedi::Timer timer(classname(), "~State");
  fset_.clear();
  state_.reset();
  Log::trace() << "State<MODEL>::~State done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
State<MODEL> & State<MODEL>::operator=(const State & rhs) {
  Log::trace() << "State<MODEL>::operator= starting" << std::endl;
  utiljedi::Timer timer(classname(), "operator=");
  fset_.clear();
  *state_ = *rhs.state_;
  Log::trace() << "State<MODEL>::operator= done" << std::endl;
  return *this;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::read(const Parameters_ & parameters) {
  Log::trace() << "State<MODEL>::read starting" << std::endl;
  utiljedi::Timer timer(classname(), "read");
  fset_.clear();
  state_->read(parameters.toConfiguration());
  Log::trace() << "State<MODEL>::read done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::read(const eckit::Configuration & conf) {
  Log::trace() << "State<MODEL>::read starting" << std::endl;
  utiljedi::Timer timer(classname(), "read");
  fset_.clear();
  state_->read(conf);
  Log::trace() << "State<MODEL>::read done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::write(const WriteParameters_ & parameters) const {
  Log::trace() << "State<MODEL>::write starting" << std::endl;
  utiljedi::Timer timer(classname(), "write");
  state_->write(parameters.toConfiguration);
  Log::trace() << "State<MODEL>::write done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::write(const eckit::Configuration & conf) const {
  Log::trace() << "State<MODEL>::write starting" << std::endl;
  utiljedi::Timer timer(classname(), "write");
  state_->write(conf);
  Log::trace() << "State<MODEL>::write done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
double State<MODEL>::norm() const {
  Log::trace() << "State<MODEL>::norm starting" << std::endl;
  utiljedi::Timer timer(classname(), "norm");
  double zz = state_->norm();
  Log::trace() << "State<MODEL>::norm done" << std::endl;
  return zz;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
size_t State<MODEL>::serialSize() const {
  Log::trace() << "State<MODEL>::serialSize" << std::endl;
  utiljedi::Timer timer(classname(), "serialSize");
  return 0; //  state_->serialSize();
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::serialize(std::vector<double> & vect) const {
  Log::trace() << "State<MODEL>::serialize starting" << std::endl;
  utiljedi::Timer timer(classname(), "serialize");
//  state_->serialize(vect);
  Log::trace() << "State<MODEL>::serialize done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::deserialize(const std::vector<double> & vect, size_t & current) {
  Log::trace() << "State<MODEL>::State deserialize starting" << std::endl;
  utiljedi::Timer timer(classname(), "deserialize");
  fset_.clear();
//  state_->deserialize(vect, current);
  Log::trace() << "State<MODEL>::State deserialize done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::toFieldSet(atlas::FieldSet & fset) const {
  Log::trace() << "State<MODEL>::toFieldSet starting" << std::endl;
  utiljedi::Timer timer(classname(), "toFieldSet");
//  state_->toFieldSet(fset);
  Log::trace() << "State<MODEL>::toFieldSet done" << std::endl;
}

// -----------------------------------------------------------------------------


template<typename MODEL>
void State<MODEL>::fromFieldSet(const atlas::FieldSet & fset) {
  Log::trace() << "State<MODEL>::fromFieldSet starting" << std::endl;
  utiljedi::Timer timer(classname(), "fromFieldSet");
//  state_->fromFieldSet(fset);
  Log::trace() << "State<MODEL>::fromFieldSet done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::print(std::ostream & os) const {
  Log::trace() << "State<MODEL>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *state_;
  Log::trace() << "State<MODEL>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::zero() {
  Log::trace() << "State<MODEL>::zero starting" << std::endl;
  utiljedi::Timer timer(classname(), "zero");
  fset_.clear();
  state_->zero();
  Log::trace() << "State<MODEL>::zero done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void State<MODEL>::accumul(const double & zz, const State & xx) {
  Log::trace() << "State<MODEL>::accumul starting" << std::endl;
  utiljedi::Timer timer(classname(), "accumul");
  fset_.clear();
  state_->accumul(zz, *xx.state_);
  Log::trace() << "State<MODEL>::accumul done" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace interface

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_STATE_H_
