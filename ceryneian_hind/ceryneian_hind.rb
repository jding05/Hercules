# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ceryneian_hind.rb                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/09 18:52:01 by sding             #+#    #+#              #
#    Updated: 2018/03/09 18:52:03 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

require "oauth2"
require "colorize"

UID = "2c74bf6ef4116f96f8e0b46a6a1ca15b4b7487e1b526a14b5f1b4acc8421e049"
SECRET = "9641a5a15fdbca6d10100538007ce48c16e67dc81d269b92615b11280ebaf3d9"

# Create the client with your credentials
$client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")

# Get an access token
$token = $client.client_credentials.get_token

def user_location(login)
	begin
		response = $token.get("/v2/users/#{login}/locations")
        until response.status == 200
			puts ("No server 😱")
			sleep(4.2) 
		end 
		if !response.parsed[0]["end_at"]
			puts (login.ljust(12) + ": " + response.parsed[0]["host"] + 
					" in zone " + response.parsed[0]["host"].slice!(3))
		else
			puts (login.ljust(12) + ": currently not in the lab, LAZY🙄 🙄 🙄").light_blue
            puts ("\t\t(last login -> " + response.parsed[0]["host"] + ")").light_blue
            puts ("\t\t(logout at: " + response.parsed[0]["end_at"].slice!(0..18) + ")").light_blue
		end
	rescue
		puts (login.ljust(12) + ": username doesn't exist!").red
	end
end

# line = "\n" ? next : login = line.strip
#   means if line = "\n" 
#               next
#         else
#               login = line.strip
#         end

# File.file?() -> check whether or not a file exist = File.exist?()
# each and each_line is the same This is a deprecated alias for each_codepoint.
# strip -> return a copy of str w/ leading and trailing whitespace removed
if ARGV[0]
	if File.exist?(ARGV[0]) and File.extname(ARGV[0]) == ".txt"
		file = File.open(ARGV[0], "r").each do |line|
			line == "\n" ? next : login = line.strip
			user_location(login)
		end
		file.close
	else
		puts "wrong file type! should use '.txt'".yellow
	end
else
	puts "you didn't put the file.\nput your file right after ceryneian_hind.rb".yellow
end
