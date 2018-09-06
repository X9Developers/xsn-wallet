#!/bin/bash

MODULES_DIR=$1
OUTPUT_DIR=$PWD/output
BOOST_DIR=$MODULES_DIR/boost
LIBBITCOIN_DIR=$MODULES_DIR/libbitcoin

./install.sh --prefix=$OUTPUT_DIR --build-boost --disable-shared

if [ $? -ne 0 ]; then
    echo "Failed to install libbitcoin"
    exit
fi

make_symbolink() {
	filter=$1
	from=$2
	to=$3
	find $from -iname $filter -printf "%f\n" | while read filename;
	do
		ln -s $from/$filename $to/$filename
	done
}

mkdir $BOOST_DIR/include
mkdir $BOOST_DIR/lib
ln -s $OUTPUT_DIR/include/boost $BOOST_DIR/include/boost
make_symbolink "libboost_*.a" $OUTPUT_DIR/lib $BOOST_DIR/lib



mkdir $LIBBITCOIN_DIR/include
mkdir $LIBBITCOIN_DIR/lib
ln -s $OUTPUT_DIR/include/bitcoin $LIBBITCOIN_DIR/include/bitcoin
make_symbolink "secp256k1*.h" $OUTPUT_DIR/include $LIBBITCOIN_DIR/include
make_symbolink "libbitcoin.*a" $OUTPUT_DIR/lib $LIBBITCOIN_DIR/lib
make_symbolink "libsecp256k1.*a" $OUTPUT_DIR/lib $LIBBITCOIN_DIR/lib
