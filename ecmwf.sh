#!/usr/bin/env bash

# Update or clone OOPS-JEDI repo
if test -d $1/oops-jcsda; then
  cd $1/oops-jcsda
  git checkout develop
  git pull
else
  git clone https://github.com/jcsda/oops $1/oops-jcsda
fi

# Copy cmake
if test ! -d $1/cmake; then
  cp -fr $1/oops-jcsda/cmake $1
fi

# Copy cmake
if test ! -d $1/tools; then
  cp -fr $1/oops-jcsda/tools $1
fi

# Copy src and rename src_tmp/oops into src_tmp/oopsjedi
rm -fr $1/src_tmp
cp -fr $1/oops-jcsda/src $1/src_tmp
mv $1/src_tmp/oops $1/src_tmp/oopsjedi

# Update src_tmp/CMakeLists.txt
sed -i -e s:"oops/":"oopsjedi/":g $1/src_tmp/CMakeLists.txt
sed -i -e s:"/oops":"/oopsjedi":g $1/src_tmp/CMakeLists.txt
sed -i -e s:"oopsjedijedi":"oopsjedi/":g $1/src_tmp/CMakeLists.txt

# Copy src_tmp into src
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

# Link extension files
for file in `find $1/extension -name *.h -o -name *.cc -o -name *.F90 -name *.txt`; do
  ln -sf ${file} ${file/extension/src_tmp}
done

# Copy modified files
for file in `find $1/src_tmp -name *.h -o -name *.cc -o -name *.F90`; do
  if ! cmp -s "${file}" "${file/src_tmp/src}"; then
    echo -e " - File "${file}" is different from "${file/src_tmp/src}
    cp -f ${file} ${file/src_tmp/src}
  fi
done

# Cleaning
rm -fr $1/src_tmp
