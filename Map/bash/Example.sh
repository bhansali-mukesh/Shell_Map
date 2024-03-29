#!/bin/bash

# include class header
. Map.h

echo

# Create Map Object
Map map

echo "Populating Map via Property File"
map.populate Hamari.properties

echo
echo Iterating through Map
echo
map.display

echo
echo Clearing Map
map.clear

echo
echo Iterating through Map after Clearing
echo
map.display

echo
echo Putting Some Values in Map
map.put Rajasthan Jodhpur
map.put Polar Bear
map.put Rajasthan Jaipur

echo
echo Getting Values From Map
echo Rajasthan = `map.get Rajasthan`
echo Polar = `map.get Polar`

echo
echo Removing Key Rajasthan
map.remove Rajasthan

echo
echo Iterating Map
echo
map.display

echo
