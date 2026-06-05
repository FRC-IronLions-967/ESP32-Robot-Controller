#!/bin/bash

mkdir -p ./tmp/ESP32-Robot-Controller/src

cp ./library.properties ./tmp/ESP32-Robot-Controller

pushd ./tmp

cp ../include/* ./ESP32-Robot-Controller/src

cp ../src/* ./ESP32-Robot-Controller/src

zip -r ESP32-Robot-Controller.zip ./ESP32-Robot-Controller

mv ESP32-Robot-Controller.zip ../

popd

rm -rf ./tmp