git config --global user.email "BaekkieSong@github.com"
git config --global user.name "BaekkieSong"
cp ./settings/bashrc ~/
cp ./settings/vimrc ~/
./settings/install_packages.sh
./settings/build_googletest.sh
./settings/build_fp_test_base.sh
cd ~/
ctags -R
source ~/.bashrc
