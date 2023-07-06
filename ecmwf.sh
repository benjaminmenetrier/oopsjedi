#!/usr/bin/env bash

if [ -z ${OOPSJEDI_NO_UPDATE+x} ]; then
  # Remember path
  PWD_INIT=${PWD}

  # Update or clone OOPS-JEDI repo (TODO: should be develop when modifs are merged)
  GIT_BRANCH=feature/saber_for_ecmwf+task_with_no_point
  echo -e "-- Clone OOPS-JEDI repository, branch ${GIT_BRANCH}"
  if test -d $1/oops-jcsda; then
    cd $1/oops-jcsda
    git checkout ${GIT_BRANCH}
    git pull
    cd ${PWD_INIT}
  else
    git clone https://github.com/jcsda-internal/oops $1/oops-jcsda
    cd $1/oops-jcsda
    git checkout ${GIT_BRANCH}
    git pull
    cd ${PWD_INIT}
  fi

  # Copy cmake
  if test ! -d $1/cmake; then
    cp -fr $1/oops-jcsda/cmake $1
  fi

  # Copy tools
  if test ! -d $1/tools; then
    cp -fr $1/oops-jcsda/tools $1
  fi

  # Copy src and rename src_tmp/oops into src_tmp/oopsjedi
  rm -fr $1/src_tmp
  mkdir -p $1/src_tmp
  cp -fr $1/oops-jcsda/src/oops $1/src_tmp/oopsjedi
  cp -f $1/oops-jcsda/src/CMakeLists.txt $1/src_tmp/CMakeLists.txt
  cp -f $1/oops-jcsda/src/CPPLINT.cfg $1/src_tmp/CPPLINT.cfg

  # Copy src_tmp/oopsjedi into src/oopsjedi to get the correct tree
  if test ! -d $1/src; then
    cp -fr $1/src_tmp $1/src
  fi

  echo -e "-- Process OOPS-JEDI source files (might take some time...)"

  # Loop over source files
  for file in `find $1/src_tmp -name *.h -o -name *.cc -o -name *.F90`; do
    # Change namespaces
    sed -i -e s/"namespace oops"/"namespace oopsjedi"/g \
           -e s/"namespace util"/"namespace utiljedi"/g \
           -e s/"oops::"/"oopsjedi::"/g \
           -e s/"util::"/"utiljedi::"/g \
           -e s:"oops/":"oopsjedi/":g \
           -e s:"OOPS_":"OOPSJEDI_":g \
           ${file}

    # Reset some unwanted changes
    sed -i -e s/"atlas::utiljedi::"/"atlas::util::"/g \
           -e s:"OOPSJEDI_ABSTRACT_PARAMETERS":"OOPS_ABSTRACT_PARAMETERS":g \
           -e s:"OOPSJEDI_CONCRETE_PARAMETERS":"OOPS_CONCRETE_PARAMETERS":g \
           -e s:"LIBOOPSJEDI":"LIBOOPS":g \
           ${file}
  done

  # Deal with C++/Fortran interfaces
  cf_list=()
  for file in `find $1/src_tmp/oopsjedi -name *.f -o -name *.intfb.h`;do
    for sub in `grep -s "end subroutine c_" ${file} | awk '{print $3}' | cut -c 3-`;do
      cf_list+=("${sub}")
    done
    for func in `grep -s "end function c_" ${file} | awk '{print $3}' | cut -c 3-`;do
      cf_list+=("${func}")
    done
  done
  for file in `find $1/src_tmp/oopsjedi -type f`;do
    for item in "${cf_list[@]}"; do
       sed -i -e s/"c_"${item}/"cjedi_"${item}/g -e s/${item}"_f"/${item}"_fjedi"/g ${file}
    done
  done
  rm -f $1/cf_list.txt
  for item in "${cf_list[@]}"; do
     echo ${item} >> $1/cf_list.txt
  done

  # Deal with modules
  mod_list=()
  for file in `find $1/src_tmp/oopsjedi -name *.F90`;do
    for mod in `grep -s "end module" ${file} | awk '{print $3}'`;do
      mod_list+=("${mod}")
    done
  done
  for file in `find $1/src_tmp/oopsjedi -type f`;do
    for item in "${mod_list[@]}"; do
       sed -i -e s/"module "${item}/"module jedi_"${item}/gi -e s/"use "${item}/"use jedi_"${item}/gi ${file}
    done
  done
  rm -f $1/mod_list.txt
  for item in "${mod_list[@]}"; do
     echo ${item} >> $1/mod_list.txt
  done

  # Copy modified files
  echo -e "-- Copy modified files (different from their src counterpart)"
  for file in `find $1/src_tmp -name *.h -o -name *.cc -o -name *.f -o -name *.F90`; do
    if ! cmp -s "${file}" "${file/src_tmp/src}"; then
      echo -e "--  + "${file}
      rm -f ${file/src_tmp/src}
      cp -f ${file} ${file/src_tmp/src}
    fi
  done

  # Link extension files
  echo -e "-- Link extension files"
  rm -f $1/diff.txt
  for file in `find $1/extension -name *.h -o -name *.cc -o -name *.F90` "$1/extension/CMakeLists.txt"; do
    echo -e "--  + "${file}
    diff ${file} ${file/extension/src_tmp} >> $1/diff.txt
    ln -sf ${file} ${file/extension/src}
  done
  echo -e "-- Diff available in: $1/diff.txt"

  # Cleaning
  rm -fr $1/src_tmp
else
  echo -e "-- OOPS-JEDI source files not processed (OOPSJEDI_NO_UPDATE is set)"
fi
