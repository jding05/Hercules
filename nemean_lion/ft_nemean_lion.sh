#!/bin/bash

apt-get -y install openssh-server
sed -i 's/^.*Port 22/Port 4200/' /etc/ssh/sshd_config
/etc/init.d/ssh restart
