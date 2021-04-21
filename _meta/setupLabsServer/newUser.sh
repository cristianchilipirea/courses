#!/bin/bash

echo $1 $2
useradd -m -s /bin/bash -d /home/$2/$1 $1
ssh-keygen -f keys/$1 -N ""
#sudo apt-get install putty
puttygen keys/$1 -q -o keys/$1.ppk
mkdir /home/$2/$1/.ssh
mv keys/$1.pub /home/$2/$1/.ssh/authorized_keys
chmod 750 /home/$2/$1
#cp -R labs /home/$2/$1/labs
#chown -R $1:$1 /home/$2/$1