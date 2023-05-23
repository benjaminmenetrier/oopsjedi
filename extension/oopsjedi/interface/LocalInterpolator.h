/*
 * (C) Copyright 2022-2022 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "atlas/field/FieldSet.h"
#include "eckit/config/Configuration.h"
#include "oopsjedi/base/Geometry.h"
#include "oopsjedi/base/GeometryData.h"
#include "oopsjedi/base/Increment.h"
#include "oopsjedi/base/State.h"
#include "oopsjedi/base/Variables.h"
#include "oopsjedi/util/ObjectCounter.h"
#include "oopsjedi/util/Printable.h"
#include "oopsjedi/util/Timer.h"
#include "oopsjedi/util/TypeTraits.h"

namespace detail {

// ApplyHelper selects whether to call the model interpolator's apply and applyAD methods using an
// atlas::FieldSet interface or a model State/Increment interface.
//
// The fallback case uses the model State/Increment interface.
template <typename MODEL, typename = cpp17::void_t<>>
struct ApplyHelper {
  // without mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::State<MODEL> & state,
             std::vector<double> & buffer) {
    interp.apply(vars, state.state(), buffer);
  }
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::Increment<MODEL> & increment,
             std::vector<double> & buffer) {
    interp.apply(vars, increment.increment(), buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, oopsjedi::Increment<MODEL> & increment,
             const std::vector<double> & buffer) {
    interp.applyAD(vars, increment.increment(), buffer);
  }

  // with mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::State<MODEL> & state,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    interp.apply(vars, state.state(), mask, buffer);
  }
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::Increment<MODEL> & increment,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    interp.apply(vars, increment.increment(), mask, buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, oopsjedi::Increment<MODEL> & increment,
             const std::vector<bool> & mask, const std::vector<double> & buffer) {
    interp.applyAD(vars, increment.increment(), mask, buffer);
  }
};

// The specialization calls the interpolator's FieldSet interface.
// Note: Here we *assume* that...
// - if the interpolator has apply(FieldSet interface), then it has applyAD(FieldSet interface)
// - if the interpolator has apply(with mask), then it has apply(without mask)
// Code may fail to compile if either assumption is violated.
template <typename MODEL>
struct ApplyHelper<MODEL, cpp17::void_t<decltype(std::declval<typename MODEL::LocalInterpolator>().
                                                   apply(std::declval<oopsjedi::Variables>(),
                                                         std::declval<atlas::FieldSet>(),
                                                         std::declval<std::vector<bool>>(),
                                                         std::declval<std::vector<double>&>()))>> {
  // without mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::State<MODEL> & state,
             std::vector<double> & buffer) {
    interp.apply(vars, state.fieldSet(), buffer);
  }
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::Increment<MODEL> & increment,
             std::vector<double> & buffer) {
    interp.apply(vars, increment.fieldSet(), buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, oopsjedi::Increment<MODEL> & increment,
             const std::vector<double> & buffer) {
    interp.applyAD(vars, increment.fieldSet(), buffer);
  }

  // with mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::State<MODEL> & state,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    interp.apply(vars, state.fieldSet(), mask, buffer);
  }
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const oopsjedi::Increment<MODEL> & increment,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    interp.apply(vars, increment.fieldSet(), mask, buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, oopsjedi::Increment<MODEL> & increment,
             const std::vector<bool> & mask, const std::vector<double> & buffer) {
    interp.applyAD(vars, increment.fieldSet(), mask, buffer);
  }
};

// Constructor helper - determine whether interpolator has a GeomData based constructor
template <typename MODEL, typename = void>
struct ConstructHelper {
  static typename MODEL::LocalInterpolator* apply(const eckit::Configuration & conf,
                                                  const oopsjedi::Geometry<MODEL> & geom,
                                                  const std::vector<double> & lats,
                                                  const std::vector<double> & lons) {
    return new typename MODEL::LocalInterpolator(conf, geom.geometry(), lats, lons);
  }
};

template <typename MODEL>
struct ConstructHelper<MODEL, cpp17::void_t<typename std::enable_if<std::is_constructible<
                              typename MODEL::LocalInterpolator,
                              const eckit::Configuration &,
                              const oopsjedi::GeometryData &,
                              const std::vector<double> &,
                              const std::vector<double> &>::value>::type>>{
  static typename MODEL::LocalInterpolator* apply(const eckit::Configuration & conf,
                                                  const oopsjedi::Geometry<MODEL> & geom,
                                                  const std::vector<double> & lats,
                                                  const std::vector<double> & lons) {
    return new typename MODEL::LocalInterpolator(conf, geom.generic(), lats, lons);
  }
};

// ApplyAtlasHelper tries to call the model interpolator's apply(AD) methods.
// The fallback case errors.
template <typename MODEL, typename = cpp17::void_t<>>
struct ApplyAtlasHelper {
  // without target-point mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const atlas::FieldSet & fset,
             std::vector<double> & buffer) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "apply (taking an atlas::FieldSet), but an oopsjedi::LocalInterpolator "
                           "tried to call this non-existent method.");
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, atlas::FieldSet & fset,
             const std::vector<double> & buffer) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "applyAD (taking an atlas::FieldSet), but an oopsjedi::LocalInterpolator "
                           "tried to call this non-existent method.");
  }
  // with target-point mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const atlas::FieldSet & fset,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "apply (taking an atlas::FieldSet), but an oopsjedi::LocalInterpolator "
                           "tried to call this non-existent method.");
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, atlas::FieldSet & fset,
             const std::vector<bool> & mask, const std::vector<double> & buffer) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "applyAD (taking an atlas::FieldSet), but an oopsjedi::LocalInterpolator "
                           "tried to call this non-existent method.");
  }
};

// The specialization calls the model-specific interpolator's atlas::FieldSet interface.
// Note: Here we simplify the template metaprogramming by assuming that if the interpolator has a
//       method apply(FieldSet), then it also has applyAD(FieldSet), and also assuming that
//       interfaces without and with target-point masks exist. The code may fail to compile if these
//       assumptions are violated.
template <typename MODEL>
struct ApplyAtlasHelper<MODEL,
    cpp17::void_t<decltype(std::declval<typename MODEL::LocalInterpolator>().apply(
        std::declval<oopsjedi::Variables>(),
        std::declval<atlas::FieldSet>(),
        std::declval<std::vector<double>&>()))>> {
  // without target-point mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const atlas::FieldSet & fset,
             std::vector<double> & buffer) {
    interp.apply(vars, fset, buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, atlas::FieldSet & fset,
             const std::vector<double> & buffer) {
    interp.applyAD(vars, fset, buffer);
  }
  // with target-point mask
  static void apply(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, const atlas::FieldSet & fset,
             const std::vector<bool> & mask, std::vector<double> & buffer) {
    interp.apply(vars, fset, mask, buffer);
  }
  static void applyAD(const typename MODEL::LocalInterpolator & interp,
             const oopsjedi::Variables & vars, atlas::FieldSet & fset,
             const std::vector<bool> & mask, const std::vector<double> & buffer) {
    interp.applyAD(vars, fset, mask, buffer);
  }
};

// BufferToAtlasHelper tries to call the model interpolator's bufferToFieldSet(AD) methods.
// The fallback case errors.
template <typename MODEL, typename = cpp17::void_t<>>
struct BufferToAtlasHelper {
  static void bufferToFieldSet(const oopsjedi::Variables & vars,
                               const std::vector<size_t> & buffer_indices,
                               const std::vector<double> & buffer,
                               atlas::FieldSet & fset) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "bufferToFieldSet, but an oopsjedi::LocalInterpolator tried to call this "
                           "non-existent method.");
  }
  static void bufferToFieldSetAD(const oopsjedi::Variables & vars,
                                 const std::vector<size_t> & buffer_indices,
                                 std::vector<double> & buffer,
                                 const atlas::FieldSet & fset) {
    throw eckit::Exception("The LocalInterpolator for model " + MODEL::name() + " has no method "
                           "bufferToFieldSetAD, but an oopsjedi::LocalInterpolator tried to call this "
                           "non-existent method.");
  }
};

// The specialization calls the model-specific interpolator's bufferToFieldSet interface.
// Note: Here we simplify the template metaprogramming by assuming that if the interpolator has a
//       method bufferToFieldSet, then it also has bufferToFieldSetAD. The code may fail to compile
//       if these assumptions are violated.
template <typename MODEL>
struct BufferToAtlasHelper<MODEL,
    cpp17::void_t<decltype(std::declval<typename MODEL::LocalInterpolator>().bufferToFieldSet(
        std::declval<oopsjedi::Variables>(),
        std::declval<std::vector<size_t>&>(),
        std::declval<std::vector<double>&>(),
        std::declval<atlas::FieldSet&>()))>> {
  static void bufferToFieldSet(const oopsjedi::Variables & vars,
                               const std::vector<size_t> & buffer_indices,
                               const std::vector<double> & buffer,
                               atlas::FieldSet & fset) {
    MODEL::LocalInterpolator::bufferToFieldSet(vars, buffer_indices, buffer, fset);
  }
  static void bufferToFieldSetAD(const oopsjedi::Variables & vars,
                                 const std::vector<size_t> & buffer_indices,
                                 std::vector<double> & buffer,
                                 const atlas::FieldSet & fset) {
    MODEL::LocalInterpolator::bufferToFieldSetAD(vars, buffer_indices, buffer, fset);
  }
};

}  // namespace detail

namespace oopsjedi {

/// \brief Encapsulates local (ie on current MPI task) interpolators
// -----------------------------------------------------------------------------

template <typename MODEL>
class LocalInterpolator : public utiljedi::Printable,
                          private utiljedi::ObjectCounter<LocalInterpolator<MODEL> > {
  typedef typename MODEL::LocalInterpolator   LocalInterpolator_;
  typedef oopsjedi::Geometry<MODEL>            Geometry_;
  typedef oopsjedi::Increment<MODEL>           Increment_;
  typedef oopsjedi::State<MODEL>               State_;

 public:
  static const std::string classname() {return "oopsjedi::LocalInterpolator";}

  LocalInterpolator(const eckit::Configuration &, const Geometry_ &,
                    const std::vector<double> &, const std::vector<double> &);
  ~LocalInterpolator();

  void apply(const Variables &, const State_ &,
             const std::vector<bool> &, std::vector<double> &) const;
  void apply(const Variables &, const State_ &,
             std::vector<double> &) const;
  void apply(const Variables &, const Increment_ &,
             const std::vector<bool> &, std::vector<double> &) const;
  void apply(const Variables &, const Increment_ &,
             std::vector<double> &) const;
  void apply(const Variables &, const atlas::FieldSet &,
             const std::vector<bool> &, std::vector<double> &) const;
  void apply(const Variables &, const atlas::FieldSet &,
             std::vector<double> &) const;
  void applyAD(const Variables &, Increment_ &,
               const std::vector<bool> &, const std::vector<double> &) const;
  void applyAD(const Variables &, Increment_ &,
               const std::vector<double> &) const;
  void applyAD(const Variables &, atlas::FieldSet &,
               const std::vector<bool> &, const std::vector<double> &) const;
  void applyAD(const Variables &, atlas::FieldSet &,
               const std::vector<double> &) const;

  static void bufferToFieldSet(const Variables &, const std::vector<size_t> &,
                               const std::vector<double> &, atlas::FieldSet &);
  static void bufferToFieldSetAD(const Variables &, const std::vector<size_t> &,
                                 std::vector<double> &, const atlas::FieldSet &);

 private:
  std::unique_ptr<LocalInterpolator_> interpolator_;
  void print(std::ostream &) const override;
};

// -----------------------------------------------------------------------------

template<typename MODEL>
LocalInterpolator<MODEL>::LocalInterpolator(const eckit::Configuration & conf,
                                            const Geometry_ & resol,
                                            const std::vector<double> & lats,
                                            const std::vector<double> & lons)
  : interpolator_()
{
  Log::trace() << "LocalInterpolator<MODEL>::LocalInterpolator starting" << std::endl;
  utiljedi::Timer timer(classname(), "LocalInterpolator");
  interpolator_.reset(detail::ConstructHelper<MODEL>::apply(conf, resol, lats, lons));
  Log::trace() << "LocalInterpolator<MODEL>::LocalInterpolator done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
LocalInterpolator<MODEL>::~LocalInterpolator() {
  Log::trace() << "LocalInterpolator<MODEL>::~LocalInterpolator starting" << std::endl;
  utiljedi::Timer timer(classname(), "~LocalInterpolator");
  interpolator_.reset();
  Log::trace() << "LocalInterpolator<MODEL>::~LocalInterpolator done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const State_ & xx,
                                     const std::vector<bool> & mask,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::apply starting" << std::endl;
  utiljedi::Timer timer(classname(), "apply");
  detail::ApplyHelper<MODEL>::apply(*interpolator_, vars, xx, mask, vect);
  Log::trace() << "LocalInterpolator<MODEL>::apply done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const State_ & xx,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::apply starting" << std::endl;
  utiljedi::Timer timer(classname(), "apply");
  detail::ApplyHelper<MODEL>::apply(*interpolator_, vars, xx, vect);
  Log::trace() << "LocalInterpolator<MODEL>::apply done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const Increment_ & dx,
                                     const std::vector<bool> & mask,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyTL starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyTL");
  detail::ApplyHelper<MODEL>::apply(*interpolator_, vars, dx, mask, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyTL done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const Increment_ & dx,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyTL starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyTL");
  detail::ApplyHelper<MODEL>::apply(*interpolator_, vars, dx, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyTL done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const atlas::FieldSet & fs,
                                     const std::vector<bool> & mask,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::apply(FieldSet) starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyTL");
  detail::ApplyAtlasHelper<MODEL>::apply(*interpolator_, vars, fs, mask, vect);
  Log::trace() << "LocalInterpolator<MODEL>::apply(FieldSet) done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::apply(const Variables & vars, const atlas::FieldSet & fs,
                                     std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::apply(FieldSet) starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyTL");
  detail::ApplyAtlasHelper<MODEL>::apply(*interpolator_, vars, fs, vect);
  Log::trace() << "LocalInterpolator<MODEL>::apply(FieldSet) done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::applyAD(const Variables & vars, Increment_ & dx,
                                       const std::vector<bool> & mask,
                                       const std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyAD starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyAD");
  detail::ApplyHelper<MODEL>::applyAD(*interpolator_, vars, dx, mask, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyAD done" << std::endl;
}

// -----------------------------------------------------------------------------
template<typename MODEL>
void LocalInterpolator<MODEL>::applyAD(const Variables & vars, Increment_ & dx,
                                       const std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyAD starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyAD");
  detail::ApplyHelper<MODEL>::applyAD(*interpolator_, vars, dx, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyAD done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::applyAD(const Variables & vars, atlas::FieldSet & fs,
                                       const std::vector<bool> & mask,
                                       const std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyAD(FieldSet) starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyAD");
  detail::ApplyAtlasHelper<MODEL>::applyAD(*interpolator_, vars, fs, mask, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyAD(FieldSet) done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::applyAD(const Variables & vars, atlas::FieldSet & fs,
                                       const std::vector<double> & vect) const {
  Log::trace() << "LocalInterpolator<MODEL>::applyAD(FieldSet) starting" << std::endl;
  utiljedi::Timer timer(classname(), "applyAD");
  detail::ApplyAtlasHelper<MODEL>::applyAD(*interpolator_, vars, fs, vect);
  Log::trace() << "LocalInterpolator<MODEL>::applyAD(FieldSet) done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::bufferToFieldSet(const Variables & vars,
                                                const std::vector<size_t> & buffer_indices,
                                                const std::vector<double> & buffer,
                                                atlas::FieldSet & target) {
  Log::trace() << "LocalInterpolator<MODEL>::bufferToFieldSet starting" << std::endl;
  utiljedi::Timer timer(classname(), "bufferToFieldSet");
  detail::BufferToAtlasHelper<MODEL>::bufferToFieldSet(vars, buffer_indices, buffer, target);
  Log::trace() << "LocalInterpolator<MODEL>::bufferToFieldSet done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::bufferToFieldSetAD(const Variables & vars,
                                                  const std::vector<size_t> & buffer_indices,
                                                  std::vector<double> & buffer,
                                                  const atlas::FieldSet & target) {
  Log::trace() << "LocalInterpolator<MODEL>::bufferToFieldSetAD starting" << std::endl;
  utiljedi::Timer timer(classname(), "bufferToFieldSetAD");
  detail::BufferToAtlasHelper<MODEL>::bufferToFieldSetAD(vars, buffer_indices, buffer, target);
  Log::trace() << "LocalInterpolator<MODEL>::bufferToFieldSet done" << std::endl;
}

// -----------------------------------------------------------------------------

template<typename MODEL>
void LocalInterpolator<MODEL>::print(std::ostream & os) const {
  Log::trace() << "LocalInterpolator<MODEL>::print starting" << std::endl;
  utiljedi::Timer timer(classname(), "print");
  os << *interpolator_;
  Log::trace() << "LocalInterpolator<MODEL>::print done" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace oopsjedi