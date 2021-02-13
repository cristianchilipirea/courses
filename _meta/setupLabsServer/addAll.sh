#!/bin/bash

labsFolder=labs-anul3
studentListCsv=anul3.csv

while read row; do
  group=$(echo "$row" | cut -f3 -d",");
  name=$(echo "$row" | cut -f4 -d",");
  echo $group $name;
  #userdel $name
  ./newUser.sh $name $group
  #rm -R /home/$group/$name/labs
  mkdir /home/$group/$name/labs
  cp -n -R $labsFolder /home/$group/$name/labs
  chown -R $name:$name /home/$group/$name
  chmod 555 /home/$group/$name/.ssh
  chmod 444 /home/$group/$name/.ssh/authorized_keys
done < $studentListCsv