#!/bin/bash

if [ -z $1 ]; then
  echo "Usage: test.sh <script>"
  echo "    example: test.sh sites/all/modules/ecolex/elis_consumer/tests/CourtDecisions.php"
  exit -1;
fi

drush -v scr $1
