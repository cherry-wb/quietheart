http://zhidao.baidu.com/question/27937543.html

linux中的/etc/rc.d/init.d 这个目录的主要功能是什么?
在这个目录下的档案都是连结档，均指向到 /etc/rc.d/init.d 这个目录下，而这个 /etc/rc.d/init.d 目录则是以 Linux 的 rpm 安装方法时，设定一些服务的启动目录。举个例子来说，如果你要重新启动 sendmail 的话，而且你的 sendmail 是以 rpm 来安装的，那么下达 /etc/rc.d/init.d/sendmail restart 就可以直接启动 sendmail 啰！所以你即可知道 /etc/rc.d/init.d 里面档案的主要功能！因此，当你的 run-level 内的 scripts 要启动哪写服务呢，呵呵！就将档案连结到该 init.d 目录下的档案并加以启动即可啰！也就是说『当你以 文字模式 ( run-level=3 ) 启动 Linux 时，你的系统在经过 BIOS、 MBR、 Kernel、 init、/etc/rc.d/rc.sysinit 之后，就会进入 /etc/rc.d/rc3.d 来启动一些服务』啰！不过，需要注意的是，在 rc3.d (或其它目录下 rc0.d ~ rc6.d )目录中 S 开头的档案为执行该服务， K 为开头的档案则是杀掉该服务的意思。那么那些数字代表的意义为何？那就是启动的顺序啦！例如S12syslog 会比S90crond 更早被执行呢！那么为什么要有这些顺序呢？这是有原因的！例如您的主机有要启动 WWW 好了，那么您的网络设定应该要先启动才对吧！所以啰，如果 WWW 先启动，才驱动网络，那么 WWW 自然就一定起不来啦！所以各项服务的启动顺序也是相当重要的！目前 Mandrake 当中，可以使用 chkconfig 来设定开机要启动的服务选项呢！

根本没具体讲它的主要功能...是启动某些服务的么?

最佳答案
这段是说明linux怎样在开机时启动服务的。 


说白一点，这个目录主要是用来控制各种服务的。如你要开启httpd服务，在bash下输入/etc/rc.d/init.d/httpd restart 就可以了。等同于图形界面下的ntsysv命令。
