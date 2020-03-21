git config --global user.email "BaekkieSong@github.com"
git config --global user.name "BaekkieSong"
cp .bashrc ~/
cp .vimrc ~/
./install_packages.sh
./build_googletest.sh
./build_fp_test_base.sh
cd
ctags -R
source ~/.bashrc
