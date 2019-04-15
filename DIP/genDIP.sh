#!/bin/sh

cat << EOF
#ifndef _DIP_DIP_hpp_
#define _DIP_DIP_hpp_

#include <DIP/DefConfig.hpp>
#include <DIP/Config.hpp>

EOF

find | grep \.hpp$ | egrep -v '^\./(DIP|DefConfig|Config)\.hpp$' | sort | sed 's/^\./#include <DIP/;s/$/>/;'

cat << EOF

#undef EIGEN_DEFAULT_DENSE_INDEX_TYPE

#endif
EOF
