#!/bin/bash

##########################################
#
# Simple C++ class creation
# Creates hpp and cpp files
#
##########################################


echo 'Create new class'
echo '---------------------------'
echo 'Type class name: '
read class
# convert Upper Camel case to header guard, ex: NewClass -> NEW_CLASS_H_
guard=`echo $class | sed -e 's/\([A-Z]\)/_\1/g' | awk '{printf toupper($0)} END{printf "_H_";}'`

# first character in class name to lower case
# comment out line below if a filename equal to the
# class name is prefered
filename="$(tr '[:upper:]' '[:lower:]' <<< ${class:0:1})${class:1}"

if [ -e include/$filename.hpp -o -e src/$filename.cpp ]; then
    echo "Class $class already exists."
    echo 'Do you want to overwrite it? [y/n]: '
    read answer
    if [ "$answer" == "n" ]; then
	exit
    fi
fi

#Write to hpp file
echo "#ifndef $guard" > include/$filename.hpp
echo "#define $guard" >> include/$filename.hpp
echo "" >> include/$filename.hpp
echo "class $class {" >> include/$filename.hpp
echo "public:" >> include/$filename.hpp
echo "$class();" >> include/$filename.hpp
echo "virtual ~$class();" >> include/$filename.hpp
echo "" >> include/$filename.hpp
echo "private:" >> include/$filename.hpp
echo "" >> include/$filename.hpp
echo "};" >> include/$filename.hpp
echo "" >> include/$filename.hpp
echo "#endif // $guard" >> include/$filename.hpp

#Write to cpp file
echo "#include \"$filename.hpp\"" > src/$filename.cpp
echo "" >> src/$filename.cpp
echo "$class::$class(){" >> src/$filename.cpp
echo "}" >> src/$filename.cpp
echo "" >> src/$filename.cpp
echo "$class::~$class(){" >> src/$filename.cpp
echo "}" >> src/$filename.cpp
