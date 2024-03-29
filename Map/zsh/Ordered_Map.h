#!/bin/zsh

# declare an associative array
declare -A Properties

# Initial Values for Orders and Current Index
declare -A Index_Key
declare -A Key_Index

# Current Index of Array
Current_Index=0
Indices=()

# read file line by line and populate the array. Field separator is "="

Map()
{
	. <(sed "s/Object/$1/g" Ordered_Map.h)
}

Object.put()
{
	#echo Current_Index ${Current_Index}

	Properties[${1}]="$2"
	Index_Key[${Current_Index}]="${1}"
	Key_Index[${1}]="${Current_Index}"
	Indices+=(${Current_Index})
	Current_Index=$((Current_Index+1)) 
}

Object.get()
{
	eval echo '${'"Properties[$1]"'#hash}'
}

Object.getByIndex()
{
        key=`eval echo '${'"Index_Key[$1]"'#hash}'`
	if [ ! -z ${key} ]
	then
		eval echo '${'"Properties[$key]"'#hash}'
	fi
}

Object.remove()
{
	Index=`eval echo '${'"Key_Index[$1]"'#hash}'`
	#echo Index $Index
	unset "Properties[${1}]"
	unset "Key_Index[${1}]"
	unset "Index_Key[${Index}]"
	Indices[${Index}]=()
}

Object.display()
{
	#echo Current_Index ${Current_Index}

	for index in ${Indices}
	do
		#echo index ${index}
	
		key=`eval echo '${'"Index_Key[${index}]"'#hash}'`
		if [ ! -z ${key} ]
		then
			value=`eval echo '${'"Properties[${key}]"'#hash}'`
                	echo "$key -> $value"
		fi
	done
}

Object.keys()
{
	#echo Current_Index ${Current_Index}
	
	for index in ${Indices}
        do
#                echo index ${index}

                key=`eval echo '${'"Index_Key[${index}]"'#hash}'`
                if [ ! -z ${key} ]
                then
                        echo ${index}"." "$key"
                fi
        done
}

Object.clear()
{
	#echo Current_Index ${Current_Index}

	for index key in "${(@kv)Index_Key}"
	do
	#	echo Removing ${key}
		unset "Index_Key[${(b)index}]"
		unset "Key_Index[${(b)key}]"
		unset "Properties[${(b)key}]"
	done
	Indices=()
	Current_Index=0
}

Object.populate()
{
	#echo Current_Index ${Current_Index}

	while IFS='=' read -r key value; do
#		echo Current_Index ${Current_Index}
		Properties[${key}]="$value"
		Index_Key[${Current_Index}]="${key}"
        	Key_Index[${key}]="${Current_Index}"
		Indices+=(${Current_Index})
		Current_Index=$((Current_Index+1))
	done < "$1"

	#echo Current_Index ${Current_Index}
}
