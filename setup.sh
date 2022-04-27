# need to have correct $ROOTSYS, $FASTJET and $PYTHIA8 are needed in Makefile
# In case you have installed all from Aliroot installation including fastjet packages based on https://dberzano.github.io/alice/install-aliroot/
# no need to setup $ROOTSYS, $FASTJET need to have only $PYTHIA8
#source ~/software/root_install/bin/thisroot.sh
#export ROOTSYS=$HOME/.sw/slc7_x86-64/ROOT/latest-aliroot6-user-next-root6
#export ROOTSYS=$HOME/.sw/slc7_x86-64/AliPhysics/aliroot6-local1
#source ~/.sw/slc7_x86-64/ROOT/latest-aliroot6-user-next-root6/bin/thisroot.sh

export PYTHIA8=$HOME/software/pythia8306
export PATH=${PATH}:$PYTHIA8/bin
export FASTJET=$HOME/software/fastjet-install
export PATH=$PATH:${FASTJET}/bin
#export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:$PYTHIA8/lib:$FASTJET/lib:$ROOTSYS/lib


