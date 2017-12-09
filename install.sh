#!/bin/bash

# Place here the Path of Qemu Dir
export QEMU_SRC_DIR=


if [ -z "${QEMU_SRC_DIR}" ]; then
   echo "You should edit the install.sh to set the QEMU_SRC_DIR variable"
   exit
fi

# Copy main files into Qemu Dir
cp -R rabbits ${QEMU_SRC_DIR}

# Run the annotate-qemu script to insert the annotation
./annotate-qemu ${QEMU_SRC_DIR}

# Update some makefiles !
cd ${QEMU_SRC_DIR}
echo "common-obj-y += rabbits/" >> Makefile.objs
echo "obj-y += rabbits/" >> Makefile.objs

RES=$(grep  -n Makefile.target -e "obj-y =" | head -n 1)
NUM_LINE=$(echo ${RES} | cut -d ":" -f1)
NUM_LINE=`expr "${NUM_LINE}" + 1`

sed -i "${NUM_LINE}i\obj-y += rabbits/" Makefile.target



# Configure Qemu
# This is the minimal configuration needed
# So feel free to update this with what you want !
#  the --disable-werror is mandatory !
#  Don't specify more targets or you will get errors
cd ${QEMU_SRC_DIR}
mkdir BUILD
cd BUILD
../configure --target-list="arm-softmmu mips-softmmu" --disable-werror


# we are done, we can run Make !
