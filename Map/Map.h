#!/bin/bash

# declare an associative array
declare -A properties

size=0

# Script Name
MY_NAME=$BASH_SOURCE

Map()
{
	directory=`dirname $MY_NAME`
	MapFile=$directory"/."$1_Map.h
		#echo $MapFile
	sed "s/Object/$1/g" $MY_NAME > $MapFile
	. $MapFile
}

Object.put()
{
	#echo PUT "$1" "$2"

	contains=`Object.contains $1`
	
	if [ $contains == "false" ]
	then
		size=$((size+1))
	fi
			
	eval properties['"$1"']='"$2"'
}

Object.get()
{
	eval echo '${'"properties[$1]"'#hash}' 2> /dev/null
}

Object.remove()
{
	contains=`Object.contains $1`

    if [ $contains == "true" ]
	then
		size=$((size-1))
	fi

	unset properties["$1"]
}

Object.display()
{
	for key in "${!properties[@]}"
	do
		echo -e "$key"="${properties[$key]}"
	done
}

Object.clear()
{
	for key in "${!properties[@]}"
	do
		Object.remove "$key"
	done
}

Object.populate()
{
	while IFS='=' read -r key value; do
	Object.put "$key" "$value"		
	done < "$1"
}

Object.contains()
{
	value=`Object.get "$1"`
	if [ "M""$value" == "M" ]
	then
		#echo "Doesn't Contain" $1
		echo "false"
	else
		echo "true"
		#echo Contains Key $1
	fi
}

Object.size()
{
	echo $size
}

Object.values()
{
	for key in "${!properties[@]}"
	do
		echo $key "${properties[$key]}"
#echo "${properties[$key]}"
	done
}
