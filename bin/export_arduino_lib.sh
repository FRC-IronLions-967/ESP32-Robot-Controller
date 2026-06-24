#!/bin/bash

mkdir -p ./tmp/ESP32-Robot-Controller/src
mkdir -p ./tmp/ESP32-Robot-Controller/examples

cp ./library.properties ./tmp/ESP32-Robot-Controller

pushd ./tmp

cp ../include/* ./ESP32-Robot-Controller/src

cp ../src/* ./ESP32-Robot-Controller/src

cp -r ../examples/ESP32S3TankDrive ./ESP32-Robot-Controller/examples
cp -r ../examples/ESP32S3StarterCode ./ESP32-Robot-Controller/examples
cp -r ../examples/ESP32S3FullCode ./ESP32-Robot-Controller/examples

zip -r ESP32-Robot-Controller.zip ./ESP32-Robot-Controller

mv ESP32-Robot-Controller.zip ../

popd

rm -rf ./tmp