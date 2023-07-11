#! /bin/sh
# $Id: MKkeys_list.sh,v 1.1.2.1 2012/10/05 16:14:21 arnabd Exp $
##############################################################################
# Copyright (c) 2001,2003 Free Software Foundation, Inc.                     #
#                                                                            #
# Permission is hereby granted, free of charge, to any person obtaining a    #
# copy of this software and associated documentation files (the "Software"), #
# to deal in the Software without restriction, including without limitation  #
# the rights to use, copy, modify, merge, publish, distribute, distribute    #
# with modifications, sublicense, and/or sell copies of the Software, and to #
# permit persons to whom the Software is furnished to do so, subject to the  #
# following conditions:                                                      #
#                                                                            #
# The above copyright notice and this permission notice shall be included in #
# all copies or substantial portions of the Software.                        #
#                                                                            #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    #
# THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    #
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        #
# DEALINGS IN THE SOFTWARE.                                                  #
#                                                                            #
# Except as contained in this notice, the name(s) of the above copyright     #
# holders shall not be used in advertising or otherwise to promote the sale, #
# use or other dealings in this Software without prior written               #
# authorization.                                                             #
##############################################################################
#
# MKkey_defs.sh -- generate list of function-keys for terminfo database
#
# Author: Thomas E. Dickey 2001
#
# Extract function-key names from the Caps file
#
: ${AWK-awk}
DATA=${1-../../include/Caps}

data=data$$
trap 'rm -f $data' 0 1 2 5 15
sed -e 's/[	][	]*/	/g' < $DATA >$data

cat <<EOF
# These definitions were generated by $0 $DATA
KEY_BREAK
KEY_SRESET
KEY_RESET
KEY_RESIZE
EOF

${AWK-awk} <$data '
/^#/		{next;}
/^capalias/	{next;}
/^infoalias/	{next;}

$5 != "-" {
		if (substr($5, 1, 4) == "KEY_" ) {
			printf "%s	%s\n", $5, $1
	}
}
'
