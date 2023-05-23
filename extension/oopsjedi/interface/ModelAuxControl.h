/*
 * (C) Copyright 2009-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef OOPSJEDI_INTERFACE_MODELAUXCONTROL_H_
#define OOPSJEDI_INTERFACE_MODELAUXCONTROL_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "oopsjedi/base/Geometry.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/parameters/GenericParameters.h"
#include "oopsjedi/util/parameters/HasParameters_.h"
#include "oopsjedi/util/parameters/Parameters.h"
#include "oopsjedi/util/parameters/ParametersOrConfiguration.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace eckit {
  class Configuration;
}

namespace oopsjedi {

// -----------------------------------------------------------------------------
/// \brief Auxiliary state related to model (could be e.g. model bias), not used at the moment.
/// \details
/// This class is used to manipulate parameters of the model that can be estimated in the
/// assimilation. This includes model bias but could be used for other parameters.
/// This is sometimes referred to as augmented state or augmented control variable in the
/// literature.
/// This class calls the model's implementation of ModelAuxControl.

// -----------------------------------------------------------------------------

/// Note: implementations of this interface can opt to extract their settings either from
/// a Configuration object or from a subclass of Parameters.
///
/// In the former case, they should provide a constructor with the following signature:
///
///    ModelAuxControl(const Geometry_ &, const eckit::Configuration &);
///
/// In the latter case, the implementer should first define a subclass of Parameters holding the
/// settings of the model bias in question. The implementation of the ModelAuxControl interface
/// should then typedef `Parameters_` to the name of that subclass and provide a constructor with
/// the following signature:
///
///    ModelAuxControl(const Geometry_ &, const Parameters_ &);
template <typename MODEL>
class ModelAuxControl : public utiljedi::Printable,
                        public utiljedi::Serializable,
                        private utiljedi::ObjectCounter<ModelAuxControl<MODEL> > {
  typedef typename MODEL::ModelAuxControl      ModelAuxControl_;
  typedef Geometry<MODEL>            Geometry_;

 public:
  /// Set to ModelAuxControl_::Parameters_ if ModelAuxControl_ provides a type called Parameters_
  /// and to GenericParameters (a thin wrapper of an eckit::LocalConfiguration object) if not.
  typedef TParameters_IfAvailableElseFallbackType_t<ModelAuxControl_, GenericParameters>
    Parameters_;

  static const std::string classname() {return "oopsjedi::ModelAuxControl";}

  ModelAuxControl(const Geometry_ &, const Parameters_ &);
  ModelAuxControl(const Geometry_ &, const eckit::Configuration &);
  /// Copies \p other ModelAuxControl, changing its resolution to \p resol
  ModelAuxControl(const Geometry_ & resol, const ModelAuxControl & other);
  /// Creates ModelAuxControl with the same structure as \p other.
  /// Copies \p other if \p copy is true, otherwise creates zero ModelAuxControl
  explicit ModelAuxControl(const ModelAuxControl &, const bool copy = true);
  /// Destructor (defined explicitly for timing and tracing)
  ~ModelAuxControl();

  /// const Accessor
  const ModelAuxControl_ & modelauxcontrol() const {return *aux_;}
  /// Accessor
  ModelAuxControl_ & modelauxcontrol() {return *aux_;}

  /// Read this ModelAuxControl from file
  void read(const eckit::Configuration &);
  /// Write this ModelAuxControl out to file
  void write(const eckit::Configuration &) const;
  /// Norm (used in tests)
  double norm() const;

  /// Serialize and deserialize
  size_t serialSize() const override {return 0;}
  void serialize(std::vector<double> &) const override {}
  void deserialize(const std::vector<double> &, size_t &) override {}

 private:
  ModelAuxControl & operator=(const ModelAuxControl &);
  void print(std::ostream &) const override;
  std::unique_ptr<ModelAuxControl_> aux_;
};

// =============================================================================

template<typename MODEL>
ModelAuxControl<MODEL>::ModelAuxControl(const Geometry_ & resol,
                                        const Parameters_ & parameters) : aux_()
{
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl starting" << std::endl;
  utiljedi::Timer timer(classname(), "ModelAuxControl");
  aux_.reset(new ModelAuxControl_(
               resol.geometry(),
               parametersOrConfiguration<HasParameters_<ModelAuxControl_>::value>(parameters)));
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelAuxControl<MODEL>::ModelAuxControl(const Geometry_ & resol,
                                        const eckit::Configuration & conf)
  : ModelAuxControl(resol, validateAndDeserialize<Parameters_>(conf))
{}

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelAuxControl<MODEL>::ModelAuxControl(const Geometry_ & resol,
                                        const ModelAuxControl & other) : aux_()
{
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl interpolated starting" << std::endl;
  utiljedi::Timer timer(classname(), "ModelAuxControl");
  aux_.reset(new ModelAuxControl_(resol.geometry(), *other.aux_));
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl interpolated done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelAuxControl<MODEL>::ModelAuxControl(const ModelAuxControl & other,
                                        const bool copy) : aux_()
{
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl copy starting" << std::endl;
  utiljedi::Timer timer(classname(), "ModelAuxControl");
  aux_.reset(new ModelAuxControl_(*other.aux_, copy));
  Log::trace() << "ModelAuxControl<MODEL>::ModelAuxControl copy done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelAuxControl<MODEL>::~ModelAuxControl() {
  Log::trace() << "ModelAuxControl<MODEL>::~ModelAuxControl starting" << std::endl;
  utiljedi::Timer timer(classname(), "~ModelAuxControl");
  aux_.reset();
  Log::trace() << "ModelAuxControl<MODEL>::~ModelAuxControl done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void ModelAuxControl<MODEL>::read(const eckit::Configuration & conf) {
  Log::trace() << "ModelAuxControl<MODEL>::read starting" << std::endl;
  utiljedi::Timer timer(classname(), "read");
  aux_->read(conf);
  Log::trace() << "ModelAuxControl<MODEL>::read done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void ModelAuxControl<MODEL>::write(const eckit::Configuration & conf) const {
  Log::trace() << "ModelAuxControl<MODEL>::write starting" << std::endl;
  utiljedi::Timer timer(classname(), "write");
  aux_->write(conf);
  Log::trace() << "ModelAuxControl<MODEL>::write done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
double ModelAuxControl<MODEL>::norm() const {
  Log::trace() << "ModelAuxControl<MODEL>::norm starting" << std::endl;
  utiljedi::Timer timer(classname(), "norm");
  double zz = aux_->norm();
  Log::trace() << "ModelAuxControl<MODEL>::norm done" << std::endl;
  return zz;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void ModelAuxControl<MODEL>::print(std::ostream & os) const {
  Log::trace() << "ModelAuxControl<MODEL>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *aux_;
  Log::trace() << "ModelAuxControl<MODEL>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_MODELAUXCONTROL_H_
