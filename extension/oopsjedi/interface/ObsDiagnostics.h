/*
 * (C) Copyright 2018  UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef OOPSJEDI_INTERFACE_OBSDIAGNOSTICS_H_
#define OOPSJEDI_INTERFACE_OBSDIAGNOSTICS_H_

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include "oopsjedi/base/Variables.h"
#include "oopsjedi/interface/ObsSpace.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/parameters/EmptyParameters.h"
#include "oopsjedi/util/parameters/HasParameters_.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace oopsjedi {

template <typename OBS> class Locations;

// -----------------------------------------------------------------------------

template <typename OBS>
class ObsDiagnostics : public utiljedi::Printable,
                       private boost::noncopyable,
                       private utiljedi::ObjectCounter<ObsDiagnostics<OBS> > {
  typedef typename OBS::ObsDiagnostics   ObsDiags_;
  typedef ObsSpace<OBS>                  ObsSpace_;
  typedef Locations<OBS>                 Locations_;

 public:
  // fall back to EmptyParameters if none specified in ObsDiagnostics
  typedef TParameters_IfAvailableElseFallbackType_t<ObsDiags_, EmptyParameters> Parameters_;

  static const std::string classname() {return "oopsjedi::ObsDiagnostics";}

  ObsDiagnostics(const ObsSpace_ &, const Locations_ &, const Variables &);
  // ctor used in the test for ObsFilters (not implemented in toy models)
  ObsDiagnostics(const Parameters_ &, const ObsSpace_ &, const Variables &);

  ~ObsDiagnostics();

/// Interfacing
  ObsDiags_ & obsdiagnostics() {return *diags_;}
  const ObsDiags_ & obsdiagnostics() const {return *diags_;}

// I/O
  void save(const std::string &) const;

 private:
  void print(std::ostream &) const;
  std::unique_ptr<ObsDiags_> diags_;
};

// -----------------------------------------------------------------------------
template <typename OBS>
ObsDiagnostics<OBS>::ObsDiagnostics(const ObsSpace_ & os,
                                    const Locations_ & locations,
                                    const Variables & vars) : diags_()
{
  Log::trace() << "ObsDiagnostics<OBS>::ObsDiagnostics starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsDiagnostics");
  diags_.reset(new ObsDiags_(os.obsspace(), locations, vars));
  Log::trace() << "ObsDiagnostics<OBS>::ObsDiagnostics done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS>
ObsDiagnostics<OBS>::ObsDiagnostics(const Parameters_ & params, const ObsSpace_ & os,
                                      const Variables & vars) : diags_()
{
  Log::trace() << "ObsDiagnostics<OBS>::ObsDiagnostics starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsDiagnostics");
  diags_.reset(new ObsDiags_(params, os.obsspace(), vars));
  Log::trace() << "ObsDiagnostics<OBS>::ObsDiagnostics done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS>
ObsDiagnostics<OBS>::~ObsDiagnostics() {
  Log::trace() << "ObsDiagnostics<OBS>::~ObsDiagnostics starting" << std::endl;
  utiljedi::Timer timer(classname(), "~ObsDiagnostics");
  diags_.reset();
  Log::trace() << "ObsDiagnostics<OBS>::~ObsDiagnostics done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS>
void ObsDiagnostics<OBS>::save(const std::string & name) const {
  Log::trace() << "ObsDiagnostics<OBS, DATATYPE>::save starting " << name << std::endl;
  utiljedi::Timer timer(classname(), "save");
  diags_->save(name);
  Log::trace() << "ObsDiagnostics<OBS, DATATYPE>::save done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS>
void ObsDiagnostics<OBS>::print(std::ostream & os) const {
  Log::trace() << "ObsDiagnostics<OBS>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *diags_;
  Log::trace() << "ObsDiagnostics<OBS>::print done" << std::endl;
}
// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_OBSDIAGNOSTICS_H_
