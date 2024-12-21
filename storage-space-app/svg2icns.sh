#!/bin/bash

# Convert 1024x1024 svg icon to png
sips -s format png -o app-icon.png app-icon.svg

# Make iconset by scaling down png to a complete set of sizes
mkdir storagespace.iconset
sips -z 16 16     app-icon.png --out storagespace.iconset/icon_16x16.png
sips -z 32 32     app-icon.png --out storagespace.iconset/icon_16x16@2x.png
sips -z 32 32     app-icon.png --out storagespace.iconset/icon_32x32.png
sips -z 64 64     app-icon.png --out storagespace.iconset/icon_32x32@2x.png
sips -z 128 128   app-icon.png --out storagespace.iconset/icon_128x128.png
sips -z 256 256   app-icon.png --out storagespace.iconset/icon_128x128@2x.png
sips -z 256 256   app-icon.png --out storagespace.iconset/icon_256x256.png
sips -z 512 512   app-icon.png --out storagespace.iconset/icon_256x256@2x.png
sips -z 512 512   app-icon.png --out storagespace.iconset/icon_512x512.png
cp app-icon.png storagespace.iconset/icon_512x512@2x.png
iconutil -c icns storagespace.iconset
mv storagespace.icns images/storagespace.icns
rm -R storagespace.iconset app-icon.png
