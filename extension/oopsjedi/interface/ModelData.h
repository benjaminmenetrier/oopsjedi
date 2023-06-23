/*
 * (C) Copyright 2023 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef OOPSJEDI_INTERFACE_MODELDATA_H_
#define OOPSJEDI_INTERFACE_MODELDATA_H_

#include <memory>
#include <string>

#include "oopsjedi/util/Logger.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"

namespace oopsjedi {

// -----------------------------------------------------------------------------
/// \brief Model Data
///
template <typename MODEL>
class ModelData : public  utiljedi::Printable,
                  private utiljedi::ObjectCounter<ModelData<MODEL> >  {
//  typedef typename MODEL::ModelData ModelData_;
  typedef Geometry<MODEL>           Geometry_;

 public:
  static const std::string classname() {return "oopsjedi::ModelData";}

  explicit ModelData(const Geometry_ &);
  virtual ~ModelData();
  ModelData(const ModelData &) = delete;
  ModelData(ModelData &&) = default;
  const ModelData & operator=(const ModelData &) = delete;
  ModelData & operator=(ModelData &&) = default;

  const eckit::LocalConfiguration modelData() const;

 private:
  void print(std::ostream &) const override;

//  std::unique_ptr<ModelData_> modeldata_;  // pointer to the ModelData implementation
};

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelData<MODEL>::ModelData(const Geometry_ & geometry)
{
  Log::trace() << "ModelData<MODEL>::ModelData starting" << std::endl;
  utiljedi::Timer timer(classname(), "ModelData");
//  modeldata_.reset(new ModelData_(geometry.geometry()));
  Log::trace() << "ModelData<MODEL>::ModelData done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
ModelData<MODEL>::~ModelData() {
  Log::trace() << "ModelData<MODEL>::~ModelData starting" << std::endl;
  utiljedi::Timer timer(classname(), "~ModelData");
//  modeldata_.reset();
  Log::trace() << "ModelData<MODEL>::~ModelData done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
const eckit::LocalConfiguration ModelData<MODEL>::modelData() const {
  Log::trace() << "ModelData<MODEL>::modelData starting" << std::endl;
  utiljedi::Timer timer(classname(), "modelData");
  Log::trace() << "ModelData<MODEL>::modelData done" << std::endl;
//  return modeldata_->modelData();
  return eckit::LocalConfiguration();
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void ModelData<MODEL>::print(std::ostream & os) const {
  Log::trace() << "ModelData<MODEL>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
//  os << *modeldata_;
  Log::trace() << "ModelData<MODEL>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace oopsjedi

#endif  // OOPSJEDI_INTERFACE_MODELDATA_H_
