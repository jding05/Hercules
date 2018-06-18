# since we don't have any access on my current computer, so I use this in virtual machine


# if you want to execute the code in the future or certain time, you use 'at' command


# if your virtual machine doesn't have at command installed, install use:
# apt-get install at


# if you want to use pipe at, we need stdout to printout the command echo
# also, we need input into txt file in order to show, it won't show stdout w/ at

echo "echo 'You are right!' > boar.txt" | at 08:42 AM December 21 2018

echo "your task will be executed at 08:42 AM December 21 2018"
