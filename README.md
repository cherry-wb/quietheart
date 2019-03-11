quietheart
==========

find the things you want.

本文档随时间会更新。

***项目介绍***

存放各类代码和文档相关的信息。
文档为公开内容，包含可能各类信息，可供查阅。
文档管理将存放至这里，利用git进行版本控制。
为保证安全性，该文档在各类云端作为备份和分布开发。



***项目管理***

本项目通过git进行版本控制，目前使用git hub提供的git服务进行管理，oschina做为备份托管防止被墙。
使用方式：
1、通过云服务：
通过git clone在类似百度云、微云中保存该项目库的分布开发版本。
添加时，对其工作内容进行添加，保险起见：先git pull；再添加；再git add/commit/push；
通过上述步骤，可保证各个云端的分布库，每次更新都可在本项目最新版本上进行，并且每次的更新也能同步至git hub，以便其它云端能获取最新版本。

2、通过git hub
如果不通过云端添加内容，也可通过git hub将该项目内容以正常git开发的工作方式更新。

3、其它
若git hub服务由于意外终止，这里的内容在其它云端也有备份，可以更改其.git/config信息，迁移至其他git服务上继续本项目的延续。



***目录结构***

test:包含各种内容，用于临时和测试。

codes:包含各类代码，用于学习和参考等，详见codes/readme。

tmpdoc:包含记录的各类文档，此处文档将被整理至合适的位置。

misc:不知如何分类的内容，如我的系统上的vim配置等。以后会归类，也可能不归类。


当前托管状态git config：


[core]

    repositoryformatversion = 0 
    filemode = true
    bare = false
    logallrefupdates = true
    
[remote "origin"]

    fetch = +refs/heads/*:refs/remotes/origin/*
    url = https://github.com/vaqeteart/quietheart.git #config for github
    #url = https://git.oschina.net/quietheart/quietheart.git #config for oschina
    
[branch "master"]

    remote = origin
    merge = refs/heads/master

bla bla bla...
bbb
