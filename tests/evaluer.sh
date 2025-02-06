#!/bin/bash
# INF3105 - Structures de données et algorithmes
# 2024E / TP4
# http://cria2.uqam.ca/INF3105/tp4/
#
# Script d'auto-évaluation.
# Ce script doit être lancé depuis le répertoire contenant le fichier exécutable tp4.
# Ce script et les fichiers test doivent être dans un répertoire différent du programme tp4 à évaluer.

echo "Évaluation du TP4 d'INF3105..."

# Obtenir le répertoire contenant les tests.
repertoire_tests=`dirname $0`
# Énumerer les fichiers test.
tests=`cd $repertoire_tests && ls test[0-9][0-9].txt`

if [ `pwd` -ef $repertoire_tests ];
then
    echo "Ce script doit être dans un répertoire différent de celui contenant votre programme tp4."
    echo "Ce script a été arrêté afin de ne pas écraser les fichiers de résultat."
    exit -2;
fi

# Programme à tester
programme="tp4"
# Vérifier la présence du programme tp4.
if [ ! -e ${programme} ]
	then
	echo "Erreur : le fichier ${programme} est inexistant!"
	exit -1
fi

if [ ! -x ${programme} ]
	then
	echo "Erreur : le fichier ${programme} n'est pas exécutable!"
	exit -1
fi

# Détection du valideur.
valideur="${repertoire_tests}/valideur"
if [ -x ${valideur}-`uname` ]
then
  valideur=${valideur}-`uname`
fi

if [ ! -x ${valideur} ]
then
   echo "Avertissement : le valideur n'est pas disponible. Il sera donc impossible de vérifier les résultats."
fi

# Détection pour /usr/bin/time sous Linux?
/usr/bin/time -f %U echo 2>&1 > /dev/null
souslinux=$?

# Limiter le temps d'exécution à 240 secondes, 2Go de mémoire et 512Mo d'écriture sur disque
# Cette limite est par processus lancé.
ulimit -t 240 -v 2097152 -f 524288
echo "Limite de `ulimit -t` secondes par test."

# Détection du CPU
if [ -e /proc/cpuinfo ] ; then
    cpuinfo=`grep "model name" /proc/cpuinfo | sort -u | cut -d ":" -f 2`
else
    cpuinfo="?"
fi

# Date du test
date=`date +%Y%m%d_%H%M%S`
logfile="log-${date}.txt"

echo "Évaluation des temps d'exécution de ${programme} sur les jeux de tests."
echo "Les résultats sont déposés dans $logfile."


echo "Machine : " `hostname` "."
echo "#Machine : " `hostname` "."  > $logfile
echo "CPU :$cpuinfo"
echo "#CPU :$cpuinfo"  >> $logfile
echo "Date début : $date."
echo "#Date début : $date."  >> $logfile
echo "Limite de `ulimit -t` secondes par test."
echo "#Limite de `ulimit -t` secondes par test."  >> $logfile
echo
echo "#" >> $logfile

if [ $souslinux -eq 0 ]; then
  echo -e "Fichier test\tTotal\tMém.(k)\tTrace\tLocal\tPrés\tFreq\tDR\tTrace\tLocal\tPrés\tFreq\tDR"
  echo -e "Fichier test\tTotal\tMém.(k)\tTrace\tLocal\tPrés\tFreq\tDR\tTrace\tLocal\tPrés\tFreq\tDR" >> $logfile
else
  echo -e "Fichier test\tTotal\tTrace\tLocal\tPrés\tFreq\tDR\tTrace\tLocal\tPrés\tFreq\tDR"
  echo -e "Fichier test\tTotal\tTrace\tLocal\tPrés\tFreq\tDR\tTrace\tLocal\tPrés\tFreq\tDR" >> $logfile
fi

for test in $tests;
do
  fichier=$repertoire_tests/$test

  if [ $souslinux -eq 0 ]; then
   tG="`                                               (/usr/bin/time -f "%U\t%Mk" ./tp4 < $fichier > ${test%.txt}+.txt) 2>&1 | tail -n 1`"
   tTrace=`egrep "^trace"                   $fichier | (/usr/bin/time -f "%U" ./tp4 > /dev/null) 2>&1 | tail -n 1`
   tLocal=`egrep "^trace|^localiser"        $fichier | (/usr/bin/time -f "%U" ./tp4 > /dev/null) 2>&1 | tail -n 1`
   tPres=` egrep "^trace|^presences"        $fichier | (/usr/bin/time -f "%U" ./tp4 > /dev/null) 2>&1 | tail -n 1`
   tFreq=` egrep "^trace|^frequentations"   $fichier | (/usr/bin/time -f "%U" ./tp4 > /dev/null) 2>&1 | tail -n 1`
   tDR=`   egrep "^trace|^duree_rencontres" $fichier | (/usr/bin/time -f "%U" ./tp4 > /dev/null) 2>&1 | tail -n 1`
  else
   tG=`                                                (time -p ./tp4 < $fichier > ${test%.txt}+.txt) 2>&1 | egrep user | cut -f 2 -d " "`
   tTrace=`egrep "^trace"                   $fichier | (time -p ./tp4 > /dev/null) 2>&1 | egrep user | cut -f 2 -d " "`
   tLocal=`egrep "^trace|^localiser"        $fichier | (time -p ./tp4 > /dev/null) 2>&1 | egrep user | cut -f 2 -d " "`
   tPres=` egrep "^trace|^presences"        $fichier | (time -p ./tp4 > /dev/null) 2>&1 | egrep user | cut -f 2 -d " "`
   tFreq=` egrep "^trace|^frequentations"   $fichier | (time -p ./tp4 > /dev/null) 2>&1 | egrep user | cut -f 2 -d " "`
   tDR=`   egrep "^trace|^duree_rencontres" $fichier | (time -p ./tp4 > /dev/null) 2>&1 | egrep user | cut -f 2 -d " "`
  fi

  if ( [ -x ${valideur} ] && [ -e "${fichier%.txt}+.txt" ] )
  then
	 verif=`$valideur -q $fichier "${fichier%.txt}+.txt" ${test%.txt}+.txt`
  else
     verif=""
  fi

  echo -e "$test\t$tG\t$tTrace\t$tLocal\t$tPres\t$tFreq\t$tDR\t$verif"
  echo -e "$test\t$tG\t$tTrace\t$tLocal\t$tPres\t$tFreq\t$tDR\t$verif" >> $logfile

done
