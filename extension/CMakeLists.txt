include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

list( APPEND oops_src_files

oopsjedi/assimilation/BMatrix.h
oopsjedi/assimilation/CMatrix.h
oopsjedi/assimilation/ControlIncrement.h
oopsjedi/assimilation/ControlVariable.h
oopsjedi/assimilation/CostFct3DVar.h
oopsjedi/assimilation/CostFct4DEnsVar.h
oopsjedi/assimilation/CostFct4DVar.h
oopsjedi/assimilation/CostFctWeak.h
oopsjedi/assimilation/CostFunction.h
oopsjedi/assimilation/CostJb3D.h
oopsjedi/assimilation/CostJb4D.h
oopsjedi/assimilation/CostJbJq.h
oopsjedi/assimilation/CostJbState.h
oopsjedi/assimilation/CostJbTotal.h
oopsjedi/assimilation/CostJcDFI.h
oopsjedi/assimilation/CostJo.h
oopsjedi/assimilation/CostTermBase.h
oopsjedi/assimilation/DRGMRESRMinimizer.h
oopsjedi/assimilation/DRIPCGMinimizer.h
oopsjedi/assimilation/DRMinimizer.h
oopsjedi/assimilation/DRPBlockLanczosMinimizer.h
oopsjedi/assimilation/DRPCGMinimizer.h
oopsjedi/assimilation/DRPFOMMinimizer.h
oopsjedi/assimilation/DRPLanczosMinimizer.h
oopsjedi/assimilation/DualMinimizer.h
oopsjedi/assimilation/DualVector.h
oopsjedi/assimilation/FGMRES.h
oopsjedi/assimilation/FGMRESMinimizer.h
oopsjedi/assimilation/FtnTriDiagSpectrum.F90
oopsjedi/assimilation/FullGMRES.h
oopsjedi/assimilation/GETKFSolver.h
oopsjedi/assimilation/gletkfInterface.h
oopsjedi/assimilation/gletkf_interface.f90
oopsjedi/assimilation/gletkf_mod.f90
oopsjedi/assimilation/GMRESR.h
oopsjedi/assimilation/GMRESRMinimizer.h
oopsjedi/assimilation/HBHtMatrix.h
oopsjedi/assimilation/HessianMatrix.h
oopsjedi/assimilation/HMatrix.h
oopsjedi/assimilation/HtMatrix.h
oopsjedi/assimilation/HtRinvHMatrix.h
oopsjedi/assimilation/IncrementalAssimilation.h
oopsjedi/assimilation/instantiateCostFactory.h
oopsjedi/assimilation/instantiateLocalEnsembleSolverFactory.h
oopsjedi/assimilation/instantiateMinFactory.h
oopsjedi/assimilation/IPCG.h
oopsjedi/assimilation/IPCGMinimizer.h
oopsjedi/assimilation/JqTerm.h
oopsjedi/assimilation/JqTermTLAD.h
oopsjedi/assimilation/LBGMRESRMinimizer.h
oopsjedi/assimilation/LBHessianMatrix.h
oopsjedi/assimilation/LBMinimizer.h
oopsjedi/assimilation/LETKFSolver.h
oopsjedi/assimilation/LETKFSolverGSI.h
oopsjedi/assimilation/LocalEnsembleSolverParameters.h
oopsjedi/assimilation/LocalEnsembleSolver.h
oopsjedi/assimilation/Minimizer.h
oopsjedi/assimilation/MinimizerUtils.cc
oopsjedi/assimilation/MinimizerUtils.h
oopsjedi/assimilation/MINRES.h
oopsjedi/assimilation/MINRESMinimizer.h
oopsjedi/assimilation/PCG.h
oopsjedi/assimilation/PCGMinimizer.h
oopsjedi/assimilation/PFF.h
oopsjedi/assimilation/PLanczos.h
oopsjedi/assimilation/PLanczosMinimizer.h
oopsjedi/assimilation/PMatrix.h
oopsjedi/assimilation/PrimalMinimizer.h
oopsjedi/assimilation/QNewtonLMP.h
oopsjedi/assimilation/RinvHMatrix.h
oopsjedi/assimilation/RinvMatrix.h
oopsjedi/assimilation/rotmat.h
oopsjedi/assimilation/RPCGMinimizer.h
oopsjedi/assimilation/RPLanczosMinimizer.h
oopsjedi/assimilation/SaddlePointLMPMatrix.h
oopsjedi/assimilation/SaddlePointMatrix.h
oopsjedi/assimilation/SaddlePointMinimizer.h
oopsjedi/assimilation/SaddlePointPrecondMatrix.h
oopsjedi/assimilation/SaddlePointVector.h
oopsjedi/assimilation/SpectralLMP.h
oopsjedi/assimilation/TriDiagSolve.h
oopsjedi/assimilation/TriDiagSpectrum.h
oopsjedi/assimilation/UpHessSolve.h
oopsjedi/assimilation/UpTriSolve.h
oopsjedi/base/Accumulator.h
oopsjedi/base/AnalyticInit.h
oopsjedi/base/Departures.h
oopsjedi/base/DeparturesEnsemble.h
oopsjedi/base/DiagonalMatrix.h
oopsjedi/base/DolphChebyshev.cc
oopsjedi/base/DolphChebyshev.h
oopsjedi/base/EnsembleCovariance.h
oopsjedi/base/ForecastParameters.h
oopsjedi/base/GeneralizedDepartures.h
oopsjedi/base/Geometry.h
oopsjedi/base/GeometryData.cc
oopsjedi/base/GeometryData.h
oopsjedi/base/GetValuePosts.h
oopsjedi/base/GetValues.h
oopsjedi/base/GetValueTLADs.h
oopsjedi/base/LocalIncrement.cc
oopsjedi/base/LocalIncrement.h
oopsjedi/base/Locations.h
oopsjedi/base/HybridCovariance.h
oopsjedi/base/IdentityMatrix.h
oopsjedi/base/Increment.h
oopsjedi/base/Increment4D.h
oopsjedi/base/IncrementEnsemble.h
oopsjedi/base/IncrementEnsemble4D.h
oopsjedi/base/instantiateCovarFactory.h
oopsjedi/base/instantiateObsFilterFactory.h
oopsjedi/base/LatLonGridPostProcessor.h
oopsjedi/base/LatLonGridWriter.h
oopsjedi/base/LinearModel.h
oopsjedi/base/LinearVariableChangeParametersBase.h
oopsjedi/base/Localization.h
oopsjedi/base/Model.h
oopsjedi/base/ModelSpaceCovarianceBase.h
oopsjedi/base/ModelSpaceCovarianceParametersBase.h
oopsjedi/base/ObsAuxControls.h
oopsjedi/base/ObsAuxCovariances.h
oopsjedi/base/ObsAuxIncrements.h
oopsjedi/base/ObsAuxPreconditioners.h
oopsjedi/base/ObsEnsemble.h
oopsjedi/base/ObsError.h
oopsjedi/base/ObsErrors.h
oopsjedi/base/Observations.h
oopsjedi/base/Observer.h
oopsjedi/base/Observers.h
oopsjedi/base/ObserversTLAD.h
oopsjedi/base/ObserverTLAD.h
oopsjedi/base/ObserverUtils.h
oopsjedi/base/ObsFilter.h
oopsjedi/base/ObsFilters.h
oopsjedi/base/ObsLocalizationBase.h
oopsjedi/base/ObsLocalizationParametersBase.h
oopsjedi/base/ObsLocalizations.h
oopsjedi/base/ObsSpaceBase.cc
oopsjedi/base/ObsSpaceBase.h
oopsjedi/base/ObsSpaces.h
oopsjedi/base/ObsTypeParameters.h
oopsjedi/base/ObsVector.h
oopsjedi/base/ParameterTraitsVariables.cc
oopsjedi/base/ParameterTraitsVariables.h
oopsjedi/base/PostBase.h
oopsjedi/base/PostBaseTLAD.h
oopsjedi/base/PostProcessor.h
oopsjedi/base/PostProcessorTLAD.h
oopsjedi/base/PostTimer.cc
oopsjedi/base/PostTimer.h
oopsjedi/base/PostTimerParameters.h
oopsjedi/base/SamplingMethodSelector.h
oopsjedi/base/State.h
oopsjedi/base/State4D.h
oopsjedi/base/StateEnsemble.h
oopsjedi/base/StateEnsemble4D.h
oopsjedi/base/StateInfo.h
oopsjedi/base/StateParametersND.h
oopsjedi/base/StateWriter.h
oopsjedi/base/TrajectorySaver.h
oopsjedi/base/TrivialSamplingMethodSelector.h
oopsjedi/base/WriteParametersBase.cc
oopsjedi/base/WriteParametersBase.h
oopsjedi/base/VariableChangeParametersBase.h
oopsjedi/base/variables_f.cc
oopsjedi/base/variables_f.h
oopsjedi/base/variables_mod.F90
oopsjedi/base/Variables.cc
oopsjedi/base/Variables.h
oopsjedi/base/WeightedDiff.h
oopsjedi/base/WeightedDiffTLAD.h
oopsjedi/base/WeightedMean.h
oopsjedi/base/WeightingFct.h

oopsjedi/contrib/dcmip_initial_conditions_test_1_2_3_v5.f90
oopsjedi/contrib/dcmip_initial_conditions_test_4_v3.f90
oopsjedi/contrib/dcmip_initial_conditions_test_4_v3_interface.f90
oopsjedi/contrib/dcmipInitialConditionsTest_4_v3_Fortran.h

oopsjedi/coupled/AuxCoupledModel.h
oopsjedi/coupled/GeometryCoupled.h
oopsjedi/coupled/GetValuesCoupled.h
oopsjedi/coupled/ModelCoupled.h
oopsjedi/coupled/StateCoupled.h
oopsjedi/coupled/TraitCoupled.h
oopsjedi/coupled/UtilsCoupled.cc
oopsjedi/coupled/UtilsCoupled.h
oopsjedi/coupled/VariableChangeCoupled.h
oopsjedi/coupled/instantiateCoupledFactory.h

oopsjedi/external/stripack/stripack.cc
oopsjedi/external/stripack/stripack.h
oopsjedi/external/stripack/stripack.f90
oopsjedi/external/stripack/stripack_interface.f90

oopsjedi/generic/AnalyticInitBase.h
oopsjedi/generic/AtlasInterpolator.cc
oopsjedi/generic/AtlasInterpolator.h
oopsjedi/generic/fft_gpoint2spectral_f.F90
oopsjedi/generic/fft_init_f.F90
oopsjedi/generic/fft_interface_f.h
oopsjedi/generic/fft_multiple_f.F90
oopsjedi/generic/fft_pass_proc_f.F90
oopsjedi/generic/fft_spectral2gpoint_f.F90
oopsjedi/generic/gc99.h
oopsjedi/generic/gc99.cc
oopsjedi/generic/gc99_mod.F90
oopsjedi/generic/GeoVaLsWriter.h
oopsjedi/generic/GlobalAtlasInterpolator.h
oopsjedi/generic/GlobalInterpolator.h
oopsjedi/generic/HtlmCalculator.h
oopsjedi/generic/HtlmEnsemble.h
oopsjedi/generic/HtlmRegularization.cc
oopsjedi/generic/HtlmRegularization.h
oopsjedi/generic/HybridLinearModel.h
oopsjedi/generic/HybridLinearModelCoeffs.h
oopsjedi/generic/IdentityLinearModel.h
oopsjedi/generic/IdentityModel.h
oopsjedi/generic/instantiateLinearModelFactory.h
oopsjedi/generic/instantiateModelFactory.h
oopsjedi/generic/instantiateObsErrorFactory.h
oopsjedi/generic/LinearModelBase.h
oopsjedi/generic/LocalizationBase.h
oopsjedi/generic/ModelBase.h
oopsjedi/generic/ObsErrorDiag.h
oopsjedi/generic/ObsErrorDiag.cc
oopsjedi/generic/ObsErrorBase.h
oopsjedi/generic/ObsFilterBase.h
oopsjedi/generic/ObsFilterParametersBase.h
oopsjedi/generic/PseudoModel.h
oopsjedi/generic/PseudoModelState4D.h
oopsjedi/generic/soar.h
oopsjedi/generic/soar.cc
oopsjedi/generic/UnstructuredInterpolator.h
oopsjedi/generic/UnstructuredInterpolator.cc
oopsjedi/generic/VerticalLocEV.h
oopsjedi/generic/HybridLinearModel.h

oopsjedi/interface/AnalyticInitBase.h
oopsjedi/interface/ErrorCovariance.h
oopsjedi/interface/Geometry.h
oopsjedi/interface/GeometryIterator.h
oopsjedi/interface/GeoVaLs.h
oopsjedi/interface/Increment.h
oopsjedi/interface/LinearModelBase.h
oopsjedi/interface/LinearObsOperator.h
oopsjedi/interface/LinearVariableChange.h
oopsjedi/interface/LocalInterpolator.h
oopsjedi/interface/LocalizationBase.h
oopsjedi/interface/ModelAuxControl.h
oopsjedi/interface/ModelAuxCovariance.h
oopsjedi/interface/ModelAuxIncrement.h
oopsjedi/interface/ModelBase.h
oopsjedi/interface/NormGradient.h
oopsjedi/interface/ObsAuxControl.h
oopsjedi/interface/ObsAuxCovariance.h
oopsjedi/interface/ObsAuxIncrement.h
oopsjedi/interface/ObsAuxPreconditioner.h
oopsjedi/interface/ObsDataVector.h
oopsjedi/interface/ObsDataVector_head.h
oopsjedi/interface/ObsDiagnostics.h
oopsjedi/interface/ObsErrorBase.h
oopsjedi/interface/ObsFilterBase.h
oopsjedi/interface/ObsOperator.h
oopsjedi/interface/ObsSpace.h
oopsjedi/interface/ObsVector.h
oopsjedi/interface/SampledLocations.h
oopsjedi/interface/State.h
oopsjedi/interface/VariableChange.h

oopsjedi/mpi/mpi.cc
oopsjedi/mpi/mpi.h

oopsjedi/runs/AddIncrement.h
oopsjedi/runs/AdjointForecast.h
oopsjedi/runs/Application.cc
oopsjedi/runs/Application.h
oopsjedi/runs/ConvertIncrement.h
oopsjedi/runs/ConvertState.h
oopsjedi/runs/ConvertToLatLon.h
oopsjedi/runs/DiffStates.h
oopsjedi/runs/EnsembleApplication.h
oopsjedi/runs/EnsRecenter.h
oopsjedi/runs/EnsVariance.h
oopsjedi/runs/ExternalDFI.h
oopsjedi/runs/Forecast.h
oopsjedi/runs/GenEnsPertB.h
oopsjedi/runs/HofX3D.h
oopsjedi/runs/HofX4D.h
oopsjedi/runs/HybridGain.h
oopsjedi/runs/LocalEnsembleDA.h
oopsjedi/runs/RTPP.h
oopsjedi/runs/RTPS.h
oopsjedi/runs/Run.cc
oopsjedi/runs/Run.h
oopsjedi/runs/SqrtOfVertLoc.h
oopsjedi/runs/Test.h
oopsjedi/runs/Variational.h

oopsjedi/util/abor1_cpp.cc
oopsjedi/util/abor1_cpp.h
oopsjedi/util/abor1_ftn.F90
oopsjedi/util/algorithms.h
oopsjedi/util/AnyOf.h
oopsjedi/util/AssociativeContainers.h
oopsjedi/util/CompareNVectors.h
oopsjedi/util/CompositePath.cc
oopsjedi/util/CompositePath.h
oopsjedi/util/ConfigFunctions.cc
oopsjedi/util/ConfigFunctions.h
oopsjedi/util/dateFunctions.cc
oopsjedi/util/dateFunctions.h
oopsjedi/util/datetime_f.cc
oopsjedi/util/datetime_f.h
oopsjedi/util/datetime_mod.F90
oopsjedi/util/PartialDateTime.cc
oopsjedi/util/PartialDateTime.h
oopsjedi/util/DateTime.cc
oopsjedi/util/DateTime.h
oopsjedi/util/datetime.intfb.h
oopsjedi/util/dot_product.h
oopsjedi/util/duration_f.cc
oopsjedi/util/duration_f.h
oopsjedi/util/duration_mod.F90
oopsjedi/util/Duration.cc
oopsjedi/util/Duration.h
oopsjedi/util/duration.intfb.h
oopsjedi/util/Expect.h
oopsjedi/util/FieldSetHelpers.cc
oopsjedi/util/FieldSetHelpers.h
oopsjedi/util/FieldSetOperations.cc
oopsjedi/util/FieldSetOperations.h
oopsjedi/util/FloatCompare.h
oopsjedi/util/formats.h
oopsjedi/util/gatherPrint.h
oopsjedi/util/IntSetParser.cc
oopsjedi/util/IntSetParser.h
oopsjedi/util/IsAnyPointInVolumeInterior.h
oopsjedi/util/IsPointInVolumeInterior.h
oopsjedi/util/kinds.F90
oopsjedi/util/liboops_f.cc
oopsjedi/util/liboops_f.h
oopsjedi/util/liboops_mod.F90
oopsjedi/util/LibOOPS.cc
oopsjedi/util/LibOOPS.h
oopsjedi/util/LocalEnvironment.cc
oopsjedi/util/LocalEnvironment.h
oopsjedi/util/Logger_f.cc
oopsjedi/util/Logger_f.h
oopsjedi/util/Logger.h
oopsjedi/util/logger_mod.F90
oopsjedi/util/missing_values_f.cc
oopsjedi/util/missing_values_f.h
oopsjedi/util/missing_values_mod.F90
oopsjedi/util/missingValues.cc
oopsjedi/util/missingValues.h
oopsjedi/util/NamedEnumerator.h
oopsjedi/util/netcdf_utils_mod.f90
oopsjedi/util/ObjectCounter.h
oopsjedi/util/ObjectCountHelper.cc
oopsjedi/util/ObjectCountHelper.h
oopsjedi/util/Printable.h
oopsjedi/util/PrintAdjTest.h
oopsjedi/util/printRunStats.cc
oopsjedi/util/printRunStats.h
oopsjedi/util/PropertiesOfNVectors.h
oopsjedi/util/random_f.cc
oopsjedi/util/random_f.h
oopsjedi/util/random_mod.F90
oopsjedi/util/Random.h
oopsjedi/util/random.intfb.h
oopsjedi/util/Range.h
oopsjedi/util/ScalarOrMap.h
oopsjedi/util/Serializable.h
oopsjedi/util/signal_trap.cc
oopsjedi/util/sqr.h
oopsjedi/util/string_f_c_interface.cc
oopsjedi/util/string_f_c_interface.h
oopsjedi/util/string_f_c_mod.F90
oopsjedi/util/string_utils.F90
oopsjedi/util/stringFunctions.cc
oopsjedi/util/stringFunctions.h
oopsjedi/util/TestReference.cc
oopsjedi/util/TestReference.h
oopsjedi/util/Timer.cc
oopsjedi/util/Timer.h
oopsjedi/util/TimerHelper.cc
oopsjedi/util/TimerHelper.h
oopsjedi/util/TypeTraits.h
oopsjedi/util/utilNamespaceDoc.h
oopsjedi/util/wildcard.h
oopsjedi/util/wildcard.cc

oopsjedi/util/parameters/ConfigurationParameter.cc
oopsjedi/util/parameters/ConfigurationParameter.h
oopsjedi/util/parameters/EmptyParameters.h
oopsjedi/util/parameters/GenericParameters.h
oopsjedi/util/parameters/HasDiracParameters_.h
oopsjedi/util/parameters/HasParameters_.h
oopsjedi/util/parameters/HasReadParameters_.h
oopsjedi/util/parameters/HasWriteParameters_.h
oopsjedi/util/parameters/IgnoreOtherParameters.cc
oopsjedi/util/parameters/IgnoreOtherParameters.h
oopsjedi/util/parameters/NumericConstraints.h
oopsjedi/util/parameters/ObjectJsonSchema.cc
oopsjedi/util/parameters/ObjectJsonSchema.h
oopsjedi/util/parameters/OptionalParameter.h
oopsjedi/util/parameters/OptionalParameter.cc
oopsjedi/util/parameters/OptionalPolymorphicParameter.h
oopsjedi/util/parameters/Parameter.h
oopsjedi/util/parameters/ParameterBase.cc
oopsjedi/util/parameters/ParameterBase.h
oopsjedi/util/parameters/ParameterConstraint.h
oopsjedi/util/parameters/Parameters.cc
oopsjedi/util/parameters/Parameters.h
oopsjedi/util/parameters/ParametersOrConfiguration.h
oopsjedi/util/parameters/ParameterTraits.cc
oopsjedi/util/parameters/ParameterTraits.h
oopsjedi/util/parameters/ParameterTraitsAnyOf.h
oopsjedi/util/parameters/ParameterTraitsScalarOrMap.h
oopsjedi/util/parameters/PolymorphicParameter.h
oopsjedi/util/parameters/PolymorphicParameterTraits.h
oopsjedi/util/parameters/PropertyJsonSchema.cc
oopsjedi/util/parameters/PropertyJsonSchema.h
oopsjedi/util/parameters/RequiredParameter.h
oopsjedi/util/parameters/RequiredPolymorphicParameter.h
)

