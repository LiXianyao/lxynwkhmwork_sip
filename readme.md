工程是MFCApp...那个，hellowworld是pjsua_simple的demo代码（只是hellowworld.cpp），还有从pjsua贴过来的，用来参考的代码（没有引入项目，但是在文件夹里）
重点看这个/hellowworld/pjsua_app.c
第1289行static pj_status_t app_init()是它的初始化及各种绑定函数
里面还有很多回调、还有各种可能是媒体绑定之类的东西，需要实验。或许你可以试下开个分支整个贴进去？？？？

