#!/bin/sh

mvn clean install -DskipTests -f apache-log4j-2.3-src/pom.xml -Dadditionalparam=-Xdoclint:none



