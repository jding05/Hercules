# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cattle.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/28 19:52:32 by sding             #+#    #+#              #
#    Updated: 2018/04/28 23:38:35 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import requests
import sys
import time

# Set up parameters
url = input("Enter URL                 :")
max_hits = eval(input("Input Numbers of hit      :"))
clients = eval(input("Input Numbers of Client   :"))
data = {
    'transactions': clients * max_hits,
    'success': 0,
    'failure': 0,
    'time': 0,
    'size': 0
}

# Check for valid url
try:
    print('\nSTARTING SERVER BENCHMARKING')
    time.sleep(1.5)
except:
    print('Invalid URL, stopping')
    sys.exit(1)

# Start benchmark
for i in range(0 , clients):
    for hits in range (0, max_hits):
        r = requests.get(url)

        # Status of request
        status = r.status_code
        if status == 200:
            data['success'] += 1
        else:
            data['failure'] += 1

        # Time of request
        time = str(r.elapsed)[5:-4]
        data['time'] += float(time)

        # Size of data transfered
        size = len(r.content)
        data['size'] += size

        # Method
        method = str(r.request)[18:-2]

        # Print request data
        print('\033[1;30m', 'HTTP/1.1 ', status, '\t', time, 'secs\t', size, 'bytes ==>', method, '', url)




print('\033[0;34m', '\nNumber of Transactions:\t\t', data['transactions'], 'hits')
print('\033[0;34m', 'Availability:\t\t\t', (data['success'] * 100) / data['transactions'], '%')
print('\033[0;34m', 'Elapsed time:\t\t\t', data['time'], 'secs')
print('\033[0;34m', 'Average response time:\t\t', data['time'] / data['transactions'], 'secs')
print('\033[0;34m', 'Data transfered:\t\t', data['size'] / 1024, 'KB')
print('\033[0;34m', 'Successful transactions:\t', data['success'])
print('\033[0;34m', 'Failed transactions:\t\t', data['failure'])
