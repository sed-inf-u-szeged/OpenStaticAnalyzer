#!/bin/sh

ant -f apache-log4j-1.2.17/build.xml clean jar -Djavac.source=1.7 -Djavac.target=1.7
