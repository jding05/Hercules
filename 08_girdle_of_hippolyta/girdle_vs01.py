# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    girdle_vs01.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:20 by sding             #+#    #+#              #
#    Updated: 2018/04/20 18:10:22 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import smtplib
import getpass
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText


fromaddr = input("What's your email address? ")

addrpassword = getpass.getpass('Enter your password: ')
toaddr = input("The email address you want to send. ")

msg = MIMEMultipart()

msg['From'] = fromaddr
msg['To'] = toaddr
msg['Subject'] = input("Write your Subject: ")

body = input("Text you want to send: ")

msg.attach(MIMEText(body, 'plain'))


server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(fromaddr, addrpassword)
text = msg.as_string()
server.sendmail(fromaddr, toaddr, text)
server.quit()
