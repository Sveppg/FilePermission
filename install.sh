#!/bin/sh
echo "fetching the git repo..."
git clone https://github.com/Sveppg/FilePermisson.git

cd /FilePermissions-git/build
make

echo "creating alias..."
alias ChangePerm="./executable"
chmod +x executable
echo "Your command will be ChangePerm"
echo "Add a File as a Programm parameter"
ChangePerm
