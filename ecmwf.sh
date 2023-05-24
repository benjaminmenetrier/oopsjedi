#!/usr/bin/env bash

# Remember path
PWD_INIT=${PWD}

# Update or clone OOPS-JEDI repo
GIT_BRANCH=feature/use_oops_ecmwf
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

# Copy src_tmp/oopsjedi into src/oopsjedi to get the correct tree
if test ! -d $1/src; then 
  cp -fr $1/src_tmp $1/src
fi

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
         -e s:"OOPSJEDI_ABSTRACT":"OOPS_ABSTRACT":g \
         -e s:"OOPSJEDI_CONCRETE":"OOPS_CONCRETE":g \
         -e s:"OOPSJEDI_UTIL":"OOPS_UTIL":g \
         ${file}
done

# Copy modified files
echo -e "-- Copy modified files (different from their src counterpart)"
for file in `find $1/src_tmp -name *.h -o -name *.cc -o -name *.F90`; do
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
  diff --color ${file} ${file/extension/src_tmp} >> $1/diff.txt
  ln -sf ${file} ${file/extension/src}
done
echo -e "-- Diff available in: $1/diff.txt"

# Cleaning
rm -fr $1/src_tmp
