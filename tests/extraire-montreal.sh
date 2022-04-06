#!/bin/sh

osmosis --read-pbf quebec-latest.osm.pbf --bounding-polygon file="montreal.polygone" --write-xml montreal.osm 