list( APPEND oops_test_src_files
test/TestEnvironment.h
test/TestFixture.h

test/assimilation/FullGMRES.h
test/assimilation/rotmat.h
test/assimilation/SolveMatrixEquation.h
test/assimilation/SpectralLMP.h
test/assimilation/TestVector3D.h
test/assimilation/TriDiagSolve.h
test/assimilation/Vector3D.cc
test/assimilation/Vector3D.h

test/base/Fortran.h
test/base/ObsErrorCovariance.h
test/base/ObsLocalizations.h
test/base/variables.F90

test/interface/ErrorCovariance.h
test/interface/Geometry.h
test/interface/GeometryIterator.h
test/interface/GeometryFixture.h
test/interface/GeoVaLs.h
test/interface/GetValues.h
test/interface/GlobalInterpolator.h
test/interface/Increment.h
test/interface/LinearModel.h
test/interface/LinearObsOperator.h
test/interface/LinearVariableChange.h
test/interface/Model.h
test/interface/ModelAuxControl.h
test/interface/ModelAuxCovariance.h
test/interface/ModelAuxIncrement.h
test/interface/ObsAuxControl.h
test/interface/ObsAuxCovariance.h
test/interface/ObsAuxIncrement.h
test/interface/ObsDataVector.h
test/interface/ObsIterator.h
test/interface/ObsLocalization.h
test/interface/ObsOperator.h
test/interface/ObsSpace.h
test/interface/ObsTestsFixture.h
test/interface/ObsVector.h
test/interface/SampledLocations.h
test/interface/State.h
test/interface/UnstructuredInterpolator.h
test/interface/VariableChange.h

test/mpi/mpi.h

test/generic/fft_multiple.h
test/generic/PseudoModelState4D.h
test/generic/VerticalLocEV.h

test/util/Fortran.h
test/util/IsAnyPointInVolumeInterior.h
test/util/Random.h
test/util/random.F90
test/util/FCString.h
test/util/f_c_string.F90
test/util/AssociativeContainers.h
test/util/Parameters.h
test/util/ScalarOrMap.h
test/util/FloatCompare.h
test/util/CompareNVectors.h
test/util/CompositePath.h
test/util/MissingValues.h
test/util/PropertiesOfNVectors.h
test/util/stringFunctions.h
test/util/LocalEnvironment.h
test/util/TestReference.h
test/util/TypeTraits.h
test/util/algorithms.h
test/util/ConfigFunctions.h
)

