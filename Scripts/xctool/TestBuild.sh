#!/bin/sh
SCHEME=FactoryEngine
PROJECT=FactoryEngine.xcodeproj
CONFIG=Debug
SDK=macosx10.9

xctool \
-project $PROJECT \
-scheme $SCHEME \
-configuration $CONFIG \
-sdk $SDK \
-reporter junit:test-results.xml \
-reporter plain \
test


