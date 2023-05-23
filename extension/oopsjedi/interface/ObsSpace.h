/*
 * (C) Copyright 2009-2016 ECMWF.
 * (C) Copyright 2017-2019 UCAR.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef OOPSJEDI_INTERFACE_OBSSPACE_H_
#define OOPSJEDI_INTERFACE_OBSSPACE_H_

#include <memory>
#include <ostream>
#include <string>

#include "eckit/system/ResourceUsage.h"

#include "oopsjedi/interface/GeometryIterator.h"
#include "oopsjedi/mpi/mpi.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace utiljedi {
  class DateTime;
}

namespace oopsjedi {

class Variables;

// -----------------------------------------------------------------------------

template <typename OBS>
class ObsSpace : public utiljedi::Printable,
                 private utiljedi::ObjectCounter<ObsSpace<OBS> > {
  typedef typename OBS::ObsSpace          ObsSpace_;
  typedef GeometryIterator<OBS>           ObsIterator_;

 public:
  typedef typename ObsSpace_::Parameters_ Parameters_;

  static const std::string classname() {return "oopsjedi::ObsSpace";}

  ObsSpace(const Parameters_ &, const eckit::mpi::Comm &,
           const utiljedi::DateTime &, const utiljedi::DateTime &,
           const eckit::mpi::Comm & time = oopsjedi::mpi::myself());
  ~ObsSpace();

  ObsSpace(const ObsSpace &) = delete;

/// Interfacing
  ObsSpace_ & obsspace() const {return *obsdb_;}  // const problem? YT

/// Assimilation window
  const utiljedi::DateTime & windowStart() const {return obsdb_->windowStart();}
  const utiljedi::DateTime & windowEnd() const {return obsdb_->windowEnd();}

  const Variables & obsvariables() const;
  const Variables & assimvariables() const;

// Other
  const std::string & obsname() const {return obsdb_->obsname();}

  /// Iterator to the first observation
  ObsIterator_ begin() const;
  /// Iterator to the past-the-end observation (after last)
  ObsIterator_ end() const;

  const eckit::mpi::Comm & timeComm() const {return time_;}

// Save to file
  void save() const;

 private:
  void print(std::ostream &) const;

  std::unique_ptr<ObsSpace_> obsdb_;
  const eckit::mpi::Comm & time_;
};

// -----------------------------------------------------------------------------

template <typename OBS>
ObsSpace<OBS>::ObsSpace(const Parameters_ & params,
                        const eckit::mpi::Comm & comm,
                        const utiljedi::DateTime & bgn,
                        const utiljedi::DateTime & end,
                        const eckit::mpi::Comm & time) : obsdb_(), time_(time) {
  Log::trace() << "ObsSpace<OBS>::ObsSpace starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsSpace");
  size_t init = eckit::system::ResourceUsage().maxResidentSetSize();
  obsdb_.reset(new ObsSpace_(params, comm, bgn, end, time));
  size_t current = eckit::system::ResourceUsage().maxResidentSetSize();
  this->setObjectSize(current - init);
  Log::trace() << "ObsSpace<OBS>::ObsSpace done" << std::endl;
}

// -----------------------------------------------------------------------------

template <typename OBS>
ObsSpace<OBS>::~ObsSpace() {
  Log::trace() << "ObsSpace<OBS>::~ObsSpace starting" << std::endl;
  utiljedi::Timer timer(classname(), "~ObsSpace");
  obsdb_.reset();
  Log::trace() << "ObsSpace<OBS>::~ObsSpace done" << std::endl;
}

// -----------------------------------------------------------------------------

template <typename OBS>
void ObsSpace<OBS>::save() const {
  Log::trace() << "ObsSpace<OBS>::save starting" << std::endl;
  utiljedi::Timer timer(classname(), "save");
  obsdb_->save();
  Log::trace() << "ObsSpace<OBS>::save done" << std::endl;
}

// -----------------------------------------------------------------------------

template <typename OBS>
void ObsSpace<OBS>::print(std::ostream & os) const {
  Log::trace() << "ObsSpace<OBS>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *obsdb_;
  Log::trace() << "ObsSpace<OBS>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

template <typename OBS>
const Variables & ObsSpace<OBS>::obsvariables() const {
  Log::trace() << "ObsSpace<OBS>::obsvariables starting" << std::endl;
  utiljedi::Timer timer(classname(), "obsvariables");
  return obsdb_->obsvariables();
}

// -----------------------------------------------------------------------------

template <typename OBS>
const Variables & ObsSpace<OBS>::assimvariables() const {
  Log::trace() << "ObsSpace<OBS>::assimvariables starting" << std::endl;
  utiljedi::Timer timer(classname(), "assimvariables");
  return obsdb_->assimvariables();
}

// -----------------------------------------------------------------------------

template <typename OBS>
GeometryIterator<OBS> ObsSpace<OBS>::begin() const {
  Log::trace() << "ObsSpace<OBS>::begin starting" << std::endl;
  utiljedi::Timer timer(classname(), "begin");
  Log::trace() << "ObsSpace<OBS>::begin done" << std::endl;
  return ObsIterator_(obsdb_->begin());
}

// -----------------------------------------------------------------------------

template <typename OBS>
GeometryIterator<OBS> ObsSpace<OBS>::end() const {
  Log::trace() << "ObsSpace<OBS>::end starting" << std::endl;
  utiljedi::Timer timer(classname(), "end");
  Log::trace() << "ObsSpace<OBS>::end done" << std::endl;
  return ObsIterator_(obsdb_->end());
}

// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_OBSSPACE_H_
