# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    apple.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <sding@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 16:02:19 by sding             #+#    #+#              #
#    Updated: 2018/06/17 16:02:23 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Create Authentication SSH-Kegen Keys
ssh-keygen -t rsa

# Copy key to remote host
ssh-copy-id sding@localhost -p 4200

# Now you can access the remote host with "ssh -p 4200 sding@localhost"