list (APPEND oops_fheader_files
oopsjedi/util/linkedList_c.f
oopsjedi/util/linkedList_i.f
)

ecbuild_add_library( TARGET     ${PROJECT_NAME}
                     SOURCES    ${oops_src_files}
                     INSTALL_HEADERS LISTED
                     HEADER_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                     LINKER_LANGUAGE CXX )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/oopsjedi/util/linkedList_i.f
               ${CMAKE_CURRENT_SOURCE_DIR}/oopsjedi/util/linkedList_c.f
               DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oopsjedi/util )

target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_14 )
if(OpenMP_FOUND)
    target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_Fortran OpenMP::OpenMP_CXX )
endif()

target_link_libraries( ${PROJECT_NAME} PUBLIC NetCDF::NetCDF_Fortran NetCDF::NetCDF_C ) # For utils/netcdf_utils_mod
target_link_libraries( ${PROJECT_NAME} PUBLIC MPI::MPI_Fortran MPI::MPI_CXX )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${LAPACK_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} PUBLIC Eigen3::Eigen )
target_link_libraries( ${PROJECT_NAME} PUBLIC eckit )
target_link_libraries( ${PROJECT_NAME} PUBLIC fckit )
target_link_libraries( ${PROJECT_NAME} PUBLIC atlas_f )
target_link_libraries( ${PROJECT_NAME} PUBLIC Boost::boost )
if ( GPTL_FOUND )
	target_link_libraries( ${PROJECT_NAME} PUBLIC GPTL::GPTL )
