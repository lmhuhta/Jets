# Jets
Running the code is easy:

First add all own paths into setup.sh file

Then run the following:

source setup.sh

make clean

make 

./jetreco pythia_config_ATLAS.cmnd_pthard5 3 -1 TESTING.root 1


Change the parameters of the ./jetreco-line according to "pythia.config pTHatMin pTHatMax <output.root> [random_seed]"

(pthatmax=-1 means no upper limit)
