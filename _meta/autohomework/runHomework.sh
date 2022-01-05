#!/bin/bash

homeworkCheckersPath=/var/www/html/ap-homework/checkers/
rezultsPath=/var/www/html/ap-homework/rezults/

homeworkType=$(echo $2 | cut -d'#' -f1)
homeworkIdentifier=$(echo $2 | cut -d'#' -f2)
userName=$(echo $2 | cut -d'#' -f2 | cut -d'@' -f1)
timeStamp=$(echo $2 | cut -d'#' -f2 | cut -d'@' -f2)
machine=$(echo $3 | cut -f 1 -d "-")
port=$(echo $3 | cut -f 2 -d "-")
keyFile=student.pem

mkdir $rezultsPath$homeworkType &> /dev/null
mkdir $rezultsPath$homeworkType/$userName &> /dev/null
mkdir $rezultsPath$homeworkType/$userName/$timeStamp &> /dev/null

#upload homework
echo "Your archive contains" > $rezultsPath$homeworkType/$userName/$timeStamp/contents.txt
unzip -Z1 $1$2 >> $rezultsPath$homeworkType/$userName/$timeStamp/contents.txt
echo "Your archive should contain" >> $rezultsPath$homeworkType/$userName/$timeStamp/contents.txt
unzip -Z1 $homeworkCheckersPath$homeworkType-solution.zip >> $rezultsPath$homeworkType/$userName/$timeStamp/contents.txt
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "mkdir $2" &>> debug.txt
scp -i $keyFile -o StrictHostKeyChecking=no -P $port $1$2 student@$machine:$2/$2 &>> debug.txt
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "unzip -o $2/$2 -d $2" &>> debug.txt

#upload checker
scp -i $keyFile -o StrictHostKeyChecking=no -P $port $homeworkCheckersPath$homeworkType.zip student@$machine:$2/$homeworkType.zip &>> debug.txt
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "unzip -o $2/$homeworkType.zip -d $2" &>> debug.txt

#run
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "cd $2; chmod 777 runAll.sh" &>> debug.txt
timeout 300 ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "cd $2; ./runAll.sh" &>> $rezultsPath$homeworkType/$userName/$timeStamp/rezult.txt
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "killall -9 runAll.sh" &>> debug.txt
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "killall -9 mpirun" &>> debug.txt

#cleanup
ssh -i $keyFile -o StrictHostKeyChecking=no -p $port student@$machine "rm -R $2" &>> debug.txt

mv $1$2 $rezultsPath$homeworkType/$userName/$timeStamp/$2
