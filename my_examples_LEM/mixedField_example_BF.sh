
#source ./setenv.sh

binNum=$1

output="LQ_pars"

model="LEMIII"
calculusType="rapidLEM_Russo2011"

precision=0.015
parallelismType=0

#set doses="1 2 3 4 5 6"

cellType="HSG"
LEM_alpha0=0.312
LEM_beta0=0.073
LEM_rNucleus=4.611
LEM_Dt=30.

#set ion="C"

#set lets="0.25 0.5 0.75 1 1.3 1.6 1.9 2.2 2.5 3 3.5 4 4.5 5 5.5 6 7 8 9 10.5 12 14 17 20 25 30 35 40 45 50 55 60 65 70 75 80 84.3"
#set energies="12 24 36 48 60 120 240 360 480 600 1200 2400 3600 4800"

spectrumFile="ParticleFieldBF"

projectName="${cellType}_${model}"

projectName="${spectrumFile}_${projectName}"
runOptions="-spectrum_file ${spectrumFile}${binNum}.mixedField"

trackMode="histogram"

#set lets="0.25 0.5 0.75 1 1.3 1.6 1.9 2.2 2.5 3 3.5 4 4.5 5 5.5 6 7 8 9 10.5 12 14 17 20 25 30 35 40 45 50 55 60 65 70 75 80 84.3"
#set energies="12 24 36 48 60 120 240 360 480 600 1200 2400 3600 4800"
echo "Run Option : "${runOptions}

../survival	-projectName $projectName \
		-output $output \
		-model $model \
		-calculusType $calculusType \
		-precision $precision \
		-parallelismType $parallelismType \
		-cellType $cellType \
		-LEM_alpha0 $LEM_alpha0 \
		-LEM_beta0 $LEM_beta0 \
		-LEM_rNucleus $LEM_rNucleus \
		-LEM_Dt $LEM_Dt \
		-trackMode $trackMode \
		${runOptions}
		#-doses $doses \
