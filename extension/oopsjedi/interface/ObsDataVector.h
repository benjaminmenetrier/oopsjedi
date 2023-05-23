/*
 * (C) Copyright 2018  UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef OOPSJEDI_INTERFACE_OBSDATAVECTOR_H_
#define OOPSJEDI_INTERFACE_OBSDATAVECTOR_H_

#include <memory>
#include <ostream>
#include <string>

#include "oopsjedi/base/ObsVector.h"
#include "oopsjedi/base/Variables.h"
#include "oopsjedi/interface/ObsSpace.h"
#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/Timer.h"

#include "oopsjedi/interface/ObsDataVector_head.h"

namespace oopsjedi {

// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
ObsDataVector<OBS, DATATYPE>::ObsDataVector(const ObsSpace<OBS> & os,
                                            const Variables & vars, const std::string name)
  : data_()
{
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsDataVector");
  data_.reset(new ObsDataVec_(os.obsspace(), vars, name));
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
ObsDataVector<OBS, DATATYPE>::ObsDataVector(const ObsDataVector & other): data_() {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsDataVector");
  data_.reset(new ObsDataVec_(*other.data_));
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
ObsDataVector<OBS, DATATYPE>::ObsDataVector(ObsVector<OBS> & other): data_() {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector starting" << std::endl;
  utiljedi::Timer timer(classname(), "ObsDataVector");
  data_.reset(new ObsDataVec_(other.obsvector()));
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::ObsDataVector done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
ObsDataVector<OBS, DATATYPE>::~ObsDataVector() {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::~ObsDataVector starting" << std::endl;
  utiljedi::Timer timer(classname(), "~ObsDataVector");
  data_.reset();
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::~ObsDataVector done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE> ObsDataVector<OBS, DATATYPE> &
ObsDataVector<OBS, DATATYPE>::operator=(const ObsDataVector & rhs) {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::operator= starting" << std::endl;
  utiljedi::Timer timer(classname(), "operator=");
  *data_ = *rhs.data_;
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::operator= done" << std::endl;
  return *this;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
void ObsDataVector<OBS, DATATYPE>::zero() {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::zero starting" << std::endl;
  utiljedi::Timer timer(classname(), "zero");
  data_->zero();
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::zero done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
void ObsDataVector<OBS, DATATYPE>::mask(const ObsDataVector<OBS, int> & qc) {
  Log::trace() << "ObsDataVector<OBS>::mask starting" << std::endl;
  utiljedi::Timer timer(classname(), "mask");
  data_->mask(qc.obsdatavector());
  Log::trace() << "ObsDataVector<OBS>::mask done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
void ObsDataVector<OBS, DATATYPE>::print(std::ostream & os) const {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *data_;
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::print done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
void ObsDataVector<OBS, DATATYPE>::read(const std::string & name) {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::read starting " << name << std::endl;
  utiljedi::Timer timer(classname(), "read");
  data_->read(name);
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::read done" << std::endl;
}
// -----------------------------------------------------------------------------
template <typename OBS, typename DATATYPE>
void ObsDataVector<OBS, DATATYPE>::save(const std::string & name) const {
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::save starting " << name << std::endl;
  utiljedi::Timer timer(classname(), "save");
  data_->save(name);
  Log::trace() << "ObsDataVector<OBS, DATATYPE>::save done" << std::endl;
}
// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_OBSDATAVECTOR_H_