endif()
target_link_libraries( ${PROJECT_NAME} PUBLIC oops )

# Stack traces on floating point exceptions
include( backtrace_deps )

target_link_libraries( ${PROJECT_NAME} PUBLIC ${OOPS_STACKTRACE_${OOPS_STACKTRACE_PROVIDER}_LIBS} )
target_compile_definitions( ${PROJECT_NAME} PRIVATE ${OOPS_STACKTRACE_${OOPS_STACKTRACE_PROVIDER}_DEFS} )

target_include_directories(${PROJECT_NAME} INTERFACE
                                $<BUILD_INTERFACE:${OOPS_BUILD_DIR_INCLUDE_PATH}>
                                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

#Fortran module output directory for build and install interfaces
set(MODULE_DIR module/${PROJECT_NAME}/${CMAKE_Fortran_COMPILER_ID}/${CMAKE_Fortran_COMPILER_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/${MODULE_DIR})
install(DIRECTORY ${CMAKE_BINARY_DIR}/${MODULE_DIR}/ DESTINATION ${MODULE_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE
                                $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${MODULE_DIR}>
                                $<INSTALL_INTERFACE:${MODULE_DIR}>)

if (${nlohmann_json_FOUND} AND ${nlohmann_json_schema_validator_FOUND})
  message(STATUS "[OOPS] JSON Schema Validator activated.")
  target_link_libraries( ${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json_schema_validator )
  target_compile_definitions( ${PROJECT_NAME} PRIVATE OOPS_HAVE_NLOHMANN_JSON_SCHEMA_VALIDATOR )
endif()

## Tests

ecbuild_add_test( TARGET ${PROJECT_NAME}_coding_norms
                  TYPE SCRIPT
                  COMMAND ${CMAKE_BINARY_DIR}/bin/oopsjedi_cpplint.py
                  ARGS --quiet --recursive ${CMAKE_CURRENT_SOURCE_DIR} )
