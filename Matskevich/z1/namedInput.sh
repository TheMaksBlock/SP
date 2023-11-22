mkfifo pipe

echo -e "$(uname -a) \n$(date) \n$(cal)"  > pipe
