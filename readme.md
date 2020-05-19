1.mac下 安装 zsh

brew install zsh

sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"


查看当前已安装shells：
cat /etc/shells

更改mac默认shell为zsh:
chsh -s /usr/local/bin/zsh

更改zsh配置文件：
vim ~/.zshrc

更改完配置记得运行：
source ~/.zshrc

还原默认shell：
chsh -s /bin/bash


